#include "stm8s.h"
#include "matrix.h"

/*   CN2
PIN_7: GRND
PIN_8: VDD

PIN_PC2: SS = SH-CP - Impulse
PIN_PC4: LT = ST-CP - Latch
PIN_PC5: MOSI = DS - Data
*/

void GPIO_Configuration(void);

void putINmatrix (u32 input);

void initMatrix(void);

void lightMYled (u8 x, u8 y, u8 colour);

  
void main( void )
{
  CLK_DeInit();
    
    /* Clock divider to HSI/1 */
  CLK_HSIPrescalerConfig(CLK_PRESCALER_CPUDIV128);
    
 
  GPIO_Configuration();
  
  initMatrix ();
  
  //putINmatrix(0xFFFF00FD);
  
  while (1)
  {
    /*u8 a = 0, b = 0;
    for (b = 0; b <= 7; ++b)
      lightMYled(b, b+1, WHITE);*/
    
    //putINmatrix(0xFFFF00FD);
    //putINmatrix(0xFBFDFEF7);
    //putINmatrix(0xFBFDFEEF);
    
    u8 i;
    u8 j;
    for (i = 0; i < 9; ++i)
      for(j = 0; j < 9; ++j)
        lightMYled (j + 1, 8 - i, WHITE + i);
    
    //lightMYled (5, 8, YELLOW);
    /*u8 i;
    for (i = 1; i < 6; ++i){
      lightMYled(4, i, YELLOW);
      lightMYled(5, i, YELLOW);
    }
     for (i = 7; i < 9; ++i){
      lightMYled(4, i, BLUE);
      lightMYled(5, i, BLUE);
    }*/
  }
  
}


void GPIO_Configuration(void)
{
  /* GPIOC reset */
  GPIO_DeInit(GPIOC);

  /* Configure PC2, PC4, PC5 as output push-pull low */
  GPIO_Init(GPIOC, GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);
 }


void putINmatrix (u32 input)
{
  u8 i;
  u8 data;
  
  
  for (i=0; i<32; ++i)
  {
    
    data = (input >> i) &1;
    GPIO_WriteLow(GPIOC, GPIO_PIN_2); /*0 impulse*/
        
      /*write data*/
    if (data == 0)
      GPIO_WriteLow(GPIOC, GPIO_PIN_5);
    else
      GPIO_WriteHigh(GPIOC, GPIO_PIN_5);
    
    GPIO_WriteHigh(GPIOC, GPIO_PIN_2);  /*1 impulse*/
  }
    /*latch*/
  GPIO_WriteLow(GPIOC, GPIO_PIN_4);
  GPIO_WriteHigh(GPIOC, GPIO_PIN_4);
  
}



void initMatrix(void)
{
  
  putINmatrix (0xFFFFFFFF);
  
  /*u32 full = 0xFFFFFFFF;
  char i;
  char data;
 
  
  for (i=0; i<32; ++i)
  {
    
    data = (full >> i) &1;
    GPIO_WriteLow(GPIOC, GPIO_PIN_2);
        
    if (data == 0)
      GPIO_WriteLow(GPIOC, GPIO_PIN_5);
    else
      GPIO_WriteHigh(GPIOC, GPIO_PIN_5);
    
    GPIO_WriteHigh(GPIOC, GPIO_PIN_2);
  }
  
  GPIO_WriteLow(GPIOC, GPIO_PIN_4);
  GPIO_WriteHigh(GPIOC, GPIO_PIN_4);*/
  
  
}

void lightMYled (u8 x, u8 y, u8 colour){
  
    /*set up anod output in coord. y*/
  u8 anod = 0xFF;
  anod &= ~( 1 << (x - 1));
  
    /*set up green colour*/
  u32 greenColour = 0xFF;
  if ((colour &1) == 0)
    greenColour &= ~(1 << (y - 1));
  
    /*set up red colour*/
  u32 redColour = 0xFF;
  if (((colour >> 1) &1) == 0)
    redColour &= ~(1 << (y - 1));
  
  /*set up blue colour*/
  u32 blueColour = 0xFF;
  if (((colour >> 2) &1) == 0)
    blueColour &= ~(1 << (y - 1));
  
  
  u32 full = 0;
    
  full = anod + (greenColour << 8 ) + (redColour << 16) + (blueColour << 24);
  
  putINmatrix (full);
  
  
}