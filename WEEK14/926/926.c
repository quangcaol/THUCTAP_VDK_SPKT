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
unsigned int16 duty,t1,t1_tam;
int1 OnOff = 1;
int8 rev = 7;
unsigned int16 step = 0;
//stepmotor_delay = 30;

#INT_TIMER1
void interrupt_timer1()
{
   duty = 0;
   pwm_capso = 0;
   xuat_4led_7doan_giaima_xoa_so0(pwm_capso);
   set_timer1(0);
   set_pwm1_duty(duty);   
   OnOff = 0;
}



void phim_up(){
   if (!input(up) && (duty<1000))
   {
         delay_quet_8led(100);
         if (!input(up)) {
         OnOff = 1;
         stepmotor_delay -=5;
         rev--;
         duty = duty + 50;
         set_pwm1_duty(duty);
         pwm_capso++;
         if (stepmotor_delay < 5) {stepmotor_delay = 5; rev = 1; }
         xuat_4led_7doan_giaima_xoa_so0(pwm_capso);
      }
   }
}
void phim_dw()
{
   if (!input(dw) && (duty>0))
   {
         delay_quet_8led(100);
         if (!input(dw)) {
         OnOff = 1;
         stepmotor_delay -=5;
         rev--;
         duty = duty - 50;
         set_pwm1_duty(duty);
         pwm_capso--;
         if (stepmotor_delay < 5) {stepmotor_delay = 5; rev = 1; }
         xuat_4led_7doan_giaima_xoa_so0(pwm_capso);
         }
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




void main()
{
   set_up_port_ic_chot();
   dc_enable=1;
   output_low(pin_c1);
   xuat_buzzer_relay();
   setup_ccp1(CCP_PWM);
   setup_timer_2(T2_DIV_BY_1,249,1);

   setup_timer_1(T1_EXTERNAL_SYNC | T1_DIV_BY_1);
   set_timer1(0);

   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER1);


   duty = 0;
   pwm_capso = 0;
   xuat_4led_7doan_giaima_xoa_so0(pwm_capso);
   set_pwm1_duty(duty);



   t1 = t1_tam = 0;
   while (true)
   {
      phim_dw();
      phim_up();
      phim_inv();
      t1 = get_timer1();
      if (t1!=t1_tam  && OnOff)
      {
         giai_ma_gan_cho_8led_quet_16_xoa(t1);
         t1_tam = t1;
      }
      hien_thi_8led_7doan_quet();

      if(!input(stop))
      {
         duty = 0;
         pwm_capso = 0;
         xuat_4led_7doan_giaima_xoa_so0(pwm_capso);
         set_pwm1_duty(duty);
      }
   }
   
}

