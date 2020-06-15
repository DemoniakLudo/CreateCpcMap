#ifndef BITMAPCPC_H
#define BITMAPCPC_H


#define     MARKER_OCP      1


#include  "Constantes.h"


//
// Structure palette (comme OCP art studio)
//
typedef struct
    {
    BYTE    Mode;
    BYTE    AnimFlag;
    BYTE    AnimDelay;
    BYTE    Palette[ 16 ][ 12 ];
    BYTE    Border[ 12 ];
    BYTE    ExcludedInk[ 16 ];
    BYTE    ProtectedInk[ 16 ];
    } StPal;


StRVB GetPalCPC( int c, BOOL CpcPlus );

int GetRgbCPC( int c, BOOL CpcPlus );


class CBitmapCPC
{
public :
    BOOL CreateImageFile( char * Nom, int * Mode, int * p, int * Plus, BOOL LectP );
    void Render( StRVB * Bitmap, int Mode, BOOL CpcPlus );
    BYTE * GetBitmapCPC( void ) { return( BitmapCPC ); }

private :
    void DepactOCP( void );
    void InitPalette( int * Mode, int * p, int * Plus );

    BYTE BitmapCPC[ 0x4000 ];
    int Palette[ 16 ];
};


#endif
