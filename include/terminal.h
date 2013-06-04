/*------------------------------------------------------
   FILE NAME   : terminal.h
   DESCRIPTION : terminal
   VERSION     : 0.0.0 (C)aureole
   AUTHOR      : Aureole
   CREATE DATE : 8.20.2008
   MODIFY DATE :
   LOGS        :-\

   -V
   --------------------------------------------------------*/

#include "..\config\config.h"
#include <stdio.h>

#ifndef __terminal_h__
#define __terminal_h__



//-------------------- define -----------------------//


//---------------------data struct-------------------//
typedef const struct _COMMAND {
	char * command;
	void (* function)(void);
	const struct _COMMAND * next;
}COMMAND_T;

typedef struct {
	int (* initialize)(void);
	int (* ci)(void);
}TERMINAL_T;

//----------------extern variable--------------------//
extern TERMINAL_T terminal;

//----------------extern function--------------------//
void sleep(int times);
#endif /* __terminal_h__ */


