
#if !defined (StarShip_H)
#define StarShip_H

#include <SPI.h>

class StarShip 
{
  public:
    byte TypeDark;//0 black, 1 white
    uint8_t Skin;//pour les different skin possible
    int8_t PosX;
    int8_t PosY;
    int8_t VX;
    int8_t VY;
    int8_t Life;
   int NbFrameLife;
   int FrameLife;
};

#endif 

