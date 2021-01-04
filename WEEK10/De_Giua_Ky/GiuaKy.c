#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "TV_PICKIT2_SHIFT_LCD.c"
#include "TV_PICKIT2_SHIFT_GLCD128X64.c"
#include "18F4550.h"
#include <graphics.c>


const unsigned char hang2[] = {0x11,0xE,0,0,0,0,0,0x1F,0x1F,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1F,0x1F,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1F};

unsigned char DichTrai[4] = {ma7doan[16],ma7doan[16],ma7doan[16],ma7doan[16]};

signed int8 giay,bdn;
signed int8 u,v;
int8 mode = 1;
int8 shift = 0;
signed int8 max = 13,D,C;
unsigned int8 count = 3,countT = 0;
unsigned int8 donvi = 0;

#int_timer1
void interrupt_timer1(){
   bdn++;
   set_timer1(3036); //3036
}




void LCD_SO_LON(signed int8 lcd_so,x1,y1){
   lcd_goto_xy(x1,y1);
   for (int i = 0; i<6;i++){
      if(i==3) lcd_goto_xy(x1+1,y1);
      lcd_data(lcd_so_x[lcd_so][i]);
   }
}

void giai_ma(){
   led_7dq[v] = ma7doan[giay%10];
   led_7dq[u] = ma7doan[giay/10];
}

void switch_mode() {
   if (mode == 2) {
      setup_timer_0(T0_EXT_L_TO_H|T0_DIV_2);
   }
   if (mode == 3) {
      setup_timer_0(T0_EXT_L_TO_H|T0_DIV_4);
   }
}

void Dich_Trai(){
   for (int i = 3; i >= 1;i--) {
      DichTrai[i] = DichTrai[i-1];
   }
}
void Dich_Phai(){
   for (int i = 0; i < 3;i++) {
      DichTrai[i] = DichTrai[i+1];
   }
}

void Xoa_So_Lon(){
   lcd_command(lcd_addr_line1);
   lcd_data("      ");
   lcd_command(lcd_addr_line2);
   lcd_data("      ");
}

void LCD_DISPLAY_COUNTER(){
   if (mode == 1) {
      Xoa_So_Lon();
      xuat_32led_don_2word(0,0);
      lcd_command(lcd_addr_line1);
      printf(lcd_data,"%d ",count);      
   }
   if (mode == 2) {
      Xoa_So_Lon();
      D = count/10;
      C = count%10;
      LCD_SO_LON(D,0,0);
      lcd_goto_xy(0,3);
      lcd_data(C+0x30);
      xuat_32led_don_2word(0,0xFFFF);
   }
   if (mode==3){
      Xoa_So_Lon();
      D = count/10;
      C = count%10;
      lcd_command(lcd_addr_line1);
      lcd_data(D+0x30); 
      LCD_SO_LON(C,0,1);
      xuat_32led_don_2word(0xFFFF,0);                
   }
}

void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   setup_lcd();


   lcd_command(0x40);
   for (int i = 0; i<64;i++){
      lcd_data(lcd_ma_8doan[i]);
   }


   switch_mode(); LCD_DISPLAY_COUNTER();
   xuat_4led_7doan_4so(ma7doan[16],ma7doan[16],ma7doan[16],ma7doan[16]);   

   setup_timer_0(T0_EXT_L_TO_H|T0_DIV_1);
   set_timer0(3);   
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   set_timer1(3036); // 3036
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER1);

   u = 4;
   v = 3;
   giay = 4;
   bdn = 0;
   giai_ma();
   while(TRUE)
   {
      if (bdn<10) {
         hien_thi_8led_7doan_quet_all();
         if (mode>1) {    
         count = get_timer0();
         if (count != countT) {
            countT = count;         
            LCD_DISPLAY_COUNTER();
            if (count >= max+1) {set_timer0(3);}   
         }
         }
         else set_timer0(count);
         signed int8 mp = key_4x4_dw();
         if (mp != 0xFF ) {
            if (mp < 10) {
               if (!shift&1) {
               Dich_Trai();
               DichTrai[0] = ma7doan[mp];
               }
               else {
                  Dich_Phai();
                  DichTrai[3] = ma7doan[mp];
               }
            }
            else if (mp == 10) {
               mode++; 
               if (mode > 3) 
               {  
                  mode = 1; 
               } 
               switch_mode(); 
               LCD_DISPLAY_COUNTER();
            }
            else if (mp ==11) {
               led_7dq[u] = 0xFF;
               led_7dq[v] = 0xFF;
               u++;
               v++;
               if (u > 7) {
                  u = 0;
               }
               if (v > 7) {
                  v = 0;
               }
            }
            else if (mp ==12)
            {
               led_7dq[u] = 0xFF;
               led_7dq[v] = 0xFF;               
               u--;
               v--;
               if (u < 0) {
                  u = 7;
               }
               if (v < 0) {
                  v = 7;
               }               
            }
            else if (mp ==14){
               shift = !shift;
            }
            delay_quet_8led(2);
            xuat_4led_7doan_4so(DichTrai[3],DichTrai[2],DichTrai[1],DichTrai[0]);
         }         
      }
      else 
      {
         bdn = bdn -10;
         giay++;
            if (giay==36) { 
               giay = 4;
            } 
         giai_ma();
         hien_thi_8led_7doan_quet_all();         
      }
   }           
}

