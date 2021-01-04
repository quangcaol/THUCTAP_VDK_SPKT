#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "18F4550.h"

unsigned int16 dem;
unsigned int16 donvi,chuc,tram;

void giai_ma_hien_thi(unsigned int16 num){
   donvi = ma7doan[num%10];
   chuc = ma7doan[num/10%10];
   tram = ma7doan[num/100];
   if(tram == 0xc0) {
      tram = 0xff;
      if(chuc == 0xc0) chuc = 0xff;
   }
   //if(chuc=0xc0) chuc = 0xff;
   xuat_4led_7doan_3so(tram,chuc,donvi);
}


void main()
{
   set_up_port_ic_chot();
   setup_timer_0(T0_EXT_L_TO_H|T0_DIV_1|T0_8_BIT);
   set_timer0(0);
   while(TRUE)
   {
      dem = get_timer0();
      giai_ma_hien_thi(dem);
      if(dem>=101) set_timer0(1);
      
   }
}

