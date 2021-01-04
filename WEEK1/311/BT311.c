#include "TV_PICKIT2_SHIFT_1.c"
#include <stdint.h>



unsigned int32 Y,Y1;
int8 flag = 1,flag1 =1;
int8 stat = 1;

void left_to_right_reserver() {
   if (stat == 1){
      if ((y == 0xFFF00)) { y1 =0xFFF00; stat++;}   //if ((y == 0xFFF00) ||  (y == 0)) { flag = ~flag;}
      if (0x1) {                            //if (flag & 0x1) {
         y = (y << 1) | 0x100; }
      else {
         y = 0;}   //y = y<<1;
      xuat_32led_don_2word( 0xF & (y>>16),y);
      delay_ms(30);
   }
}

void left_to_right_reserver_off() {
   if (stat == 2) {
      if ((y1 == 0xFF00000)) { y = 0; stat++;}
      if (0x1) {
         y1 = (y1 << 1) & 0xFFFFFFE; }
      else {
         y1 = 0;}   //y = y<<1;
      xuat_32led_don_2word(0xF &(y1>>16),y1);
      delay_ms(30);
   }
}   

void convert_number(int number){
   int8 donvi = number%10;
   int8 chuc = number/10;
   int16 Z1 = 0;
   int16 Z = 0;
   for (int x = 1; x<=donvi;x++) {
      Z = Z<<1;
      Z = Z | 1;
   }
   for (int x = 1; x<=chuc;x++) {
      Z1 = Z1<<1;
      Z1 = Z1 | 1;
   }
   xuat_32led_don_2word(Z1,Z);

}




int main(void) {
   set_up_port_ic_chot();
   y = 0;
   y1 = 0xFFFE;
   while(true) {
      convert_number(y);
      delay_ms(100);
      y++;
   }
   return 1;
}

