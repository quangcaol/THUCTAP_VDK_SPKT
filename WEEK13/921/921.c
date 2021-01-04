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
//stepmotor_delay = 30;

void phim_up(){
   if (!input(up) && (duty<1000))
   {
      stepmotor_delay -=5;
      rev--;
      duty = duty + 50;
      set_pwm1_duty(duty);
      pwm_capso++;
      if (stepmotor_delay < 5) {stepmotor_delay = 5; rev = 1; }
      xuat_32led_don_2word(0xffff,0xffff);
      delay_ms(200);
   }
}
void phim_dw()
{
   if (!input(dw) && (duty>0))
   {
      stepmotor_delay += 5;
      rev++;
      duty = duty - 50;
      set_pwm1_duty(duty);
      pwm_capso--;
      if (stepmotor_delay > 45) {stepmotor_delay = 50; rev = 9;} 
      xuat_32led_don_2word(0,0);
      delay_ms(200);
   }
}
void phim_inv()
{
   if (!input(inv) )
   {
      delay_ms(20);
      if (!input(inv))
      {
         step = 0;
      }
   }
}

void HienThi()
{
   xuat_4led_7doan_4so(ma7doan[pwm_capso/10],ma7doan[pwm_capso%10],ma7doan[16],ma7doan[rev]);
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
   pwm_capso = 0;
   HienThi();
   set_pwm1_duty(duty);
   while (true)
   {
      if (OnOff) {
         motor_step_run_hs();
         delay_ms(stepmotor_delay);
         step++;
      }
      phim_dw();
      phim_up();
      phim_inv();
      if(!input(stop)){
         duty = 0;
         pwm_capso = 0;
         HienThi();
         set_pwm1_duty(0);
      }
      HienThi();
   }
   
}

