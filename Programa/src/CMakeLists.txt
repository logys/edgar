project (Edgar)

include_directories(../tests)
#add_executable(edgar ./main.c)
add_library(push ./push.cpp)
add_library(robot ./robot.cpp)
add_library(motor ./motorDc.cpp)
add_library(timer ./timer_delay.cpp)
