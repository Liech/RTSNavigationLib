cmake_minimum_required(VERSION 2.8...3.20)
project(RTSNavigation)

option(ENABLE_GODOT "Enable Godot" OFF) #OFF by default


add_subdirectory(RTSNavigationLib)
add_subdirectory(Test)
if(ENABLE_GODOT)
	add_subdirectory(godot/godot-cpp)
	add_subdirectory(godot/extension)
endif()

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT RTSNavigationLibTests)