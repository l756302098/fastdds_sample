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
 * @file Report.cpp
 * This source file contains the definition of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifdef _WIN32
// Remove linker warning LNK4221 on Visual Studio
namespace {
char dummy;
}  // namespace
#endif  // _WIN32

#include "Report.h"
#include <fastcdr/Cdr.h>

#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

#include <utility>

#define mind_interfaces_msg_Report_max_cdr_typesize 409865ULL;
#define mind_interfaces_msg_Report_max_key_cdr_typesize 0ULL;

mind_interfaces::msg::Report::Report()
{
    // string m_topic
    m_topic ="";
    // string m_data
    m_data ="";

}

mind_interfaces::msg::Report::~Report()
{


}

mind_interfaces::msg::Report::Report(
        const Report& x)
{
    m_topic = x.m_topic;
    m_data = x.m_data;
}

mind_interfaces::msg::Report::Report(
        Report&& x) noexcept 
{
    m_topic = std::move(x.m_topic);
    m_data = std::move(x.m_data);
}

mind_interfaces::msg::Report& mind_interfaces::msg::Report::operator =(
        const Report& x)
{

    m_topic = x.m_topic;
    m_data = x.m_data;

    return *this;
}

mind_interfaces::msg::Report& mind_interfaces::msg::Report::operator =(
        Report&& x) noexcept
{

    m_topic = std::move(x.m_topic);
    m_data = std::move(x.m_data);

    return *this;
}

bool mind_interfaces::msg::Report::operator ==(
        const Report& x) const
{

    return (m_topic == x.m_topic && m_data == x.m_data);
}

bool mind_interfaces::msg::Report::operator !=(
        const Report& x) const
{
    return !(*this == x);
}

size_t mind_interfaces::msg::Report::getMaxCdrSerializedSize(
        size_t current_alignment)
{
    static_cast<void>(current_alignment);
    return mind_interfaces_msg_Report_max_cdr_typesize;
}

size_t mind_interfaces::msg::Report::getCdrSerializedSize(
        const mind_interfaces::msg::Report& data,
        size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) + data.topic().size() + 1;

    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) + data.data().size() + 1;


    return current_alignment - initial_alignment;
}

void mind_interfaces::msg::Report::serialize(
        eprosima::fastcdr::Cdr& scdr) const
{

    scdr << m_topic.c_str();
    scdr << m_data.c_str();

}

void mind_interfaces::msg::Report::deserialize(
        eprosima::fastcdr::Cdr& dcdr)
{

    dcdr >> m_topic;
    {
        std::string aux;
        dcdr >> aux;
        m_data = aux.c_str();
    }
}

/*!
 * @brief This function copies the value in member topic
 * @param _topic New value to be copied in member topic
 */
void mind_interfaces::msg::Report::topic(
        const std::string& _topic)
{
    m_topic = _topic;
}

/*!
 * @brief This function moves the value in member topic
 * @param _topic New value to be moved in member topic
 */
void mind_interfaces::msg::Report::topic(
        std::string&& _topic)
{
    m_topic = std::move(_topic);
}

/*!
 * @brief This function returns a constant reference to member topic
 * @return Constant reference to member topic
 */
const std::string& mind_interfaces::msg::Report::topic() const
{
    return m_topic;
}

/*!
 * @brief This function returns a reference to member topic
 * @return Reference to member topic
 */
std::string& mind_interfaces::msg::Report::topic()
{
    return m_topic;
}
/*!
 * @brief This function copies the value in member data
 * @param _data New value to be copied in member data
 */
void mind_interfaces::msg::Report::data(
        const eprosima::fastrtps::fixed_string<409600>& _data)
{
    m_data = _data;
}

/*!
 * @brief This function moves the value in member data
 * @param _data New value to be moved in member data
 */
void mind_interfaces::msg::Report::data(
        eprosima::fastrtps::fixed_string<409600>&& _data)
{
    m_data = std::move(_data);
}

/*!
 * @brief This function returns a constant reference to member data
 * @return Constant reference to member data
 */
const eprosima::fastrtps::fixed_string<409600>& mind_interfaces::msg::Report::data() const
{
    return m_data;
}

/*!
 * @brief This function returns a reference to member data
 * @return Reference to member data
 */
eprosima::fastrtps::fixed_string<409600>& mind_interfaces::msg::Report::data()
{
    return m_data;
}


size_t mind_interfaces::msg::Report::getKeyMaxCdrSerializedSize(
        size_t current_alignment)
{
    static_cast<void>(current_alignment);
    return mind_interfaces_msg_Report_max_key_cdr_typesize;
}

bool mind_interfaces::msg::Report::isKeyDefined()
{
    return false;
}

void mind_interfaces::msg::Report::serializeKey(
        eprosima::fastcdr::Cdr& scdr) const
{
    (void) scdr;
}



