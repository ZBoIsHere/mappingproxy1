#include <iostream>
#include <ros/ros.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>

ros::Subscriber colored_pointcloud_sub;
ros::Subscriber uncolored_pointcloud_sub;

void colored_pointcloud_callback(const sensor_msgs::PointCloud2::ConstPtr & input);
void uncolored_pointcloud_callback(const sensor_msgs::PointCloud2::ConstPtr & input);

int main(int argc, char** argv) {
    ROS_INFO("map controller start");
    ros::init (argc, argv, "mapcontroller", ros::init_options::AnonymousName);
    ros::NodeHandle nh;

    colored_pointcloud_sub = nh.subscribe("colored_pointcloud_pub", 100, colored_pointcloud_callback);
    uncolored_pointcloud_sub = nh.subscribe("uncolored_pointcloud_pub", 100, uncolored_pointcloud_callback);

    ros::spin();
    return 0;
}

void colored_pointcloud_callback(const sensor_msgs::PointCloud2::ConstPtr& input) {
    pcl::PointCloud<pcl::PointXYZRGB> output_ptr ;
    pcl::fromROSMsg(*input, output_ptr);
    if(pcl::io::savePCDFileASCII("/root/rosbag/test.pcd", output_ptr) == 0) {
        ROS_INFO("save pcd file success");
    }
}

void uncolored_pointcloud_callback(const sensor_msgs::PointCloud2::ConstPtr& input) {
    pcl::PointCloud<pcl::PointXYZI> output_ptr ;
    pcl::fromROSMsg(*input, output_ptr);
    if(pcl::io::savePCDFileASCII("/root/rosbag/test.pcd", output_ptr) == 0) {
        ROS_INFO("save pcd file success");
    }
}