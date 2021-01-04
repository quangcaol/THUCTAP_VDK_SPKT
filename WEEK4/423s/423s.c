#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "18F4550.h"

unsigned int16 dem = 0;
int16 temp = 0;
unsigned int flag=1;
int8 tt = 0;
tt = temp = 10;


void phim_on() {
   if(!input(on)){
      delay_ms(20);
      while (!input(on))
      flag = 1;
      //xuat_32led_don_4byte(0xff,0xff,0xff,0xff);
   }
}



void phim_off() {
   if(!input(off)){
      delay_ms(20);
      while (!input(off))
      flag = 0;
      //xuat_32led_don_4byte(0,0,0,0);
   }
}


void main()
{
   setup_timer_0(T0_EXT_H_TO_L|T0_DIV_1);
   set_timer0(0);
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   while(TRUE)
   {
      phim_on();
      phim_off();
      if (flag==1) {
         if (temp != get_timer0()) {
            int16 temp1 = get_timer0();
            int16 delta = temp1 - temp;
            temp = temp1;
            dem = dem+delta;
            if(dem>=1000) {set_timer0(0); dem=1000; temp = 1000; delta = 0;}
            xuat_4led_7doan_giaima_xoa_so0(dem);
         }
      }
      else
      {
            if (temp != get_timer0()) {
            int16 temp1 = get_timer0();
            int16 delta = temp1 - temp;
            temp = temp1;
            if(dem == 0) {set_timer0(0); dem=0; temp =0; delta = 0;}
            dem = dem-delta;
            xuat_4led_7doan_giaima_xoa_so0(dem);
         }
      }
      tt = ttct_td;
      if(tt==1) sang_tat_32led(10,0);
      if(tt==2) sang_tat_dan_ngoai_vao_32led(10,0);
      if(tt==3) sang_don_pst_32led(10,0);
      if(tt==4) sang_tat_dan_pst_32led(10,0);
      if(tt==5) sang_tat_dan_phai_sang_trai_2x16led(10,0);
      if(tt==6) sang_don_pst_32led(10,0);
      if(tt==7) sang_don_pst_32led(10,0);
      if(tt==8) sang_tat_32led(10,0);
      if(tt==9) sang_tat_dan_ngoai_vao_32led(10,0);
      if(tt==10) sang_don_pst_32led(10,0);
      if(tt==11) sang_tat_dan_pst_32led(10,0);
      if(tt==12) sang_tat_dan_phai_sang_trai_2x16led(10,0);
      if(tt==13) sang_don_pst_32led(10,0);
      if(tt==14) sang_don_pst_32led(10,0);
      if(tt==15) sang_don_pst_32led(10,0);
      if(tt>15) ttct_td =1;
   }
}

