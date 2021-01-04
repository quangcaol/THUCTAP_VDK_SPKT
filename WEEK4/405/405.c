#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "18F4550.h"

int dem = 0;
int flag = 0;

void main()
{
   set_up_port_ic_chot();
   xuat_4led_7doan_4so(0xff,0xff,0xff,0xff);
   while(TRUE)
   {
      delay_ms(100);
      xuat_4led_7doan_2so(ma7doan[dem/10],ma7doan[dem%10]);
      if (!flag){
         dem++;
         if (dem==59) flag = 1;
      }
      else {
         dem--;
         if (dem == 0) flag = 0;
      }

      
   }
}

