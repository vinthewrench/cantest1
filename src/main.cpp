//
//  main.cpp
//  canrecord
//
//  Created by Vincent Moscaritolo on 3/12/22.
//

 

#include "CanClient.hpp"

using namespace std;



class JeepClient : public CANClientProcessor {
	void rcvFrame(struct can_frame );
};


void JeepClient::rcvFrame(struct can_frame frame ){
	
	char      	 lineBuf[80];
	char       	 *p = lineBuf;

	p += sprintf(p, "%03X [%d] ",  frame.can_id, frame.can_dlc);
	
	for (int i = 0; i < frame.can_dlc; i++) p += sprintf(p,"%02X ",frame.data[i]);
	for (int i = 7; i >=  frame.can_dlc ; i--) p += sprintf(p,"   ");
	p += sprintf(p,"  ");
	for (int i = 0; i < frame.can_dlc; i++)  {
		
		uint8_t c = frame.data[i] & 0xFF;
		if (c > ' ' && c < '~')
			*p++ = c ;
		else {
			*p++ = '.';
		}
	}
	*p++ = 0;
	
	printf("%s\n",lineBuf);
}



int main(int argc, const char * argv[]) {
 
	JeepClient jeep;
	CANClient 	can0;
	
	can0.begin("can0", &jeep);
//	can0.setFilter(0x03E6, 0x7ff);

	while(true) {
		sleep(2);
	}
 
	return 0;
}
