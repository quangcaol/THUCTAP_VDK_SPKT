int1 dcmotor_tn = 0, dcmotor_onoff=0;
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//cac ham cho dk dong co dc on off
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void dc_motor_enable()
{
      dc_enable=1;
      xuat_buzzer_relay();
}
void dc_motor_quay_thuan()
{
      output_high(pin_c1);
      output_low(pin_c2);
}
void dc_motor_quay_nghich()
{
      output_low(pin_c1);
      output_high(pin_c2);
}
void dc_motor_stop()
{
      output_low(pin_c1);
      output_low(pin_c2);
}
void dc_motor_control()
{
      if (dcmotor_onoff==1)
      {
         if (dcmotor_tn)   dc_motor_quay_thuan();
         else              dc_motor_quay_nghich();
      }
      else                 dc_motor_stop();
      
}         
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//cac ham cho dk dong co dc bang pwm
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
unsigned int16    pwm_duty;
void dc_motor_ktao_ccp1_thuan()
{     
      setup_ccp2(ccp_off);      
      setup_ccp1(ccp_pwm);
      output_low(pin_c1);      
}
void dc_motor_ktao_ccp2_nghich()
{            
      setup_ccp1(ccp_off);      
      setup_ccp2(ccp_pwm);
      output_low(pin_c2);
}
void dc_motor_ktao_ccpx_ktao()
{         
     if (dcmotor_tn)   dc_motor_ktao_ccp1_thuan();
     else               dc_motor_ktao_ccp2_nghich();            
}
void dc_motor_pww_setup_duty()
{     
     if (dcmotor_tn)   set_pwm1_duty(pwm_duty);
     else               set_pwm2_duty(pwm_duty);     
} 
void dc_motor_pwm_ccp1_ccp2_stop()
{         
      pwm_duty=0;            
      setup_ccp1(ccp_off);
      setup_ccp2(ccp_off);
      dc_motor_ktao_ccpx_ktao();
      dc_motor_pww_setup_duty();
}
