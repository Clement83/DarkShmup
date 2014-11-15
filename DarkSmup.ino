//imports the SPI library (needed to communicate with Gamebuino's screen)
#include <SPI.h>
#include <stdint.h>
//imports the Gamebuino library
#include <Gamebuino.h>
//creates a Gamebuino object named gb
Gamebuino gb;

#include "StarShip.h"
#include "Bullet.h"
#include "StarShipPlayer.h"
#define VITTESSE_SHIP 1
#define STARS 12
#define MAX_SCROLL_PLAYER_X 2
extern const byte font3x3[]; //a really tiny font
extern const byte font3x5[]; //a small but efficient font (default)
extern const byte font5x7[]; //a large, comfy font

byte starspeed = 1;
byte star[STARS*2];

void drawStarShip(StarShip ship);
const byte* const GetSpritePlayer(uint8_t num);
void tasseTabEnnemie(uint8_t index);
const char* const GetResumePlayer(uint8_t num);
void UpdatePosVaisseauEnnemie(StarShip *en);
void UpdateBugsStarShip(StarShip *en);
void UpdateBugsTFight(StarShip *en);
bool testColision(uint8_t bx,uint8_t by, StarShip *en);

const byte TitleScreen[] PROGMEM = {64,31,0x1,0xFF,0xFF,0xFE,0x0,0x78,0x0,0x10,0x1,0xFF,0xFF,0xFE,0x3C,0x3,0x80,0x70,0x3,0xFF,0xFF,0xC0,0x0,0x0,0x3,0xF0,0x7F,0xFF,0xFF,0x80,0x0,0x0,0xF,0xF0,0x7F,0xFF,0xFF,0x0,0x0,0x0,0x3F,0xF0,0x7F,0xFF,0xFE,0x0,0x3,0x0,0xF3,0xF0,0x1F,0xFF,0xFC,0x0,0x3,0x83,0xE3,0xF0,0xF,0xFF,0xF8,0x0,0x0,0xCF,0xCF,0xF0,0xF,0xFF,0xF8,0x0,0x0,0x5F,0x9F,0xF0,0xF,0xFF,0xF8,0x0,0x0,0xCF,0x3F,0xF0,0xF,0xFF,0xF8,0x0,0x3,0xE6,0x7F,0xF0,0x1F,0xFF,0xFC,0x0,0xF,0xE6,0x7F,0xF0,0x7F,0xFF,0x1E,0x0,0x3C,0xE0,0x73,0xF0,0x7F,0xFE,0xF,0xC0,0xFC,0xE0,0x73,0xF0,0x7F,0xFE,0xF,0xE3,0xFC,0x0,0x3,0xF0,0x7F,0xFE,0xF,0xEF,0xFC,0x0,0x3,0xF0,0x7F,0xFE,0xF,0xFF,0xFC,0x19,0x83,0xF0,0x7F,0xFF,0x1F,0xFF,0xFC,0x19,0x83,0xF0,0x1F,0xFF,0xFF,0xFF,0xFC,0xC0,0x33,0xF0,0xF,0xFF,0xFF,0xFF,0xFC,0xC0,0x33,0xF0,0xF,0xFF,0xF7,0xFF,0xFC,0xFF,0xF3,0xF0,0xF,0xFF,0xC7,0xFF,0xFC,0xFF,0xF3,0xF0,0xF,0xFF,0x7,0xFF,0xFC,0xFF,0xF3,0xF0,0x1F,0xFC,0x3,0xFF,0xFF,0xFF,0xFF,0xF0,0x7F,0xF0,0x1,0xFF,0xFF,0xFF,0xFF,0xF0,0x7F,0xC0,0x0,0xFF,0xFF,0xFF,0xFF,0xF0,0x7F,0x0,0x0,0x7F,0xFF,0xFF,0xFF,0xF0,0x2,0x0,0x0,0x3F,0xFF,0xFF,0xFF,0xF0,0x4,0x0,0x0,0x1,0xC7,0xFC,0x7F,0xF0,0xC,0x0,0x0,0x1,0xFF,0x1F,0xFF,0xF0,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,};

#define NB_SKIN_PLAYER 3
const char * txtFm  = "Vaisseau lour et lent capable de detruire tous les ennemis";
const byte fm[] PROGMEM = {16,10,0x80,0x40,0x8C,0x40,0xCC,0xC0,0xFF,0xC0,0xF3,0xC0,0xFF,0xC0,0xFF,0xC0,0xFF,0xC0,0x7F,0x80,0x4C,0x80,};
const char * txtRapide  = "Vaisseau polivalent. Un bon copromie entre vitesse et puissance de feux";
const byte rapide[] PROGMEM = {16,10,0xC,0x0,0xC,0x0,0x8C,0x40,0x92,0x40,0x8C,0x40,0xFF,0xC0,0xFF,0xC0,0x8C,0x40,0x12,0x0,0x21,0x0,};
const char * txtSmall  = "Vaisseau petit et maniable. Peux esquiver facilement les tires ennemie";
const byte small[] PROGMEM = {8,9,0x10,0x10,0x10,0x28,0xBA,0xFE,0x10,0x10,0x28,};

