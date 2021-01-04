#include "TV_PICKIT2_SHIFT_1.c"

unsigned int8 Y;

int main(void) {
   set_up_port_ic_chot();
   y = 1;
   while(true) {
      xuat_32led_don_4byte(y,0,0,0);
      y = y<<1;
      if (y == 0x80) y = 1;
      delay_ms(100);
   }

   return 1;
}

