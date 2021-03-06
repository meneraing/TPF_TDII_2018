#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>

int sec1(){
    wiringPiSetupGpio() ;
    int i=0;
    int pins_leds[]={23,24,25,12,16,20,21,26};
    pinMode(17, INPUT);
    for(i=0;i<8;i++)
      pinMode(pins_leds[i], OUTPUT);
    srand(time(NULL));

    while(digitalRead(17) != 1){
      for(i = 0; i < 8; i++){
        digitalWrite(pins_leds[i], 1);
        if (digitalRead(17) == 1) return 0;
      }
      for (int i = 0; i < (rand()%1000)+1; ++i){ /*Genera numero aleatorio entre 1 y 1000*/
      	delay(1);
      	if (digitalRead(17) == 1) return 0;
      	}
         
      for(i = 0; i < 8; i++){
        digitalWrite(pins_leds[i], 0);
        if (digitalRead(17) == 1) return 0;
      }
      delay(rand() % 1000 + 1);
    }
}
