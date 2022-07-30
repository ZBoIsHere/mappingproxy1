#include <iostream>
#include <ros/ros.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include "boost/filesystem.hpp"

const char* ENV_CLOUDMAPPATH = "CLOUD_MAP_PATH";
const char* ENV_CLOUDMAPNAME = "CLOUD_MAP_NAME";
char* cloud_map_path;
char* cloud_map_name;

ros::Subscriber colored_pointcloud_sub;
ros::Subscriber uncolored_pointcloud_sub;

void colored_pointcloud_callback(const sensor_msgs::PointCloud2::ConstPtr & input);
void uncolored_pointcloud_callback(const sensor_msgs::PointCloud2::ConstPtr & input);

int main(int argc, char** argv) {
    ROS_INFO("map controller start");
    ros::init (argc, argv, "mapcontroller", ros::init_options::AnonymousName);
    ros::NodeHandle nh;

    cloud_map_path = getenv(ENV_CLOUDMAPPATH);
    if (cloud_map_path == nullptr) {
        ROS_ERROR("Can not get env %s", ENV_CLOUDMAPPATH);
        return -1;
    }

    cloud_map_name = getenv(ENV_CLOUDMAPNAME);
    if (cloud_map_name == nullptr) {
        ROS_ERROR("Can not get env %s", ENV_CLOUDMAPNAME);
        return -1;
    }

    colored_pointcloud_sub = nh.subscribe("colored_pointcloud_pub", 100, colored_pointcloud_callback);
    uncolored_pointcloud_sub = nh.subscribe("uncolored_pointcloud_pub", 100, uncolored_pointcloud_callback);

    ros::spin();
    return 0;
}

void colored_pointcloud_callback(const sensor_msgs::PointCloud2::ConstPtr& input) {
    if (!boost::filesystem::is_directory(cloud_map_path)) {
        ROS_INFO("start create path %s", cloud_map_path);
        if (!boost::filesystem::create_directories(cloud_map_path)) {
            ROS_INFO("failed create path %s", cloud_map_path);
        }
    }

    std::string pcd_file = std::string(cloud_map_path).append(cloud_map_name);

    pcl::PointCloud<pcl::PointXYZRGB> output_ptr ;
    pcl::fromROSMsg(*input, output_ptr);
    if (output_ptr.empty()) {
        ROS_WARN("point cloud has no data");
        return;
    }

    if(pcl::io::savePCDFileBinary(pcd_file, output_ptr) == 0) {
        ROS_INFO("save pcd file success");
        ros::shutdown();
    }
}

void uncolored_pointcloud_callback(const sensor_msgs::PointCloud2::ConstPtr& input) {
    pcl::PointCloud<pcl::PointXYZI> output_ptr ;

    if (!boost::filesystem::is_directory(cloud_map_path)) {
        ROS_INFO("start create path %s", cloud_map_path);
        if (!boost::filesystem::create_directories(cloud_map_path)) {
            ROS_INFO("failed create path %s", cloud_map_path);
        }
    }

    std::string pcd_file = std::string(cloud_map_path).append(cloud_map_name);

    pcl::fromROSMsg(*input, output_ptr);
    if (output_ptr.empty()) {
        ROS_WARN("point cloud has no data");
        return;
    }

    if(pcl::io::savePCDFileBinary(pcd_file, output_ptr) == 0) {
        ROS_INFO("save pcd file success");
        ros::shutdown();
    }
}