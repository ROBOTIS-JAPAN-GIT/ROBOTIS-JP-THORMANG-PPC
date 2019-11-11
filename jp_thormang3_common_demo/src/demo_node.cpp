/*******************************************************************************
* Copyright 2019 ROBOTIS Japan CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/* Author: Yoshimaru Tanaka */

#include <ros/ros.h>
#include <ros/package.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>

void playSound(const std::string &path);
void thormang3CommandCallback(const std_msgs::String::ConstPtr &msg);
void manipInitCallback(const std_msgs::String::ConstPtr &msg);
void balanceCommandCallback(const std_msgs::Bool::ConstPtr &msg);

const int SPIN_RATE = 30;
ros::Publisher play_sound_pub;
std::string default_mp3_path = "";

int main(int argc, char **argv)
{
  //init ros
  ros::init(argc, argv, "demo_node");
  ros::NodeHandle nh(ros::this_node::getName());

  // ros::Subscriber sound_command_sub = nh.subscribe("/robotis/mode_command", 1, thormang3CommandCallback);
  ros::Subscriber sound_command_sub = nh.subscribe("/robotis/base/ini_pose", 1, thormang3CommandCallback);
  ros::Subscriber enable_ctrl_module_sub = nh.subscribe("/robotis/enable_ctrl_module", 1, thormang3CommandCallback);
  ros::Subscriber move_lidar_sub = nh.subscribe("/robotis/head_control/move_lidar", 1, thormang3CommandCallback);
  ros::Subscriber manip_init_sub = nh.subscribe("/robotis/manipulation/ini_pose_msg", 1, manipInitCallback);
  ros::Subscriber balance_command_sub = nh.subscribe("/robotis/thormang3_foot_step_generator/balance_command", 1, balanceCommandCallback);

  default_mp3_path = ros::package::getPath("jp_thormang3_common_demo") + "/data/mp3/";
  play_sound_pub = nh.advertise<std_msgs::String>("sound/play_sound_file", 0);
  ROS_INFO("MP3 Path : %s", default_mp3_path.c_str());

  // ros::start();
  ros::Rate loop_rate(SPIN_RATE);

  //node loop
  while (ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}

void playSound(const std::string &path)
{
  std_msgs::String sound_msg;
  sound_msg.data = path;

  play_sound_pub.publish(sound_msg);
}

void thormang3CommandCallback(const std_msgs::String::ConstPtr &msg)
{
  if (msg->data == "ini_pose")
    {
      playSound(default_mp3_path + "thormang3_001_init.mp3");
    }
  else if(msg->data == "manipulation_module")
    {
      playSound(default_mp3_path + "thormang3_002_manip.mp3");
    }
  else if(msg->data == "walking_module")
    {
      playSound(default_mp3_path + "thormang3_003_walk.mp3");
    }
  else if(msg->data == "start")
    {
      playSound(default_mp3_path + "thormang3_004_scan.mp3");
    }
}

void manipInitCallback(const std_msgs::String::ConstPtr &msg)
{
  playSound(default_mp3_path + "thormang3_005_manip_ready.mp3");
}

void balanceCommandCallback(const std_msgs::Bool::ConstPtr &msg)
{
  if (msg->data == true)
    {
      playSound(default_mp3_path + "thormang3_010_auto_balancer.mp3");
    }
}
