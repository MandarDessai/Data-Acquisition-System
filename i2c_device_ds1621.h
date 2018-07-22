
unsigned char i2c_device_read_ds1621(unsigned char sa,unsigned char mr)
{
 unsigned char temp1,temp2;
 i2c_start();
 i2c_write(sa);
 i2c_ack();
 i2c_write(mr);
 i2c_ack();
 i2c_start();
 i2c_write(sa|0x1);
 i2c_ack();
 temp1=i2c_read();  //msb
 i2c_ack();
 temp2=i2c_read();  //lsb
 i2c_noack();
 i2c_stop();
 return temp1;
}

void i2c_device_write_ds1261(unsigned char sa,unsigned char mr,unsigned char d1,unsigned char d2)
{
 i2c_start();
 i2c_write(sa);
 i2c_ack();
 i2c_write(mr);
 i2c_ack();
 i2c_write(d1);
 i2c_ack();
 i2c_write(d2);
 i2c_ack();
 i2c_stop();
}

void i2c_device_init_conv(unsigned char sa,unsigned char ba)
{
 i2c_start();
 i2c_write(sa);
 i2c_ack();
 i2c_write(ba);
 i2c_ack();
 i2c_stop();
}

void i2c_set_temp_threshold(unsigned char sa,unsigned char ba,unsigned char ca)
{
 i2c_start();
 i2c_write(sa);
 i2c_ack();
 i2c_write(ba);
 i2c_ack();
 i2c_write(ca);
 i2c_ack();
 i2c_stop();
}

unsigned char i2c_read_csc(unsigned char sa,unsigned char ba, unsigned char ca)
{
 i2c_start();
 i2c_write(sa);
 i2c_ack();
 i2c_write(ba);
 i2c_ack();
 i2c_start();
 i2c_write(sa);
 i2c_ack();
 i2c_write(ca);
 i2c_nack();
 i2c_stop();
}

void temp_config()
{
	i2c_start();
	i2c_write(0x90);
	i2c_ack();
	i2c_write(0xac);
	i2c_ack();
	i2c_write(9);
	i2c_ack();
	i2c_stop();
	delay_ms(20);	
}

void temp_start()
{
	i2c_start();
	i2c_write(0x90);
	i2c_ack();
	i2c_write(0xee);
	i2c_ack();
	i2c_stop();
	delay_ms(20);	
}

void temp_stop()
{
	i2c_start();
	i2c_write(0x90);
	i2c_ack();
	i2c_write(0x22);
	i2c_ack();
	i2c_stop();
	delay_ms(20);	
}

void temp_setlimit(signed char l,signed char h)
{
	i2c_start();
	i2c_write(0x90);
	i2c_ack();
	i2c_write(0xA1);
	i2c_ack();
	i2c_write(h);
	i2c_ack();
	i2c_write(0x00);
	i2c_ack();
	i2c_stop();
	delay_ms(20);
	
	i2c_start();
	i2c_write(0x90);
	i2c_ack();
	i2c_write(0xA2);
	i2c_ack();
	i2c_write(l);
	i2c_ack();
	i2c_write(0x00);
	i2c_ack();
	i2c_stop();
	delay_ms(20);	
}

char read_th()
{
	char th;
	
	i2c_start();
	i2c_write(0x90);
	i2c_ack();
	i2c_write(0xAA);
	i2c_ack();
	i2c_start();
	i2c_write(0x91);
	i2c_ack();
	th=i2c_read();
	i2c_stop();
	
	return th;	
}

char read_tl()
{
	char tl;
	
	i2c_start();
	i2c_write(0x90);
	i2c_ack();
	i2c_write(0xAA);
	i2c_ack();
	i2c_start();
	i2c_write(0x91);
	i2c_ack();
	tl=i2c_read();
	i2c_stop();
	
	return tl;	
}

unsigned char read_slope()
{
	unsigned char count_per_c;
	i2c_start();
	i2c_write(0x90);
	i2c_ack();
	i2c_write(0xA9);
	i2c_ack();
	i2c_start();
	i2c_write(0x90|0x1);
	i2c_ack();
	count_per_c=i2c_read();
	i2c_noack();
	i2c_stop();
	
	return count_per_c;	
}

unsigned char read_count()
{
	unsigned char count_per_c;
	i2c_start();
	i2c_write(0x90);
	i2c_ack();
	i2c_write(0xA8);
	i2c_ack();
	i2c_start();
	i2c_write(0x90|0x1);
	i2c_ack();
	count_per_c=i2c_read();
	i2c_noack();
	i2c_stop();
	
	return count_per_c;	
}
