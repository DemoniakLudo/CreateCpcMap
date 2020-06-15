#ifndef SPRITECPC_H
#define SPRITECPC_H


#include  "BitmapCPC.h"


class SpriteCPC
{
public :
    SpriteCPC() {};
    ~SpriteCPC() {};
    void SetDatas( BYTE * Datas, int Longueur ) 
        {
        if ( Longueur <= sizeof( BitmapCPC ) )
            memcpy( BitmapCPC, Datas, Longueur );
        }
    BYTE * GetDatas( void ) { return( BitmapCPC ); }
    void Render( StRVB * Bitmap
               , int TailleBmX
               , int Mode
               , int Palette[ 16 ]
               , int NbLig
               , int NbCol
               , BOOL CpcPlus
               );

private :
    void EcrisOctet( StRVB * Bitmap
                   , BYTE Octet
                   , int Mode
                   , int Palette[ 16 ]
                   , BOOL CpcPlus
                   );

    BYTE BitmapCPC[ 0x4000 ];
};


BOOL DejaSprite( SpriteCPC * a, BYTE * Data );


#endif
