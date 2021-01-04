unsigned int8 glcd_control;  
#bit glcd_p    = glcd_control.5
#bit glcd_rs   = glcd_control.4
#bit glcd_rw   = glcd_control.3
#bit glcd_e    = glcd_control.2
#bit glcd_cs2  = glcd_control.1
#bit glcd_cs1  = glcd_control.0

//#define glcd_function_set       0x30
#define glcd_text_mode          0x30
#define glcd_graphic_mode       0x36 

#define glcd_clear_display      0x01
#define glcd_cursor_display     0x0c
#define glcd_entry_mode         0x06


#define glcd_addr_line1         0x80
#define glcd_addr_line2         0x90
#define glcd_addr_line3         0x88
#define glcd_addr_line4         0x98

void glcd_xuat_8bit(int8 glcd_data1)
{
      glcd_e=1; xuat_glcd128x64(glcd_control,glcd_data1);     
      glcd_e=0; xuat_glcd128x64(glcd_control,glcd_data1); 
}

void glcd_command(int8 glcd_data2)   
  {
      glcd_rs = 0;
      glcd_xuat_8bit(glcd_data2);      
  }
void glcd_data(int8 glcd_data3)       
  {
      glcd_rs = 1;     
      glcd_xuat_8bit(glcd_data3);     
  }
  
  void glcd_data_x(int8 glcd_data3)
{
      glcd_rs = 1;     
      glcd_xuat_8bit(0xa1);
      glcd_xuat_8bit(0x40);  
}
void setup_glcd (int8 glcd_function_set_mode)
{                     
         glcd_cs1 = 1;
         glcd_cs2 = 1;
         glcd_e  = 0;
         glcd_rw = 0;          
         glcd_p =0;         
         glcd_command(glcd_function_set_mode);         
         delay_us(10);
         glcd_command(glcd_cursor_display);       
         delay_us(10);    
         glcd_command(glcd_clear_display);      
         delay_ms(2);
         glcd_command(glcd_entry_mode);      
         delay_us(10);                          
}

#define glcd_ngang     16 //256 pixel
#define glcd_doc       32 //32 hang
#define glcd_width     128 //danh cho thu vien graphic.c
int8 doc, ngang;

typedef union 
{ 
  unsigned int16 word; 
  unsigned int8 nbyte[2]; 
} dots; 

typedef struct 
{ 
  int1 refresh; 
  dots pixel[glcd_doc][glcd_ngang];    
  } gd_ram;    

gd_ram gdram_vdk; 


void glcd_mau_nen(int1 glcd_color) 
{  
  int16 d; 
  if(glcd_color)  d=0xffff; else d=0;
  for (doc=0; doc < glcd_doc; doc++) 
  { 
    for (ngang=0; ngang < glcd_ngang; ngang++) 
    { 
      gdram_vdk.pixel[doc][ngang].word = d; 
    } 
  } 
  gdram_vdk.refresh = true; 
} 

void glcd_pixel(int8 x, int8 y, int1 color) 
{ 
  int8  b; 
  if(y>31){x += 128; y-= 32;}; 
  doc = y; 
  ngang = x/16; 
  b = 15 - (x % 16); 
  
  if (color == 1) bit_set (gdram_vdk.pixel[doc][ngang].word, b); 
  else bit_clear (gdram_vdk.pixel[doc][ngang].word, b); 
  gdram_vdk.refresh = true; 
} 


void gdram_vdk_to_gdram_glcd_all() 
{ 
  if (gdram_vdk.refresh) 
  { 
    for (doc = 0; doc <glcd_doc; doc++) 
    { 
      glcd_command( 0x80 | doc);   // set vertical address. 
      glcd_command( 0x80 | 0);   // set horizontal address. 

      for (ngang=0; ngang <glcd_ngang; ngang++) 
      { 
        glcd_data( gdram_vdk.pixel[doc][ngang].nbyte[1]);   // write high byte. 
        glcd_data( gdram_vdk.pixel[doc][ngang].nbyte[0]);   // write low byte. 
      } 
    } 
    gdram_vdk.refresh = false; 
  } 
} 

