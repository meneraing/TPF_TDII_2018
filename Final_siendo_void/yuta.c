#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "funciones.h"

int delay_mio(int ch);

int i, flag, retardo, file_descriptor;
static int cnt=0, retardo2=0;
char data_in;

void yuta(int ch){
	wiringPiSetupGpio() ;
	char   * uart  =  "/dev/serial0";
	int  k;
	int pins_leds[]={23,24,25,12,16,20,21,26};
	pinMode(17, INPUT);
	for(k=0;k<8;k++) pinMode(pins_leds[k], OUTPUT);

	retardo=adc()/2;
	if(cnt==0) retardo2=retardo;

	file_descriptor = serialOpen(uart, 9600);

	printf("USTED SE A COMUNICADO CON LA COMISARIA\n");
	printf("Pulse el maravilloso botón de la plaqueta para salir\n");


	while(digitalRead(17) != 1){
		for (i = 0; i < 2; i++){
			for(k=0;k<4;k++) digitalWrite(pins_leds[k], 1);
			delay_mio(ch);
			if(i==1) delay_mio(ch);
			for(k=0;k<4;k++) digitalWrite(pins_leds[k], 0);
			for(k=4;k<8;k++) digitalWrite(pins_leds[k], 1);
        		delay_mio(ch);
			if(i==1) delay_mio(ch);
			for(k=4;k<8;k++) digitalWrite(pins_leds[k], 0);

        	if(i==1){
			for(k=0;k<4;k++) digitalWrite(pins_leds[k], 1);
			delay_mio(ch);
			for (k = 0; k < 4; k++){
		        	delay_mio(ch);
		        	digitalWrite(pins_leds[k], 0);
		        }

		for(k=4;k<8;k++) digitalWrite(pins_leds[k], 1);
		delay_mio(ch);
        	for (k = 7; k > 3; k--){
			delay_mio(ch);
			digitalWrite(pins_leds[k], 0);
			if (digitalRead(17) == 1) break;

            	}
        }
        if (digitalRead(17) == 1) break;
	delay_mio(ch);
	if(i==1) delay_mio(ch);
	if (digitalRead(17) == 1 || flag == 1){
		serialFlush(file_descriptor);
		serialClose(file_descriptor);
		break;
	}
      }
      if (digitalRead(17) == 1) break;
    }

    for(i=0;i<8;i++)  digitalWrite(pins_leds[i], 0);
    system("clear");
}

int delay_mio(int ch){
	char c;
	int j;
	for (j = -1; j < retardo2; ++j) //bucle de retardos 1 para poder salir cuando quiera
	        {
	            delay(2);
		    if(i!=1) delay(3);
	            if (digitalRead(17) == 1) { flag=1; break;}


							if(ch==0){
							if(kbhit()){
										system("/bin/stty raw");
								if( c = getchar() == '[')      c = getchar();
									if( c  == 'A'){ //modo de observar si se pulso flecha abajo
										if(retardo2 != 0) retardo2-=10;
										j=-1;
										system("clear");
										printf("Pulse el maravilloso botón de la plaqueta para salir\n");}
									else if ( c == 'B') { //flecha arriba
										retardo2+=10;
										j=-1;
										system("clear");
										printf("Pulse el maravilloso botón de la plaqueta para salir\n");}
										system("/bin/stty cooked");
								}
							}else if(ch==1){
								if(serialDataAvail(file_descriptor) > 0){
								delay(10);
								data_in  = serialGetchar(file_descriptor);
				              if(data_in  == 'A'){ //modo de observar si se pulso flecha abajo
				                  if(retardo2 != 0) retardo2-=10;
				                  j=-1;
				                  system("clear");
				                  printf("Pulse el maravilloso botón de la plaqueta para salir\n");}
				                else if ( data_in == 'B') { //flecha arriba
				                  retardo2+=10;
				                  j=-1;
				                  system("clear");
				                  printf("Pulse el maravilloso botón de la plaqueta para salir\n");}
				            }
						}
				            if (digitalRead(17) == 1) break;
        }

}
