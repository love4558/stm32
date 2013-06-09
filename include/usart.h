/*------------------------------------------------------
   FILE NAME   : usart.h
   2008.4.25
   --------------------------------------------------------*/

#ifndef __usart_h__
#define __usart_h__

//---------------Include files--------------------------//
 #include "..\config\config.h"

//----------------Data struct---------------------------//

typedef struct {
//varitable
	char receive_buffer[BUFFER_SIZE];
	int receive_count;
	int receive_ok_flag;
	int baudrate;
	int error;

//function

	int (* initialize)(int);
	int (* send_string)(char *);
	int (* send_byte)(char);
	int (* send_buffer)(char *, int len);
	int (* printf)(const char *, ...);
}UART_T;


//-----------------extern function---------------------//

extern UART_T usart1;
extern UART_T usart3;



#endif // __uart_h__
