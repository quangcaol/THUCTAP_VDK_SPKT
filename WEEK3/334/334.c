#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "18F4550.h"

signed int8 mp;
int8 pattern = 0;
int8 patternD = 0xFF;
unsigned int8 Y = 0;


void UP1(){
        switch (mp)
        {
        case 0:
            pattern = 0x1;
            break;
        case 1:
            pattern = 0x2;
            break;
        case 2:
            pattern = 0x4;
            break;
        case 3:
            pattern = 0x8;
            break;
        case 4:
            pattern = 0x10;
            break;
        case 5:
            pattern = 0x20;
            break;
        case 6:
            pattern = 0x40;
            break;
        case 7:
            pattern = 0x80;
            break;
        default:
            pattern = 0;
            break;
    }
}
void DOWN(){
        switch (mp)
        {
        case 8:
            patternD = 0xFE;
            break;
        case 9:
            patternD = 0xFD;
            break;
        case 10:
            patternD = 0xFB;
            break;
        case 11:
            patternD = 0xF7;
            break;
        case 12:
            patternD = 0xEF;
            break;
        case 13:
            patternD = 0xDF;
            break;
        case 14:
            patternD = 0xBF;
            break;
        case 15:
            patternD = 0x7F;
            break;
        default:
            patternD = 0xFF;
            break;
        }
}
void main()
{
    set_up_port_ic_chot();
    set_tris_b(0x3c);
    while(TRUE) {
        mp = key_4x4_dw();
        if(mp!=0xff) {
        UP1();
        DOWN();
        Y &= patternD;
        Y |=  pattern;
        xuat_32led_don_4byte(0,0,0,Y);   //Y  = Y &(~(1<<mp)) Y = Y|(1<<mp)
        }
    }
}
