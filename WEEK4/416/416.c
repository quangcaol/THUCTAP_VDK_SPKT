#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "18F4550.h"

unsigned int16 dem = 0;
unsigned int16 donvi,chuc,tram;


void main()
{
   set_up_port_ic_chot();
   setup_timer_0(T0_EXT_L_TO_H|T0_DIV_1);
   set_timer0(0);
   while(TRUE)
   {
      if (dem != get_timer0()) {
         dem = get_timer0();
         if(dem>=9999) {set_timer0(0); dem=0;}
         xuat_4led_7doan_giaima_xoa_so0(dem);
      }
   }
}

