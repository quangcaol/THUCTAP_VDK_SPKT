#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "18F4550.h"

int dem = 0;


void main()
{
   set_up_port_ic_chot();
   setup_timer_0(T0_EXT_L_TO_H|T0_DIV_1|T0_8_BIT);
   set_timer0(0);
   xuat_4led_7doan_4so(0xff,0xff,0xff,0xff);
   while(TRUE)
   {
      dem = get_timer0();
      xuat_4led_7doan_3so(ma7doan[dem/100],ma7doan[dem/10%10],ma7doan[dem%10]);
      if(dem>101) set_timer0(1);
      
   }
}

