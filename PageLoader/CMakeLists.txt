project(PageLoader)

add_library(pageLoader STATIC Page.cpp PageLoader.cpp)
target_link_libraries(pageLoader -lcurl)
