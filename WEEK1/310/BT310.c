#include "TV_PICKIT2_SHIFT_1.c"
#include <stdint.h>

#define no 2

unsigned int16 Y;
unsigned int16 X;
uint16_t i = 0;

void blink() {
   for(int i = 0 ; i <2; i++) {
      xuat_32led_don_2word(0xffff,0xffff);
      delay_ms(40);
      xuat_32led_don_2word(0,0);
      delay_ms(40);
   }
}
void left_to_right_reserver() {
   for(int j = 0; j<2; j++) {
      for(i = 0; i< 16; i++) {
         xuat_32led_don_2word(x,y);
         Y = (Y >> 1) | 0x8000;
         x = (x << 1) | 1;
         delay_ms(50);
      }
      for(i = 0; i< 16; i++) {
         xuat_32led_don_2word(x,y);
         Y = (Y >>1);
         X = (x << 1);
         delay_ms(50);
      }
      for(i = 0; i< 16; i++) {
         xuat_32led_don_2word(x,y);
         Y = (Y << 1) | 1;
         X = (x >> 1) | 0x8000;
         delay_ms(50);
      }
      for(i = 0; i< 16; i++) {
         xuat_32led_don_2word(x,y);
         Y = (Y <<1);
         X = (x >> 1);
         delay_ms(50);
      }
   }
}

int main(void) {
   set_up_port_ic_chot();
   y = 0;
   x= 0;
   while(true) {
      //blink();
      left_to_right_reserver();
   }
   return 1;
}

