#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "18F4550.h"

#define dot 16


signed int8 mp;
unsigned int8 digit[8] = {dot,dot,dot,dot,dot,dot,dot,dot};

void reset() {
   for (int i = 0; i<8;i++) {
      digit[i] = dot;
   }
}
void undo(){
   for(int i = 0; i<7; i++){
      digit[i] = digit[i+1];
   }
   digit[7] = dot;
}
void swapVar(int last){
   for(int i = 7; i>0 ; i--) {
      digit[i] = digit[i-1];
   }
   digit[0] = last;
}


void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   xuat_4led_7doan_4so(ma7doan[digit[3]],ma7doan[digit[2]],ma7doan[digit[1]],ma7doan[digit[0]]);
   while(TRUE)
   {
      mp = key_4x4_dw();
      if( mp != 0xff ) {
      if (mp == 12){
         reset();
      } 
      if (mp == 11){
         undo();
      }
      if(mp<10){
         swapVar(mp);
      }
      delay_ms(100);
      xuat_4led_7doan_4so(ma7doan[digit[3]],ma7doan[digit[2]],ma7doan[digit[1]],ma7doan[digit[0]]);
      }
   }
}

