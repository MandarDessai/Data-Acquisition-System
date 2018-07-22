// uart_init() header file
void uart_init(unsigned int baud)
{

SCON=0x50;
TMOD=0x20;
 switch(baud)
 {
  case 7200: TH1=251; break;
  case 9600: TH1=253; break;
  case 28800:TH1=255;break;
  case 57600:TH1=255; PCON=0x80;break;
  default: TH1=253;  // default baud rate 9600 kbps
 }
 TR1=1;
}

void uart_tx(unsigned char ch)
{
 SBUF=ch;
 while(TI==0);
 TI=0;            //important
}

unsigned char uart_rx()
{
while(RI==0);
RI=0;
return SBUF;
}

void uart_string(char *s)
{
 while(*s)
 uart_tx(*s++);
}

void uart_int(int num)
{
 char buf[7],i=0,temp,j=0,buf2[7],k;
 while(num)
  {
   buf[i++]=num%10+48;
   num=num/10;
  }
  buf[i]=0;
	for(j=i-1,k=0;j>=0;j--,k++)
	{ 
		buf2[k]=buf[j];
	}
	buf2[k]=0;
	
 // uart_string(buf);
	uart_string(buf2);
}		



void uart_float(float n)
	 {
		 int i;
		 i=n;
		 uart_int(i);
		 
		 uart_string(".");
		 n=n-i;
		 n=n*100;
		 uart_int(n);
	 }