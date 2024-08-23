// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file RequestPublisher.cpp
 * This file contains the implementation of the publisher functions.
 *
 * This file was generated by the tool fastcdrgen.
 */


#include "RequestPublisher.h"
#include "RequestPubSubTypes.h"

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>

#include <thread>
#include <chrono>

#include "../DDSConfig.h"
#include <fastdds/rtps/attributes/RTPSParticipantAllocationAttributes.hpp>

using namespace eprosima::fastdds::dds;

RequestPublisher::RequestPublisher()
    : participant_(nullptr)
    , publisher_(nullptr)
    , topic_(nullptr)
    , writer_(nullptr)
    , type_(new mind_interfaces::msg::RequestPubSubType())
{
}

RequestPublisher::~RequestPublisher()
{
    if (writer_ != nullptr)
    {
        publisher_->delete_datawriter(writer_);
    }
    if (publisher_ != nullptr)
    {
        participant_->delete_publisher(publisher_);
    }
    if (topic_ != nullptr)
    {
        participant_->delete_topic(topic_);
    }
    DomainParticipantFactory::get_instance()->delete_participant(participant_);
    SLOG(INFO) << __func__;
}

bool RequestPublisher::init(const std::string& name)
{
    /* Initialize data_ here */

    //CREATE THE PARTICIPANT
    DomainParticipantQos pqos;
    pqos.name("Participant_pub");
    pqos.allocation().send_buffers.preallocated_number = 1;
    pqos.allocation().send_buffers.dynamic = false;
    pqos.allocation().locators.max_unicast_locators = 4;
    SLOG(INFO) << "ROS_DOMAIN_ID:" << wk::ROS_DOMAIN_ID;
    participant_ = DomainParticipantFactory::get_instance()->create_participant(wk::ROS_DOMAIN_ID, pqos);
    if (participant_ == nullptr)
    {
        return false;
    }

    //REGISTER THE TYPE
    type_.register_type(participant_);

    //CREATE THE PUBLISHER
    publisher_ = participant_->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);
    if (publisher_ == nullptr)
    {
        return false;
    }

    //CREATE THE TOPIC
    std::string topic = wk::PREFIX+name+wk::REQ_SUFFIX;
    SLOG(INFO) << "topic:" << topic;
    topic_ = participant_->create_topic(
        topic,
        type_.get_type_name(),
        TOPIC_QOS_DEFAULT);
    if (topic_ == nullptr)
    {
        return false;
    }

    // CREATE THE WRITER
    DataWriterQos writer_qos;
    writer_qos.history().kind = KEEP_LAST_HISTORY_QOS;
    writer_qos.history().depth = 1;
    writer_qos.resource_limits().max_samples = 1;
    writer_qos.resource_limits().max_instances = 1;
    writer_qos.resource_limits().max_samples_per_instance = 1;
    writer_qos.resource_limits().allocated_samples = 0;
    // Drop non matching locators
    writer_qos.endpoint().ignore_non_matching_locators = true;
    // The RTPSWriterQos is constructed with history_memory_policy = PREALLOCATED by default
    // Change the history_memory_policy to DYNAMIC_RESERVE
    writer_qos.endpoint().history_memory_policy = eprosima::fastrtps::rtps::DYNAMIC_RESERVE_MEMORY_MODE;
    //writer_qos.reliability().kind = BEST_EFFORT_RELIABILITY_QOS;
    writer_ = publisher_->create_datawriter(topic_, writer_qos, &listener_);
    if (writer_ == nullptr)
    {
        return false;
    }

    std::cout << "mind_interfaces::msg::Request DataWriter created." << std::endl;
    return true;
}

void RequestPublisher::PubListener::on_publication_matched(
        eprosima::fastdds::dds::DataWriter*,
        const eprosima::fastdds::dds::PublicationMatchedStatus& info)
{
    if (info.current_count_change == 1)
    {
        matched = info.total_count;
        std::cout << "DataWriter matched." << std::endl;
    }
    else if (info.current_count_change == -1)
    {
        matched = info.total_count;
        std::cout << "DataWriter unmatched." << std::endl;
    }
    else
    {
        std::cout << info.current_count_change
                  << " is not a valid value for PublicationMatchedStatus current count change" << std::endl;
    }
}

bool RequestPublisher::publish(int64_t index,const std::string& topic,const std::string& payload)
{
    std::cout << "mind_interfaces::msg::Request DataWriter waiting for DataReaders." << std::endl;
    while (listener_.matched == 0)
    {
        std::cout << __func__ << " listener not matched." << std::endl;
        return false;
    }

    /* Initialize your structure here */
    mind_interfaces::msg::Request st;
    st.index(index);
    st.topic(topic);
    st.data(payload);
    return writer_->write(&st);
}
