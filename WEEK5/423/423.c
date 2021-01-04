#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "18F4550.h"

#define dot 16


signed int8 mp;
unsigned int8 n1 =dot,n2 = dot,n3 = dot,n4 = dot;
unsigned int8 pos = 1;



void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   xuat_4led_7doan_4so(n1,n2,n3,n4);
   while(TRUE)
   {
      mp = key_4x4_dw();
      if (mp!=0xff) {
         n4 = n3;
         n3 = n2;
         n2 = n1;
         n1 = mp;
         delay_ms(200);
      }
      xuat_4led_7doan_4so(ma7doan[n1],ma7doan[n2],ma7doan[n3],ma7doan[n4]);

   }
}

