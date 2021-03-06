#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <wifi_scanner/wifi_signal_msg.h>
tf::TransformListener *listener;

void writeToFile(wifi_scanner::wifi_signal_msg msg){
                FILE* outfile=fopen("pose.txt","a");
		try{
			//tf::StampedTransform transform;
			printf("Scanner message found, writing to file\n");
  			//listener->lookupTransform("/camera_link", "/camera_rgb_frame", ros::Time(0), transform);
			//fprintf(outfile,"x:	%f, y:	%f, z:	%f||",
			//	transform.getOrigin().x(),
			//	transform.getOrigin().y(),
			//	transform.getOrigin().z());
			fprintf(outfile,"%f|",ros::Time::now().toSec());

			int x=0;
			while(msg.MAC[x]!=""){
                            fprintf(outfile,"[MAC: %s, Str %d]",msg.MAC[x].c_str(),msg.Sig[x]);
			    x++;
			}
			printf("%d routers were found!\n",x);
			fprintf(outfile,"\n");

   		}
		catch (tf::TransformException ex){
    			ROS_ERROR("%s",ex.what());
      			ros::Duration(1.0).sleep();
   		}
 		fclose(outfile);

};
int main(int argc, char** argv){

	ros::init(argc, argv, "my_tf_listener");
	ros::NodeHandle node;
	//listener = new tf::TransformListener();
	FILE* outfile=fopen("pose.txt","w");
         printf("1\n");
        fclose(outfile);
        ros::Subscriber sub = node.subscribe<wifi_scanner::wifi_signal_msg>("signals",10,writeToFile);
        ros::spin();
}


