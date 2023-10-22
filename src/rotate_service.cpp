#include "my_rb1_ros/custom_service_messages.h"
#include "ros/publisher.h"
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <ros/ros.h>
#include <sstream>
#include <std_srvs/Empty.h>
#include <string>

bool handleService(my_rb1_ros::custom_service_messages::Request &req,
                   my_rb1_ros::custom_service_messages::Response &res) {
  int degrees = req.degrees;
  ROS_INFO("Received degrees: %d", degrees);

  // Calculate the time to reach the desired degrees at a constant angular
  // velocity
  double angular_velocity =
      degrees * 3.14 / 180 / 4 ; // radians per second (to be done over 4 secs)

  // Create a Timer to publish the Twist message over 4 seconds
  ros::NodeHandle nh;
  ros::Publisher cmd_vel_publisher =
      nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
  ros::Rate loop_rate(100); // Publish at 10 Hz
  ros::Time start_time = ros::Time::now();

  while ((ros::Time::now() - start_time).toSec() < 4) {
    geometry_msgs::Twist twist_msg;
    twist_msg.angular.z = angular_velocity;
    cmd_vel_publisher.publish(twist_msg);
    loop_rate.sleep();
  }

  // Stop the rotation when the desired time has passed
  geometry_msgs::Twist stop_twist;
  stop_twist.angular.z = 0;
  cmd_vel_publisher.publish(stop_twist);
  ROS_INFO("The robot has rotated");

  return true;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "rotate_node");
  ros::NodeHandle nh;

  ros::ServiceServer service =
      nh.advertiseService("/rotate_service", handleService);
  ROS_INFO("Rotate service server is ready.");

  ros::spin();

  return 0;
}
