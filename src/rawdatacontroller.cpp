#include "iostream"
#include "ros/ros.h"
#include "rosbag/player.h"
#include "std_msgs/String.h"
#include "../include//mappingproxy/rawdatacontroller.h"
#include "rosbag/bag.h"
#include "rosbag/view.h"
#include "thread"

ros::Publisher rawdata_status_pub;
ros::Subscriber algorithm_status_sub;

void rawdataPlayCountdown();

int main(int argc, char** argv) {
    ROS_INFO("rawdata controller start");
    ros::init(argc, argv, "rawdatacontroller", ros::init_options::AnonymousName);
    ros::NodeHandle nh;
    // todo zhangbo how to set reasonable queue_size
    rawdata_status_pub = nh.advertise<std_msgs::String>("rawdata_status", 100);
    algorithm_status_sub = nh.subscribe("algorithm_status", 100, algorithmStatusCallback);
    ros::spin();
    return 0;
}

void algorithmStatusCallback(const std_msgs::String::ConstPtr& msg) {
    rosbag::Bag bag;
    bag.open("/root/rosbag/test.bag", rosbag::bagmode::Read);
    rosbag::View view(bag);
    auto bag_length_time = view.getEndTime() - view.getBeginTime();
    auto bag_length_time2sec = bag_length_time.toSec();
    std::thread thr1(rawdataPlayCountdown);
    ros::Duration(bag_length_time2sec - 3).sleep();
    std_msgs::String rawdata_status;
    rawdata_status.data = "FINISHED";
    rawdata_status_pub.publish(rawdata_status);
    ROS_INFO("rawdata play finished");
    thr1.join();
}

void rawdataPlayCountdown() {
    // todo zhangbo why when bag play finished the main process exit
    rosbag::PlayerOptions opts;
    opts.bags.push_back(std::string("/root/rosbag/test.bag"));
    rosbag::Player player(opts);
    try {
        std_msgs::String rawdata_status;
        rawdata_status.data = "STARTED";
        rawdata_status_pub.publish(rawdata_status);
        ROS_INFO("rawdata play started");
        player.publish();
    }
    catch (std::runtime_error& e) {
        ROS_FATAL("%s", e.what());
    }
}