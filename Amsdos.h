#ifndef AMSDOS_H
#define AMSDOS_H


//
// Structure d'une entrée AMSDOS
//
typedef struct
    {
    BYTE    UserNumber;             // User
    BYTE    FileName[ 15 ];         // Nom + extension
    BYTE    BlockNum;               // Numéro du premier bloc (disquette)
    BYTE    LastBlock;              // Numéro du dernier bloc (disquette)
    BYTE    FileType;               // Type de fichier
    WORD    Length;                 // Longueur
    WORD    Adress;                 // Adresse
    BYTE    FirstBlock;             // Premier bloc de fichier (disquette)
    WORD    LogicalLength;          // Longueur logique
    WORD    EntryAdress;            // Point d'entrée
    BYTE    Unused[ 0x24 ];
    WORD    RealLength;             // Longueur réelle
    BYTE    BigLength;              // Longueur réelle (3 octets)
    WORD    CheckSum;               // CheckSum Amsdos
    BYTE    Unused2[ 0x3B ];
    } StAmsdos;


void CreeEntete( FILE * fp
               , char * NomFic
               , WORD Start
               , WORD Length
               , WORD Entry
               );

BOOL CheckAmsdos( BYTE * Buf );


#endif
