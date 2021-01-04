#include "18F4550.h"
#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "TV_PICKIT2_SHIFT_LCD.c"
#include "TV_PICKIT2_SHIFT_GLCD128X64.c"
#include "TV_PICKIT2_SHIFT_STEP_MOTOR.c"
#include "TV_PICKIT2_SHIFT_DC_MOTOR.c"
#include <math.h>
#include <graphics.c>




unsigned char DichTrai[4] = {ma7doan[16],ma7doan[16],ma7doan[16],ma7doan[16]};


unsigned char text[10];
signed int8 max = 13,D,C,giay,bdn;
unsigned int8 count = 0,countT = 0,donvi = 0;
unsigned int8 preKey, preDis,Pretem;
unsigned int16 distance, tem;
float tempo;
unsigned int16 step = 0, maxstep = 0, prestep, number;







void READ_BTN()
{
   prestep = step;
   unsigned int8 key = key_4x4_dw();
   if (key!=0xff)
   {
      if (key == 1)
      {
         stepmotor_tn= 0;
         step = 1;
      }
      if (key == 2)
      {
         stepmotor_tn= 0;
         step = 2;
      }
      if (key == 3)
      {
         stepmotor_tn= 0;
         step = 3;
      }
      if (key == 4)
      {
         stepmotor_tn= 0;
         step = 4;
      }
      if (key == 5)
      {
         stepmotor_tn= 1;
         step = 1;
      }
      if (key == 6)
      {
         stepmotor_tn= 1;
         step = 2;
      }
      if (key == 7)
      {
         stepmotor_tn= 1;
         step = 3;
      }
      if (key == 8)
      {
         stepmotor_tn= 1;
         step = 4;
      }
      maxstep = step;
   }
}

void LCD_SO_LON(signed int8 lcd_so,x1,y1){
   lcd_goto_xy(x1,y1);
   for (int i = 0; i<6;i++){
      if(i==3) lcd_goto_xy(x1+1,y1);
      lcd_data(lcd_so_x[lcd_so][i]);
   }
}

void DISPLAY_GLCD()
{
   glcd_bar(20,24,20+2*count,24,7,1);
   glcd_bar(20,44,count*2+20,44,7,1);
   delay_quet_8led(5);
   gdram_vdk_to_gdram_glcd_area(20,24,50,10);
}

void CLEAR_GLCD()
{
   glcd_bar(20,24,20+2*count,24,7,0);
   glcd_bar(20,44,20+2*count,44,7,0);
   gdram_vdk_to_gdram_glcd_area(20,24,50,10);
   delay_quet_8led(5);
}

void XOA_SO_LON(signed int8 x1,y1){
   lcd_goto_xy(x1,y1);
   lcd_data("      ");
   lcd_goto_xy(x1+1,y1);
   lcd_data("      ");
   lcd_goto_xy(x1,y1+2);
   lcd_data("      ");
   lcd_goto_xy(x1+1,y1+2);
   lcd_data("      ");
}

void XOA_SO_1_LON(signed int8 x1,y1){
   lcd_goto_xy(x1,y1);
   lcd_data("      ");
   lcd_goto_xy(x1+1,y1);
   lcd_data("      ");
}

void DISPLAY_8SEVSEG()
{
   led_7dq[0] = ma7doan[Count%10];
   led_7dq[1] = ma7doan[Count/10];

   led_7dq[4] = ma7doan[Count%10];
   led_7dq[5] = ma7doan[Count/10];
}

void LCD_DISPLAY_COUNTER(){
   sprintf(text,"%d",count);
   glcd_mau_nen(0);
   glcd_circle(32,32,30,0,1);
   glcd_text57(15,20,text,3,1);
   gdram_vdk_to_gdram_glcd_all();
}

unsigned int16 READ_TEMP()
{
   unsigned int16 lm35a;
   set_adc_channel(0);
   lm35a = read_adc();
   delay_quet_8led(2);
   lm35a = lm35a/2.046;
   return lm35a;
}

