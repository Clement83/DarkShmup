
#if !defined (Explosion_H)
#define Explosion_H

#include <SPI.h>

class Explosion 
{
  public:
    int8_t PosX;
    int8_t PosY;
    int8_t Temps;
    int8_t TempsMax;
    bool IsAlive;
};

#endif 

