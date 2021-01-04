#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "18F4550.h"



void main()
{
   set_up_port_ic_chot();
   xuat_4led_7doan_4so(0xb0,0xa4,0xf9,0xc0);
   while(TRUE)
   {
   }
}

