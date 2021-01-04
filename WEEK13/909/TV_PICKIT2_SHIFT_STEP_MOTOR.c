unsigned  int8 stepmotor_fullstep[]=  {0x1d,0x17,0x1b,0x0f};
unsigned  int8 stepmotor_halfstep[]=  {0x1d,0x15,0x17,0x13,0x03,0x0b,0x09,0x0d};
unsigned  int8 stepmotor_i=0, stepmotor_delay;
int1 stepmotor_tn=0,stepmotor_onoff=0;
void step_motor_quay_thuan_fs()
{
      rbdc=rbdc & 0xffe0;           
      rbdc=rbdc | stepmotor_fullstep[stepmotor_i];
      xuat_buzzer_relay(); 
      stepmotor_i++;
      stepmotor_i = stepmotor_i & 0x03;
}
void step_motor_quay_nghich_fs()
{
      rbdc=rbdc & 0xffe0;           
      rbdc=rbdc | stepmotor_fullstep[stepmotor_i];
      xuat_buzzer_relay(); 
      stepmotor_i--;
      stepmotor_i = stepmotor_i & 0x03;
}
void motor_step_run_fs()
{
   if (stepmotor_tn) step_motor_quay_thuan_fs();
   else           step_motor_quay_nghich_fs();
}

void step_motor_quay_thuan_hs()
{
      rbdc=rbdc & 0xe0;           
      rbdc=rbdc | stepmotor_halfstep[stepmotor_i];
      xuat_buzzer_relay(); 
      stepmotor_i++;
      stepmotor_i = stepmotor_i & 0x07;
}
void step_motor_quay_nghich_hs()
{
      rbdc=rbdc & 0xe0;           
      rbdc=rbdc | stepmotor_halfstep[stepmotor_i];
      xuat_buzzer_relay(); 
      stepmotor_i--;
      stepmotor_i = stepmotor_i & 0x07;
}
void motor_step_run_hs()
{
   if (stepmotor_tn) step_motor_quay_thuan_hs();
   else           step_motor_quay_nghich_hs();
}

