#ifndef ROBOT_HH
#define ROBOT_HH

#include <vector>

#include <gazebo/gazebo_config.h>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/gazebo_client.hh>

class LaserHit {
  public:
    LaserHit()
        : range(0.0), angle(0.0)
    {
        // do nothing
    };

    LaserHit(float x, float t)
        : range(x), angle(t)
    {
        // do nothing
    }

    const float range;
    const float angle;
};

class Robot {
  public:
    void (*on_update)(Robot*);

    std::vector<LaserHit> ranges;
    float pos_x;
    float pos_y;
    float pos_t;

    Robot(int argc, char* argv[], void (*cb)(Robot*));
    ~Robot();

    bool at_goal();
    void do_stuff();
    void done();

    void set_vel(double lvel, double rvel);

    void on_scan(ConstSonarStampedPtr &msg);
    void on_pose(ConstPoseStampedPtr &msg);

  private:
    bool task_done;

    gazebo::transport::NodePtr node;
    gazebo::transport::PublisherPtr vel_pub;
    gazebo::transport::SubscriberPtr scan_sub;
    gazebo::transport::SubscriberPtr pose_sub;
};

#endif
