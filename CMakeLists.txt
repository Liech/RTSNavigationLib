cmake_minimum_required(VERSION 2.8...3.20)
project(RTSNavigation)

add_subdirectory(RTSNavigationLib)
add_subdirectory(Test)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT RTSNavigationLibTests)