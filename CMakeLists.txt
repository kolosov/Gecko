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

#set mozilla version
message( "GECKO_SDK_PATH is ${GECKO_SDK_PATH}")
file(READ ${GECKO_SDK_PATH}/include/mozilla-config.h MCONFILE)
string(REGEX MATCH "#define[ ]+MOZILLA_VERSION[ ]\"+[0-9.]+\"" MOZVERSTR ${MCONFILE})
string(REGEX REPLACE "#define[ ]MOZILLA_VERSION[ ]\"([0-9]+).[0-9.]+\"" "\\1" MOZILLA_VERSION_1 ${MOZVERSTR})
#check Qt and Gtk support
string(REGEX MATCH "#define[ ]+MOZ_WIDGET_QT" MOZ_QT ${MCONFILE})
string(REGEX MATCH "#define[ ]+MOZ_WIDGET_GTK2" MOZ_GTK2 ${MCONFILE})
string(REGEX MATCH "#define[ ]+MOZ_WINSDK" MOZ_WINSDK ${MCONFILE})

message("MOZVERSTR is ${MOZVERSTR}")

#TODO rename MOZILLA_VERSION_* to another name
message("MOZILLA_VERSION_1 is ${MOZILLA_VERSION_1}")

if(CMAKE_SYSTEM_NAME MATCHES Windows)
  string(REGEX REPLACE "/" "\\\\\\\\" GECKO_SDK_PATH_CONFIG ${GECKO_SDK_PATH})
 else()
  set(GECKO_SDK_PATH_CONFIG ${GECKO_SDK_PATH})
endif()
message("GECKO_SDK_PATH_CONFIG is ${GECKO_SDK_PATH_CONFIG}")
#config header
configure_file (
  "${PROJECT_SOURCE_DIR}/geckoembed_config.h.in"
  "${PROJECT_BINARY_DIR}/geckoembed_config.h"
  )

include_directories("${PROJECT_BINARY_DIR}")
include_directories("/usr/include/nspr")

if (CMAKE_SYSTEM_NAME MATCHES Linux)
 message("Linux build")
 add_definitions(-g -std=c++11  -DXPCOM_GLUE_USE_NSPR -DXPCOM_GLUE=1)
endif()

if(CMAKE_SYSTEM_NAME MATCHES Windows)
 message("Windows build")
 add_definitions( -DXPCOM_GLUE_USE_NSPR -DXPCOM_GLUE=1 -DXP_WIN=1 -D_ITERATOR_DEBUG_LEVEL=0)
endif()

if (CMAKE_SYSTEM_NAME MATCHES Darwin)
 message("Darwin build")
 add_definitions(-g -std=c++11  -DXPCOM_GLUE_USE_NSPR -DXPCOM_GLUE=1)
endif()

add_subdirectory (common)
add_subdirectory (listener)
add_subdirectory (gtkskel)

add_subdirectory (gtk/common)
if (CMAKE_SYSTEM_NAME MATCHES Linux)
 add_subdirectory (gtk/x11)
endif()
if (CMAKE_SYSTEM_NAME MATCHES Darwin)
 add_subdirectory (gtk/x11)
endif()
if (CMAKE_SYSTEM_NAME MATCHES Windows)
 add_subdirectory (gtk/win32)
endif()
add_subdirectory (gtk/tests)
