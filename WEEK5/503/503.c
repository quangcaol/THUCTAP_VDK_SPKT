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
      xuat_8led_7doan_quet_2(0,ma7doan[9]);
      delay_ms(1);
      xuat_8led_7doan_quet_2(1,ma7doan[8]);
      delay_ms(1);
      xuat_8led_7doan_quet_2(2,ma7doan[7]);
      delay_ms(1);
      xuat_8led_7doan_quet_2(3,ma7doan[6]);
      delay_ms(1);
      xuat_8led_7doan_quet_2(4,ma7doan[5]);
      delay_ms(1);
      xuat_8led_7doan_quet_2(5,ma7doan[4]);
      delay_ms(1);
      xuat_8led_7doan_quet_2(6,ma7doan[3]);
      delay_ms(1);
      xuat_8led_7doan_quet_2(7,ma7doan[2]);
      delay_ms(1);                                    
   }
}

