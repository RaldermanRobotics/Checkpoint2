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
double kP = 0.5; //Proportional gain
ros::Publisher pub;
ros::ServiceServer srv_rotate_by_degrees;
ros::Subscriber sub;

//(const nav_msgs::Odometry::custom_service::Requestg& req, pkg_name::custom_service::Response& res)

void getRotation(const nav_msgs::Odometry::ConstPtr& msg)
{
    geometry_msgs::Quaternion orientation = msg->pose.pose.orientation;
    tf::Quaternion tf_orientation;
    tf::quaternionMsgToTF(orientation, tf_orientation);
    tf::Matrix3x3(tf_orientation).getRPY(roll, pitch, yaw);
    ROS_INFO("Yaw = %.2f", yaw);
}   

bool rotate_with_degrees(my_rb1_ros::custom_service_messages::Request& req, my_rb1_ros::custom_service_messages::Response& res)
{
    ROS_INFO("Rotation Callback has been called");
    //variable relative to the callback, likely need to reset counters or values.
    
    geometry_msgs::Twist turn1;
    

    if (req.degrees >= 0) //turn left
    {
        turn1.angular.z = 1.0;
        ROS_INFO("the input is telling the robot to turn left");
    }
    if (req.degrees < 0) //turn right
    {
        turn1.angular.z = -1.0;
        ROS_INFO("the input is telling the robot to turn right");
    }
    ROS_INFO("We are rotating no mater what");
    pub.publish(turn1);
    return true;
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "rotate_this_thing");
    ros::NodeHandle nh;

    sub = nh.subscribe("/odom", 1 ,getRotation); 
    pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
    srv_rotate_by_degrees = nh.advertiseService("/rotate_by_degree", rotate_with_degrees);
    ros::spin();
    
    return 0;  
}
