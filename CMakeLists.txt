cmake_minimum_required(VERSION 3.5)

# Set the project name
project (fastdds_samples)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DMY_DEBUG")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g ")
# Find requirements
set(DDS_LIBS ${PROJECT_SOURCE_DIR}/dds/lib/x64)
include(FindUnwind.cmake)

find_package(OpenCV 3.4 REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}/dds/lib/include
    ${PROJECT_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
    ${Unwind_INCLUDE_DIR}
)

message(STATUS "Configuring dds...")
add_library(ddsmsg_lib SHARED
    #msg
    src/report/Report.cxx 
    src/request/Request.cxx 
    src/response/Response.cxx
    #report
    src/report/ReportPublisher.cxx
    src/report/ReportSubscriber.cxx
    src/report/ReportPubSubTypes.cxx
    #request
    src/request/RequestPublisher.cxx
    src/request/RequestPubSubTypes.cxx
    src/request/RequestSubscriber.cxx
    #response
    src/response/ResponsePublisher.cxx
    src/response/ResponsePubSubTypes.cxx
    src/response/ResponseSubscriber.cxx
)
target_link_libraries(ddsmsg_lib
    ${DDS_LIBS}/libfastcdr.so
    ${DDS_LIBS}/libfastrtps.so
)

message(STATUS "Configuring fastdds_samples...")
add_executable(fastdds_samples src/main.cpp
    src/DDSConfig.cpp
    src/wrapper/ClientWrapper.cpp
    src/wrapper/ClientBase.cpp
    src/wrapper/ServiceWrapper.cpp
    src/wrapper/ServiceBase.cpp
    src/wrapper/PublisherWrapper.cpp
    src/wrapper/SubscriberWrapper.cpp
)
target_link_libraries(fastdds_samples 
    pthread
    glog
    ddsmsg_lib
    ${DDS_LIBS}/libfastcdr.so
    ${DDS_LIBS}/libfastrtps.so
    ${OpenCV_LIBS}
    ${Unwind_LIBRARY} 
    unwind-x86_64
)