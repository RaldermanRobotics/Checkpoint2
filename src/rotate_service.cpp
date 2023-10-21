#include "my_rb1_ros/custom_service_messages.h"
#include "ros/publisher.h"
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <sstream>
#include <std_srvs/Empty.h>

bool my_callback(my_rb1_ros::custom_service_messages::Request &req,
                 my_rb1_ros::custom_service_messages::Response &res) {
  // res.some_variable = req.some_variable + req.other_variable;
  ROS_INFO("You want to turn"); // We print an string whenever the
                                // Service gets called
  return true;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "rotate_node");
  ros::NodeHandle nh;
  ros::Publisher turning = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
  ros::ServiceServer my_service =
      nh.advertiseService("/rotate_service", my_callback);
  ros::spin(); // mantain the service open.

  // if (argc > 1) {
  //  int degree;
  //  degree = int argv;
  //  int radians = argv * 3.14 / 180;
  //  ROS_INFO("We got to the if statement");
  //}
  return 0;
}
