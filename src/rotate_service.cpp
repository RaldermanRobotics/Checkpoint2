#include "my_rb1_ros/custom_service_messages.h"
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <std_srvs/Empty.h>

bool my_callback(my_rb1_ros::custom_service_messages::Request &req,
                 my_rb1_ros::custom_service_messages::Response &res) {
  // res.some_variable = req.some_variable + req.other_variable;
  ROS_INFO("My_callback has been called"); // We print an string whenever the
                                           // Service gets called
  return true;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "rotate_node");
  ros::NodeHandle nh;

  ros::ServiceServer my_service = nh.advertiseService(
      "/rotate_service",
      my_callback); // create the Service called // my_service with the defined
                    // // callback
  ros::spin();      // mantain the service open.

  return 0;
}
