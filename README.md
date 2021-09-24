# Research Track I - First assignment
The purpose of the assignment is to control a robot in a 2D space, which is shown via a 2D simulator, and therefore comparable to a cartesian plane.
In particular, the robot asks to the user for a random target to be reached.
Any of these random targets have coordinates -6 and 6 both along x and y.
Established the target, the robot goes to this one and then asks for a new random target.
# Structure of the package
The package is composed of the two nodes:
* [robot.cpp](https://github.com/RiccardoZuppetti/assignment1/blob/main/src/robot.cpp)
* [random_number.cpp](https://github.com/RiccardoZuppetti/assignment1/blob/main/src/random_number.cpp)

On top, the [random_number.cpp](https://github.com/RiccardoZuppetti/assignment1/blob/main/src/random_number.cpp) has implemented a service [Random.srv](https://github.com/RiccardoZuppetti/assignment1/blob/main/srv/Random.srv). This server accepts two floating points numbers as inputs and releases other two floating points numbers.
The [random_number.cpp](https://github.com/RiccardoZuppetti/assignment1/blob/main/src/random_number.cpp) node initializes the server and implements a function that returns a random number in a given interval. The server receives as input the interval and two numbers, that are the minimum and maximum acceptable number that the user can have as outputs. When a request is sent to the server the random function is called twice passing as inputs the two numbers received from the server request in order to generate the x and y coordinates that the robot will have to reach.
The [robot.cpp](https://github.com/RiccardoZuppetti/assignment1/blob/main/src/robot.cpp) node initializes a client for the server random, a subscriber for the topic `/odom` and a publisher on the topic `/cmd_vel`. The subscriber on the topic `/odom` receives the position of the robot in a variable of type `nav_msgs/Odometry`. Everytime that the robot receives a new position, the function `positionCallback` is called and the values of the position and of the distances from the target are updated. The distance is calculated along x and y and it is the difference between the target coordinates and the current position of the robot. If the distance is less than 0.1, the [robot.cpp](https://github.com/RiccardoZuppetti/assignment1/blob/main/src/robot.cpp) node recall the server in order to ask for another target. As soon as a response is received from the server, the values of the target are updated. If the distance is not less than 0.1, a linear velocity is assigned along x and y both proportional to the distance along x and y respectively. That linear velocity is then published on the topic `/cmd_vel`.
# How to launch
1. Open a shell, move to your catkin_ws and in the src folder type:
```
git clone https://github.com/RiccardoZuppetti/assignment1.git
```
2. Go to the root of the workspace, and from there launch `catkin_make`

3. Start the ROS Master typing:
```
roscore &
```
3. Then launch the simulation environment through the command:
```
rosrun stage_ros stageros $(rospack find assignment1)/world/exercise.world
```
4. Open a second shell and type:
```
rosrun assignment1 random_number
```
5. Finally, open a third shell and type:
```
rosrun assignment1 robot
```

