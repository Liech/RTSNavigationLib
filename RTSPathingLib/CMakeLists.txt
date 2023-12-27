cmake_minimum_required(VERSION 2.8...3.20)
project(RTSPathingLib)

find_package(glm REQUIRED)
find_package(Boost)

set(Source_Files
    "Source/RTSPathingLib/Body.h"
    "Source/RTSPathingLib/Body.cpp"
    "Source/RTSPathingLib/BodyUtil.h"
    "Source/RTSPathingLib/BodyUtil.cpp"
    "Source/RTSPathingLib/Usher.h"
    "Source/RTSPathingLib/Usher.cpp"
)
source_group("Source" FILES ${Source_Files})

set(HexagonGrid_Files
    "Source/RTSPathingLib/Util/HexagonGrid/HexGridUtils.h"
    "Source/RTSPathingLib/Util/HexagonGrid/HexGridUtils.cpp"
    "Source/RTSPathingLib/Util/HexagonGrid/Hex2DVoxelizer.h"
    "Source/RTSPathingLib/Util/HexagonGrid/Hex2DVoxelizer.cpp"
    "Source/RTSPathingLib/Util/HexagonGrid/TopFlatHexGrid.h"
    "Source/RTSPathingLib/Util/HexagonGrid/TopFlatHexGrid.cpp"
    "Source/RTSPathingLib/Util/HexagonGrid/HexGridSvg.h"
    "Source/RTSPathingLib/Util/HexagonGrid/HexGridSvg.cpp"
)
source_group("Source/Util/HexagonGrid" FILES ${HexagonGrid_Files})

set(RectangleGrid_Files
    "Source/RTSPathingLib/Util/RectangleGrid/RectangleGrid.h"
    "Source/RTSPathingLib/Util/RectangleGrid/RectangleGrid.cpp"
    "Source/RTSPathingLib/Util/RectangleGrid/RectangleGridVoxelizer.h"
    "Source/RTSPathingLib/Util/RectangleGrid/RectangleGridVoxelizer.cpp"
    "Source/RTSPathingLib/Util/RectangleGrid/RectangleGridSvg.h"
    "Source/RTSPathingLib/Util/RectangleGrid/RectangleGridSvg.cpp"
)
source_group("Source/Util/RectangleGrid" FILES ${RectangleGrid_Files})

set(Util_Files
    "Source/RTSPathingLib/Util/glmBoostGeometry.h"
    "Source/RTSPathingLib/Util/glmBoostGeometry.cpp"
    "Source/RTSPathingLib/Util/RTree2D.h"
    "Source/RTSPathingLib/Util/RTree2D.cpp"
    "Source/RTSPathingLib/Util/svg.h"
    "Source/RTSPathingLib/Util/svg.cpp"	
    "Source/RTSPathingLib/Util/String2File.h"
    "Source/RTSPathingLib/Util/String2File.cpp"	
    "Source/RTSPathingLib/Util/Geometry2D.h"
    "Source/RTSPathingLib/Util/Geometry2D.cpp"	
)
source_group("Source/Util" FILES ${Util_Files})

set(FormationShape_Files
    "Source/RTSPathingLib/Formation/FormationShape/ArcFormationShape.h"
    "Source/RTSPathingLib/Formation/FormationShape/ArcFormationShape.cpp"
    "Source/RTSPathingLib/Formation/FormationShape/FormationShape.h"
    "Source/RTSPathingLib/Formation/FormationShape/FormationShape.cpp"
    "Source/RTSPathingLib/Formation/FormationShape/RectangleFormationShape.h"
    "Source/RTSPathingLib/Formation/FormationShape/RectangleFormationShape.cpp"	
    "Source/RTSPathingLib/Formation/FormationShape/TriangleFormationShape.h"
    "Source/RTSPathingLib/Formation/FormationShape/TriangleFormationShape.cpp"	
    "Source/RTSPathingLib/Formation/FormationShape/FormationShapeFactory.h"
    "Source/RTSPathingLib/Formation/FormationShape/FormationShapeFactory.cpp"	
    "Source/RTSPathingLib/Formation/FormationShape/ScalingBehavior.h"	
    "Source/RTSPathingLib/Formation/FormationShape/RectangleInterfacePoint.h"	
    "Source/RTSPathingLib/Formation/FormationShape/TriangleInterfacePoint.h"	
)
source_group("Source/Formation/FormationShape" FILES ${FormationShape_Files})

set(Formation_Files
    "Source/RTSPathingLib/Formation/Formation.h"	
    "Source/RTSPathingLib/Formation/Formation.cpp"	
    "Source/RTSPathingLib/Formation/FormationCalculator.h"	
    "Source/RTSPathingLib/Formation/FormationCalculator.cpp"	
    "Source/RTSPathingLib/Formation/UnitPlacement.h"	
    "Source/RTSPathingLib/Formation/UnitPlacement.cpp"	
)
source_group("Source/Formation" FILES ${Formation_Files})

set(ALL_FILES
    ${Source_Files}
    ${Util_Files}
    ${HexagonGrid_Files}
    ${RectangleGrid_Files}
    ${FormationShape_Files}
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