// ConsoleGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <conio.h>

void setConsoleCursorVisible(bool showFlag)
{
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO     cursorInfo;
  GetConsoleCursorInfo(out, &cursorInfo);
  cursorInfo.bVisible = showFlag; // set the cursor visibility
  SetConsoleCursorInfo(out, &cursorInfo);
}


int main()
{
  setConsoleCursorVisible(false);
  const int size = 20;
  char* game = new char[size];
  game[size - 1] = '\0';

  const char cPlayer = 'A';
  int iPlayerPos = size / 2;

  const char cEnemy = '$';
  int iEnemyPos = size-1;

  const char cBullet = '\'';
  const int iMaxBullets = 5;
  int* bullets = new int[iMaxBullets];

  for (int i = 0; i < iMaxBullets; i++)
  {
    bullets[i] = -1;
  }
  int iNumBullets = 0;

  int iInput;

  while (true)
  {
    system("cls");

    //PLAYER CONTROLS
    if (_kbhit())
    {
      iInput = _getch();
      switch (iInput)
      {
      case 'a':
        iPlayerPos--;
        break;
      case 'd':
        iPlayerPos++;
        break;
      case ' ':
        bullets[iNumBullets] = iPlayerPos + 1;
        iNumBullets++;
        if (iNumBullets > iMaxBullets) {
          iNumBullets = 0;
        }
        break;
      }
    }

    //ENEMY LOGIC
    if (iEnemyPos > iPlayerPos) iEnemyPos--;
    else iEnemyPos++;

    //BULLET LOGIC
    for (int i = 0; i < iMaxBullets; i++) {
      if (bullets[i] == iEnemyPos || bullets[i] == iEnemyPos-1)
      {
        bullets[i] = -1;
        iEnemyPos = size - 2;
      }else if (bullets[i] >= 0) 
      {
        if (bullets[i] > iPlayerPos) bullets[i]++;
        else bullets[i]--;
      }
    }

    if (iPlayerPos == iEnemyPos)
    {
      printf("GAME OVER");
      return(0);
    }

    //DRAWING
    for (int i = 0; i < size-1; i++)
    {
      game[i] = '_';
    }
    game[iPlayerPos] = cPlayer;
    game[iEnemyPos] = cEnemy;
    for (int i = 0; i < iMaxBullets; i++) {
      
      if (bullets[i] >= 0)
      {
        game[bullets[i]] = cBullet;
      }
      
    }

    printf("%s", game);
    Sleep(500);
  }
  
  delete [] game;
}
