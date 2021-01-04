#include "TV_PICKIT2_SHIFT_1.c"
#include <stdint.h>



unsigned int32 Y = 0;
int8 flag = 0;
int8 flag1 = 0xff;
int8 count = 0;


void left_to_right_reserver() {
    if(flag1 == 0xff) {
      
      if (flag & 0x1) {
         y = (y << 1) | 1; }
      else {
         y = y<<1; }
      xuat_32led_don_2word(y>>16,y);
      delay_ms(10);
      if ((y == 0xffffffff) ||  (y == 0)) {flag = ~flag; count++;}
      if(count > 2) {count = 0; flag1 = 0;}
      }
}
void right_to_left_reserver() {
   if(flag1 == 0) {
      if (flag & 0x1) {
         y = (y >> 1) | 0x80000000; }
      else {
         y = y>>1; }
      xuat_32led_don_2word(y>>16,y);
      delay_ms(10);
      if ((y == 0xffffffff) ||  (y == 0)) { flag = ~flag; count++;}
      if(count > 2) { count = 0; flag1 = 0xff; }
      }
}

int main(void) {
   set_up_port_ic_chot();
   while(true) {
      left_to_right_reserver();
      right_to_left_reserver();
   }
   return 1;
}

