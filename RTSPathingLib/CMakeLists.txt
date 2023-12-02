cmake_minimum_required(VERSION 2.8...3.20)
project(RTSPathingLib)

find_package(glm REQUIRED)

set(Source_Files
    "Source/RTSPathingLib/HelloWorld.h"
    "Source/RTSPathingLib/HelloWorld.cpp"
)
source_group("Source" FILES ${Source_Files})

set(ALL_FILES
    ${Source_Files}
)

############################################################################
############################################################################
############################################################################

add_library(RTSPathingLib ${ALL_FILES})
set_property(TARGET RTSPathingLib PROPERTY CXX_STANDARD 20)

target_include_directories(RTSPathingLib PUBLIC 
./Source/
)