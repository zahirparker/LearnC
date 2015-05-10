/**********************************************************
 *        TI FM firmware 
 *
 *        Filename typedefs.h
 *
 *
 *	Redefine types for the TI's FM firmware
 *
 **********************************************************/

#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_

#define FALSE 0
#define TRUE 1

#define False 0
#define True 1

typedef unsigned char  BOOL;

//typedef enum { False=0, True=1} boolean_t;
//#define BOOL boolean_t

typedef unsigned char  UINT8;
typedef signed   char  SINT8;

typedef unsigned short UINT16;
typedef          short SINT16;

typedef unsigned int   UINT32;
typedef          int   SINT32;

//typedef void(* const ExecFuncPtr)(void) __irq;

#endif /* _TYPEDEFS_H_ */
