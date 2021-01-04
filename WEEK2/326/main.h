#include <18F4550.h>
#device ADC=10

#FUSES NOWDT                 	//No Watch Dog Timer

#use delay(crystal=20000000)
#use i2c(Master,Fast,sda=PIN_B0,scl=PIN_B1)

