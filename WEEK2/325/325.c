#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"


unsigned int16 y = 0;
int1 stat = 0;


void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   xuat_32led_don_4byte(0,0,0,0);
   
   while(true)
   {
      if(!input(UP)) {
         delay_ms(20);
         if(input(UP)) {
            if(!stat) y = (y<<1) | 1 ;
            else y = (y>>1) | 0x8000;
         }
      }
      
      if(!input(DW)) {
         delay_ms(20);
         if(input(DW)){
            if(!stat) y = y>>1;
            else y = y<<1;
         }
      }
      
      if(!input(CLR)) {
         delay_ms(20);
         if(input(CLR)) {
            y = 0;
            stat = ~stat;
         }
      }
      xuat_32led_don_2word(0,y);
   }
}


