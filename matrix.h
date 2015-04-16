#ifndef MATRIX_H
#define MATRIX_H

typedef enum
{               /*Control signal is '0'*/
	WHITE	= ((u8)0x0),	/*0b 000*/
	PINK	= ((u8)0x1),	/*0b 001*/
	SKY	= ((u8)0x2),	/*0b 010*/
	BLUE	= ((u8)0x3),	/*0b 011*/
	YELLOW	= ((u8)0x4),	/*0b 100*/
	RED	= ((u8)0x5),	/*0b 101*/
	GREEN	= ((u8)0x6),	/*0b 110*/
	OFF	= ((u8)0x7)	/*0b 111*/
 }Colour;


#endif /* MATRIX_H */ 