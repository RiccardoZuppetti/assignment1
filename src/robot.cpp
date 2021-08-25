#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "assignment1/Random.h"
#include "nav_msgs/Odometry.h"
#include <sstream>
#include <iostream>
#include <math.h>

ros::Publisher pub; 
ros::ServiceClient client;

int k = 2;
bool cond = true;
double c,d;

void positionCallback(const nav_msgs::Odometry::ConstPtr& posemsg)
{

	assignment1::Random rand_pose;
  	geometry_msgs::Twist msg_sent;
  
	if(cond==true){
	  	rand_pose.request.min=-6.0;
	  	rand_pose.request.max=6.0;
  		client.call(rand_pose);
  		c=rand_pose.response.a;
  		d=rand_pose.response.b;
  		ROS_INFO("NEW TARGET POSITION [%lf, %lf]",c,d);
  		cond=false;	
  	}
  	float d1=c-(posemsg->pose.pose.position.x);
  	float d2=d-(posemsg->pose.pose.position.y);
  	float distance = sqrt((d1*d1)+(d2*d2));
  	if(distance<0.1){
  		msg_sent.linear.x=0.0;
  		msg_sent.linear.y=0.0;
  		ROS_INFO("POSITION REACHED!");
  		cond=true;
  	}
	if(distance>=0.1){
	  	msg_sent.linear.x=k*d1;
	  	msg_sent.linear.y=k*d2;
	  	ROS_INFO("I'M MOVING TO THE TARGET");
	  	cond=false;
	}
	pub.publish(msg_sent);  		
}

int main(int argc, char **argv)
{
	ros::init(argc,argv,"robot");
	ros::NodeHandle n;
        client = n.serviceClient<assignment1::Random>("/random");

	pub=n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
	ros::Subscriber sub = n.subscribe("/odom", 1000, positionCallback); 
        ros::spin();
	return 0;
}


