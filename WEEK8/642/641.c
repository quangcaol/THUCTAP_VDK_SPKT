#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "TV_PICKIT2_SHIFT_LCD.c"
#include "18F4550.h"


const unsigned char hang2[] = {0x11,0xE,0,0,0,0,0,0x1F,0x1F,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1F,0x1F,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1F};


signed int8 giay,bdn,phut,gio,dem_tg_exit = 0;
int8 dem = 0;
int8 dead = 0;
int8 mode = 0;
signed int8 max = 100;
unsigned int8 count = 0,countT = 0;
unsigned int8 donvi = 0;

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
void LCD_DISPLAY() {  
      lcd_goto_xy(3,5);
      printf(lcd_data,"%2d:",gio);
      delay_quet_8led(1);
      printf(lcd_data,"%2d:",phut);
      delay_quet_8led(1);
      printf(lcd_data,"%2d",giay);
      delay_quet_8led(2);
      lcd_goto_xy(2,5);
      lcd_data("ITEMS:");
      lcd_goto_xy(2,11);
      printf(lcd_data,"%3d",count);
      lcd_goto_xy(1,4);
      lcd_data("MAX");
      lcd_goto_xy(1,8);
      printf(lcd_data,"%3d",max);      
}
void LCD_DISPLAY_COUNTER(){
   lcd_goto_xy(2,11);
   printf(lcd_data,"%3d",count);
}

void LCD_DISPLAY_MAX(){
   lcd_goto_xy(1,8);
   printf(lcd_data,"%3d",max);  
}

void LCD_SO_LON(signed int8 lcd_so,x1,y1){
   lcd_goto_xy(x1,y1);
   for (int i = 0; i<6;i++){
      if(i==3) lcd_goto_xy(x1+1,y1);
      lcd_data(lcd_so_x[lcd_so][i]);
   }
}





void tat_2_led_chinh(){
   if (mode == 1) {led_7dq[0] = 0xff; led_7dq[1] = 0xff;}
   else if (mode == 2) {led_7dq[3] = 0xff; led_7dq[4] = 0xff;}
   else if (mode == 3) {led_7dq[6] = 0xff; led_7dq[7] = 0xff;}   
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

   LCD_SO_LON(0,2,0);
   LCD_SO_LON(1,0,0);
   LCD_SO_LON(2,0,3);
   LCD_SO_LON(3,2,3);

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
         count = get_timer0();
         if (count != countT) {
            countT = count;
            xuat_4led_7doan_giaima_xoa_so0(count);
            if (count >= max+1) set_timer0(1);
            LCD_DISPLAY_COUNTER();
         }
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
            if (mp < 10 && donvi <= 2) {
               if (donvi == 0) max = mp;
               if (donvi == 1) max = max*10 + mp;;
               donvi++; 
            }
            else if (mp == 12) {max = 1; donvi = 0;}
            LCD_DISPLAY_MAX();
         }         

      }
      else 
      {
         bdn = bdn -10;
         dem_tg_exit++;
         if (dem_tg_exit == 20) mode = 0; giay++;
            if (giay==60) { giay = 0; phut++;
               if (phut == 60) { phut = 0; gio++; 
                  if (gio == 24) gio = 0;
               } 
            }
         LCD_DISPLAY();
         giai_ma();
      }
   }           
}

