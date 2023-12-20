cmake_minimum_required(VERSION 2.8...3.20)
project(RTSPathingLib)

find_package(glm REQUIRED)
find_package(Boost)

set(Source_Files
    "Source/RTSPathingLib/Body.h"
    "Source/RTSPathingLib/Body.cpp"
    "Source/RTSPathingLib/RectangleFormatter.h"
    "Source/RTSPathingLib/RectangleFormatter.cpp"
    "Source/RTSPathingLib/BodyUtil.h"
    "Source/RTSPathingLib/BodyUtil.cpp"
    "Source/RTSPathingLib/Usher.h"
    "Source/RTSPathingLib/Usher.cpp"
)
source_group("Source" FILES ${Source_Files})

set(Hexagon_Files
    "Source/RTSPathingLib/Hexagon/HexGridUtils.h"
    "Source/RTSPathingLib/Hexagon/HexGridUtils.cpp"
    "Source/RTSPathingLib/Hexagon/Hex2DVoxelizer.h"
    "Source/RTSPathingLib/Hexagon/Hex2DVoxelizer.cpp"
    "Source/RTSPathingLib/Hexagon/TopFlatHexGrid.h"
    "Source/RTSPathingLib/Hexagon/TopFlatHexGrid.cpp"
    "Source/RTSPathingLib/Hexagon/HexGridSvg.h"
    "Source/RTSPathingLib/Hexagon/HexGridSvg.cpp"
)
source_group("Source/Hexagon" FILES ${Hexagon_Files})

set(Util_Files
    "Source/RTSPathingLib/Util/glmBoostGeometry.h"
    "Source/RTSPathingLib/Util/glmBoostGeometry.cpp"
    "Source/RTSPathingLib/Util/RTree2D.h"
    "Source/RTSPathingLib/Util/RTree2D.cpp"
    "Source/RTSPathingLib/Util/svg.h"
    "Source/RTSPathingLib/Util/svg.cpp"	
    "Source/RTSPathingLib/Util/String2File.h"
    "Source/RTSPathingLib/Util/String2File.cpp"	
)
source_group("Source/Util" FILES ${Util_Files})

set(Formation_Files
    "Source/RTSPathingLib/Formation/ArcFormationShape.h"
    "Source/RTSPathingLib/Formation/ArcFormationShape.cpp"
    "Source/RTSPathingLib/Formation/FormationShape.h"
    "Source/RTSPathingLib/Formation/FormationShape.cpp"
    "Source/RTSPathingLib/Formation/RectangleFormationShape.h"
    "Source/RTSPathingLib/Formation/RectangleFormationShape.cpp"	
    "Source/RTSPathingLib/Formation/TriangleFormationShape.h"
    "Source/RTSPathingLib/Formation/TriangleFormationShape.cpp"	
    "Source/RTSPathingLib/Formation/FormationShapeFactory.h"
    "Source/RTSPathingLib/Formation/FormationShapeFactory.cpp"	
)
source_group("Source/Formation" FILES ${Formation_Files})

set(ALL_FILES
    ${Source_Files}
    ${Util_Files}
    ${Hexagon_Files}
    ${Formation_Files}
)

############################################################################
############################################################################
############################################################################

add_library(RTSPathingLib ${ALL_FILES})
set_property(TARGET RTSPathingLib PROPERTY CXX_STANDARD 20)

target_link_libraries(RTSPathingLib PUBLIC 
glm::glm
${Boost_LIBRARIES}
)

target_include_directories(RTSPathingLib PUBLIC 
./Source/
)
target_include_directories(RTSPathingLib PRIVATE 
./Source/RTSPathingLib/
)