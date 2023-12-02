cmake_minimum_required(VERSION 2.8...3.20)
project(RTSPathing)

add_subdirectory(RTSPathingLib)
add_subdirectory(Test)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT RTSPathingLibTests)