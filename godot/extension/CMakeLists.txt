cmake_minimum_required(VERSION 3.19)
project(RTSNavigationGodotExtension)

set(Source_Files
    "register_types.h"
    "register_types.cpp"
    "RTSNavigation.h"
    "RTSNavigation.cpp"
    "RTSFormation.h"
    "RTSFormation.cpp"
    "RTSFormationShape.h"
    "RTSFormationShape.cpp"
    "RTSShapeRect.h"
    "RTSShapeRect.cpp"
    "RTSShapeArc.h"
    "RTSShapeArc.cpp"
    "RTSShapeTri.h"
    "RTSShapeTri.cpp"
    "RTSBody.h"
    "RTSBody.cpp"
)
source_group("Source" FILES ${Source_Files})

set(ALL_FILES
    ${Source_Files}
)

add_library(RTSNavigationGodotExtension SHARED ${ALL_FILES})
set_property(TARGET RTSNavigationGodotExtension PROPERTY DBG_POSTFIX d)
set_property(TARGET RTSNavigationGodotExtension PROPERTY CXX_STANDARD 20)


target_include_directories(RTSNavigationGodotExtension PRIVATE 
./../godot-cpp/include
./../../RTSNavigationLib/Source
)

target_link_libraries(RTSNavigationGodotExtension PUBLIC 
godot::cpp 
RTSNavigationLib)

add_custom_command(TARGET RTSNavigationGodotExtension POST_BUILD 
               COMMAND ${CMAKE_COMMAND} -E copy_directory 
               $<TARGET_FILE_DIR:RTSNavigationGodotExtension>              
                ${CMAKE_SOURCE_DIR}/godot/GodotProject/bin)