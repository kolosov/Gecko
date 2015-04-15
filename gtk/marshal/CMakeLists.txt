find_package(GTK2 2.6 REQUIRED gtk)

find_library(gecko_libs xpcomglue PATHS ${GECKO_SDK_PATH}/lib)

include_directories(${GTK2_INCLUDE_DIRS})
include_directories ("${PROJECT_SOURCE_DIR}/common")
include_directories ("${PROJECT_SOURCE_DIR}/gtk/common")
include_directories ("${PROJECT_SOURCE_DIR}/gtk/include")
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${GECKO_SDK_PATH}/include ${GECKO_SDK_PATH}/include/nspr)

set(gtkhelperlib2_src moz-web-view-marshal.c )
if (CMAKE_SYSTEM_NAME MATCHES Linux)
 add_definitions(-fshort-wchar -fno-rtti)
endif()

add_library(gtkhelperlib2 STATIC ${gtkhelperlib2_src})

