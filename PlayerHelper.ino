

void initilisePlayerByType()
{
  
  (&player)->PosY = 36;
  (&player)->PosX = 15;
  (&player)->SpeedX = 0;
     
  switch(player.Skin)
  {
    case 0:
    (&player)->Life = 15;
     (&player)->MaxSpeedX = 2;
    (&player)->PuissanceTire = 2;
    break;
    case 1:
    (&player)->Life = 10;
     (&player)->MaxSpeedX = 3;
    (&player)->PuissanceTire = 2;
    break;
    case 2:
    (&player)->Life = 8;
     (&player)->MaxSpeedX = 4;
    (&player)->PuissanceTire = 1;
    break;
  }
}

void PlayerFire()
{
  uint8_t posB = 0;
  
  while(PlayerBullet[posB].IsAlive && posB <NBMAX_PLAYER_BULLET)posB++;
 
  if(posB<NBMAX_PLAYER_BULLET)
  {
    Bullet *b = &PlayerBullet[posB];
    
    b->Dmg = player.PuissanceTire;
    b->IsAlive = true;
    b->PosY = player.PosY;
    
    switch(player.Skin)
    {
      case 0:
        b->PosX = player.PosX;
        while(PlayerBullet[posB].IsAlive && posB <NBMAX_PLAYER_BULLET)posB++;
 
        if(posB<NBMAX_PLAYER_BULLET)
        {
          Bullet *b1 = &PlayerBullet[posB];
          b1->Dmg = player.PuissanceTire;
          b1->IsAlive = true;
          b1->PosX = player.PosX + 10;
          b1->PosY = player.PosY;
        }
      break;
      case 1:
        b->PosX = player.PosX+5;
      break;
      case 2:
        b->PosX = player.PosX+3;
      break;
    }
  }
}


