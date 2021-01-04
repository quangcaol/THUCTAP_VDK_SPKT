#include "18F4550.h"
#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
//#include "TV_PICKIT2_SHIFT_LCD.c"
#include "TV_PICKIT2_SHIFT_STEP_MOTOR.c"
#include "TV_PICKIT2_SHIFT_DC_MOTOR.c"
#include "TV_PICKIT2_SHIFT_GLCD128X64.c"
#include "TV_PICKIT2_SHIFT_DS18B20.c"
#include "TV_PICKIT2_SHIFT_DS1307_I2C.c"

#include <math.h>



signed int16 t1;
signed int8 donvi,chuc,tram,ngan,bdn;
signed int16 xung,xungdat,duty,e,ecu =0,tocdo;
float kp =1,kd = 0.2, ki = 0.002,tp = 0,td = 0,ti = 0;




#int_timer3
void interrupt_timer3()
{
   set_timer3(3036);
      bdn = 0;
      xung = get_timer1();
      set_timer1(0);
      e = xungdat - xung;
      tp = e;
      td = (e-ecu)*10;
      ti = ti*e*0.1;
      ecu = e;
      duty = duty + kp*tp + kd*td + ki*ti;
      if (duty > 1000) duty = 1000;
      else if (duty<0) duty = 0;
      set_pwm1_duty(duty);    
}

void hienthi_lcd_t1(signed int16 tam)
{
   lcd_command(lcd_addr_line1);
   printf(lcd_data,"LEVEL %4ld",tam);
}


void hienthi_lcd_cap_tocdo()
{
   lcd_command(lcd_addr_line2);
   printf(lcd_data,"SPEED %4ld",tocdo);
}
void hienthi_lcd_xung_dat()
{
   lcd_command(lcd_addr_line3);
   printf(lcd_data,"SETPOINT %4ld",xungdat);
}
void heinthi_lcd_xung_dem()
{
   lcd_command(lcd_addr_line4);
   printf(lcd_data,"COUNT %4ld",xung);
}



void phim_up(){
   if (!input(up) && (xungdat<300))
   {
      delay_ms(20);
      if (!input(up)) {
      xungdat = xungdat+10;
      tocdo++;
      hienthi_lcd_cap_tocdo();
      delay_ms(200);      
   }
   enable_interrupts(INT_TIMER3);
   }
}  
void phim_dw()
{
   if (!input(dw) && (xungdat>0))
   {
      delay_ms(20);
      if (!input(dw)) {
         xungdat = xungdat-10;
         tocdo--;
         hienthi_lcd_cap_tocdo();
         delay_ms(200);
      }
   }
}


void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3C);
   set_tris_c(0xf9);
   dc_enable=1;
   output_low(pin_c1);
   xuat_buzzer_relay();

   setup_lcd();

   setup_ccp1(CCP_PWM);
   setup_timer_2(T2_DIV_BY_1,249,1);

   dcmotor_tn = 1;
   pwm_duty = 0;
   dc_motor_ktao_ccpx_ktao();
   dc_motor_pww_setup_duty();


   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER3);
   
   

   setup_timer_3(T3_INTERNAL|T3_DIV_BY_8);
   set_timer3(3036);


   setup_timer_1(T1_EXTERNAL_SYNC | T1_DIV_BY_1);
   set_timer1(0);

   hienthi_lcd_cap_tocdo();
   tocdo =0;
   xuat_buzzer_relay();
   duty = 0;
   bdn = 0;
   xungdat = 0;

   while (true)
   {
      phim_dw();
      phim_up();
      if (!input(stop))
      {
         disable_interrupts(INT_TIMER3);
         duty = 0;
         set_timer1(0);
         tocdo = 0;
         xungdat = 0;
         xung = 0;
         hienthi_lcd_cap_tocdo();
         set_pwm1_duty(0);
      }
      t1 = (xung*40)/3;
      hienthi_lcd_t1(t1);
      hienthi_lcd_xung_dat();
      heinthi_lcd_xung_dem();
   }
   
}

