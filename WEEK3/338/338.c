#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "18F4550.h"

signed int8 tt= 1;


void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   xuat_32led_don_4byte(0,0,0,0);
   
   while(TRUE)
   {
       tt = ttct_td;
       xuat_4led_7doan_2so(ma7doan[tt/10],ma7doan[tt%10]);
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

