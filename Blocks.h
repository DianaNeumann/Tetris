#ifndef _BLOCKS_
#define _BLOCKS_

class Blocks
{
public:

    int GetBlockType(int pPiece, int pRotation, int pX, int pY);
    int GetXInitialPosition(int pPiece, int pRotation);
    int GetYInitialPosition (int pPiece, int pRotation);
};

#endif //_BLOCKS_

