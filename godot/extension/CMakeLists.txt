cmake_minimum_required(VERSION 3.19)
project(gdextension)

set(Source_Files
    "register_types.h"
    "register_types.cpp"
    "RTSNavigation.h"
    "RTSNavigation.cpp"
)
source_group("Source" FILES ${Source_Files})

set(ALL_FILES
    ${Source_Files}
)

add_library(gdextension SHARED ${ALL_FILES})
set_property(TARGET gdextension PROPERTY CXX_STANDARD 20)


target_include_directories(gdextension PRIVATE 
./../godot-cpp/include
)

target_link_libraries(gdextension PUBLIC godot::cpp)