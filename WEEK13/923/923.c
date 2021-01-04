#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
//#include "TV_PICKIT2_SHIFT_LCD.c"
#include "TV_PICKIT2_SHIFT_STEP_MOTOR.c"
#include "TV_PICKIT2_SHIFT_DC_MOTOR.c"
#include "TV_PICKIT2_SHIFT_GLCD128X64.c"
#include "TV_PICKIT2_SHIFT_DS18B20.c"
#include "TV_PICKIT2_SHIFT_DS1307_I2C.c"
#include "18F4550.h"
#include <math.h>




signed int8 pwm_capso;
unsigned int16 duty;
int1 OnOff = 1;
int8 rev = 7;
unsigned int16 step = 0;

void HienThi()
{
   xuat_4led_7doan_4so(ma7doan[16],ma7doan[duty],ma7doan[16],ma7doan[16]);
}


void phim_bt0()
{
   if(!input(bt0)) 
   {
      delay_ms(20);
      if (!input(bt0))
      {
         duty = 0;
         HienThi();
         set_pwm1_duty(0);
         while(!input(bt0));
      }
      
   };
}

void phim_bt1()
{
   if(!input(bt1)) 
   {
      delay_ms(20);
      if (!input(bt1))
      {
         duty = 1;
         HienThi();
         set_pwm1_duty(350);
         while(!input(bt1));
      }
      
   };
}

void phim_bt2()
{
   if(!input(bt2)) 
   {
      delay_ms(20);
      if (!input(bt2))
      {
         duty = 2;
         HienThi();
         set_pwm1_duty(700);
         while(!input(bt2));
      }
      
   }
}


void phim_bt3()
{
   if(!input(bt3)) 
   {
      delay_ms(20);
      if (!input(bt3))
      {
         duty = 3;
         HienThi();
         set_pwm1_duty(1000);
         while(!input(bt3));
      }
      
   }
}








void main()
{
   set_up_port_ic_chot();
   stepmotor_onoff = 0;
   stepmotor_delay = 15;
   dc_enable=1;
   output_low(pin_c1);
   xuat_buzzer_relay();

   setup_ccp1(CCP_PWM);
   setup_timer_2(T2_DIV_BY_1,249,1);
   duty = 0;
   HienThi();
   set_pwm1_duty(duty);
   while (true)
   {
      if (OnOff) {
         motor_step_run_hs();
         delay_ms(stepmotor_delay);
      }
      phim_bt0();
      phim_bt1();
      phim_bt2();
      phim_bt3();
   }
   
}

