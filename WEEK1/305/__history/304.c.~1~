#include "TV_PICKIT2_SHIFT_1.c"
#include <stdint.h>

unsigned int8 Y;

int main(void) {
   set_up_port_ic_chot();
   y = 1;
   uint8_t flag = 1;
   while(true) {
      if ( y == 0x80 | y == 0x1) flag = ~flag;
      if (flag == 0) y = y<<1;
      else y = y>>1;
      xuat_32led_don_4byte(y,y,y,y);
      delay_ms(100);
   }
   return 1;
}