void gdram_vdk_to_gdram_glcd_area (int8 x,int8 y,int8 rong, int8 cao)
{
  int8 hesox,hesoy; 
  if (gdram_vdk.refresh) 
  { 
      if((x/16)!=(x + rong)/16)
            rong=((rong+15)/16)+1;
      else rong=((rong+15)/16); 
      
      x = x/16;
      for (doc = y; doc <(y+cao); doc++) 
      { 
         if(doc>31)
            {  
               hesox = 8+x;
               hesoy = doc-32;
               }
         else {hesox = x; hesoy = doc;}
         glcd_command( 0x80 |hesoy);   
         glcd_command( 0x80 |hesox);  
      
         for (ngang=hesox; ngang <(hesox+rong); ngang++) 
         { 
            glcd_data( gdram_vdk.pixel[hesoy][ngang].nbyte[1]);   // write high byte. 
            glcd_data( gdram_vdk.pixel[hesoy][ngang].nbyte[0]);   // write low byte. 
         } 
       } 
    gdram_vdk.refresh = false; 
  }      
}


//!const unsigned char logo_dhspkttp []= { 0x00,0x01,0x2e,0x00,0x39,0x00,
//!0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//!0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//!0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,
//!0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x02,0x04,0x00,0x00,0x00,0x01,0x02,0x0c,
//!0x00,0x00,0x00,0x01,0x82,0x0c,0x00,0x00,0x00,0x00,0x80,0x08,0x00,0x00,0x00,0x00,
//!0x80,0x00,0x00,0x00,0x00,0x00,0x0f,0x80,0x00,0x00,0x00,0x00,0x3f,0xc0,0x00,0x00,
//!0x00,0x70,0x70,0x70,0x70,0x00,0x00,0x38,0xc8,0x18,0xe0,0x00,0x00,0x18,0xd8,0x18,
//!0xc0,0x00,0x00,0x01,0xb0,0x0c,0x00,0x00,0x00,0x01,0xa0,0x0c,0x00,0x00,0x00,0x01,
//!0x60,0x0c,0x00,0x00,0x00,0x01,0x00,0x04,0x00,0x00,0x00,0x01,0x00,0x04,0x00,0x00,
//!0x00,0x31,0x00,0x04,0x00,0x00,0x00,0x79,0x80,0x0c,0xf0,0x00,0x00,0x71,0x80,0x0c,
//!0x70,0x00,0x00,0x01,0x80,0x0c,0x00,0x00,0x00,0x00,0xc0,0x18,0x00,0x00,0x00,0x00,
//!0xc0,0x18,0x00,0x00,0x00,0x00,0x60,0x30,0x00,0x00,0x00,0x00,0x60,0x30,0x00,0x00,
//!0x00,0x00,0x20,0x20,0x00,0x00,0x00,0x00,0x30,0x60,0x00,0x00,0x00,0x00,0x30,0x60,
//!0x00,0x00,0x00,0x00,0x3f,0xe0,0x00,0x00,0x00,0x00,0x3f,0xe0,0x00,0x00,0x00,0x00,
//!0x3f,0xe0,0x00,0x00,0x00,0x00,0x3f,0xe0,0x00,0x00,0x00,0x00,0x1f,0x80,0x00,0x00,
//!0x00,0x00,0x3e,0x60,0x00,0x00,0x00,0x00,0x39,0xe0,0x00,0x00,0x00,0x00,0x07,0xe0,
//!0x00,0x00,0x00,0x00,0x1f,0x80,0x00,0x00,0x00,0x00,0x3e,0x60,0x00,0x00,0x00,0x00,
//!0x3d,0xe0,0x00,0x00,0x00,0x00,0x3f,0xe0,0x00,0x00,0x00,0x00,0x1f,0xc0,0x00,0x00,
//!0x00,0x00,0x0f,0x80,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//!0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//!0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//!0x00,0x00,0x00,0x00,0x00,0x00,};
//!

