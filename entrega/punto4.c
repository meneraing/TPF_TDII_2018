#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>

void salida();

void main(){
	wiringPiSetupGpio() ;
	int a=0, i=0;
	int ins[]={17,5,6,13,19};
	int outs[]={23,24,25,12};

	for(i=0;i<5;i++)
		pinMode(ins[i], INPUT);
	for(i=0;i<4;i++)
		pinMode(outs[i], OUTPUT);
	while(a!=0){
		if(digitalRead(17)==1){
			salida();
			a=1;
		}else a=0;
	}
}

void salida(){
	digitalWrite(23,digitalRead(5));
	digitalWrite(24,digitalRead(6));
	digitalWrite(25,digitalRead(13));
	digitalWrite(12,digitalRead(19));
}