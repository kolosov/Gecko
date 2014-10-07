cmake_minimum_required (VERSION 3.0)
project(gecko-embedding)
cmake_policy(SET CMP0011 OLD)

#check for xulrunner dir
if(NOT GECKO_SDK_PATH)
 if(CMAKE_SYSTEM_NAME MATCHES Linux)
  set(GECKO_SDK_PATH "/usr/include/xulrunner-24.0")
 endif()
 if(CMAKE_SYSTEM_NAME MATCHES Windows)
  set(GECKO_SDK_PATH "c:/dev/xulrunner-sdk")
 endif()
endif()

#set mozilla version
message( "GECKO_SDK_PATH is ${GECKO_SDK_PATH}")

include_directories("${PROJECT_BINARY_DIR}")
include_directories("/usr/include/nspr")

if (CMAKE_SYSTEM_NAME MATCHES Linux)
 add_definitions(-g -std=c++11  -DXPCOM_GLUE_USE_NSPR -DXPCOM_GLUE=1)
endif()

if(CMAKE_SYSTEM_NAME MATCHES Windows)
 add_definitions( -DXPCOM_GLUE_USE_NSPR -DXPCOM_GLUE=1 -DXP_WIN=1)
endif()

add_subdirectory (common)

