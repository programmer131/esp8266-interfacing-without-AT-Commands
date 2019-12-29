#line 1 "C:/Users/Public/Documents/Mikroelektronika/mikroC PRO for PIC/Examples/MyProject.c"
char uart_rd;
char txt[50]={0x00};
char temp[5]={0x00};
char *res;
void main() {
 unsigned char button_state;
 unsigned char temperature;
 unsigned short temp_res;
 UART1_Init(9600);
 Delay_ms(100);
 TRISC.RC0=1;
 TRISA.RA0 = 0x01;
 ADCON0=0b01000001 ;
 ADCON1=0b00001110;

 do {
 strcpy(txt, "{\"temperature\":");
 temp_res= ADC_Read(0)*500.0/1023.0;
 ByteToStr(temp_res, temp);
 strcat(txt, temp);
 strcat(txt,",\"button_state\":");
 if(PORTC.RC0)
 strcat(txt,"1}");
 else
 strcat(txt,"0}");
 UART1_Write_text(txt);
 UART1_Write(0x0D);UART1_Write(0x0A);
 delay_ms(5000);
 }
 while(1);
}
