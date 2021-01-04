#include "TV_PICKIT2_SHIFT_1.c"
#include <stdint.h>

#define no 2

unsigned int16 Y;


int main(void) {
   set_up_port_ic_chot();
   y = 0;
   uint16_t i = 0;
   
   while(true) {
      for(i = 0; i< 16; i++) {
      xuat_32led_don_2word(y,y);
         Y = (Y >> 1) | 0x8000;
         delay_ms(200);
      }
      for(i = 0; i< 16; i++) {
         xuat_32led_don_2word(y,y);
         Y = (Y >>1);
         delay_ms(200);
      }
   }
   return 1;
}

