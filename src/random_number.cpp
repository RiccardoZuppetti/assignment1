#include "ros/ros.h"
#include "assignment1/Random.h"

double randMToN(double min, double max)
{     
    return min + (rand() / ( RAND_MAX / (max-min) ) );
}


bool myrandom(assignment1::Random::Request &req, assignment1::Random::Response &res){
    res.a = randMToN(req.min, req.max);
    res.b = randMToN(req.min, req.max);
    return true;
}



int main(int argc, char **argv)
{
   ros::init(argc, argv, "random_number");
   ros::NodeHandle n;
   ros::ServiceServer service= n.advertiseService("/random", myrandom);
   ros::spin();
   return 0;
}

