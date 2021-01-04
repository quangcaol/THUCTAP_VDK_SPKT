#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "TV_PICKIT2_SHIFT_LCD.c"
#include "TV_PICKIT2_SHIFT_GLCD128X64.c"
#include "18F4550.h"
#include <graphics.c>


const unsigned char hang2[] = {0x11,0xE,0,0,0,0,0,0x1F,0x1F,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1F,0x1F,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1F};

unsigned char Clock[8],SHOW[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

signed int8 giay,bdn,phut,gio,dem_tg_exit = 0;
int8 dem = 0;
int8 mode = 1;
int8 convert = 0;
signed int8 max = 100,D,C;
unsigned int8 count = 0,countT = 0;
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
   Clock[0] = ma7doan[giay%10];
   Clock[1] = ma7doan[giay/10];
   Clock[2] = ma7doan[phut%10];
   Clock[3] = ma7doan[phut/10];
   Clock[4] = ma7doan[gio%10];
   Clock[5] = ma7doan[gio/10];
   for (int n = 0; n<8;n++){
      SHOW[n+1] = Clock[n];
   }
   Clock[7] = SHOW[0];
   led_7dq[0] = SHOW[0];
   led_7dq[1] = SHOW[1];
   led_7dq[2] = SHOW[2];
   led_7dq[3] = SHOW[3];
   led_7dq[4] = SHOW[4];
   led_7dq[5] = SHOW[5];
   led_7dq[6] = SHOW[6];
   led_7dq[7] = SHOW[7];
   led_7dq[8] = SHOW[8];

}

void phim_mode() {
   lcd_command(lcd_addr_line2);
   if (mode&0x1) lcd_data("DANG DEM ");
   else
   {
      lcd_data("DANG DUNG");
   }
}

void Xoa_So_Lon(){
   lcd_command(lcd_addr_line3);
   lcd_data("      ");
   lcd_command(lcd_addr_line4);
   lcd_data("      ");
}

void LCD_DISPLAY_COUNTER(){
   if (count%2 == 0) {
      D = count/10;
      C = count%10;
      LCD_SO_LON(D,2,0);
      LCD_SO_LON(C,2,3);
   }
   else {
      Xoa_So_Lon();
      lcd_command(lcd_addr_line3);
      printf(lcd_data,"%2d",count);
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

   lcd_command(lcd_addr_line1);
   lcd_data("QUANG CAO");
   lcd_command(lcd_addr_line2);
   lcd_data("DANG DEM");



   xuat_4led_7doan_4so(0xF0,0xF0,0xF0,0xF0);   

   setup_timer_0(T0_EXT_L_TO_H|T0_DIV_1);
   set_timer0(0);   
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   set_timer1(3036); // 3036
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER1);


   giay = 30;
   bdn = 0;
   phut = 29;
   gio = 15;
   giai_ma();
   while(TRUE)
   {
      if (bdn<10) {
         hien_thi_8led_7doan_quet_all();
         if (mode & 0x1) {    
         count = get_timer0();
         if (count != countT) {
            countT = count;         
            LCD_DISPLAY_COUNTER();
            if (count >= max+1) {set_timer0(1);}   
         }
         }
         else set_timer0(count);
         phim_mode();
         if(ttct_td==1) sang_tat_32led(5,1);
         if(ttct_td==2) sang_tat_dan_ngoai_vao_32led(5,1);
         if(ttct_td==3) sang_don_pst_32led(5,1);
         if(ttct_td==4) sang_tat_dan_pst_32led(5,1);
         if(ttct_td==5) sang_tat_dan_phai_sang_trai_2x16led(5,1);
         if(ttct_td==6) sang_don_pst_32led(5,1);
         if(ttct_td==7) sang_don_pst_32led(5,1);
         if(ttct_td==8) sang_tat_32led(5,1);
         if(ttct_td==9) sang_tat_dan_ngoai_vao_32led(5,1);
         if(ttct_td==10) sang_don_pst_32led(5,1);
         if(ttct_td==11) sang_tat_dan_pst_32led(5,1);
         if(ttct_td==12) sang_tat_dan_phai_sang_trai_2x16led(5,1);
         if(ttct_td==13) sang_tat_dan_pst_32led(5,1);
         if(ttct_td==14) sang_tat_dan_tsp_32led(5,1);
         if(ttct_td==15) sang_don_pst_32led(5,1);
         if(ttct_td>15) ttct_td =1;
         signed int8 mp = key_4x4_dw();
         if (mp != 0xFF ) {
            if (mp < 10) {
               if (donvi == 0) max = mp;
               if (donvi == 1) {max = max*10 + mp; donvi=0; }
               donvi++; 
            }
            else if (mp == 12) {max = 1; donvi = 0;}
            else if (mp == 13) { mode = !mode ;}
            //else if (mp == 14) {convert = !convert; Xoa_So_Lon(); LCD_DISPLAY_COUNTER();}
            xuat_4led_7doan_giaima_xoa_so0(max);
         }         
      }
      else 
      {
         bdn = bdn -10;
         giay++;
            if (giay==60) { giay = 0; phut++;
               if (phut == 60) { phut = 0; gio++; 
                  if (gio == 24) gio = 0;
               } 
            }
         giai_ma();
      }
   }           
}

