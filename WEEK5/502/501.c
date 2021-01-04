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

      xuat_8led_7doan_quet_1(0x7f,ma7doan[1]);
      delay_ms(1);        

      xuat_8led_7doan_quet_1(0xbf,ma7doan[0]);
      delay_ms(1);              

   }
}

