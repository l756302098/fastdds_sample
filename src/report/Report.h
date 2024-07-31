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
 * @file Report.h
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifndef _FAST_DDS_GENERATED_MIND_INTERFACES_MSG_REPORT_H_
#define _FAST_DDS_GENERATED_MIND_INTERFACES_MSG_REPORT_H_


#include <fastrtps/utils/fixed_size_string.hpp>

#include <stdint.h>
#include <array>
#include <string>
#include <vector>
#include <map>
#include <bitset>

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#define eProsima_user_DllExport __declspec( dllexport )
#else
#define eProsima_user_DllExport
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define eProsima_user_DllExport
#endif  // _WIN32

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#if defined(REPORT_SOURCE)
#define REPORT_DllAPI __declspec( dllexport )
#else
#define REPORT_DllAPI __declspec( dllimport )
#endif // REPORT_SOURCE
#else
#define REPORT_DllAPI
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define REPORT_DllAPI
#endif // _WIN32

namespace eprosima {
namespace fastcdr {
class Cdr;
} // namespace fastcdr
} // namespace eprosima


namespace mind_interfaces {
    namespace msg {
        /*!
         * @brief This class represents the structure Report defined by the user in the IDL file.
         * @ingroup Report
         */
        class Report
        {
        public:

            /*!
             * @brief Default constructor.
             */
            eProsima_user_DllExport Report();

            /*!
             * @brief Default destructor.
             */
            eProsima_user_DllExport ~Report();

            /*!
             * @brief Copy constructor.
             * @param x Reference to the object mind_interfaces::msg::Report that will be copied.
             */
            eProsima_user_DllExport Report(
                    const Report& x);

            /*!
             * @brief Move constructor.
             * @param x Reference to the object mind_interfaces::msg::Report that will be copied.
             */
            eProsima_user_DllExport Report(
                    Report&& x) noexcept;

            /*!
             * @brief Copy assignment.
             * @param x Reference to the object mind_interfaces::msg::Report that will be copied.
             */
            eProsima_user_DllExport Report& operator =(
                    const Report& x);

            /*!
             * @brief Move assignment.
             * @param x Reference to the object mind_interfaces::msg::Report that will be copied.
             */
            eProsima_user_DllExport Report& operator =(
                    Report&& x) noexcept;

            /*!
             * @brief Comparison operator.
             * @param x mind_interfaces::msg::Report object to compare.
             */
            eProsima_user_DllExport bool operator ==(
                    const Report& x) const;

            /*!
             * @brief Comparison operator.
             * @param x mind_interfaces::msg::Report object to compare.
             */
            eProsima_user_DllExport bool operator !=(
                    const Report& x) const;

            /*!
             * @brief This function copies the value in member topic
             * @param _topic New value to be copied in member topic
             */
            eProsima_user_DllExport void topic(
                    const std::string& _topic);

            /*!
             * @brief This function moves the value in member topic
             * @param _topic New value to be moved in member topic
             */
            eProsima_user_DllExport void topic(
                    std::string&& _topic);

            /*!
             * @brief This function returns a constant reference to member topic
             * @return Constant reference to member topic
             */
            eProsima_user_DllExport const std::string& topic() const;

            /*!
             * @brief This function returns a reference to member topic
             * @return Reference to member topic
             */
            eProsima_user_DllExport std::string& topic();
            /*!
             * @brief This function copies the value in member data
             * @param _data New value to be copied in member data
             */
            eProsima_user_DllExport void data(
                    const eprosima::fastrtps::fixed_string<409600>& _data);

            /*!
             * @brief This function moves the value in member data
             * @param _data New value to be moved in member data
             */
            eProsima_user_DllExport void data(
                    eprosima::fastrtps::fixed_string<409600>&& _data);

            /*!
             * @brief This function returns a constant reference to member data
             * @return Constant reference to member data
             */
            eProsima_user_DllExport const eprosima::fastrtps::fixed_string<409600>& data() const;

            /*!
             * @brief This function returns a reference to member data
             * @return Reference to member data
             */
            eProsima_user_DllExport eprosima::fastrtps::fixed_string<409600>& data();

            /*!
            * @brief This function returns the maximum serialized size of an object
            * depending on the buffer alignment.
            * @param current_alignment Buffer alignment.
            * @return Maximum serialized size.
            */
            eProsima_user_DllExport static size_t getMaxCdrSerializedSize(
                    size_t current_alignment = 0);

            /*!
             * @brief This function returns the serialized size of a data depending on the buffer alignment.
             * @param data Data which is calculated its serialized size.
             * @param current_alignment Buffer alignment.
             * @return Serialized size.
             */
            eProsima_user_DllExport static size_t getCdrSerializedSize(
                    const mind_interfaces::msg::Report& data,
                    size_t current_alignment = 0);


            /*!
             * @brief This function serializes an object using CDR serialization.
             * @param cdr CDR serialization object.
             */
            eProsima_user_DllExport void serialize(
                    eprosima::fastcdr::Cdr& cdr) const;

            /*!
             * @brief This function deserializes an object using CDR serialization.
             * @param cdr CDR serialization object.
             */
            eProsima_user_DllExport void deserialize(
                    eprosima::fastcdr::Cdr& cdr);



            /*!
             * @brief This function returns the maximum serialized size of the Key of an object
             * depending on the buffer alignment.
             * @param current_alignment Buffer alignment.
             * @return Maximum serialized size.
             */
            eProsima_user_DllExport static size_t getKeyMaxCdrSerializedSize(
                    size_t current_alignment = 0);

            /*!
             * @brief This function tells you if the Key has been defined for this type
             */
            eProsima_user_DllExport static bool isKeyDefined();

            /*!
             * @brief This function serializes the key members of an object using CDR serialization.
             * @param cdr CDR serialization object.
             */
            eProsima_user_DllExport void serializeKey(
                    eprosima::fastcdr::Cdr& cdr) const;

        private:

            std::string m_topic;
            eprosima::fastrtps::fixed_string<409600> m_data;

        };
    } // namespace msg
} // namespace mind_interfaces

#endif // _FAST_DDS_GENERATED_MIND_INTERFACES_MSG_REPORT_H_

