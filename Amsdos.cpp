#include  <afxwin.h>

#include  "Amsdos.h"


//
// Crée l'en-tête Amsdos d'un fichier
//
void CreeEntete( FILE * fp
               , char * NomFic       // Nom du fichier
               , WORD Start          // Adresse de début
               , WORD Length         // Longueur
               , WORD Entry          // Point d'entrée
               )
{
    static StAmsdos Entete;
    static char Nom[ 12 ];
    int i, l, CheckSum = 0;
    char * p;

    memset( &Entete, 0, sizeof( Entete ) );

    // Convertir le nom du fichie au format "AMSDOS" 8.3
    memset( Nom, ' ', sizeof( Nom ) );
    do
        {
        p = strchr( NomFic, '\\' );
        if ( p )
            NomFic = ++p;
        }
    while( p );
    p = strchr( NomFic, '.' );
    if ( p )
        * p++ = 0;

    l = strlen( NomFic );
    if ( l > 8 )
        l = 8;

    for ( i = 0; i < l; i++ )
        Nom[ i ] = ( char )( NomFic[ i ] & 0xDF );

    if ( p )
        for ( i = 0; i < 3; i++ )
            Nom[ i + 8 ] = ( char )( p[ i ] & 0xDF );

    // Initialisation de l'en-tête avec les valeurs passées en paramètre
    memcpy( Entete.FileName, Nom, 11 );
    BYTE * pEntete = ( BYTE * )&Entete;
    Entete.Adress = Start;
    Entete.Length = Entete.RealLength = Entete.LogicalLength = Length;
    Entete.FileType = 2;
    Entete.EntryAdress = Entry;

    // Calcul du checksum
    for ( i = 0; i < 67; i++ )
        CheckSum += * pEntete++;

    Entete.CheckSum = ( WORD )CheckSum;
    fwrite( &Entete, sizeof( Entete ), 1, fp );
}


BOOL CheckAmsdos( BYTE * Buf )
{
    int i, Checksum = 0;
    BOOL ModeAmsdos = FALSE;
    StAmsdos * pEntete = ( StAmsdos * )Buf;

    for ( i = 0; i < 67; i++ )
        Checksum += Buf[ i ];

    if ( pEntete->CheckSum == ( WORD )Checksum )
        ModeAmsdos = TRUE;

    return( ModeAmsdos );
}


