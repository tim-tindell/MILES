#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <termios.h>
#include <unistd.h>   // for read()

static struct termios initial_settings, new_settings;
static int peek_character = -1;

void init_keyboard()
{
    tcgetattr(0,&initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_lflag &= ~ISIG;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
}

void close_keyboard()
{
    tcsetattr(0, TCSANOW, &initial_settings);
}

int kbhit()
{
unsigned char ch;
int nread;

    if (peek_character != -1) return 1;
    new_settings.c_cc[VMIN]=0;
    tcsetattr(0, TCSANOW, &new_settings);
    nread = read(0,&ch,1);
    new_settings.c_cc[VMIN]=1;
    tcsetattr(0, TCSANOW, &new_settings);
    if(nread == 1)
    {
        peek_character = ch;
        return 1;
    }
    return 0;
}

int readch()
{
char ch;

    if(peek_character != -1)
    {
        ch = peek_character;
        peek_character = -1;
        return ch;
    }
    read(0,&ch,1);
    return ch;
}

int main(int argc, char **argv)
{
double x,y=0;
double xdelta=0.01;
double ydelta=0.01;
        // initialize ros
        ros::init(argc, argv, "talker");
        ros::NodeHandle n;

        // create publisher
        ros::Publisher cmd_vel_topic = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
	//initialize keyboard
	init_keyboard();
        // our loop will publish at 10Hz
        ros::Rate loop_rate(5);

        int count = 0;
        while (ros::ok())
        {
		if(kbhit()){
			
			
			char pressed=readch();
			printf( "\nKey struck was '%c'\n", pressed);
			if(pressed=='w'&&x<1)
				x=x+xdelta;
			else if(pressed=='s'&&x>-1)
				x=x-xdelta;
			else if(pressed=='a'&&y<1)
				y=y+xdelta;
			else if(pressed=='d'&&y>-1)
				y=y-ydelta;	
			else if(pressed=='q'){
				close_keyboard();
				return 0;
			}
			else
				printf("Stop");
		}

		else{
			/*if(x==0.0||x==-0.0)
				x=x;
			else if(x>0)
				x=x-xdelta/2;
			else if(x<1)
				x=x+xdelta/2;
			if(y==0.0||y==-0.0)
				y=y;		
			else if(y>0)
				y=y-ydelta/2;
			else if(y<1)
				y=y+ydelta/2;*/
		}
		printf("speed: %f | turn: %f\n",x,y);
                geometry_msgs::Twist twist;
                twist.linear.x = x;
                twist.linear.y = 0;
                twist.angular.z= y;
                cmd_vel_topic.publish(twist);
                //loop_rate.sleep();
                //++count;
        }
        return 0;
}
