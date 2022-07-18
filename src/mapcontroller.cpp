#include <iostream>
#include <ros/ros.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>


void clouda_cb(const sensor_msgs::PointCloud2ConstPtr& input);

int main(int argc, char** argv) {
    ros::init (argc, argv, "mapproxy");
    ros::NodeHandle nh;

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr clouda_ptr (new pcl::PointCloud<pcl::PointXYZRGB>);
    if (pcl::io::loadPCDFile<pcl::PointXYZRGB> ("/root/rosbag/rgb_pt.pcd", *clouda_ptr) == -1) {
        PCL_ERROR ("Couldn't read file pcl_2_pcd1.pcd ^.^\n");
        return (-1);
    }
    std::cerr << "size of a : " << clouda_ptr->width*clouda_ptr->height<< std::endl;

    sensor_msgs::PointCloud2 clouda_ros;
    pcl::toROSMsg (*clouda_ptr, clouda_ros);

    ros::Publisher puba = nh.advertise<sensor_msgs::PointCloud2> ("clouda", 1);
    ros::Subscriber suba = nh.subscribe("clouda", 1, clouda_cb);

    clouda_ros.header.stamp = ros::Time::now();
    clouda_ros.header.frame_id = "sensor_framea";
    puba.publish(clouda_ros);

    ros::spin();
    return 0;
}

void clouda_cb(const sensor_msgs::PointCloud2ConstPtr& input) {
    pcl::PointCloud<pcl::PointXYZRGB> output_ptr ;
    pcl::fromROSMsg(*input, output_ptr);
    if(pcl::io::savePCDFileASCII("/root/rosbag/test.pcd", output_ptr) == 0) {
        ROS_INFO("save pcd file success");
    }
}
