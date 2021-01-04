#include "TV_PICKIT2_SHIFT_1.c"
#include <stdint.h>

#define no 2

unsigned int32 Y;


int main(void) {
   set_up_port_ic_chot();
   y = 0;
   uint16_t i = 0;
   
   while(true) {
      for(i = 0; i< 16; i++) {
      xuat_32led_don_2word(y>>16,y);
         Y = (Y >> 1) | 0x80000000;
         delay_ms(100);
      }
      for(i = 0; i< 16; i++) {
         xuat_32led_don_2word(y>>16,y);
         Y = (Y >>1);
         delay_ms(100);
      }
   }
   return 1;
}

