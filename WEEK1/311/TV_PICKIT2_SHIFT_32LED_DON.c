unsigned int32    y=0,yp_chay=1,yt_chay=0x80000000,y_codinh=0;
unsigned int16 zt,zt_chay_t=0x8000,zt_chay_p=1,zt_codinh=0;
unsigned int16 zp,zp_chay_t=0x8000,zp_chay_p=1,zp_codinh=0;

unsigned int16 tgdlay=0;
unsigned int8 dem_led=0; 
signed i32=32,j32=0,ttct_td=1,i16=16,j16=0;

unsigned int32    za=1,ya=1,xa=0xfffffffe,zb=0x80000000,yb=0x80000000,xb=0x7fffffff;   
signed ia=1,ja=1;  
void reset_toan_bo_bien()
{ 
      ttct_td++;     //chuyen chuong trinh cho tu dong
      y=0;      yp_chay=1;      yt_chay=0x80000000;      y_codinh=0;
      zt_chay_t=0x8000;    zt_chay_p=1;   zt_codinh=0;
      zp_chay_t=0x8000;    zp_chay_p=1;   zp_codinh=0;
      zt=zp=0;
      i32=32;j32=0;i16=16,j16=0;
      dem_led=0;
      
      za=1;    ya=1;    xa=0xfffffffe;     ia=1;    ja=1;
     zb=0x80000000;    yb=0x80000000;    xb=0x7fffffff;
     tgdlay = 0;
} 

void tang_dem_led_delay_1(unsigned int8 dl)
{ 
      unsigned int8 i;
      for (i=0; i<dl;i++)
      hien_thi_8led_7doan_quet_all();
      dem_led++;
} 

void tang_dem_led_delay_0(unsigned int8 dl)
{ 
      if (dl>0)      delay_ms(dl); 
      dem_led++;
} 

