#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "TV_PICKIT2_SHIFT_LCD.c"
#include "TV_PICKIT2_SHIFT_GLCD128X64.c"
#include "TV_PICKIT2_SHIFT_DS18B20.c"
#include "18F4550.h"
#include <math.h>
#include <graphics.c>


float kcs;

void dispDis(float x)
{
   unsigned int16 Y;
   y = (unsigned int16) x;
   xuat_4led_7doan_giaima_xoa_so0(x);  
}

void Trig()
{
   delay_ms(10);
   output_high(trigger);
   delay_ms(10);
   output_low(trigger);

   set_timer1(0);
   while(!input(echo));
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_4);
   while(input(echo));
   kcs = get_timer1();
   set_timer1(T1_DISABLED);
}

void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   setup_timer_1(T1_DISABLED);
   dispDis(0);
   while(TRUE)
   {
      Trig();
      kcs = kcs*0.8;
      kcs = (kcs/58);
      dispDis(kcs);
      delay_ms(500);
   }
}

