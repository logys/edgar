project (Edgar)

# CppUTest
include(FetchContent)
FetchContent_Declare(
    CppUTest
    GIT_REPOSITORY https://github.com/cpputest/cpputest.git
    GIT_TAG        latest-passing-build # or use release tag, eg. v3.8
)
# Set this to ON if you want to have the CppUTests in your project as well.
set(TESTS OFF CACHE BOOL "Switch off CppUTest Test build")
FetchContent_MakeAvailable(CppUTest)

# include project source
include_directories(${PROJECT_SOURCE_DIR}/../src)
include_directories(${PROJECT_SOURCE_DIR}/./)
include_directories(env ${CPPUTEST_HOME}/include)

add_library(avr avr/io.cpp)
add_library(util util/delay.cpp)

add_executable(run_tests test_serial.cpp test_bluetooth.cpp test_robotController.cpp
	test_motorDc.cpp test_pwm.cpp test_gpioHandler.cpp test_differential.cpp 
	test_timerDelay.cpp test_mobile_robot.cpp test_button.cpp RunAllTests.cpp)
target_link_libraries(run_tests PRIVATE avr)
target_link_libraries(run_tests PRIVATE util)
target_link_libraries(run_tests PRIVATE CppUTest CppUTestExt)
target_link_libraries(run_tests PRIVATE mobile_robot)
target_link_libraries(run_tests PRIVATE push)
target_link_libraries(run_tests PRIVATE timer)
target_link_libraries(run_tests PRIVATE differential)
target_link_libraries(run_tests PRIVATE motor)
target_link_libraries(run_tests PRIVATE pwm)
target_link_libraries(run_tests PRIVATE gpio)
target_link_libraries(run_tests PRIVATE serial)
target_link_libraries(run_tests PRIVATE bluetooth)
target_link_libraries(run_tests PRIVATE robotController)
