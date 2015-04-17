/*
 * Copyright (C) 2015, Lentin Joseph and Qbotics Labs Inc.
 
* Email id : qboticslabs@gmail.com

 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the names of Stanford University or Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.


* This code will publish a integers from 0 to n with a delay of 100ms

 */



#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <actionlib/client/simple_action_client.h>
#include "mastering_ros_demo_pkg/Demo_actionAction.h"
#include <iostream>
#include <sstream>


//Defining namespace using in this code
using namespace std;
//using namespace ros;
using namespace std_msgs;
//using namespace mastering_ros_demo_pkg;
//using namespace actionlib;




class Demo_action_Client{


public:
	Demo_action_Client(std::string name):
	//Set up client
	ac("demo_action_client",true),
	//Store the name
	action_name(name){
	//Waiting for server.
	ROS_INFO("%s Waiting for server ...", action_name.c_str());
	ac.waitForServer();
	ROS_INFO("%s Got connected ...",action_name.c_str());

	}


	void doneCb(const actionlib::SimpleClientGoalState& state,

			const mastering_ros_demo_pkg::Demo_actionResultPtr& result)

	{

		ROS_INFO("Finished in state [%s]", state.toString().c_str());

		ROS_INFO("Result: %d", result->final_count);

		ros::shutdown();

	};

	// Called once when the goal becomes active

	void activeCb()

	{

		ROS_INFO("Goal just went active...");

	};


 	// Called every time feedback is received for the goal

	void feedbackCb(const mastering_ros_demo_pkg::Demo_actionFeedbackPtr &feedback)

	{

		ROS_INFO("Got Feedback of Progress to Goal: %d", feedback->current_number);

	};


	void send(int goal){
		mastering_ros_demo_pkg::Demo_actionGoal new_goal;
		new_goal.count = goal;

/*		ac.sendGoal(new_goal,boost::bind(Demo_action_Client::doneCb, this, _1, _2),
				boost::bind(Demo_action_Client::activeCb, this),
				boost::bind(Demo_action_Client::feedbackCb, this,_1));
		
*/

		ac.sendGoal(new_goal,boost::bind(&Demo_action_Client::doneCb, this, _1, _2));
		

	}



private:
	actionlib::SimpleActionClient<mastering_ros_demo_pkg::Demo_actionAction> ac;
	std::string action_name;


};






int main(int argc, char** argv)
{

	ros::init(argc,argv,"demo_action_client");

	int test_goal = 100;

	if(argc != 2){
		ROS_INFO("Usage: demo_action_client <goal>");
		return 1;
	}else{
		test_goal = atoll(argv[1]);

	}


	//Init client
  	Demo_action_Client client(ros::this_node::getName());

//	client.send(test_goal);

 	ROS_INFO("Sent goal %d to Demoa action server..", test_goal);

	ros::spin();
	return 0;


}


