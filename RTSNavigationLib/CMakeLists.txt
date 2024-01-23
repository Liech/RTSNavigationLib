cmake_minimum_required(VERSION 2.8...3.20)
project(RTSNavigationLib)

find_package(glm REQUIRED)
find_package(Boost)

set(Source_Files
    "Source/RTSNavigationLib/Body.h"
    "Source/RTSNavigationLib/Body.cpp"
    "Source/RTSNavigationLib/BodyUtil.h"
    "Source/RTSNavigationLib/BodyUtil.cpp"
)
source_group("Source" FILES ${Source_Files})

set(HexagonGrid_Files
    "Source/RTSNavigationLib/Util/HexagonGrid/HexGridUtils.h"
    "Source/RTSNavigationLib/Util/HexagonGrid/HexGridUtils.cpp"
    "Source/RTSNavigationLib/Util/HexagonGrid/Hex2DVoxelizer.h"
    "Source/RTSNavigationLib/Util/HexagonGrid/Hex2DVoxelizer.cpp"
    "Source/RTSNavigationLib/Util/HexagonGrid/TopFlatHexGrid.h"
    "Source/RTSNavigationLib/Util/HexagonGrid/TopFlatHexGrid.cpp"
    "Source/RTSNavigationLib/Util/HexagonGrid/HexGridSvg.h"
    "Source/RTSNavigationLib/Util/HexagonGrid/HexGridSvg.cpp"
)
source_group("Source/Util/HexagonGrid" FILES ${HexagonGrid_Files})

set(RectangleGrid_Files
    "Source/RTSNavigationLib/Util/RectangleGrid/RectangleGrid.h"
    "Source/RTSNavigationLib/Util/RectangleGrid/RectangleGrid.cpp"
    "Source/RTSNavigationLib/Util/RectangleGrid/RectangleGridVoxelizer.h"
    "Source/RTSNavigationLib/Util/RectangleGrid/RectangleGridVoxelizer.cpp"
    "Source/RTSNavigationLib/Util/RectangleGrid/RectangleGridSvg.h"
    "Source/RTSNavigationLib/Util/RectangleGrid/RectangleGridSvg.cpp"
)
source_group("Source/Util/RectangleGrid" FILES ${RectangleGrid_Files})

set(Util_Files
    "Source/RTSNavigationLib/Util/glmBoostGeometry.h"
    "Source/RTSNavigationLib/Util/glmBoostGeometry.cpp"
    "Source/RTSNavigationLib/Util/RTree2D.h"
    "Source/RTSNavigationLib/Util/RTree2D.cpp"
    "Source/RTSNavigationLib/Util/svg.h"
    "Source/RTSNavigationLib/Util/svg.cpp"	
    "Source/RTSNavigationLib/Util/String2File.h"
    "Source/RTSNavigationLib/Util/String2File.cpp"	
    "Source/RTSNavigationLib/Util/Geometry2D.h"
    "Source/RTSNavigationLib/Util/Geometry2D.cpp"	
    "Source/RTSNavigationLib/Util/AssignmentProblemSolver.h"
    "Source/RTSNavigationLib/Util/AssignmentProblemSolver.cpp"	
)
source_group("Source/Util" FILES ${Util_Files})

set(FormationShape_Files
    "Source/RTSNavigationLib/Formation/FormationShape/ArcFormationShape.h"
    "Source/RTSNavigationLib/Formation/FormationShape/ArcFormationShape.cpp"
    "Source/RTSNavigationLib/Formation/FormationShape/FormationShape.h"
    "Source/RTSNavigationLib/Formation/FormationShape/FormationShape.cpp"
    "Source/RTSNavigationLib/Formation/FormationShape/RectangleFormationShape.h"
    "Source/RTSNavigationLib/Formation/FormationShape/RectangleFormationShape.cpp"	
    "Source/RTSNavigationLib/Formation/FormationShape/TriangleFormationShape.h"
    "Source/RTSNavigationLib/Formation/FormationShape/TriangleFormationShape.cpp"	
    "Source/RTSNavigationLib/Formation/FormationShape/FormationShapeFactory.h"
    "Source/RTSNavigationLib/Formation/FormationShape/FormationShapeFactory.cpp"	
    "Source/RTSNavigationLib/Formation/FormationShape/ScalingBehavior.h"	
    "Source/RTSNavigationLib/Formation/FormationShape/ScalingBehavior.cpp"	
    "Source/RTSNavigationLib/Formation/FormationShape/RectangleInterfacePoint.h"	
    "Source/RTSNavigationLib/Formation/FormationShape/TriangleInterfacePoint.h"	
)
source_group("Source/Formation/FormationShape" FILES ${FormationShape_Files})

set(Formation_Files
    "Source/RTSNavigationLib/Formation/Formation.h"	
    "Source/RTSNavigationLib/Formation/Formation.cpp"	
    "Source/RTSNavigationLib/Formation/FormationCalculator.h"	
    "Source/RTSNavigationLib/Formation/FormationCalculator.cpp"	
    "Source/RTSNavigationLib/Formation/UnitPlacement.h"	
    "Source/RTSNavigationLib/Formation/UnitPlacement.cpp"			
    "Source/RTSNavigationLib/Formation/UnitPlacementBehavior.h"	
    "Source/RTSNavigationLib/Formation/UnitPlacementBehavior.cpp"		
)
source_group("Source/Formation" FILES ${Formation_Files})

set(Usher_Files
    "Source/RTSNavigationLib/Usher/Usher.h"	
    "Source/RTSNavigationLib/Usher/Usher.cpp"	
    "Source/RTSNavigationLib/Usher/BoostMinCostFlowExample.h"	
    "Source/RTSNavigationLib/Usher/BoostMinCostFlowExample.cpp"	
)
source_group("Source/Usher" FILES ${Usher_Files})

set(Flocking_Files
    "Source/RTSNavigationLib/Flocking/Flock.h"	
    "Source/RTSNavigationLib/Flocking/Flock.cpp"	
    "Source/RTSNavigationLib/Flocking/Boid.h"	
    "Source/RTSNavigationLib/Flocking/Boid.cpp"	
)
source_group("Source/Flocking" FILES ${Flocking_Files})

set(Pathfinding_Files
    "Source/RTSNavigationLib/Pathfinding/FlowField.h"	
    "Source/RTSNavigationLib/Pathfinding/FlowField.cpp"	
    "Source/RTSNavigationLib/Pathfinding/DijkstraGrid.h"	
    "Source/RTSNavigationLib/Pathfinding/DijkstraGrid.cpp"	
    "Source/RTSNavigationLib/Pathfinding/EikonalGrid.h"	
    "Source/RTSNavigationLib/Pathfinding/EikonalGrid.cpp"	
)
source_group("Source/Pathfinding" FILES ${Pathfinding_Files})

set(ALL_FILES
    ${Source_Files}
    ${Util_Files}
    ${HexagonGrid_Files}
    ${RectangleGrid_Files}
    ${FormationShape_Files}
    ${Formation_Files}
    ${Usher_Files}
    ${Flocking_Files}
    ${Pathfinding_Files}
)

############################################################################
############################################################################
############################################################################

add_library(RTSNavigationLib ${ALL_FILES})
set_property(TARGET RTSNavigationLib PROPERTY CXX_STANDARD 20)

target_link_libraries(RTSNavigationLib PUBLIC 
glm::glm
${Boost_LIBRARIES}
)

target_include_directories(RTSNavigationLib PUBLIC 
./Source/
)
target_include_directories(RTSNavigationLib PRIVATE 
./Source/RTSNavigationLib/
)