const unsigned char logo_dhspkttp [] = {255,245,151,153,144,123,209,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
,255,195,125,217,209,229,118,137,248,255,255,255,255,255,255,255,255,254,251,248,247,248,252,255,255,255,255,255
,240,141, 82, 73,164,238,255,117,225,255,255,255,255,246,221,192,165,146,133,126,124,128,136,149,171,198,227,250
,153,106,111,133,149,159,141,131,171,255,255,233,178,126, 94, 83, 84, 74, 82, 77, 82, 73, 73, 81, 75, 82, 99,135
,216,117,147,142,181,186,135, 74,228,255,194,112, 76, 72, 72, 78,181,146,166,138,191,173,105,184,139, 69, 73, 71
,244,130,135,210,146,218,128, 99,252,198, 94, 70, 72, 73, 72, 76,117,135,116,119,114,152,119,104,138, 82, 71, 74
,255,124,184,174,188,197, 82,107,214,147, 71, 77,181,120,149,128,151,148,129,147,122,151,145,127,148,141,152,171
,211, 64, 63,116,116, 68, 93,109,184,169, 72,115,184,212,214, 88,163,171,185,141,138,177,122,216,200, 99,215,228
,128,171,163, 86,103, 85,121, 95,170,239,135,119, 78,139,141,130,128,133,109,145,105,133,137,100,124,136,120,137
,201,109,220, 70,180,147,195,120,236,255,241,173,111, 76, 67, 68, 69, 70, 71, 69, 72, 70, 71, 70, 68, 69, 69, 80
,255,185,143,116,187,153,109,211,255,255,255,255,237,196,154,123,103, 91, 85, 82, 82, 83, 86, 93,106,128,162,205
,255,217, 53, 65, 80, 68,231,255,255,255,254,255,255,255,255,245,231,217,205,198,196,199,207,219,234,248,255,255
,255,217,172,198,197, 58,178,255,255,253,255,253,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
,255,255,255,255,255,240,241,255,192,189,230,227,253,235,246,240,250,251,253,244,234,252,253,224,229,219,243,228
,255,255,255,255,255,255,255,255,182,177,173,172,220,177,165,155,168,190,219,170,170,207,205,163,167,177,224,177
,255,255,255,255,255,255,255,255,244,245,244,243,248,245,236,242,234,231,251,243,243,248,247,246,243,244,252,244
,255,255,255,255
,255,255,255,255
,255,255,255,255
,190,241,255,255
, 80,126,211,255
, 73, 73,109,222
,142,106, 73,174
,211, 80, 83,193
,144,114,153,246
,117,189,248,255
,243,255,255,255
,255,255,255,255
,255,255,255,255
,245,242,250,252
,161,158,169,207
,234,245,227,2412
};


