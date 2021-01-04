#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "18F4550.h"

int min = 0, sec = 0;

void main()
{
   set_up_port_ic_chot();
   xuat_4led_7doan_4so(0xff,0xff,0xff,0xff);
   while(TRUE)
   {
      if (sec == 60) {
         sec = 0;
         min++;
         if(min == 60) {
            min = 0;
         }
      }
      xuat_4led_7doan_4so(ma7doan[min/10],ma7doan[min%10],ma7doan[sec/10],ma7doan[sec%10]);
      delay_ms(1000);
      sec++;
      
   }
}

