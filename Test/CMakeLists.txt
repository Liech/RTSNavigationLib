cmake_minimum_required(VERSION 2.8...3.20)
project(RTSNavigationLibTests)

find_package(Catch2 REQUIRED)


set(Test_Files
	"Tests/BodyUtilTest.cpp"
	"Tests/UsherTest.cpp"
	"Tests/RTree2DTest.cpp"
	"Tests/HexagonGridTest.cpp"
	"Tests/RectangleGridTest.cpp"
	"Tests/FormationTest.cpp"
	"Tests/UnitPlacementTest.cpp"
	"Tests/FlockTest.cpp"
	"Tests/FlowFieldTest.cpp"
	"Tests/DijkstraGridTest.cpp"	
	"Tests/EikonalGridTest.cpp"
	"Tests/MapChunkTest.cpp"
	"Tests/MapTest.cpp"
)
source_group("Tests" FILES ${Test_Files})
set(Main_Files
	"main.cpp"
)
source_group("Main" FILES ${Main_Files})

set(ALL_FILES
    ${Main_Files}
    ${Test_Files}
)


add_executable(RTSNavigationLibTests ${ALL_FILES})
set_property(TARGET RTSNavigationLibTests PROPERTY CXX_STANDARD 20)

target_link_libraries(RTSNavigationLibTests PRIVATE 
Catch2::Catch2
RTSNavigationLib
)
target_include_directories(RTSNavigationLibTests SYSTEM PUBLIC 
"${CMAKE_CURRENT_LIST_DIR}/../RTSPathingLib/Source"
)

#add_custom_command(TARGET RTSNavigationLibTests POST_BUILD 
#               COMMAND ${CMAKE_COMMAND} -E copy_directory 
#               "${RTSNavigationLibTests_SOURCE_DIR}/TestData"              
#                $<TARGET_FILE_DIR:RTSNavigationLibTests>/TestData)

include(CTest)
include(Catch)
catch_discover_tests(RTSNavigationLibTests)