char uart_rd;
char txt[50]={0x00};
char temp[5]={0x00};
char *res;
void main() {
  unsigned char button_state;
  unsigned char temperature;
  unsigned short temp_res;
  UART1_Init(9600);               // Initialize UART module at 9600 bps
  Delay_ms(100);                  // Wait for UART module to stabilize
  TRISC.RC0=1;
  TRISA.RA0  = 0x01;              // PORTA is input
  ADCON0=0b01000001 ;//01 000 0 0 1
  ADCON1=0b00001110;
  //{"temperature":28,"button_state":0}
  do {
    strcpy(txt, "{\"temperature\":");
    temp_res= ADC_Read(0)*500.0/1023.0;   // Get 10-bit results of AD conversion
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

