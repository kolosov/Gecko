find_library(gecko_libs xpcomglue PATHS ${GECKO_SDK_PATH}/lib)

include_directories ("${PROJECT_SOURCE_DIR}/common")
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${GECKO_SDK_PATH}/include ${GECKO_SDK_PATH}/include/nspr)

set(listener_src listener.cpp)

if(CMAKE_SYSTEM_NAME MATCHES Linux)
  add_definitions( -std=c++11 -fshort-wchar -fno-rtti)
endif()

if(CMAKE_SYSTEM_NAME MATCHES Darwin)
  add_definitions( -std=c++11)
endif()

add_library(listener STATIC ${listener_src})

