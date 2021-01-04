#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "18F4550.h"

signed int8 tt= 1;

void phim_up()
{
    if(!input(up)&&(tt<7))
    {
        delay_ms(10);
        if (!input(up))
        {
            tt++;
            while(!input(up));
        }
        
    }
}
void phim_dw()
{
    if(!input(dw)&&(tt>1))
    {
        delay_ms(10);
        if (!input(dw))
        {
            tt++;
            while(!input(dw));
        }
        
    }
}
void phim_clr()
{
    if(!input(clr)&&(tt>1))
    {
        tt = 1;
        reset_toan_bo_bien();   
    }
}
void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   xuat_32led_don_4byte(0,0,0,0);
   
   while(TRUE)
   {
       xuat_4led_7doan_1so(ma7doan[tt]);
       if(tt==1) sang_tat_32led(10,0);
       if(tt==2) sang_tat_dan_ngoai_vao_32led(10,0);
       if(tt==3) sang_don_pst_32led(10,0);
       if(tt==4) sang_tat_dan_pst_32led(10,0);
       if(tt==5) sang_tat_dan_phai_sang_trai_2x16led(10,0);
       if(tt==6) sang_don_pst_32led(10,0);
       if(tt==7) sang_don_pst_32led(10,0);
       phim_up();
       phim_dw();
       phim_clr();
   }
}