/*const unsigned char logo_dhspkttp [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xa0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x03, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x20, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x02, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x30, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x02, 0x30, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x30, 0x00, 0x7e, 0x00,
0x00, 0xfe, 0x00, 0x07, 0xe0, 0x00, 0x3f, 0x00, 0x01, 0xf8, 0x00, 0x03, 0xe0, 0x00, 0x1f, 0x80,
0x03, 0xf0, 0x00, 0x01, 0xc0, 0x00, 0x0f, 0xc0, 0x03, 0xe0, 0x00, 0x01, 0xc0, 0x00, 0x07, 0xe0,
0x07, 0xc0, 0x00, 0x03, 0xc0, 0x00, 0x03, 0xf0, 0x0f, 0xc0, 0x00, 0x17, 0xf4, 0x00, 0x01, 0xf0,
0x0f, 0x80, 0x00, 0x1d, 0x98, 0x00, 0x00, 0xf8, 0x1f, 0x00, 0x00, 0x11, 0x8c, 0x00, 0x00, 0xf8,
0x1f, 0x01, 0x00, 0x31, 0x84, 0x00, 0x80, 0x7c, 0x3e, 0x06, 0x00, 0x31, 0x86, 0x00, 0x20, 0x7c,
0x3e, 0x18, 0x00, 0x71, 0x86, 0x00, 0x1c, 0x3e, 0x3c, 0x43, 0x00, 0x31, 0x84, 0x00, 0xc3, 0x3e,
0x7c, 0x0c, 0x00, 0x11, 0x8c, 0x00, 0x38, 0x1e, 0x7c, 0x31, 0x00, 0x1d, 0x98, 0x00, 0x86, 0x1f,
0x78, 0xc6, 0x00, 0x1f, 0xfc, 0x00, 0x63, 0x1f, 0x78, 0x18, 0x00, 0x03, 0xc0, 0x00, 0x0c, 0x1f,
0xf8, 0x63, 0x80, 0x01, 0x80, 0x00, 0xc7, 0x0f, 0xf9, 0x8e, 0x00, 0x00, 0x00, 0x00, 0x38, 0x8f,
0xf8, 0x38, 0x80, 0x00, 0x00, 0x01, 0x0c, 0x0f, 0xf8, 0xc3, 0x80, 0x00, 0x00, 0x00, 0xe3, 0x8f,
0xf9, 0x8e, 0x00, 0x00, 0x00, 0x00, 0x30, 0xcf, 0xf8, 0x38, 0xf8, 0x00, 0x00, 0x1f, 0x9e, 0x0f,
0xf8, 0xe3, 0xfe, 0x00, 0x00, 0x7f, 0xe3, 0x8f, 0xf9, 0x9f, 0xff, 0xc0, 0x03, 0xff, 0xf9, 0xcf,
0x78, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0x0f, 0x78, 0x1f, 0xff, 0xe0, 0x07, 0xff, 0xfc, 0x1f,
0x7c, 0x07, 0xff, 0xe0, 0x07, 0xff, 0xe0, 0x1f, 0x7c, 0x00, 0xff, 0xe0, 0x07, 0xff, 0x80, 0x1e,
0x7c, 0x00, 0x1f, 0xe0, 0x07, 0xfc, 0x00, 0x3e, 0x3e, 0x01, 0xcf, 0xe0, 0x07, 0xf3, 0x80, 0x3e,
0x3e, 0x01, 0xff, 0xe0, 0x03, 0xff, 0x80, 0x7c, 0x1f, 0x01, 0xff, 0xe0, 0x03, 0xff, 0xc0, 0x7c,
0x1f, 0x01, 0xff, 0xc0, 0x03, 0xff, 0xc0, 0xf8, 0x0f, 0x83, 0xff, 0xc0, 0x01, 0xff, 0xc0, 0xf8,
0x0f, 0x83, 0xff, 0xc0, 0x01, 0xff, 0xc1, 0xf0, 0x07, 0xc3, 0xff, 0x80, 0x01, 0xff, 0xe3, 0xf0,
0x03, 0xe3, 0xff, 0x80, 0x01, 0xff, 0xe7, 0xe0, 0x03, 0xf7, 0xff, 0x80, 0x00, 0xff, 0xef, 0xc0,
0x01, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x80,
0x00, 0x7f, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x3f, 0xff, 0x00, 0x00, 0xff, 0xfe, 0x00,
0x00, 0x1f, 0xff, 0x00, 0x00, 0x7f, 0xf8, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x00, 0x7f, 0xf0, 0x00,
0x00, 0x03, 0xff, 0x00, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0x00, 0xff, 0xfc, 0x1f, 0xff, 0x80, 0x00,
0x00, 0x00, 0x7f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf8, 0x00, 0x00,
0x00, 0x00, 0x01, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00
};*/


void glcd_xuat_anh(int width,int height,int x,int y) 
{ 
   unsigned int i=0, j=0, k=0; 
   unsigned int16 count=0; 
   for(j=0;j<height;j++) 
      {    
         for(;i<width;) 
         { 
            for(k=8;k>0;k--)
            {
               glcd_pixel(i+x,j+y,bit_test(logo_dhspkttp[count],(k-1))); 
               i++; 
            } 
            count++; 
         } 
      i=0; 
      } 
} 