#include <ros/ros.h>
#include <tf/transform_listener.h>


int main(int argc, char** argv){

	ros::init(argc, argv, "my_tf_listener");
	ros::NodeHandle node;
	tf::TransformListener listener;
     
	ros::Rate rate(10);
	FILE* outfile=fopen("pose.txt","w");
	while (node.ok()){
		tf::StampedTransform transform;
		try{
  			listener.lookupTransform("/camera_link", "/vodom", ros::Time(0), transform);
			fprintf(outfile,"Camera Pose:	x:	%f, y:	%f, z:	%f\n",
				transform.getOrigin().x(),
				transform.getOrigin().y(),
				transform.getOrigin().z());
		        rate.sleep();

   		}
		catch (tf::TransformException ex){
    			ROS_ERROR("%s",ex.what());
      			ros::Duration(1.0).sleep();
   		}
 

	}
	fclose(outfile);
	return 0;
};
