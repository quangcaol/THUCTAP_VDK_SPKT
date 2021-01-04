#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
//#include "TV_PICKIT2_SHIFT_LCD.c"
#include "TV_PICKIT2_SHIFT_STEP_MOTOR.c"
#include "TV_PICKIT2_SHIFT_GLCD128X64.c"
#include "TV_PICKIT2_SHIFT_DS18B20.c"
#include "TV_PICKIT2_SHIFT_DS1307_I2C.c"
#include "18F4550.h"
#include <math.h>


void main()
{
   set_up_port_ic_chot();
   stepmotor_onoff = 0;
   stepmotor_delay  = 10;
   while (true)
   {
      if(!input(on))
      { 
         stepmotor_tn = stepmotor_tn ^ 1;
         while(!input(on));
      }
      motor_step_run_fs();
      delay_ms(stepmotor_delay);
   }
   
}

