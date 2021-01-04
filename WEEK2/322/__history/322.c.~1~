#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"

void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   xuat_32led_don_4byte(0,0,0,0);
   while(true)
   {
      while(input(bt0));
      xuat_32led_don_4byte(0,0,0,0xff);
      while(input(bt1));
      xuat_32led_don_4byte(0,0,0,0);
   }
}
