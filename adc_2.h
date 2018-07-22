//header file for the adc for data acquizition
sbit clk=P1^0;
sbit din=P1^2;
sbit dout=P1^1;
sbit cs=P1^3;

unsigned int read_adc(unsigned int temp)
{
 //unsigned int temp=0;
 char i;
 cs=0;   //chip enabled;
 
 clk=0; din=1; clk=1;   //start bit
 clk=0; din=1; clk=1;   //single ended mode selected
 clk=0; din=1; clk=1;   //

switch(temp) 
{
   case 1:
          //*selecting channel CH0*//
          clk=0; din=0; clk=1;  //D1 bit
          clk=0; din=0; clk=1; // D0 bit & Tsample (short)
		  break;
   case 3: 
          //*selecting channel CH1*//
          clk=0; din=1; clk=1;  //D1 bit
          clk=0; din=0; clk=1; // D0 bit & Tsample (short)
		  break;
   case 2:
          //*selecting channel CH2*//
          clk=1; din=1; clk=1;  //D1 bit
          clk=0; din=0; clk=1; // D0 bit & Tsample (short)
		  break;
   case 4:
          //*selecting channel CH3*//
          clk=1; din=0; clk=1;  //D1 bit
          clk=0; din=0; clk=1; // D0 bit & Tsample (short)
		  break;
}

 
 clk=0; din=1; clk=1;  //Tsample finish
 clk=0; din=1; clk=1;  //null bit

 //reading 12 bit digital data from the adc
 for(i=11;i>0;i--)
 {
  clk=0;
  if(dout==1)
   temp|=(1<<i);
  clk=1;
 }
 cs=1;  //chip disabled
 return temp;
}
