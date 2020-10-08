
#include <iostream>
#include <thread>
#include <math.h>

#include "robot.hh"
#include "viz.hh"

using std::cout;
using std::endl;

void
callback(Robot* robot)
{
    cout << "\n===" << endl;
    for (auto hit : robot->ranges) {
        cout << hit.range << "@" << hit.angle << endl;
    }
    cout << "x,y,t = "
         << robot->pos_x << ","
         << robot->pos_y << ","
         << robot->pos_t << endl;
    robot->set_vel(robot->pos_t, -robot->pos_t);
}

void
robot_thread(Robot* robot)
{
    robot->do_stuff();
}

int
main(int argc, char* argv[])
{
    cout << "making robot" << endl;
    Robot robot(argc, argv, callback);
    std::thread rthr(robot_thread, &robot);

    return run_viz(argc, argv);
}
