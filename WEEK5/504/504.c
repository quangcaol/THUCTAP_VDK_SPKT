#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "18F4550.h"






void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);

   while(TRUE)
   {
      for(int i = 0; i<8; i++) {
         xuat_8led_7doan_quet_2(i,ma7doan[i]);
         delay_us(100);
         //xuat_8led_7doan_quet_tat_led();
      }                                 
   }
}

