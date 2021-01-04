#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "18F4550.h"

int16 dem = 0;
int flag = 0;

void main()
{
   set_up_port_ic_chot();
   xuat_4led_7doan_4so(0xff,0xff,0xff,0xff);
   while(TRUE)
   {
      delay_ms(100);
      if (!flag){
         dem++;
         xuat_4led_7doan_3so(ma7doan[dem/100],ma7doan[(dem/10)%10],ma7doan[dem%10]);
         if (dem==999) {flag = 1; delay_ms(3000);}
      }
      else {
         dem--;
         xuat_4led_7doan_3so(ma7doan[dem/100],ma7doan[(dem/10)%10],ma7doan[dem%10]);
         if (dem == 0) {flag = 0; delay_ms(3000);}
      }

      
   }
}

