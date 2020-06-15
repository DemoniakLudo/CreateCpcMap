#ifndef CONSTANTES_H
#define CONSTANTES_H


#define     MAX_SPRITES         512
//
// Taille et position écran CPC (importation sprites)
//
#define     TAILLE_BITMAP_X     640
#define     TAILLE_BITMAP_Y     400

#define     OFFSET_X_SCR        4
#define     OFFSET_Y_SCR        4

//
// Taille et position sélection sprites
//
#define     TAILLE_SPR_X        16
#define     TAILLE_SPR_Y        16

#define     NB_SPRITES_X        2
#define     NB_SPRITES_Y        16

#define     TAILLE_X_SPR        ( NB_SPRITES_X * ( TAILLE_SPR_X + 2 ) )
#define     TAILLE_Y_SPR        ( NB_SPRITES_Y * ( TAILLE_SPR_Y + 2 ) )

#define     OFFSET_X_SPR        14
#define     OFFSET_Y_SPR        22

//
// Taille et position MAP
//
#define     TAILLE_X_MAP        ( TAILLE_SPR_X * 24 )
#define     TAILLE_Y_MAP        ( TAILLE_SPR_X * 16 )

#define     OFFSET_X_MAP        130
#define     OFFSET_Y_MAP        22

#define     NB_ELT_MAP_X        64
#define     NB_ELT_MAP_Y        64

//
// Position sprite sélectionné
//
#define     OFFSET_X_SPSEL      510
#define     OFFSET_Y_SPSEL      584

//
// Position sprite courrant (éditeur)
//
#define     OFFSET_X_SPCUR      164
#define     OFFSET_Y_SPCUR      4

//
// Taille et position sprites suivants & précédents (éditeur)
//
#define     TAILLE_X_SPPREVNEXT ( ( 2 + TAILLE_SPR_X ) * 5 )
#define     TAILLE_Y_SPPREVNEXT ( TAILLE_SPR_Y + 2 )
#define     OFFSET_X_SPPREVNEXT 202
#define     OFFSET_Y_SPPREVNEXT 280


typedef struct
    {
    BYTE b, v, r, a;
    } StRVB;


#endif
