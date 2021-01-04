#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "18F4550.h"

signed int8 giay,bdn,phut,gio;
int8 mode = 1,Up1 = 0, Dw1 = 0;


#int_timer1
void interrupt_timer1(){
   bdn++;
   set_timer1(3036); //3036
}

void giai_ma(){
   led_7dq[0] = ma7doan[giay%10];
   led_7dq[1] = ma7doan[giay/10];
   led_7dq[3] = ma7doan[phut%10];
   led_7dq[4] = ma7doan[phut/10];
   led_7dq[6] = ma7doan[gio%10];
   led_7dq[7] = ma7doan[gio/10];
   if (mode == 1) led_7dq[0] = led_7dq[0] & 0x7f;
   else if (mode == 2) led_7dq[3] = led_7dq[3] & 0x7f;
   else if (mode == 3) led_7dq[6] = led_7dq[6] & 0x7f;
}

void phim_up(){
   if (!input(up)) {
      delay_quet_8led(20);
      if (!input(up)) {
         Up1 = 1;
      giai_ma();
      do { hien_thi_8led_7doan_quet();}         
      while (!input(up));      
      }
   }
}

void phim_dw(){
   if (!input(dw)) {
      delay_quet_8led(20);
      if (!input(dw)) {
         Dw1 = 1;
      }
      giai_ma();
      do { hien_thi_8led_7doan_quet(); }
      while(!input(dw));
   }
}

void phim_mode(){
   if (!input(mod)) {
      delay_quet_8led(20);
      if (!input(mod)) {
         mode++;
         disable_interrupts(INT_TIMER1);
         if (mode  == 4){
            mode = 0;
            enable_interrupts(INT_TIMER1);
         }
      giai_ma();
      do { hien_thi_8led_7doan_quet();}   
      while(!input(mod));

      }
   }
}

void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   set_timer1(3036); // 3036
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER1);
   giay = 0;
   bdn = 0;
   phut = 0;
   gio = 0;
   while(TRUE)
   {
      phim_mode();
      giai_ma();
      if (mode == 0) {
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
      if (mode == 1){
         phim_up();
         phim_dw();
         if (Up1 == 1) {
            giay++;
            Up1 = 0;
         }
         if (Dw1 == 1){
            giay--;
            Dw1 = 0;
         }
         if (giay < 0) giay = 0;
         if (giay >59) giay = 59;
         giai_ma();
         hien_thi_8led_7doan_quet();
      }
      if (mode == 2){
         phim_up();
         phim_dw();
         if (Up1 == 1) {
            phut++;
            Up1 = 0;
         }
         if (Dw1 == 1){
            phut--;
            Dw1 = 0;
         }
         if (phut < 0) phut = 0;
         if (phut >59) phut = 59;
         giai_ma();
         hien_thi_8led_7doan_quet();
      }
      if (mode == 3){
         phim_up();
         phim_dw();
         if (Up1 == 1) {
            gio++; 
            Up1 = 0;
         }
         if (Dw1 == 1){
            gio--;
            Dw1 = 0;
         }
         if (gio < 0) gio = 0;
         if (gio >24) gio = 24;
         giai_ma();
         hien_thi_8led_7doan_quet();
      }            
   }                                 
}