float READ_DISTANCE()
{
   float k_cach;
   unsigned int16 kqadc;
   set_adc_channel(2);
   kqadc = read_adc();
   delay_quet_8led(10);
   k_cach = pow(4277/kqadc,1.106);
   if (k_cach>80) k_cach=80;
   return k_cach;
}

unsigned int16 DECODE(float tem)
{
   unsigned int16 x;
   x = (unsigned int16) tem;
   return x;
}

void DISPLAY_TEMP()
{
   if (distance <43)
   {
      XOA_SO_LON(2,0);
      lcd_goto_xy(2,0);
      printf(lcd_data,"%ld",tem);
   }
   else
   {
      Xoa_So_Lon(2,0);
      LCD_SO_LON(tem/10,2,0);
      LCD_SO_LON(tem%10,2,3);
   }
}

void DISPLAY_DIS()
{
   if (distance <43)
   {
      XOA_SO_LON(2,14);
      LCD_SO_LON(distance/10,2,14);
      LCD_SO_LON(distance%10,2,17);
   }
   else
   {
      Xoa_So_Lon(2,14);
      lcd_goto_xy(2,14);
      printf(lcd_data,"%ld",distance);
   }
}

void DISPLAY_STEP()
{
   XOA_SO_1_LON(2,8);
   LCD_SO_LON(step,2,8);
}

void RUN_STEP()
{
   motor_step_run_fs();
   number++;
   delay_ms(stepmotor_delay);
   if (number == 200) {prestep = step; step--; number = 0; DISPLAY_STEP();}
}

void RUN_DC()
{
   if (count >= 3 && count<= 13)
   {
      dc_motor_quay_thuan();
   }
   else if(count >= 15 && count<= 25)
   {
      dc_motor_quay_nghich();
   }
   else
   {
      dc_motor_stop();
   }
   
}

#int_timer1
void interrupt_timer1(){
   bdn++;
   set_timer1(10000); //3036
         if (step > 0)
         {
            RUN_STEP();
         }
         else
         {
            disable_interrupts(INT_TIMER1);
         }
}

void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   setup_adc(ADC_CLOCK_DIV_16);
   setup_adc_ports(AN0_TO_AN2|VSS_VDD);

   setup_lcd();


   lcd_command(0x40);
   for (int i = 0; i<64;i++){
      lcd_data(lcd_ma_8doan[i]);
   }


   //LCD_DISPLAY_COUNTER();
   xuat_4led_7doan_4so(ma7doan[16],ma7doan[16],ma7doan[16],ma7doan[16]);  


   setup_glcd(glcd_graphic_mode);

   glcd_mau_nen(0);
   gdram_vdk_to_gdram_glcd_all();
   glcd_circle(32,32,30,0,1);
   gdram_vdk_to_gdram_glcd_all();


   setup_timer_0(T0_EXT_L_TO_H|T0_DIV_1);
   set_timer0(0);   
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
   set_timer1(10000); // 3036
   enable_interrupts(GLOBAL);
   disable_interrupts(INT_TIMER1);
   dc_motor_enable();

   bdn = 0;
   preKey = 0;
   preDis = 0;
   Pretem = 0;

   stepmotor_onoff = 1;
   stepmotor_delay = 1;
   while(TRUE)
   {  
      if (bdn<2) {
         tempo= READ_DISTANCE();
         distance = DECODE(tempo);
         tem = READ_TEMP();
         if (distance != preDis)
         {
            DISPLAY_DIS();
            preDis = distance;
         }
         if (tem !=Pretem || distance != preDis)
         {
            DISPLAY_TEMP();
            Pretem = tem;
         }
         count = get_timer0();
         if (count != countT) {
            countT = count;
            LCD_DISPLAY_COUNTER();
            RUN_DC();
            if (count >= 30) {set_timer0(1);}  
         }
         if (step == 0)
         {
            READ_BTN();
            enable_interrupts(INT_TIMER1);
            if (step != prestep) DISPLAY_STEP();
         }  
      }
      else 
      {
         bdn = bdn -2;
         xuat_4led_7doan_giaima_xoa_so0(bdn);
       }
   }

}