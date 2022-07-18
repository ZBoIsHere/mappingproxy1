#include "iostream"
#include "ros/ros.h"
#include "rosbag/player.h"

int main(int argc, char** argv) {
    ROS_INFO("start to play some rosbag");
    ros::init(argc, argv, "play", ros::init_options::AnonymousName);

    rosbag::PlayerOptions opts;
    opts.bags.push_back(std::string("/root/rosbag/hku_campus_seq_00.bag"));

    rosbag::Player player(opts);

    try {
        player.publish();
    }
    catch (std::runtime_error& e) {
        ROS_FATAL("%s", e.what());
        return 1;
    }

    return 0;
}