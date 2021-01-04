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
      xuat_8led_7doan_quet_1(0x7f,0xc0);
      delay_ms(1);

      xuat_8led_7doan_quet_1(0xbf,0xf9);
      delay_ms(1);

      xuat_8led_7doan_quet_1(0xdf,0xa4);
      delay_ms(1);

      xuat_8led_7doan_quet_1(0xef,0xb0);
      delay_ms(1);

      xuat_8led_7doan_quet_1(0xf7,0x99);
      delay_ms(1);

      xuat_8led_7doan_quet_1(0xfb,0x92);
      delay_ms(1);

      xuat_8led_7doan_quet_1(0xfd,0x82);
      delay_ms(1);        

      xuat_8led_7doan_quet_1(0xfe,0xf8);
      delay_ms(1);              

   }
}

