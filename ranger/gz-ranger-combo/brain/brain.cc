
#include <iostream>
#include <string>
#include <math.h>

#include "robot.hh"

using std::cout;
using std::endl;

/*
To view the camera image in time, you could press CTRL-T in Gazebo
, choosing the Topic-"~/tankbot0/tankbot/camera_sensor/link/camera/image", 
then a Image Window will pop up, in order to view the Image in time.
*/

void
callback(Robot* robot)
{
    float speed = clamp(0.0, robot->get_range() - 1.0, 1.0);
    robot->set_vel(speed, speed);
}

int
main(int argc, char* argv[])
{
    Robot* robot = 0;

    if (std::string(argv[0]) == "gz_robot") {
        cout << "making robot: Gazebo mode" << endl;
        robot = new GzRobot(argc, argv, callback);
    }

    if (std::string(argv[0]) == "rg_robot") {
        cout << "making robot: Ranger mode" << endl;
        robot = new RgRobot(argc, argv, callback);
    }

    robot->do_stuff();

    delete robot;
    return 0;
}
