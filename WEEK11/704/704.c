#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "TV_PICKIT2_SHIFT_LCD.c"
#include "TV_PICKIT2_SHIFT_GLCD128X64.c"
#include "18F4550.h"
#include <math.h>
#include <graphics.c>


const unsigned char hang2[] = {0x11,0xE,0,0,0,0,0,0x1F,0x1F,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1F,0x1F,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1F};


signed int8 giay,bdn,phut,gio,dem_tg_exit = 0;
int8 dem = 0;
int8 dead = 0;
int8 mode = 0;
float temp = 0, lm35 = 0;
int try = 0;
int1 ttqn = 0;
float M,N;
signed int8 max = 120,D,C;
unsigned int8 count = 0,countT = 0;
unsigned int8 donvi = 0;

#int_timer1
void interrupt_timer1(){
   bdn++;
   set_timer1(3036); //3036
}

void draw(int8 Number) {
   glcd_line(64,32,(int)M,(int)N,0);
   M = 64+31*cos(Number*0.104-1.57);
   N = 31+31*sin(Number*0.104-1.57);   
   glcd_line(64,32,(int)M,(int)N,1);
   gdram_vdk_to_gdram_glcd_area(32,0,64,64);
   setup_glcd(glcd_text_mode);
   glcd_command(glcd_addr_line1);
   printf(glcd_data,"%d",gio);
   glcd_command(glcd_addr_line2);
   printf(glcd_data,"%d",phut);
   glcd_command(glcd_addr_line3);   
   printf(glcd_data,"%d",giay);
   setup_glcd(glcd_graphic_mode);    
}

void BaoChay(){
   if ((lm35>40) && (ttqn==0)){
      ttqn = 1;
      triac_2_off();
   }
   if ((lm35<40)&&(ttqn==1)){
      ttqn = 0;
      triac_2_on();
   }
}

void LCD_SO_LON(signed int8 lcd_so,x1,y1){
   lcd_goto_xy(x1,y1);
   for (int i = 0; i<6;i++){
      if(i==3) lcd_goto_xy(x1+1,y1);
      lcd_data(lcd_so_x[lcd_so][i]);
   }
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
   lcd_command(lcd_addr_line4);
   printf(lcd_data,"%.1f",lm35);
}

void LCD_DISPLAY_COUNTER(){
   D = count/10;
   C = count%10;
   LCD_SO_LON(D,1,0);
   LCD_SO_LON(C,1,3);
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
   setup_glcd(glcd_graphic_mode);

   glcd_mau_nen(0);
   glcd_circle(64,32,31,0,1);
   gdram_vdk_to_gdram_glcd_all();


   lcd_command(0x40);
   for (int i = 0; i<64;i++){
      lcd_data(lcd_ma_8doan[i]);
   }

   lcd_command(lcd_addr_line1);
   lcd_data("**DEM SAN PHAM** ");

   setup_adc(ADC_CLOCK_DIV_32);
   setup_adc_ports(an0|VSS_VDD);
   set_adc_channel(0);

   setup_timer_0(T0_EXT_L_TO_H|T0_DIV_1);
   set_timer0(0);   
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   set_timer1(3036); // 3036
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER1);


   giay = 0;
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
            LCD_DISPLAY_COUNTER();
            if (count >= max+1) {set_timer0(1);}   
         }
         BaoChay();
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
      }
      else 
      {
         bdn = bdn -10;
         dem_tg_exit++;
         if (dem_tg_exit == 20) mode = 0; 
         giay++; 
         draw(giay); 
         temp = temp + read_adc(); 
         try++; 
         delay_ms(1);
         if (try == 2) {
            lm35 = temp /2.046; 
            lm35 = lm35 /2; 
            try = 0; 
            temp = 0;
            xuat_4led_7doan_giaima_xoa_so0((int)lm35);
            }
            if (giay==60) { giay = 0; phut++;
               if (phut == 60) { phut = 0; gio++; 
                  if (gio == 24) gio = 0;
               } 
            }
         giai_ma();
      }
   }           
}