void delay_chon(unsigned int8 dl,chondelay)
{    
   if (!chondelay)   tang_dem_led_delay_0(dl);
   else              tang_dem_led_delay_1(dl);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//32 led: sang don  phai sang trai
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void diem_sang_dich_trai_mat_dan_32led(unsigned int8 dl,chondelay)
{       
   if(ia<33)
   {
      if(ja>0)
      {
         zb = (zb << 1);
         y = xb|zb;        
         xuat_32led_don_1dw(y);
         delay_chon(dl,chondelay);
         ja--;
      }
      else 
      {
         ia++;
         ja=ia;      
         yb = yb>>1;
         xb = xb>>1;
         zb = yb;
      }
   }
   else reset_toan_bo_bien();
}  
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//32 led: sang don  trai sang phai
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void diem_sang_dich_phai_mat_dan_32led(unsigned int8 dl,chondelay)
{       
   if(ia<33)
   {
      if(ja>0)
      {
         za = (za >> 1);
         y = xa|za;        
         xuat_32led_don_1dw(y);
         delay_chon(dl,chondelay);
         ja--;
      }
      else 
      {
         ia++;
         ja=ia;      
         ya = ya<<1;
         xa = xa <<1;
         za = ya;
      }
   }
   else reset_toan_bo_bien();
}  
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//32 led: chop tat 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void dao_dl_32bit_va_xuat()
{
   y=~y;
   xuat_32led_don_1dw(y); 
}
void sang_tat_32led(unsigned int8 dl,chondelay)
{        
      if (tgdlay==1)          xuat_32led_don_1dw(y); 
      else if (tgdlay==50)    dao_dl_32bit_va_xuat();
      else if (tgdlay==100)   dao_dl_32bit_va_xuat();          
      else if (tgdlay==150)   dao_dl_32bit_va_xuat();                 
      else if (tgdlay==200)  
      {
//!         ttct_td++;   y=0;        tgdlay=0;
            reset_toan_bo_bien();
      }
      tgdlay++;
      delay_chon(dl,chondelay);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//32 led: sang dan roi tat dan tu ngoai vao
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void sang_tat_dan_ngoai_vao_32led(unsigned int8 dl,chondelay)
{  
   if (dem_led<16)
   {  
      xuat_32led_don_2word(zp,zt);        
      zp= (zp<<1)+1; 
      zt= (zt>>1)+0x8000;
      delay_chon(dl,chondelay);
   }
   else  if (dem_led<32)
   {  
      xuat_32led_don_2word(zp,zt);
      zp= (zp<<1); 
      zt= (zt>>1);
      delay_chon(dl,chondelay);
   }
   else reset_toan_bo_bien();

}   
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//32 led: sang dan roi tat dan tu trong ra
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void sang_tat_dan_trong_ra_32led(unsigned int8 dl,chondelay)
{  
   if (dem_led<16)
   {   
      xuat_32led_don_2word(zp,zt); 
      zp= (zp>>1)+0x8000; 
      zt= (zt<<1)+1;
      delay_chon(dl,chondelay);
   }
   else  if (dem_led<32)
   {  
      xuat_32led_don_2word(zp,zt);
      zp= (zp>>1); 
      zt= (zt<<1);
      delay_chon(dl,chondelay);
    }
   else reset_toan_bo_bien();
        
}   
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//32 led: 2nhom 16 led sang dan roi tat dan tu phai sang trai
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void sang_tat_dan_phai_sang_trai_2x16led(unsigned int8 dl,chondelay)
{  
   if (dem_led<16)
   {   
      xuat_32led_don_2word(zp,zp);
      zp= (zp>>1)+0x8000;
      delay_chon(dl,chondelay);
   }
   else  if (dem_led<32)
   {  
      xuat_32led_don_2word(zp,zp);
      zp= (zp>>1);
      delay_chon(dl,chondelay);
    }
   else reset_toan_bo_bien();
      
}   
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//32 led: 2nhom 16 led sang dan roi tat dan tu trai sang phai
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void sang_tat_dan_trai_sang_phai_2x16led(unsigned int8 dl,chondelay)
{  
   if (dem_led<16)
   {   
      xuat_32led_don_2word(zt,zt);  
      zt= (zt<<1)+1;
      delay_chon(dl,chondelay);
   }
   else  if (dem_led<32)
   {  
      xuat_32led_don_2word(zt,zt);
      zt= (zt<<1);
      delay_chon(dl,chondelay);
    }
   else reset_toan_bo_bien();
        
}   
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//32 led: sang dan roi tat dan tu phai sang trai
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void sang_tat_dan_pst_32led(unsigned int8 dl,chondelay)
{        
   if (dem_led<32)
   {  
      xuat_32led_don_1dw(y);
      y= (y<<1)+1;
      delay_chon(dl,chondelay);
   }
   else  if (dem_led<64)
   {  
      xuat_32led_don_1dw(y);   
      y= (y<<1); 
      delay_chon(dl,chondelay);
   } 
   else reset_toan_bo_bien();

}    
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//32 led: sang dan roi tat dan tu trai sang phai
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void sang_tat_dan_tsp_32led(unsigned int8 dl,chondelay)
{           
      if (dem_led<32)
      {  
         xuat_32led_don_1dw(y);
         y= (y>>1)+0x80000000; 
         delay_chon(dl,chondelay);      
      }
      else
      if (dem_led<64)
      {  
         xuat_32led_don_1dw(y); 
         y= (y>>1);
         delay_chon(dl,chondelay);
      } 
      else reset_toan_bo_bien();
    
}         
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//32 led: diem sang di chueyn tu phai sang trai
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void diem_sang_di_chuyen_pst_32led(unsigned int8 dl,chondelay)
{        
   if (dem_led==0)
   {  
      y=1;
      xuat_32led_don_1dw(y);
      y= (y<<1);
      delay_chon(dl,chondelay);
   }
   else  if (dem_led<33)
   {  
      xuat_32led_don_1dw(y);   
      y= (y<<1); 
      delay_chon(dl,chondelay);
   } 
   else  reset_toan_bo_bien();
}    

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//32 led: diem sang di chueyn tu trai sang phai
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void diem_sang_di_chuyen_tsp_32led(unsigned int8 dl,chondelay)
{        
   if (dem_led==0)
   {  
      y=0x80000000;
      xuat_32led_don_1dw(y);
      y= (y>>1);
      delay_chon(dl,chondelay);
   }
   else  if (dem_led<33)
   {  
      xuat_32led_don_1dw(y);   
      y= (y>>1); 
      delay_chon(dl,chondelay);
   } 
   else reset_toan_bo_bien();

} 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//32 led: sang don  phai sang trai
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void sang_don_pst_32led(unsigned int8 dl,chondelay)
{       
   if(i32>0)
   {
      if(j32<i32)
      {
         y = y_codinh|yp_chay;
         xuat_32led_don_1dw(y);
         delay_chon(dl,chondelay);       
         yp_chay = yp_chay <<1;
         j32++;
      }
      if (j32==i32) 
      {
         i32--;
         j32=0;         
         y_codinh=y;
         yp_chay = 1;
      }
   }
   else reset_toan_bo_bien();
}   
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//32 led: sang don  phai sang trai
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void sang_don_tsp_32led(unsigned int8 dl,chondelay)
{       
   if(i32>0)
   {
      if(j32<i32)
      {
         y = y_codinh|yt_chay;
         xuat_32led_don_1dw(y);
         delay_chon(dl,chondelay);
         yt_chay = yt_chay >>1;
         j32++;
      }
      if (j32==i32) 
      {
         i32--;
         j32=0;         
         y_codinh=y;
         yt_chay = 0x80000000;
      }
   }
   else reset_toan_bo_bien();

}  
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//32 led: sang don  tu ngoai vao
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void sang_don_tnt_32led(unsigned int8 dl,chondelay)
{       
   if(i16>0)
   {
      if(j16<i16)
      {
         zp = zp_codinh|zp_chay_p;
         zt = zt_codinh|zt_chay_t;
         xuat_32led_don_2word(zt,zp);
         delay_chon(dl,chondelay);

         zp_chay_p = zp_chay_p <<1;         
         zt_chay_t = zt_chay_t >>1;
         j16++;
      }
      if (j16==i16) 
      {
         i16--;
         j16=0;         
         zt_codinh=zt;  zp_codinh=zp;         
         zp_chay_p = 1;   zt_chay_t = 0x8000;
      }
   }
   else reset_toan_bo_bien();

}   

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//32 led: sang don  tu ngoai vao
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void sang_don_ttr_32led(unsigned int8 dl,chondelay)
{       
   if(i16>0)
   {
      if(j16<i16)
      {
         zp = zp_codinh|zp_chay_t;
         zt = zt_codinh|zt_chay_p;
         xuat_32led_don_2word(zt,zp);
         delay_chon(dl,chondelay);
         zp_chay_t = zp_chay_t >>1;         
         zt_chay_p = zt_chay_p <<1;
         j16++;
      }
      if (j16==i16) 
      {
         i16--;
         j16=0;         
         zt_codinh=zt;  
         zp_codinh=zp;
         zp_chay_t = 0x8000;   zt_chay_p = 1;
      }
   }
   else reset_toan_bo_bien();
}   
