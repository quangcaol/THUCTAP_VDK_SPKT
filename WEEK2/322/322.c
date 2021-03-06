#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"

void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   xuat_32led_don_4byte(0,0,0,0);
   unsigned int8 y = 0xf;
   
   while(true)
   {
      while(input(ON));
      xuat_32led_don_4byte(0,0,0,y);
      while(input(OFF));
      xuat_32led_don_4byte(0,0,0,0);
      if(input(INV)) {
         while(INPUT(INV));
         y = ~y;
      }
   }
}
