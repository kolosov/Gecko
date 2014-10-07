if(CMAKE_SYSTEM_NAME MATCHES Linux)
  add_definitions(-fshort-wchar -fno-rtti)
endif()

include_directories(${GECKO_SDK_PATH}/include ${GECKO_SDK_PATH}/include/nspr)

set(geckoembedlib_src ConsoleListener.cpp ContentListener.cpp DOMEventListener.cpp EmbeddingSetup.cpp WebBrowserChrome.cpp embed.cpp)

add_library(geckoembed STATIC ${geckoembedlib_src})
