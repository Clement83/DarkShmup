
const byte Hfight[] PROGMEM = {
  8,4,0x90,0x90,0xF0,0x90,};
const byte Raider[] PROGMEM = {
  8,6,0xB4,0xFC,0x84,0xFC,0x48,0x30,};
const byte Tfi[] PROGMEM = {
  8,7,0x81,0x99,0xBD,0xE7,0xE7,0xBD,0x99,};
const byte bugs[] PROGMEM = {
  8,8,0x82,0x44,0x28,0xBA,0xFE,0xD6,0xBA,0x82,};
const byte etoile[] PROGMEM = {
  16,9,0x52,0x80,0x21,0x0,0x92,0x40,0x4C,0x80,0x3F,0x0,0x4C,0x80,0x92,0x40,0x21,0x0,0x52,0x80,};

const byte* const GetSpriteEnnemi(uint8_t num)
{
  switch(num)
  {
  case 0 :
    return Hfight;
    break;
  case 1 :
    return Raider;
    break;
  case 2 :
    return Tfi;
  case 3 :
    return bugs;
    break;
  case 4 :
    return etoile;
    break;
  }
}

bool testColision(uint8_t bx,uint8_t by, StarShip *en)
{
  uint8_t w = 0;
  uint8_t h = 0;
  switch(en->Skin)
  {
  case 0 :
    h = w = 4;
    break;
  case 1 :
    h = w = 6;
    break;
  case 2 :
     w = 8;
     h = 7;
  case 3 :
     w = 8;
     h = 7;
    break;
  case 4 :
     w = 10;
     h = 9;
    break;
  }
  
  return gb.collidePointRect(bx,by,en->PosX,en->PosY,w,h);
}

bool testColisionPlayer(uint8_t bx,uint8_t by, StarShipPlayer *en)
{
  uint8_t w = 0;
  uint8_t h = 0;
  switch(en->Skin)
  {
  case 0 :
    h = w = 10;
    break;
  case 1 :
    h = w = 10;
    break;
  case 2 :
     w = 7;
     h = 9;
    break;
  }
  
  return gb.collidePointRect(bx,by,en->PosX,en->PosY,w,h);
}


void UpdatePosVaisseauEnnemie(StarShip *en)
{
  switch (en->Skin)
  {
  case 0 :
    //return Hfight;
    UpdateBugsStarShip(en);
    break;
  case 1 :
    // return Raider;
    UpdateBugsStarShip(en);
    break;
  case 2 :
    // return Tfi;
    UpdateTFightStarShip(en);
  case 3 :
    //return bugs;
    UpdateBugsStarShip(en);
    break;
  case 4 :
    // return etoile;
    UpdateBugsStarShip(en);
    break;
  }
}


void UpdateBugsStarShip(StarShip *en)
{

  if(en->PosY>0)
  {
    //des qu'il sont sur l'ecran leur vie commance
    en->NbFrameLife++;
  }
  else if(en->PosY<0 && en->NbFrameLife == 0)
  {
    en->VY = VITTESSE_SHIP;
    en->VX = VITTESSE_SHIP;
  }

  if(random(0,100) ==0 &&en->NbFrameLife>0 )
  {
    //feux!
    addBullet(*en);
  }
  if(en->NbFrameLife>en->FrameLife)
  {
    en->VY = VITTESSE_SHIP;
    if(en->PosX>44)
      en->VX = VITTESSE_SHIP;
    else
      en->VX = -VITTESSE_SHIP;
  }
  else
  {
    if(en->NbFrameLife >5 && en->NbFrameLife%5 == 0)
    {
      en->VY = -en->VY;
    }
    if(en->PosX <0 ||en->PosX>LCDWIDTH-16 )
    {
      en->VX = -en->VX;
    }
  }
}


void UpdateTFightStarShip(StarShip *en)
{

  if(en->PosY>5)
  {
    //On compte le temps de vie du vaisseau
    en->NbFrameLife++;
    en->VY = 0;
  }
  else if(en->PosY<0 && en->NbFrameLife == 0)
  {
    //Animation arriver
    en->VY = VITTESSE_SHIP;
    //en->VX = VITTESSE_SHIP;
  }

  if(random(0,50)==0 )
  {
    //feux!
    addBullet(*en);
  }
  if(en->NbFrameLife>en->FrameLife)
  {
    //Animation de fin
    en->VY = VITTESSE_SHIP;
    if(en->PosX>44)
      en->VX = VITTESSE_SHIP;
    else
      en->VX = -VITTESSE_SHIP;
  }
  else
  {
    //animation de vie
    if(en->NbFrameLife >0 && en->NbFrameLife%20 == 0)
    {
      if(en->VX == 0) en->VX = VITTESSE_SHIP;
      en->VX = -en->VX;
    }
  }
}

void addBullet(StarShip strSh)
{
  uint8_t posB = 0;
  while(EnnemieBullet[posB].IsAlive && posB <NBMAX_ENNEMI_BULLET)posB++;
 
  if(posB<NBMAX_ENNEMI_BULLET)
  {
    Bullet *b1 = &EnnemieBullet[posB];
    b1->Dmg = 1;
    b1->IsAlive = true;
    b1->PosX = strSh.PosX;
    b1->PosY = strSh.PosY;
  }
}
void addExplosion(uint8_t posX,uint8_t posY)
{
  uint8_t posB = 0;
  while(ExplosionTab[posB].IsAlive && posB <NBMAX_EXPLOSION)posB++;
 
  if(posB<NBMAX_EXPLOSION)
  {
    Explosion *ex1 = &ExplosionTab[posB];
    ex1->Temps = 0;
    ex1->TempsMax = 10;
    ex1->IsAlive = true;
    ex1->PosX = posX;
    ex1->PosY = posY;
  }
}