const byte EtoileDeco[] PROGMEM = {8,3,0x40,0xA0,0x40,};
const byte Munition[] PROGMEM = {8,6,0x40,0xA0,0xE0,0xA0,0xA0,0xE0,};
const byte infinie[] PROGMEM = {8,3,0x50,0xA8,0x50,};


#define NBMAX_ENNEMI  18
#define NBMIN_ENNEMI_SCREEN  2

StarShip Ennemies[NBMAX_ENNEMI];
StarShipPlayer player;

#define NBMAX_ENNEMI_BULLET  20
Bullet EnnemieBullet[NBMAX_ENNEMI_BULLET];


#define NBMAX_PLAYER_BULLET  10
Bullet PlayerBullet[NBMAX_PLAYER_BULLET];

//uint8_t posX = 21;
//uint8_t posY = 21;

int8_t nbEnemisAlive = 0;
unsigned int Score = 0;
unsigned int OldScore = 0;
unsigned int NbMunition = 1000;
bool isInDarkWorld;
void setup()
{
  // initialize the Gamebuino object
  gb.begin();
  //display the main menu:
  gb.titleScreen(TitleScreen);
  gb.pickRandomSeed();
  
  isInDarkWorld = false;
  nbEnemisAlive = 0;
  Score = 0;
  OldScore = 0;
  
  for(byte j=0;j<STARS;j++){
      star[j*2] += random(0,LCDHEIGHT); 
      star[j*2+1] = random(0,LCDWIDTH); 
  }
  (&player)->Life = 10;
  (&player)->Skin = 0;
  (&player)->PosY = 36;
  (&player)->PosX = 15;
   (&player)->SpeedX = 0;
  
    
}


void loop()
{
  ChoixVaisseau();
  initilisePlayerByType();
  //returns true when it's time to render a new frame (20 times/second)
  while(true)
  {
    if(gb.update())
    {
      updateWorld();
      drawWorld();
      updateStars();
    }
  }
}
#define OFFSET_DEF 17
void ChoixVaisseau()
{
    gb.battery.show = false;
  int8_t offset = OFFSET_DEF;
   while(true)
  {
     if(gb.update())
    {
      
      if(gb.buttons.pressed(BTN_A))
      {
       break; 
      }
      
       if(gb.buttons.pressed(BTN_RIGHT))
      { 
        (&player)->Skin++;
       if((&player)->Skin >= NB_SKIN_PLAYER)
       {
         (&player)->Skin = 0;
       }
         offset=OFFSET_DEF;
      }
      if(gb.buttons.pressed(BTN_LEFT))
      { 
       if((&player)->Skin ==0 )
       {
         (&player)->Skin = NB_SKIN_PLAYER-1;
       }
       else 
       {
        (&player)->Skin--;
       }
         offset=OFFSET_DEF;
      }
      
      if(offset>0) 
      {
        offset--;
      }
      gb.display.textWrap = true;
      gb.display.print(GetResumePlayer((&player)->Skin));
//      gb.display.print((&player)->PosX);
      gb.display.drawBitmap((&player)->PosX - offset , (&player)->PosY, GetSpritePlayer((&player)->Skin));
    }
  } 
}
const char* const GetResumePlayer(uint8_t num)
{
  switch(num)
	{
		case 0 : 
                return txtFm;
		break;
		case 1 : 
                return txtRapide;
		break;
		case 2 : 
                return txtSmall;
		break;
        }
}
const byte* const GetSpritePlayer(uint8_t num)
{
	switch(num)
	{
		case 0 : 
                return fm;
		break;
		case 1 : 
                return rapide;
		break;
		case 2 : 
                return small;
		break;
        }
}


void updateStars(){
  for(byte j=0;j<STARS;j++){
    star[j*2] += VITTESSE_SHIP*2; 
    if(star[j*2] > LCDHEIGHT){
      star[j*2] -= LCDHEIGHT ; 
      star[j*2+1] = random(0,LCDWIDTH); 
    }
    
    //gb.display.setColor(INVERT);
      gb.display.drawBitmap(star[j*2+1], star[j*2], EtoileDeco);
  }
}



