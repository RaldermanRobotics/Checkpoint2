//#include <iterator>
#include <my_rb1_ros/custom_service_messages.h>
//#include <ros/ros.h>
//#include <geometry_msgs/Twist.h>
//#include <nav_msgs/Odometry.h>
//#include <tf/transform_datatypes.h>

#include <ros/ros.h>
#include <tf/transform_datatypes.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <math.h>
//#include "pkg_name/srv_custom_file.h"

//now define the private variables I plan to use
double roll, pitch, yaw;
double degree_input;
double input_radian_convert;

//(const nav_msgs::Odometry::custom_service::Requestg& req, pkg_name::custom_service::Response& res)

void getRotation(const nav_msgs::Odometry::ConstPtr& msg)
{
    geometry_msgs::Quaternion orientation = msg->pose.pose.orientation;
    tf::Quaternion tf_orientation;
    tf::quaternionMsgToTF(orientation, tf_orientation);
    tf::Matrix3x3(tf_orientation).getRPY(roll, pitch, yaw);
    ROS_INFO("Yaw = %.2f", yaw);
}   

int main(int argc, char** argv)
{
    ros::init(argc, argv, "rotate_this_thing");
    ros::NodeHandle nh;
    ros::Subscriber sub;
    sub = nh.subscribe("/odom", 1 ,getRotation); 
    ros::spin();

    return 0;  
}
