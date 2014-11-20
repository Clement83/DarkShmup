void PopPattern1()
{
    if(nbEnemisAlive+4 <=NBMAX_ENNEMI)
    {
      StarShip *s1 = &Ennemies[nbEnemisAlive];
      s1->TypeDark = 0;
      s1->PosX = 10;
      s1->PosY = -10;
      s1->Life = 1;
      s1->Skin = 0;
      s1->FrameLife = 120;
      s1->NbFrameLife = 0;
        
      StarShip *s2 =  &Ennemies[nbEnemisAlive+1];
      s2->TypeDark = 1;
      s2->PosX = 30;
      s2->PosY = -6;
      s2->Life = 1;
      s2->Skin = 3;
      s2->FrameLife = 120;
      s2->NbFrameLife = 0;
      
      StarShip *s3 =  &Ennemies[nbEnemisAlive+2];
      s3->TypeDark = 1;
      s3->PosX = 20;
      s3->PosY = -6;
      s3->Life = 1;
      s3->Skin = 3;
      s3->FrameLife = 120;
      s3->NbFrameLife = 0;
      
      StarShip *s4 =  &Ennemies[nbEnemisAlive+3];
      s4->TypeDark = 0;
      s4->PosX = 40;
      s4->PosY = -10;
      s4->Life = 1;
      s4->Skin = 0;
      s4->FrameLife = 120;
      s4->NbFrameLife = 0;
      
      nbEnemisAlive += 4;
    }
}


void PopPattern2()
{
  
    if(nbEnemisAlive+6 <=NBMAX_ENNEMI)
    {
    StarShip *s1 = &Ennemies[nbEnemisAlive+0];
    s1->TypeDark = 1;
    s1->PosX = 0;
    s1->PosY = -10;
    s1->Life = 5;
    s1->Skin = 3;
      s1->FrameLife = 120;
      s1->NbFrameLife = 0;
      
    StarShip *s2 =  &Ennemies[nbEnemisAlive+1];
    s2->TypeDark = 1;
    s2->PosX = 10;
    s2->PosY = -6;
    s2->Life = 5;
    s2->Skin = 3;
      s2->FrameLife = 120;
      s2->NbFrameLife = 0;
    
    StarShip *s3 =  &Ennemies[nbEnemisAlive+2];
    s3->TypeDark = 1;
    s3->PosX = 20;
    s3->PosY = -10;
    s3->Life = 5;
    s3->Skin = 3;
      s3->FrameLife = 120;
      s3->NbFrameLife = 0;
    
    
    StarShip *s4 = &Ennemies[nbEnemisAlive+3];
    s4->TypeDark = 0;
    s4->PosX = 0;
    s4->PosY = -20;
    s4->Life = 3;
    s4->Skin = 1;
      s4->FrameLife = 120;
      s4->NbFrameLife = 0;
      
    StarShip *s5 =  &Ennemies[nbEnemisAlive+4];
    s5->TypeDark = 0;
    s5->PosX = 10;
    s5->PosY = -16;
    s5->Life = 3;
    s5->Skin = 1;
      s5->FrameLife = 120;
      s5->NbFrameLife = 0;
    
    StarShip *s6 =  &Ennemies[nbEnemisAlive+5];
    s6->TypeDark = 0;
    s6->PosX = 20;
    s6->PosY = -20;
    s6->Life = 3;
    s6->Skin = 1;
      s6->FrameLife = 120;
      s6->NbFrameLife = 0;
    
    
    nbEnemisAlive += 6;
    }
}


void PopPatternBoss1()
{
    if(nbEnemisAlive+3 <=NBMAX_ENNEMI)
    {
    StarShip *s1 = &Ennemies[nbEnemisAlive+0];
    s1->TypeDark = 0;
    s1->PosX = 10;
    s1->PosY = -6;
    s1->Life = 3;
    s1->Skin = 2;
      s1->FrameLife = 220;
      s1->NbFrameLife = 0;
      
    StarShip *s2 =  &Ennemies[nbEnemisAlive+1];
    s2->TypeDark = 0;
    s2->PosX = 40;
    s2->PosY = -6;
    s2->Life = 3;
    s2->Skin = 2;
      s2->FrameLife = 220;
      s2->NbFrameLife = 0;
    
    StarShip *s3 =  &Ennemies[nbEnemisAlive+2];
    s3->TypeDark = 1;
    s3->PosX = 25;
    s3->PosY = -10;
    s3->Life = 30;
    s3->Skin = 4;
      s3->FrameLife = 520;
      s3->NbFrameLife = 0;

    
    
    nbEnemisAlive += 3;
    }
}


void PopPattern3()
{
    for(uint8_t i=0;i<16;i++)
    {
      if(nbEnemisAlive<=NBMAX_ENNEMI)
      {
        break;
      }
      StarShip *s1 = &Ennemies[nbEnemisAlive];
      s1->TypeDark =  i%2;
      s1->PosX = 6*i+6;
      s1->PosY = random(-15,-5);
      s1->Life = 1;
      s1->Skin = 0;
      s1->FrameLife = 90;
      s1->NbFrameLife = 0;
      nbEnemisAlive++;
      
    }
  
}

void itsTimeToPop()
{
  switch(random(0,4))
  {
     case 0 :
     PopPattern1();
     break;
     case 1 :
     PopPattern2();
     break;
     case 2:
      PopPatternBoss1();
      break;
     case 3:
      PopPattern3();
      break;
  }
}
