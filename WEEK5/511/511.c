#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "18F4550.h"


int16 dem = 0;



void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);

   while(TRUE)
   {
      for(int16 i = 0; i<5000; i++ ) {
         xuat_8led_7doan_quet_2(0,ma7doan[dem%10]);
         delay_us(100);
         xuat_8led_7doan_quet_tat_led();
         xuat_8led_7doan_quet_2(1,ma7doan[dem/10]);
         delay_us(100);
         xuat_8led_7doan_quet_tat_led();
      }
         dem++;
         if (dem == 60) dem = 0;
      }                                 
}

