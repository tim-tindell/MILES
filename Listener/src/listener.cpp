#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <wifi_scanner/wifi_signal_msg.h>
tf::TransformListener *listener;
File* outfile;
//This function will be called every time a new wifi signal is detected
void writeToFile(wifi_scanner::wifi_signal_msg msg){
		try{
			tf::StampedTransform transform;
			printf("1\n");
  			listener->lookupTransform("/camera_link", "/vodom", ros::Time(0), transform);
			printf("2\n");
			fprintf(outfile,"x:	%f, y:	%f, z:	%f||",
				transform.getOrigin().x(),
				transform.getOrigin().y(),
				transform.getOrigin().z());

			printf("3\n");
			int x=0;
			while(msg.MAC[x]!=""){
                            fprintf(outfile,"	[MAC: %s, Str %d]",msg.MAC[x].c_str(),msg.Sig[x]);
			    x++;
			}
			fprintf(outfile,"\n");

   		}
		catch (tf::TransformException ex){
    			ROS_ERROR("%s",ex.what());
      			ros::Duration(1.0).sleep();
   		}

};
int main(int argc, char** argv){

	ros::init(argc, argv, "my_tf_listener");
	ros::NodeHandle node;
	listener = new tf::TransformListener();
	outfile=fopen("pose.txt","w");
        fclose(outfile);
        ros::Subscriber sub = node.subscribe<wifi_scanner::wifi_signal_msg>("signals",10,writeToFile);
        ros::spin();
	fclose(outfile);
}


