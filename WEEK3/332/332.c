#include "TV_PICKIT2_SHIFT_1.c"
#include "TV_PICKIT2_SHIFT_KEY4X4_138.c"
#include "18F4550.h"

signed int8 mp;

void main()
{
    set_up_port_ic_chot();
    set_tris_b(0x3c);
    while(TRUE) {
        mp = key_4x4_dw();
        if (mp != 0xff)
        {
            xuat_32led_don_4byte(0,0,0,mp);
        }
        
    }
}
