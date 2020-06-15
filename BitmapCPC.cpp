#include  <afxwin.h>

#include  "Constantes.h"
#include  "BitmapCPC.h"
#include  "Amsdos.h"


static StRVB RgbCPC[ 27 ] =
    {
        { 0x00, 0x00, 0x00, 0x00 },
        { 0x7F, 0x00, 0x00, 0x00 },
        { 0xFE, 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x7F, 0x00 },
        { 0x7F, 0x00, 0x7F, 0x00 },
        { 0xFE, 0x00, 0x7F, 0x00 },
        { 0x00, 0x00, 0xFE, 0x00 },
        { 0x7F, 0x00, 0xFE, 0x00 },
        { 0xFE, 0x00, 0xFE, 0x00 },
        { 0x00, 0x7F, 0x00, 0x00 },
        { 0x7F, 0x7F, 0x00, 0x00 },
        { 0xFE, 0x7F, 0x00, 0x00 },
        { 0x00, 0x7F, 0x7F, 0x00 },
        { 0x7F, 0x7F, 0x7F, 0x00 },
        { 0xFE, 0x7F, 0x7F, 0x00 },
        { 0x00, 0x7F, 0xFE, 0x00 },
        { 0x7F, 0x7F, 0xFE, 0x00 },
        { 0xFE, 0x7F, 0xFE, 0x00 },
        { 0x00, 0xFE, 0x00, 0x00 },
        { 0x7F, 0xFE, 0x00, 0x00 },
        { 0xFE, 0xFE, 0x00, 0x00 },
        { 0x00, 0xFE, 0x7F, 0x00 },
        { 0x7F, 0xFE, 0x7F, 0x00 },
        { 0xFE, 0xFE, 0x7F, 0x00 },
        { 0x00, 0xFE, 0xFE, 0x00 },
        { 0x7F, 0xFE, 0xFE, 0x00 },
        { 0xFE, 0xFE, 0xFE, 0x00 }
    };


StRVB GetPalCPC( int c, BOOL CpcPlus )
{
    static StRVB Col;

    if ( CpcPlus )
        {
        Col.b = ( BYTE )( ( c & 0x0F ) * 17 );
        Col.r = ( BYTE )( ( ( c & 0xF0 ) >> 4 ) * 17 );
        Col.v = ( BYTE )( ( ( c & 0xF00 ) >> 8 ) * 17 );
        return( Col );
        }
    if ( c >= 0 && c < 27 )
        return( RgbCPC[ c ] );

    return( RgbCPC[ 0 ] );
}


int GetRgbCPC( int c, BOOL CpcPlus )
{
    if ( CpcPlus )
        {
        return( ( ( c & 0xF0 ) >> 4 ) * 17 
              + ( ( c & 0xF00 ) * 17 )
              + ( ( c & 0x0F ) * 0x110000 )
              );
        }

    if ( c >= 0 && c < 27 )
        {
        StRVB i = RgbCPC[ c ];
        return( ( i.b << 16 ) + ( i.v << 8 ) + i.r );
        }
    return( GetSysColor( COLOR_3DFACE ) );
}


void LisseBitmap( StRVB * MemBitmap, int Tx )
{
    for ( int y = 0; y < TAILLE_BITMAP_Y; y += 2 )
        for ( int x = 0; x < TAILLE_BITMAP_X; x += Tx )
            for ( int i = 0; i < Tx; i++ )
                {
                MemBitmap[ i + x + TAILLE_BITMAP_X * ( y + 1 ) ] =
                MemBitmap[ x + TAILLE_BITMAP_X * ( y + 1 ) ] =
                MemBitmap[ i + x + TAILLE_BITMAP_X * y ] =
                MemBitmap[ x + TAILLE_BITMAP_X * y ];
                }
}


void CBitmapCPC::InitPalette( int * Mode, int * p, int * Plus )
{
    /*
    Si sauvegardé avec ConvImgCpc, alors la palette se trouve
    dans l'image...
    */
    if (  BitmapCPC[ 0x7D0 ] == 0x3A
       && BitmapCPC[ 0x7D1 ] == 0xD0
       && BitmapCPC[ 0x7D2 ] == 0xD7
       && BitmapCPC[ 0x7D3 ] == 0xCD
       )
        {
        * Mode = BitmapCPC[ 0x17D0 ];
        for ( int i = 0; i < 16; i++ )
            Palette[ i ] = BitmapCPC[ 0x17D1 + i ];

        memcpy( p, Palette, sizeof( Palette ) );
        * Plus = 0;
        }
    else
        // CPC +, écran standard
        if (  BitmapCPC[ 0x7D0 ] == 0xF3
           && BitmapCPC[ 0x7D1 ] == 0x01
           && BitmapCPC[ 0x7D2 ] == 0x11
           && BitmapCPC[ 0x7D3 ] == 0xBC
           )
            {
            for ( int i = 0; i < 16; i++ )
                Palette[ i ] = BitmapCPC[ 0x17D1 + i * 2 ] + 256 * BitmapCPC[ 0x17D2 + i * 2 ];

            memcpy( p, Palette, sizeof( Palette ) );
            * Plus = 1;
            }
}


