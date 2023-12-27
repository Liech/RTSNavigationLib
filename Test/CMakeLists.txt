cmake_minimum_required(VERSION 2.8...3.20)
project(RTSPathingLibTests)

find_package(Catch2 REQUIRED)


set(Test_Files
	"Tests/BodyUtilTest.cpp"
	"Tests/UsherTest.cpp"
	"Tests/RTree2DTest.cpp"
	"Tests/HexagonGridTest.cpp"
	"Tests/RectangleGridTest.cpp"
	"Tests/FormationTest.cpp"
	"Tests/UnitPlacementTest.cpp"
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


add_executable(RTSPathingLibTests ${ALL_FILES})
set_property(TARGET RTSPathingLibTests PROPERTY CXX_STANDARD 20)

target_link_libraries(RTSPathingLibTests PRIVATE 
Catch2::Catch2
RTSPathingLib
)
target_include_directories(RTSPathingLibTests SYSTEM PUBLIC 
"${CMAKE_CURRENT_LIST_DIR}/../RTSPathingLib/Source"
)

#add_custom_command(TARGET RTSPathingLibTests POST_BUILD 
#               COMMAND ${CMAKE_COMMAND} -E copy_directory 
#               "${RTSPathingLibTests_SOURCE_DIR}/TestData"              
#                $<TARGET_FILE_DIR:RTSPathingLibTests>/TestData)

include(CTest)
include(Catch)
catch_discover_tests(RTSPathingLibTests)