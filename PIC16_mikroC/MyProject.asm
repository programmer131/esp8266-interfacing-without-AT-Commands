
_main:

;MyProject.c,5 :: 		void main() {
;MyProject.c,9 :: 		UART1_Init(9600);               // Initialize UART module at 9600 bps
	MOVLW      51
	MOVWF      SPBRG+0
	BSF        TXSTA+0, 2
	CALL       _UART1_Init+0
;MyProject.c,10 :: 		Delay_ms(100);                  // Wait for UART module to stabilize
	MOVLW      2
	MOVWF      R11+0
	MOVLW      4
	MOVWF      R12+0
	MOVLW      186
	MOVWF      R13+0
L_main0:
	DECFSZ     R13+0, 1
	GOTO       L_main0
	DECFSZ     R12+0, 1
	GOTO       L_main0
	DECFSZ     R11+0, 1
	GOTO       L_main0
	NOP
;MyProject.c,11 :: 		TRISC.RC0=1;
	BSF        TRISC+0, 0
;MyProject.c,12 :: 		TRISA.RA0  = 0x01;              // PORTA is input
	BSF        TRISA+0, 0
;MyProject.c,13 :: 		ADCON0=0b01000001 ;//01 000 0 0 1
	MOVLW      65
	MOVWF      ADCON0+0
;MyProject.c,14 :: 		ADCON1=0b00001110;
	MOVLW      14
	MOVWF      ADCON1+0
;MyProject.c,16 :: 		do {
L_main1:
;MyProject.c,17 :: 		strcpy(txt, "{\"temperature\":");
	MOVLW      _txt+0
	MOVWF      FARG_strcpy_to+0
	MOVLW      ?lstr1_MyProject+0
	MOVWF      FARG_strcpy_from+0
	CALL       _strcpy+0
;MyProject.c,18 :: 		temp_res= ADC_Read(0)*500.0/1023.0;   // Get 10-bit results of AD conversion
	CLRF       FARG_ADC_Read_channel+0
	CALL       _ADC_Read+0
	CALL       _word2double+0
	MOVLW      0
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	MOVLW      122
	MOVWF      R4+2
	MOVLW      135
	MOVWF      R4+3
	CALL       _Mul_32x32_FP+0
	MOVLW      0
	MOVWF      R4+0
	MOVLW      192
	MOVWF      R4+1
	MOVLW      127
	MOVWF      R4+2
	MOVLW      136
	MOVWF      R4+3
	CALL       _Div_32x32_FP+0
	CALL       _double2byte+0
;MyProject.c,19 :: 		ByteToStr(temp_res, temp);
	MOVF       R0+0, 0
	MOVWF      FARG_ByteToStr_input+0
	MOVLW      _temp+0
	MOVWF      FARG_ByteToStr_output+0
	CALL       _ByteToStr+0
;MyProject.c,20 :: 		strcat(txt, temp);
	MOVLW      _txt+0
	MOVWF      FARG_strcat_to+0
	MOVLW      _temp+0
	MOVWF      FARG_strcat_from+0
	CALL       _strcat+0
;MyProject.c,21 :: 		strcat(txt,",\"button_state\":");
	MOVLW      _txt+0
	MOVWF      FARG_strcat_to+0
	MOVLW      ?lstr2_MyProject+0
	MOVWF      FARG_strcat_from+0
	CALL       _strcat+0
;MyProject.c,22 :: 		if(PORTC.RC0)
	BTFSS      PORTC+0, 0
	GOTO       L_main4
;MyProject.c,23 :: 		strcat(txt,"1}");
	MOVLW      _txt+0
	MOVWF      FARG_strcat_to+0
	MOVLW      ?lstr3_MyProject+0
	MOVWF      FARG_strcat_from+0
	CALL       _strcat+0
	GOTO       L_main5
L_main4:
;MyProject.c,25 :: 		strcat(txt,"0}");
	MOVLW      _txt+0
	MOVWF      FARG_strcat_to+0
	MOVLW      ?lstr4_MyProject+0
	MOVWF      FARG_strcat_from+0
	CALL       _strcat+0
L_main5:
;MyProject.c,26 :: 		UART1_Write_text(txt);
	MOVLW      _txt+0
	MOVWF      FARG_UART1_Write_Text_uart_text+0
	CALL       _UART1_Write_Text+0
;MyProject.c,27 :: 		UART1_Write(0x0D);UART1_Write(0x0A);
	MOVLW      13
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
	MOVLW      10
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;MyProject.c,28 :: 		delay_ms(5000);
	MOVLW      51
	MOVWF      R11+0
	MOVLW      187
	MOVWF      R12+0
	MOVLW      223
	MOVWF      R13+0
L_main6:
	DECFSZ     R13+0, 1
	GOTO       L_main6
	DECFSZ     R12+0, 1
	GOTO       L_main6
	DECFSZ     R11+0, 1
	GOTO       L_main6
	NOP
	NOP
;MyProject.c,30 :: 		while(1);
	GOTO       L_main1
;MyProject.c,31 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
