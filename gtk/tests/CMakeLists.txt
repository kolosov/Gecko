find_library(gecko_libs xpcomglue PATHS ${GECKO_SDK_PATH}/lib)
find_library(xulrunner_mozalloc mozalloc PATHS ${GECKO_SDK_PATH}/lib)
find_library(gecko_libs_mozglue mozglue PATHS ${GECKO_SDK_PATH}/lib)

if(CMAKE_SYSTEM_NAME MATCHES Linux)
  find_library(gecko_libs_memory memory PATHS ${GECKO_SDK_PATH}/lib)
endif()

#if(CMAKE_SYSTEM_NAME MATCHES Windows)
#endif()


find_package(GTK2 2.6 REQUIRED gtk)

include_directories ("${PROJECT_SOURCE_DIR}/common")
#include_directories ("${PROJECT_SOURCE_DIR}/listener")
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories ("${PROJECT_SOURCE_DIR}/gtk/common")
include_directories ("${PROJECT_SOURCE_DIR}/gtk/marshal")
include_directories ("${PROJECT_SOURCE_DIR}/gtk/include")
include_directories(${GECKO_SDK_PATH}/include ${GECKO_SDK_PATH}/include/nspr)
include_directories(${GTK2_INCLUDE_DIRS})

set(gtkmoztest_src test.cpp)

add_executable(gtkmoztest ${gtkmoztest_src})

if(CMAKE_SYSTEM_NAME MATCHES Linux)
 add_definitions(-fno-rtti  -std=c++11)
 target_link_libraries(gtkmoztest gtkembedlib gtkhelperlib1 gtkhelperlib2  geckoembed ${gecko_libs} ${GTK2_LIBRARIES} dl -Wl,--whole-archive ${gecko_libs_mozglue} -Wl,--no-whole-archive ${gecko_libs_memory} pthread ${xulrunner_mozalloc} )
endif()

if(CMAKE_SYSTEM_NAME MATCHES Darwin)
 add_definitions(-fno-rtti  -std=c++11)
 target_link_libraries(gtkmoztest gtkembedlib gtkhelperlib1 gtkhelperlib2 geckoembed ${gecko_libs} ${GTK2_LIBRARIES} dl pthread ${xulrunner_mozalloc} )
endif()

if(CMAKE_SYSTEM_NAME MATCHES Windows)
 target_link_libraries(gtkmoztest gtkembedlib gtkhelperlib1 gtkhelperlib2 geckoembed ${gecko_libs} ${xulrunner_mozalloc} ${GTK2_LIBRARIES} )
endif()

