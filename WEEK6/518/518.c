#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "18F4550.h"

signed int16 count = 0, countT = 0; 
int8 mode = 0;



void giai_ma(){
   led_7dq[0] = ma7doan[count%10];
   led_7dq[1] = ma7doan[count/10];
}

void phim_up(){
   if (phim_bt0(200)) {
      mode = 1;
      set_timer0(count);
   }
}

void phim_dw(){
   if (phim_bt1(200)) {
      mode = 0;
   }
}

void phim_mode(){
   if (phim_bt2(200)) {
      set_timer0(0);
      count = 0;
   }
}



void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   setup_timer_0(T0_EXT_L_TO_H|T0_DIV_1);
   set_timer0(0);
   giai_ma();
   hien_thi_8led_7doan_quet();
   while(TRUE)
   {
      phim_up();
      phim_dw();
      phim_mode();
      if (mode == 1) {
         count = get_timer0();
         if (count != countT) {
            countT = count;
            if (count == 100) set_timer0(0);
         }
      }
      giai_ma();
      hien_thi_8led_7doan_quet();
   }           
}

