#include "ros/ros.h"
#include "std_msgs/String.h"

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;

  // subscribe to chatter with buffer size 1000
  // when a message comes, call the function chatterCallback
  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);

  // enter a loop to listen and pump callbacks.
  ros::spin();

  return 0;
}