void drawWorld()
{
    gb.battery.show = false;
  if(isInDarkWorld)
    {
      gb.display.fillScreen(BLACK);
      gb.display.setColor(WHITE);
    }
    else 
    {
      //gb.display.fillScreen(WHITE);
      gb.display.setColor(BLACK);
    }
      for(uint8_t i=0;i<nbEnemisAlive;i++)
      {        
       if(Ennemies[i].TypeDark == isInDarkWorld && Ennemies[i].Life>0)
       {
         drawStarShip(Ennemies[i]);
       }
      }
    if(gb.buttons.pressed(BTN_B))
    {
      isInDarkWorld = !isInDarkWorld;
    }
    
    //gb.display.setColor(INVERT);
    gb.display.drawBitmap((&player)->PosX, (&player)->PosY, GetSpritePlayer((&player)->Skin));
    
    updateAndDrawHud();
    UpdateAndDrawBullet();
}

void updateAndDrawHud()
{
  gb.display.setFont(font3x3);
    //gestion du score
    if(OldScore<Score) OldScore+=7;
    if(OldScore>Score) OldScore=Score;
    displayInt(OldScore,10,1,7);
  gb.display.setFont(font3x5);
}

void UpdateAndDrawBullet()
{
  for(uint8_t i=0;i<NBMAX_PLAYER_BULLET;i++)
  {
    Bullet *b = &PlayerBullet[i];
    if(b->IsAlive)
    {
      b->PosY -=2;
      if(b->PosY<0)
      {
        b->IsAlive = false;
      }
      
      for(uint8_t cptEnnemi=0;cptEnnemi<nbEnemisAlive;cptEnnemi++)
      {
        //je ne peut toucher que ceux dans la meme dimention que moi
        if(Ennemies[cptEnnemi].TypeDark == isInDarkWorld)
        {
          if(testColision(PlayerBullet[i].PosX,PlayerBullet[i].PosY, &Ennemies[cptEnnemi]))
          {
            (&Ennemies[cptEnnemi])->Life -= PlayerBullet[i].Dmg;
            b->IsAlive = false;
            Score += 91;//pour faire un score a la con qui monte vite
          }
        }
      }
      gb.display.setColor(INVERT);
      gb.display.drawPixel(PlayerBullet[i].PosX,PlayerBullet[i].PosY);
    }
  }
}

void tasseTabEnnemie(uint8_t index)
{
  for(int i=index;i<nbEnemisAlive-1;i++)
  {
    StarShip *enMort = &Ennemies[i];
    StarShip *enTemp = &Ennemies[i+1];
    //enTemp-> = enMort->
    enMort->TypeDark = enTemp->TypeDark;
    enMort->PosX = enTemp->PosX;
    enMort->PosY = enTemp->PosY;
    enMort->Life = enTemp->Life;
    enMort->Skin = enTemp->Skin;
    enMort->FrameLife = enTemp->FrameLife;
    enMort->NbFrameLife = enTemp->NbFrameLife;
  }
}

void updateWorld()
{
    if(nbEnemisAlive<=NBMIN_ENNEMI_SCREEN)
    {
      itsTimeToPop();
    }
  
  uint8_t i=0;
  while(i<nbEnemisAlive)
  {
   StarShip *en = &Ennemies[i];
    
    UpdatePosVaisseauEnnemie(en);
    en->PosX+=en->VX;
    en->PosY+=en->VY;
    if(en->PosY > 60 || en->Life <= 0)
    {
      en->Life = 0;
      tasseTabEnnemie(i);
      nbEnemisAlive--;
    }
    else 
    {
      i++;
    }
  }
    
    if(gb.buttons.repeat(BTN_LEFT,1))
    {
        if((&player)->SpeedX>-player.MaxSpeedX)
           (&player)->SpeedX--;
    }
    else if(gb.buttons.repeat(BTN_RIGHT,1))
    {
       if((&player)->SpeedX<player.MaxSpeedX)
           (&player)->SpeedX++;
    }
    else 
    {
      (&player)->SpeedX = 0;
    }
    if(gb.buttons.pressed(BTN_A))
    {
       PlayerFire();
    }
    
    (&player)->PosX+=player.SpeedX;
    
    if(player.PosX>=LCDWIDTH-16 || player.PosX<=0)
    {
      (&player)->PosX-=player.SpeedX;
      player.SpeedX = 0;
    }
    
}



//101 starship function
void drawStarShip(StarShip ship)
{
    //gb.display.setColor(INVERT);
  gb.display.drawBitmap(ship.PosX , ship.PosY, GetSpriteEnnemi(ship.Skin));
}


void displayText(String s, byte x, byte y, byte t){
  gb.display.cursorX = x;
  gb.display.cursorY = y;  
  gb.display.fontSize = t;
  gb.display.print(s);
}
void displayText(String s, byte x, byte y){
  displayText(s,x,y,1);
}
void displayInt(long l, byte Tx, byte Ty, byte fig){
  gb.display.fontSize = 1;
  String sl = String(l);
  while(sl.length() < fig){
    sl = "0" + sl;  
  }
  gb.display.cursorX = Tx;
  gb.display.cursorY = Ty;  
  gb.display.print(sl);
}




