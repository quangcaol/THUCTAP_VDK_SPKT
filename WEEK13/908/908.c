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


int1 OnOff = 0;
unsigned int8 rev = 0;
unsigned int8 curRev = 0;
unsigned int16 step = 0;
int8 mode = 0;
//stepmotor_delay = 30;

void phim_up(){
   if (!input(up))
   {
      stepmotor_delay -=5;
      rev--;
      if (stepmotor_delay < 5) {stepmotor_delay = 5; rev = 1; }
      while (!input(up));
   }
}
void phim_dw()
{
   if (!input(dw))
   {
      stepmotor_delay += 5;
      rev++;
      if (stepmotor_delay > 45) {stepmotor_delay = 50; rev = 9;} 
      while (!input(dw));
   }
}
void phim_inv()
{
   if (!input(inv))
   {
      delay_ms(20);
      if (!input(inv))
      {
         stepmotor_tn = stepmotor_tn ^ 1;
         step = 0;
      }
   }
}

void HienThi()
{
   xuat_4led_7doan_4so(ma7doan[curRev/10],ma7doan[curRev%10],ma7doan[Rev/10],ma7doan[Rev%10]);
}


void main()
{
   set_up_port_ic_chot();
   stepmotor_onoff = 0;
   stepmotor_delay = 5;
   while (true)
   {
      if (OnOff) {
         motor_step_run_fs();
         delay_ms(stepmotor_delay);
         step++;
      }
      if (step == 200) 
      {
         step = 0; 
         curRev++;
         if (curRev == Rev) {OnOff = 0;}
      }

         unsigned int8 but = key_4x4_dw();
         if (but!=0xff){
            if (onOff == 0) {
               if (but <= 9) 
               {
                  if (mode == 0) 
                  {
                     curRev = 0;
                     rev = but;
                     mode++;
                  }
                  else if(mode == 1) 
                  {
                     curRev = 0;
                     rev =rev*10 + but;
                     mode = 0;
                  }                  
               }
            }
            if (but == 10 && OnOff == 0) {OnOff = 1; stepmotor_tn = 1; mode = 0;}
            if (but == 11 && OnOff == 0) {OnOff = 1; stepmotor_tn = 0; mode=  0;}
            if (but == 12) {OnOff = 0; stepmotor_tn = 0; mode=  0;}
            }
      HienThi();
   }
   
}

