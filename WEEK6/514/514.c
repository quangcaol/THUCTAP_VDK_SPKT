#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "18F4550.h"

signed int8 giay,bdn,phut,gio;

#int_timer1
void interrupt_timer1(){
   bdn++;
   set_timer1(65000); //3036
}

void giai_ma(){
   led_7dq[0] = ma7doan[giay%10];
   led_7dq[1] = ma7doan[giay/10];
   led_7dq[2] = ma7doan[phut%10];
   led_7dq[3] = ma7doan[phut/10];
   led_7dq[4] = ma7doan[gio%10];
   led_7dq[5] = ma7doan[gio/10];
}
void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
   set_timer1(65000); // 3036
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER1);
   giay = 0;
   bdn = 0;
   phut = 0;
   gio = 0;
   while(TRUE)
   {
      giai_ma();
      if (bdn<10) hien_thi_8led_7doan_quet();
      else
      {
         bdn = bdn -10;
         giay++;
         if (giay==60) { giay = 0; phut++;
            if (phut == 60) { phut = 0; gio++; 
               if (gio == 24) gio = 0;
            } 
         }
      }
   }                                 
}

