#include <Node.h>

std::string Node::toString(){
	std::string ret;

	ret="____________________________________________\n"+this->pos.toString()+"\n";

	for(int x=0;x<(sizeof(this->routers)/sizeof(this->routers[0]));x++){
		if(this->routers[x].Strength!=0)
			ret=ret+this->routers[x].toString()+"\n";
	}
	return ret;
}
void Node::Sort(bool up){
	router rout;
	bool done=false;
	for(int x=0;x<(sizeof(this->routers)/sizeof(this->routers[0])-1);x++){
		int y=x;
		while(!done){
			if((y<0)||this->routers[y].Strength > this->routers[y+1].Strength){
				done=true;
			}
			else{
				rout=this->routers[y];
				this->routers[y]=this->routers[y+1];
				this->routers[y+1]=rout;
				y--;
			}		
		}
		done=false;
			
	}
	return;
}
void Node::Normalize(){
	int max=0;
	for(int x=0;x<(sizeof(this->routers)/sizeof(this->routers[0]));x++){
		if(this->routers[x].Strength!=0){
			if(this->routers[x].Strength>max)
				max=this->routers[x].Strength;
		}
	}
	for(int x=0;x<(sizeof(this->routers)/sizeof(this->routers[0]));x++){
		if(this->routers[x].Strength!=0)
			this->routers[x].Strength=this->routers[x].Strength/max;
	}
}

std::string pose::toString(){
	return "x: "+std::to_string(this->x)+"\ty: "+std::to_string(this->y)+"\tz: "+std::to_string(this->z);
}
std::string router::toString(){
	return "MAC: "+this->MAC+"\tStr: "+std::to_string(this->Strength);
}

