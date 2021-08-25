# Research Track I - First Assignment

The package assignment1 is composed of two nodes: the robot node and the random number node. There is also a server, called Random.
The server Random accepts two floating points numbers as inputs and releases other two floating points numbers. 
The service is implemented in the random_number node.
The random number node initialises the server and implements a function that returns a random number in a given interval. The server receives as input the interval, two numbers that are the minimum and maximum acceptable number I can have as outputs.
When a request is sent to the server the random function is called twice passing as inputs the two numbers received from the server request in order to generate the x and y coordinates that the robot will have to reach. 
The robot node initialises a client for the server random, a subscriber for the topic odom and a publisher on the topic cmd_vel.
The subscriber on the topic odom receives the position of the robot in a variable of type Odometry, everytime it receives a new position the function chatterCallback is called and the values of the position and of the distance from the target are updated. The distance is calculated along x and y and it is the difference between the target coordinates and the current position of the robot. Then if the distance is less than 0.1 along both x and y I call the server asking for another target. When I receive an answer I update the values of the target. If on the other hand the distance is not less than 0.1 I assign a linear velocity along x and y both proportional to the distance along x and y respectively. That linear velocity is then published on the topic cmd_vel. 

The robot then moves in the space between coordinates -6 and 6 both along x and y, goes to a target and when the target is reached it asks for a new target autonomously. On the screen is printed the new target everytime the server is called.

# How to Run

Open three different linux shell.

In the first type:
- roscore &
- rosrun stage_ros stageros $(rospack find assignment1)/world/exercise.world

In the second shell then run:
- rosrun assignment1 random_number

In the third shell run:
- rosrun assignment1 robot