void CBitmapCPC::DepactOCP( void )
{
    static BYTE BufTmp[ 0x4000 ];
    int PosIn = 0, PosOut = 0;
    int LgOut, CntBlock = 0;

    memcpy( BufTmp, BitmapCPC, sizeof( BufTmp ) );
    memset( BitmapCPC, 0, 0x4000 );
    while( PosOut < 0x4000 )
        {
        if ( ! strncmp( ( char * )&BufTmp[ PosIn ], "MJH", 3 ) )
            {
            PosIn += 3;
            LgOut = BufTmp[ PosIn++ ];
            LgOut += ( BufTmp[ PosIn++ ] << 8 );
            CntBlock = 0;
            while( CntBlock < LgOut )
                {
                if ( ! strncmp( ( char * )&BufTmp[ PosIn ], "MJH", 3 ) )
                    break;

                BYTE a = BufTmp[ PosIn++ ];
                if ( a == MARKER_OCP )
                    {
                    int c = BufTmp[ PosIn++ ];
                    a = BufTmp[ PosIn++ ];
                    if ( ! c )
                        c = 0x100;

                    for ( int i = 0; i < c && CntBlock < LgOut; i++ )
                        {
                        BitmapCPC[ PosOut++ ] = a;
                        CntBlock++;
                        }
                    }
                else
                    {
                    BitmapCPC[ PosOut++ ] = a;
                    CntBlock++;
                    }
                }
            }
        else
            PosOut = 0x4000;
        }
}


BOOL CBitmapCPC::CreateImageFile( char * Nom, int * Mode, int * p, int * Plus, BOOL LectP )
{
    static BYTE Entete[ 0x80 ];
    BOOL Ret = FALSE;
    DWORD Nb;

    HANDLE hFile = CreateFile( Nom
                             , FILE_READ_DATA
                             , FILE_SHARE_READ
                             , NULL
                             , OPEN_EXISTING
                             , FILE_ATTRIBUTE_NORMAL
                             , NULL
                             );
    if ( hFile )
        {
        ReadFile( hFile, Entete, sizeof( Entete ), &Nb, NULL );
        if ( CheckAmsdos( Entete ) )
            {
            Ret = TRUE;
            ReadFile( hFile, BitmapCPC, sizeof( BitmapCPC ), &Nb, NULL );
            if ( ! strncmp( ( char * )BitmapCPC, "MJH", 3 ) )
                DepactOCP();

            memcpy( Palette, p, sizeof( Palette ) );
            if ( LectP )
                InitPalette( Mode, p, Plus );
            }
        CloseHandle( hFile );
        }
    return( Ret );

}


void CBitmapCPC::Render( StRVB * Bitmap, int Mode, BOOL CpcPlus )
{
    int AdrCPC = 0, i, p0, p1, p2, p3;

    for ( int y = 0; y < TAILLE_BITMAP_Y; y += 2 )
        {
        int AdrBitmap = TAILLE_BITMAP_X * y;
        for ( int x = 0; x < 80; x++ )
            {
            BYTE Octet = BitmapCPC[ AdrCPC + x ];
            switch( Mode )
                {
                case 0 :
                    p0 = ( Octet >> 7 )
                       + ( ( Octet & 0x20 ) >> 3 )
                       + ( ( Octet & 0x08 ) >> 2 )
                       + ( ( Octet & 0x02 ) << 2 );
                    p1 = ( ( Octet & 0x40 ) >> 6 )
                       + ( ( Octet & 0x10 ) >> 2 )
                       + ( ( Octet & 0x04 ) >> 1 )
                       + ( ( Octet & 0x01 ) << 3 );
                    Bitmap[ AdrBitmap ] = GetPalCPC( Palette[ p0 ], CpcPlus );
                    AdrBitmap += 4;
                    Bitmap[ AdrBitmap ] = GetPalCPC( Palette[ p1 ], CpcPlus );
                    AdrBitmap += 4;
                    break;

                case 1 :
                case 3 :
                    p0 = ( ( Octet >> 7 ) & 1 ) + ( ( Octet >> 2 ) & 2 );
                    p1 = ( ( Octet >> 6 ) & 1 ) + ( ( Octet >> 1 ) & 2 );
                    p2 = ( ( Octet >> 5 ) & 1 ) + ( ( Octet >> 0 ) & 2 );
                    p3 = ( ( Octet >> 4 ) & 1 ) + ( ( Octet << 1 ) & 2 );
                    Bitmap[ AdrBitmap++ ] = GetPalCPC( Palette[ p0 ], CpcPlus );
                    AdrBitmap++;
                    Bitmap[ AdrBitmap++ ] = GetPalCPC( Palette[ p1 ], CpcPlus );
                    AdrBitmap++;
                    Bitmap[ AdrBitmap++ ] = GetPalCPC( Palette[ p2 ], CpcPlus );
                    AdrBitmap++;
                    Bitmap[ AdrBitmap++ ] = GetPalCPC( Palette[ p3 ], CpcPlus );
                    AdrBitmap++;
                    break;

                case 2 :
                    for ( i = 8; i--; )
                        Bitmap[ AdrBitmap++ ] = GetPalCPC( Palette[ ( Octet >> i ) & 1 ], CpcPlus );
                    break;
                }
            }
        AdrCPC += 0x800;
        if ( AdrCPC > 0x3FFF )
            AdrCPC -= 0x3FB0;
        }
    int Tx = 4 >> Mode;
    LisseBitmap( Bitmap, Tx );
}
