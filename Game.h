#ifndef _GAME_
#define _GAME_

#include "Board.h"
#include "Blocks.h"
#include "IO.h"
#include <time.h>

#define WAIT_TIME 700



class Game
{
public:
    Game(Board *pBoard,Blocks *pPieces, IO *pIO, int pScreenHeight);

    void DrawScene();
    void CreateNewPiece();

    int mPosX, mPosY;      // Position of the piece that is falling down
    int mPiece, mRotation; // Kind and rotation the piece that is falling down
private:
    int mScreenHeight;
    int mNextPosX, mNextPosY;
    int mNextPiece, mNextRotation;

    Board *mBoard;
    Blocks *mPieces;
    IO *mIO;

    int GetRand(int pA, int pB);
    
    void InitGame();
    void DrawPiece(int pX, int pY, int pPiece, int pRotation);
    void DrawBoard();
};
#endif // _GAME_