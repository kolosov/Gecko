if(CMAKE_SYSTEM_NAME MATCHES Linux)
  add_definitions(-fshort-wchar -fno-rtti -std=c++11)
endif()

if(CMAKE_SYSTEM_NAME MATCHES Darwin)
  add_definitions(-std=c++11)
endif()

include_directories(${GECKO_SDK_PATH}/include ${GECKO_SDK_PATH}/include/nspr)

set(geckoembedlib_src ConsoleListener.cpp ContentListener.cpp DOMEventListener.cpp EmbeddingSetup.cpp WebBrowserChrome.cpp embed.cpp nsEmbedWeakReference.cpp)

add_library(geckoembed STATIC ${geckoembedlib_src})
