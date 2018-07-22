	//lcd 8bit header file
	sfr LCD_PORT=0x80;
	sbit RS=P3^4;
	sbit RW=P3^5;
	sbit EN=P3^6;

	void lcd_cmd(unsigned char c)
	{
	 LCD_PORT=c;
	 RS=0;
	 RW=0;
	 EN=1;
	 delay_ms(50);
	 EN=0;
	}	  


	void lcd_data(unsigned char d)
	{
	  LCD_PORT=d;
	  RS=1;
	  RW=0;
	  EN=1;
	  delay_ms(50);
	  EN=0;
	}

	void lcd_init()
	{
	  lcd_cmd(0x2);
	  lcd_cmd(0x38);
	  lcd_cmd(0xE);
      lcd_cmd(0x6);
      lcd_cmd(0x1);
	}

   void lcd_string(char *s)
   {
     while(*s)
	 lcd_data(*s++);
   }

   void lcd_integer(int n)
   {
	char sbuf[10];
	sprintf(sbuf,"%d",n);
	lcd_string(sbuf);
   }

	 void lcd_float(float n)
	 {
		 int i;
		 i=n;
		 lcd_integer(i);
		 
		 lcd_data('.');
		 n=n-1;
		 n=n*100;
		 lcd_integer(n);
	 }
		 
	 
   code unsigned char cgram_lookup_table[]=
   {
	0x0,0xA,0xA,0x0,0x0,0x11,0xE,0xE
   };

   void cgram_init()
   {
    char i;
	lcd_cmd(0x40);   //CG ram page 0
	for(i=0;i<8;i++)
	{
	lcd_data(cgram_lookup_table[i]);
	lcd_cmd(0x80);
	}
   }


