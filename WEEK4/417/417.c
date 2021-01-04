#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "18F4550.h"

unsigned int16 dem;
unsigned int flag=0;


void phim_on() {
   if(!input(on)){
      delay_ms(20);
      while (!input(on))
      flag = 1;
      xuat_32led_don_4byte(0xff,0xff,0xff,0xff);
   }
}



void phim_off() {
   if(!input(off)){
      delay_ms(20);
      while (!input(off))
      flag = 0;
      xuat_32led_don_4byte(0,0,0,0);
   }
}


void main()
{
   setup_timer_0(T0_EXT_L_TO_H|T0_DIV_1);
   set_timer0(90);
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   dem = get_timer0();
   while(TRUE)
   {
      phim_on();
      phim_off();
      if (flag==1) {
         if (dem != get_timer0()) {
            dem = get_timer0();
            if(dem>=101) {set_timer0(90); dem=0;}
            xuat_4led_7doan_giaima_xoa_so0(dem);
         }
      }
      else
      {
        set_timer0(dem);
      }
     
   }
}

