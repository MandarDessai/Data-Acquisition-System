#include<reg51.h>
#include<stdio.h>
#include "delay.h"
#include "uart_init.h"
#include "lcd8bit.h"
#include"i2c_2.h"
#include"i2c_device_2.h"
#include"i2c_device_ds1621.h"
#include"adc_2.h"
//#include"i2c_device_2.h"



main()
{
	
	unsigned char temp,count_per_c,count_remain,th,tl,temp_counter=0,rtc_temp,new;
	unsigned int temp1,temp2,ldr;
	float voltage,LDR_val_dark,LDR_val_light;
	float temperature;
	
	lcd_init();
	uart_init();

  i2c_device_write(0xD0,0x2,0x23);     //hour
	i2c_device_write(0xD0,0x1,0x59);     //minute 
	i2c_device_write(0xD0,0x0,0x45);     //second


	///////////////////////temp sensor ds1621 configuration + display part
	temp_config();
	temp_setlimit(1,55);
	temp_start();

  uart_string("Data Acquisition System\r\r\n");
	
	while(1)
	{	
		lcd_cmd(0x80);
	  temp=i2c_device_read(0xD0,0x4);      //Date
	  new=temp;
		lcd_data(temp/16+48);               //LCD display files
	  lcd_data(temp%16+48);               //LCD display files
	  lcd_data('/');                      //LCD display files
		uart_string("\r\r\n");
    uart_string("Date:");
		uart_tx(new/16+48);               
	  uart_tx(new%16+48);
		uart_string("/");
		
		
		
		
	  temp=i2c_device_read(0xD0,0x5);      //Month
		new=temp;
	  lcd_data(temp/16+48);                //LCD display files
	  lcd_data(temp%16+48);                //LCD display files
	  lcd_string("/18");                   //LCD display files
		uart_tx(new/16+48);               
	  uart_tx(new%16+48);
		uart_string("/18\r\r\n");
		
		
		/*
		temp=i2c_device_read(0xD0,0x6);       //year
	  //temp=temp+2000;
	  lcd_data(temp/1600+4800);
	  lcd_data(temp%1600+4800); 
		*/
		
		
		
   temp=i2c_device_read(0xD0,0x2);     //hour
	 new=temp;
	 lcd_cmd(0xC0);                      //LCD display files
	 lcd_data(temp/16+48);               //LCD display files
	 lcd_data(temp%16+48);               //LCD display files
	 lcd_data(':');                      //LCD display files
	 uart_string("Time:");
	 uart_tx(new/16+48);               
	 uart_tx(new%16+48);               
	 uart_string(":");                      
	 
	 
	 

	 temp=i2c_device_read(0xD0,0x1);     //minute
	 new=temp;
	// lcd_cmd(0x80);                    //LCD display files
	 lcd_data(temp/16+48);               //LCD display files
	 lcd_data(temp%16+48);               //LCD display files
	 lcd_data(':');	                     //LCD display files
   uart_tx(new/16+48);               
	 uart_tx(new%16+48);               
	 uart_string(":"); 




	  temp=i2c_device_read(0xD0,0x0);     //second
		new=temp;
	  // lcd_cmd(0x80);                     //LCD display files
	  lcd_data(temp/16+48);                //LCD display files
	  lcd_data(temp%16+48);		            //LCD display files
		uart_tx(new/16+48);               
	  uart_tx(new%16+48);
    uart_string("\r\r\n");		
		
		
		
		
	count_per_c=read_slope();
	count_remain=read_count();
	
	th=read_th();
	tl=read_tl();
	
	temperature=(th-0.25)+((count_per_c-count_remain)/count_per_c);
	
	if(tl&&0x8)
	temperature=temperature+0.5;
	//lcd_cmd(0xC0);
	lcd_string(" T:");	           //LCD display files
	if(temp_counter>0)             //it gives a funny output at the start thus to avoid it
	lcd_float(temperature);        //LCD display files
	uart_string("Temperature:");
	uart_float(temperature);
	uart_string("\r\r\n");
	temp_counter++;
	delay_ms(3000);
	lcd_cmd(0x1);                  //LCD display files
	
	////////////////////////////////////////////////////////////////starting the SPI part
	
	    temp1=read_adc(2);                 //reading the connection on the channel 1
			lcd_cmd(0x80);
			lcd_cmd(0x1);
			lcd_string("Ch 1=");
			lcd_integer(temp1);                //showing the potentiometer value
	    uart_string("Channel 1 value=");
	    uart_int(temp1);
	    uart_string("\r\r\n");
			voltage=temp1/409.2;               //calculating the voltage 
			lcd_string(" V=");
			lcd_float(voltage);                //display the voltage
	    uart_string("Voltage=");
			uart_float(voltage);
			uart_string("\r\r\n");

	
			//delay_ms(100);
			temp2=read_adc(3);                 //reading the LDR value
			lcd_cmd(0xC0);
			lcd_string("Ch 2=");
			lcd_integer(temp2);                //displaying the LDR value
			uart_string("Channel 2 LDR value=");
			uart_int(temp2);
			uart_string("\r\r\n");
	  	LDR_val_dark=(100*temp2)/4078;
 //   LDR_val_dark=(temp2/4078);
	//	LDR_val_dark=(LDR_val_dark)*100;
			LDR_val_light=100-LDR_val_dark;
			uart_string("Darkness Percentage=");
	//	uart_float(LDR_val_dark);
	    uart_int(LDR_val_dark);
			uart_string("%");
			uart_string("\r\r\n");
			delay_ms(3000);
			lcd_cmd(0x1);
			uart_string("\r\r\n");
			uart_string("------------------");
			uart_string("\r\r\n");
		
			
  }
}