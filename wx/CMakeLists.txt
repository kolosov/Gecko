find_library(gecko_libs xpcomglue PATHS ${GECKO_SDK_PATH}/sdk/lib)
find_library(xulrunner_mozalloc mozalloc PATHS ${GECKO_SDK_PATH}/sdk/lib)
find_library(gecko_libs_mozglue mozglue PATHS ${GECKO_SDK_PATH}/sdk/lib)

if(CMAKE_SYSTEM_NAME MATCHES Linux)
  find_library(gecko_libs_memory memory PATHS ${GECKO_SDK_PATH}/sdk/lib)
endif()

#if(CMAKE_SYSTEM_NAME MATCHES Windows)
#endif()

find_package(wxWidgets REQUIRED base core aui)
include(${wxWidgets_USE_FILE})

include_directories ("${PROJECT_SOURCE_DIR}/common")
include_directories ("${PROJECT_SOURCE_DIR}/listener")
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${GECKO_SDK_PATH}/include ${GECKO_SDK_PATH}/include/nspr)

set(wxtestapp_src wxtestapp.cpp)

add_executable(wxtestapp ${wxtestapp_src})

if(CMAKE_SYSTEM_NAME MATCHES Linux)
 add_definitions(-fno-rtti  -std=c++11 )
# target_link_libraries(gtkskel listener geckoembed ${gecko_libs} ${GTK2_LIBRARIES} dl -Wl,--whole-archive ${gecko_libs_mozglue} -Wl,--no-whole-archive  pthread ${xulrunner_mozalloc} )
 target_link_libraries(wxtestapp listener geckoembed ${gecko_libs} ${wxWidgets_LIBRARIES} dl -Wl,--whole-archive ${gecko_libs_mozglue} -Wl,--no-whole-archive ${gecko_libs_memory} pthread ${xulrunner_mozalloc} )
endif()

if(CMAKE_SYSTEM_NAME MATCHES Darwin)
  #add_definitions(-fno-rtti )
  add_definitions( -std=c++11 )
  # target_link_libraries(gtkskel listener geckoembed ${gecko_libs} ${GTK2_LIBRARIES} dl -Wl,--whole-archive ${gecko_libs_mozglue} -Wl,--no-whole-archive  pthread ${xulrunner_mozalloc} )
  # target_link_libraries(testapp webconlib ${gecko_libs} ${wxWidgets_LIBRARIES} dl  pthread )
  target_link_libraries(wxtestapp listener geckoembed ${gecko_libs} ${wxWidgets_LIBRARIES} dl -Wl,--whole-archive ${gecko_libs_mozglue} -Wl,--no-whole-archive ${gecko_libs_memory} pthread ${xulrunner_mozalloc} )
endif()

if(CMAKE_SYSTEM_NAME MATCHES Windows)
 target_link_libraries(gtkskel listener geckoembed ${gecko_libs}  ${gecko_libs_mozglue} ${xulrunner_mozalloc} ${GTK2_LIBRARIES} )
endif()

