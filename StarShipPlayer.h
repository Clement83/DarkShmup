
#if !defined (StarShipPlayer_H)
#define StarShipPlayer_H

#include <SPI.h>

class StarShipPlayer 
{
  public:
    byte TypeDark;//0 black, 1 white
    uint8_t Skin;//pour les different skin possible
    int8_t PosX;
    int8_t PosY;
    uint8_t Life;
    int8_t SpeedX;
    int8_t MaxSpeedX;
    int8_t PuissanceTire;
};

#endif 

