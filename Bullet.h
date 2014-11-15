
#if !defined (Bullet_H)
#define Bullet_H

#include <SPI.h>

class Bullet 
{
  public:
    byte TypeDark;//0 black, 1 white
    uint8_t Skin;//pour les different skin possible
    int8_t PosX;
    int8_t PosY;
    int8_t Dmg;
    bool IsAlive;
};

#endif 

