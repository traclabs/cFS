project(ROBOT_SIM C)

include_directories(fsw/mission_inc)
include_directories(fsw/platform_inc)

# Create the app module
add_cfe_app(robot_sim fsw/src/robot_sim.c)
