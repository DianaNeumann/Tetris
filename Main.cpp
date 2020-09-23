#include "Game.h"
#include <windows.h>
#include <cstdint>

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    IO mIO;
    int mScreenHeight = mIO.GetScreenHeight();

    Blocks mPieces; // pieces)
    Board mBoard(&mPieces, mScreenHeight); // board)
    Game mGame(&mBoard, &mPieces, &mIO, mScreenHeight); // game)))                                                         //))))

    uint64_t mTime1 = SDL_GetTicks();
    
    /* -_-_-_-_- MAIN LOOP -_-_-_-_-*/
    while(!mIO.IsKeyDown(SDLK_ESCAPE)){
        
        /* risuem*/
        mIO.ClearScreen();
        mGame.DrawScene();
        mIO.UpdateScreen();

        /* input*/
        int mKey = mIO.Pollkey();

        switch(mKey)
        {
            case(SDLK_RIGHT):
            {
                if(mBoard.IsPossibleMovement(mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
                mGame.mPosX++;
                break;
            }

            case(SDLK_LEFT):
            {
                if (mBoard.IsPossibleMovement(mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
                mGame.mPosX--;  
                break;
            }

            case (SDLK_DOWN):
            {
                if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
                mGame.mPosY++;  
                break;
            }

            case(SDLK_x): // X = Piece will fall down directly to the ground
            {
                // Check collision from up to down
                while (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation))
                { mGame.mPosY++; }

                mBoard.StorePiece(mGame.mPosX, mGame.mPosY - 1, mGame.mPiece, mGame.mRotation);
 
                mBoard.DeletePossibleLines ();
 
                if (mBoard.IsGameOver()){ mIO.Getkey(); exit(0); }
                mGame.CreateNewPiece();
                break;
            }

            case(SDLK_z): // Z = rotate the piece
            {
                if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRotation + 1) % 4))
                mGame.mRotation = (mGame.mRotation + 1) % 4;
                break;
            }
        }

        uint64_t mTime2 = SDL_GetTicks();

		if ((mTime2 - mTime1) > WAIT_TIME){
			if (mBoard.IsPossibleMovement (mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation)){
				mGame.mPosY++;
			}
			else{
				mBoard.StorePiece (mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);
				mBoard.DeletePossibleLines ();

				if (mBoard.IsGameOver()){
					mIO.Getkey();
					exit(0);
				}

				mGame.CreateNewPiece();
			}

			mTime1 = SDL_GetTicks();
		}
        
    }

    return 0;
}
