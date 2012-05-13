// Date:   13.5.2012
// Author: Bla� Grah

/* Start up

*/

#include "mpr121.h"
#include "i2c.h"

/* VIC globals
  i2c0_address_rw;	  // int Device address with read/write bit
  i2c0_num_of_bytes;	// int Number of bytes to be received/transmitted
  i2c0_status;		    // int Current master status
  *i2c0_buf;			    // char Receiving/transmitting buffer 
  
  I2C0CONSET = sta;   // To start?
*/

unsigned char mpr121_buf[20];
void mpr121_init(void)
{
  i2c0_buf = mpr121_buf;  // Point i2c_buffer to mpr121_buffer... test :)  
/* Opombe:
   -> ELEx_T/R registre zapi�i v for zanki, naslov pove�uj za ena (samo toliko kot jih rabi�
  
*/  
  // This group controls filtering when data is > baseline.
  mpr121_write(MHD_R, 0x01);
  mpr121_write(NHD_R, 0x01);
  mpr121_write(NCL_R, 0x00);
  mpr121_write(FDL_R, 0x00);

  // This group controls filtering when data is < baseline.
  mpr121_write(MHD_F, 0x01);
  mpr121_write(NHD_F, 0x01);
  mpr121_write(NCL_F, 0xFF);
  mpr121_write(FDL_F, 0x02);

  // This group sets touch and release thresholds for each electrode
  mpr121_write(ELE0_T, TOU_THRESH);
  mpr121_write(ELE0_R, REL_THRESH);
  mpr121_write(ELE1_T, TOU_THRESH);
  mpr121_write(ELE1_R, REL_THRESH);
  mpr121_write(ELE2_T, TOU_THRESH);
  mpr121_write(ELE2_R, REL_THRESH);
  mpr121_write(ELE3_T, TOU_THRESH);
  mpr121_write(ELE3_R, REL_THRESH);

  // Enable Auto Config and auto Reconfig
  mpr121_write(ATO_CFGU, 0xC9);	// USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V   
  mpr121_write(ATO_CFGL, 0x82);	// LSL = 0.65*USL = 0x82 @3.3V
  mpr121_write(ATO_CFGT, 0xb5);  // Target = 0.9*USL = 0xB5 @3.3V
  mpr121_write(ATO_CFG0, 0x1B);
  
  // Electrode Configuration
  mpr121_write(ELE_CFG, 0x84);   // Enable 4 Electrodes and set to run mode
}

void mpr121_write(unsigned char address_reg, unsigned char data)
{
  // i2c START
  // i2c send (MPR121_W)
  // i2c send (reg address)
  // i2c send (data)
  // i2c STOP
  
  while(i2c0_status!=i2c_idle);
  i2c0_num_of_bytes = 2;
  i2c0_address_rw = MPR121_W;
  mpr121_buf[0] = address_reg;
  mpr121_buf[1] = data;
  I2C0CONSET = sta;
  while(i2c0_status!=i2c_idle);
  I2C0CONSET = sto;
}

void mpr121_read(unsigned char address_reg)
{
  // i2c START
  // i2c send (MPR121_W)
  // i2c send (address_reg)
  
  // i2c repeated START
  // i2c send (MPR121_R)
  // i2c receive
  // i2c STOP
  
  unsigned char data;
  
  while(i2c0_status!=i2c_idle);
  i2c0_num_of_bytes = 1;
  i2c0_address_rw = MPR121_W;
  mpr121_buf[0] = address_reg;
  I2C0CONSET = sta;
  
  while(i2c0_status!=i2c_idle);
  i2c0_num_of_bytes = 1;
  i2c0_address_rw = MPR121_R;
  I2C0CONSET = sta;
  while(i2c0_status!=i2c_idle);
  data = mpr121_buf[0];
  
  mpr121_action(data);
}

void mpr121_action(unsigned char data)
{
  static char button0_state=0;
  static char button1_state=0;
  static char button2_state=0;
  static char button3_state=0;
  
// 0   
  if((data&0x01) && !button0_state)
  {
    GLCD_putch(data); button0_state=1;
  }
  else button0_state=0;
// 1  
  if((data&0x02) && !button1_state)
  {
    GLCD_putch(data); button1_state=1;
  }
  else button1_state=0;
// 2  
  if((data&0x04) && !button2_state)
  {
    GLCD_putch(data); button2_state=1;
  }
  else button2_state=0;
// 3  
  if((data&0x08) && !button2_state)
  {
    GLCD_putch(data); button2_state=1;
  }
  else button3_state=0;
}

void mpr121_irq(void)
{
  // External interrupt when touch/release detected  
}


