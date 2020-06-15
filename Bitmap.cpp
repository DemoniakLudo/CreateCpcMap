#include  <afxwin.h>

#include  "Bitmap.h"


//
// Création du bitmap
//
BOOL MonBitmap::Create( CDC * hDC, int tx, int ty )
{
    BITMAPINFO pbmi;

    TailleX = tx;
    TailleY = ty;
    pbmi.bmiHeader.biSize = sizeof( BITMAPINFOHEADER );
    pbmi.bmiHeader.biWidth = TailleX;
    pbmi.bmiHeader.biHeight = -TailleY;
    pbmi.bmiHeader.biPlanes = 1;
    pbmi.bmiHeader.biBitCount = 32;
    pbmi.bmiHeader.biCompression = BI_RGB;
    pbmi.bmiHeader.biSizeImage = 0;
    pbmi.bmiHeader.biXPelsPerMeter = 0;
    pbmi.bmiHeader.biYPelsPerMeter = 0;
    pbmi.bmiHeader.biClrUsed = 0;
    pbmi.bmiHeader.biClrImportant = 0;
    bm = CreateDIBSection( hDC->m_hDC
                         , &pbmi
                         , DIB_RGB_COLORS
                         , ( void ** )&MemBitmap
                         , NULL
                         , 0
                         );
    if ( bm )
        
        {
        DcBitmap = CreateCompatibleDC( hDC->m_hDC );
        if ( DcBitmap )
            {
            SelectObject( DcBitmap, bm );
            SetStretchBltMode( DcBitmap, COLORONCOLOR );
            Created = TRUE;
            }
        }
    return( Created );
}


//
// Suppression du bitmap
//
MonBitmap::~MonBitmap( void )
{
    if ( DcBitmap )
        DeleteDC( DcBitmap );

    if ( bm )
        DeleteObject( bm );
}


//
// Affiche le bitmap dans un "Device Context"
//
void MonBitmap::Render( HDC DcDest, int PosX, int PosY, int MulX, int MulY )
{
    StretchBlt( DcDest
          , PosX, PosY, TailleX * MulX, TailleY * MulY
          , DcBitmap, 0, 0, TailleX, TailleY
          , SRCCOPY
          );
}

//
// Efface le bitmap avec la couleur désirée
//
void MonBitmap::Clear( int Color )
{
    for ( int i = 0; i < TailleX * TailleY; i++ )
        MemBitmap[ i ] = Color;
}
