find_library(gecko_libs xpcomglue PATHS ${GECKO_SDK_PATH}/lib)

include_directories ("${PROJECT_SOURCE_DIR}/common")
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${GECKO_SDK_PATH}/include ${GECKO_SDK_PATH}/include/nspr)

set(srvlistener_src srvlistener.cpp)

add_definitions(-fshort-wchar -fno-rtti)
add_library(srvlistener STATIC ${srvlistener_src})

