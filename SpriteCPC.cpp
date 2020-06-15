#include  <afxwin.h>

#include  "Constantes.h"
#include  "SpriteCPC.h"


void SpriteCPC::Render( StRVB * Bitmap
                       , int TailleBmX
                       , int Mode
                       , int Palette[ 16 ]
                       , int NbLig
                       , int NbCol
                       , BOOL CpcPlus
                       )
{
    int AdrCPC = 0;

    for ( int y = 0; y < NbLig; y++ )
        for ( int x = 0; x < NbCol; x++ )
            EcrisOctet( &Bitmap[ ( x << 2 ) + TailleBmX * y ]
                      , BitmapCPC[ AdrCPC++ ]
                      , Mode
                      , Palette
                      , CpcPlus
                      );
}


void SpriteCPC::EcrisOctet( StRVB * Bitmap
                          , BYTE o
                          , int Mode
                          , int Pal[ 16 ]
                          , BOOL CpcPlus
                          )
{
    switch( Mode )
        {
        case 0 :
            Bitmap[ 0 ] = 
            Bitmap[ 1 ] = GetPalCPC( Pal[ ( o >> 7 ) + ( ( o & 0x20 ) >> 3 ) + ( ( o & 0x08 ) >> 2 ) + ( ( o & 0x02 ) << 2 ) ], CpcPlus );
            Bitmap[ 2 ] = 
            Bitmap[ 3 ] = GetPalCPC( Pal[ ( ( o & 0x40 ) >> 6 ) + ( ( o & 0x10 ) >> 2 ) + ( ( o & 0x04 ) >> 1 ) + ( ( o & 0x01 ) << 3 ) ], CpcPlus );
            break;

        case 1 :
            Bitmap[ 0 ] = GetPalCPC( Pal[ ( ( o >> 7 ) & 1 ) + ( ( o >> 2 ) & 2 ) ], CpcPlus );
            Bitmap[ 1 ] = GetPalCPC( Pal[ ( ( o >> 6 ) & 1 ) + ( ( o >> 1 ) & 2 ) ], CpcPlus );
            Bitmap[ 2 ] = GetPalCPC( Pal[ ( ( o >> 5 ) & 1 ) + ( ( o >> 0 ) & 2 ) ], CpcPlus );
            Bitmap[ 3 ] = GetPalCPC( Pal[ ( ( o >> 4 ) & 1 ) + ( ( o << 1 ) & 2 ) ], CpcPlus );
            break;
        }
}


BOOL DejaSprite( SpriteCPC * a, BYTE * Data )
{
    BYTE * DataSpr = a->GetDatas();

    for ( int i = 0; i < 64; i++ )
        if ( DataSpr[ i ] != Data[ i ] )
            return( FALSE );

    return( TRUE );
}