#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "TV_PICKIT2_SHIFT_32LED_DON.c"
#include "TV_PICKIT2_SHIFT_LCD.c"
#include "TV_PICKIT2_SHIFT_GLCD128X64.c"
#include "TV_PICKIT2_SHIFT_DS18B20.c"
#include "18F4550.h"
#include <math.h>
#include <graphics.c>


void main(){
   set_up_port_ic_chot();
   khoi_tao_ds18b20();
   ds18a_tam = 0;
   xuat_4led_7doan_giaima_xoa_so0(0);
   while(TRUE){
      if(touch_present()) {doc_giatri_ds18b20();}
      if (ds18al != ds18a_tam) {
         ds18a_tam = ds18al;
         ds18a = ds18a>>4;
         ds18a = ds18a & 0x0ff;
         xuat_4led_7doan_giaima_xoa_so0(ds18a);
      }
   }
}