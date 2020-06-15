// CreateCpcMapDlg.cpp : implementation file
//

#include  <afxwin.h>
#include  <afxdlgs.h>
#include  <afxcmn.h>

#include  "Bitmap.h"
#include  "Amsdos.h"
#include  "Constantes.h"
#include  "EditSprites.h"
#include  "CreateCpcMap.h"
#include  "ChoixCouleur.h"
#include  "ChoixColPlus.h"
#include  "ImportMapScr.h"
#include  "CreateCpcMapDlg.h"
#include  "ImportSpritesScr.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateCpcMapDlg dialog


SpriteCPC TabSprites[ MAX_SPRITES ];

WORD Map[ NB_ELT_MAP_Y ][ NB_ELT_MAP_X ];

static WORD CopyMap[ 400 ];

static BYTE CpcVGA[ 28 ] = "TDU\\X]LEMVFW^@_NGORBSZY[ICK";


CCreateCpcMapDlg::CCreateCpcMapDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CCreateCpcMapDlg::IDD, pParent)
{
    static int PaletteStandard[ 16 ] = 
        {
        1, 24, 20, 6, 26, 0, 2, 7, 10, 12, 14, 16, 18, 22, 1, 14
        };

    memcpy( Palette, PaletteStandard, sizeof( Palette ) );
    OffsetNumSprite = 0;
    NumSpriteSel = -1;
    xSel = ySel = -1;
    OffsetMapX = OffsetMapY = 0;
    xMulti = yMulti = -1;
    MemoBloc = FALSE;
    //{{AFX_DATA_INIT(CCreateCpcMapDlg)
    //}}AFX_DATA_INIT
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCreateCpcMapDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CCreateCpcMapDlg)
    DDX_Control(pDX, IDC_NUMSPRITE, m_NumSprite );
    DDX_Control(pDX, IDC_POSXMAP, m_PosXMap );
    DDX_Control(pDX, IDC_POSYMAP, m_PosYMap );
    DDX_Control(pDX, IDC_SPRITEMAP, m_SpriteMap );
    DDX_Control(pDX, IDC_VSCROLL_MAP, m_VscrollMap );
    DDX_Control(pDX, IDC_HSCROLL_MAP, m_HscrollMap );
    DDX_Control(pDX, IDC_SCROLL_SPRITE, m_ScrollSprite );
    DDX_Control(pDX, IDC_COL15, m_Col[ 15 ] );
    DDX_Control(pDX, IDC_COL14, m_Col[ 14 ] );
    DDX_Control(pDX, IDC_COL13, m_Col[ 13 ] );
    DDX_Control(pDX, IDC_COL12, m_Col[ 12 ] );
    DDX_Control(pDX, IDC_COL11, m_Col[ 11 ] );
    DDX_Control(pDX, IDC_COL10, m_Col[ 10 ] );
    DDX_Control(pDX, IDC_COL09, m_Col[ 9 ] );
    DDX_Control(pDX, IDC_COL08, m_Col[ 8 ] );
    DDX_Control(pDX, IDC_COL07, m_Col[ 7 ] );
    DDX_Control(pDX, IDC_COL06, m_Col[ 6 ] );
    DDX_Control(pDX, IDC_COL05, m_Col[ 5 ] );
    DDX_Control(pDX, IDC_COL04, m_Col[ 4 ] );
    DDX_Control(pDX, IDC_COL03, m_Col[ 3 ] );
    DDX_Control(pDX, IDC_COL02, m_Col[ 2 ] );
    DDX_Control(pDX, IDC_COL01, m_Col[ 1 ] );
    DDX_Control(pDX, IDC_COL00, m_Col[ 0 ] );
    DDX_Control(pDX, IDC_MEMOBLOC, m_MemoBloc );
    DDX_Control(pDX, IDC_CPCPLUS, m_CpcPlus );
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCreateCpcMapDlg, CDialog)
    //{{AFX_MSG_MAP(CCreateCpcMapDlg)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_VSCROLL()
    ON_WM_HSCROLL()
    ON_WM_RBUTTONUP()
    ON_WM_RBUTTONDOWN()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_BN_CLICKED(IDC_LIRE_SPRITES, OnLireSprites)
    ON_BN_CLICKED(IDC_IMPORT, OnImportSprites)
    ON_BN_CLICKED(IDC_SAUVER_SPRITES, OnSauverSprites)
    ON_BN_CLICKED(IDC_EDIT, OnEditSprites)
    ON_BN_CLICKED(IDC_RAZ_SPRITES, OnRazSprites)
    ON_BN_CLICKED(IDC_LIRE_MAP, OnLireMap)
    ON_BN_CLICKED(IDC_IMPORT_MAP, OnImportMap)
    ON_BN_CLICKED(IDC_SAUVER_MAP, OnSauverMap)
    ON_BN_CLICKED(IDC_RAZ_MAP, OnRazMap)
    ON_BN_CLICKED(IDC_COL00, OnCol00)
    ON_BN_CLICKED(IDC_COL01, OnCol01)
    ON_BN_CLICKED(IDC_COL02, OnCol02)
    ON_BN_CLICKED(IDC_COL03, OnCol03)
    ON_BN_CLICKED(IDC_COL04, OnCol04)
    ON_BN_CLICKED(IDC_COL05, OnCol05)
    ON_BN_CLICKED(IDC_COL06, OnCol06)
    ON_BN_CLICKED(IDC_COL07, OnCol07)
    ON_BN_CLICKED(IDC_COL08, OnCol08)
    ON_BN_CLICKED(IDC_COL09, OnCol09)
    ON_BN_CLICKED(IDC_COL10, OnCol10)
    ON_BN_CLICKED(IDC_COL11, OnCol11)
    ON_BN_CLICKED(IDC_COL12, OnCol12)
    ON_BN_CLICKED(IDC_COL13, OnCol13)
    ON_BN_CLICKED(IDC_COL14, OnCol14)
    ON_BN_CLICKED(IDC_COL15, OnCol15)
    ON_BN_CLICKED(IDC_SAUVER_PALETTE, OnSauverPalette)
    ON_BN_CLICKED(IDC_LIRE_PALETTE, OnLirePalette)
    ON_BN_CLICKED(IDC_CPCPLUS, OnCpcPlus )
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCreateCpcMapDlg message handlers


BOOL CCreateCpcMapDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    hDC = GetDC();
    if ( BmSprites.Create( hDC, TAILLE_X_SPR, TAILLE_Y_SPR ) )
        {
        m_ScrollSprite.SetScrollRange( 0, ( MAX_SPRITES - NB_SPRITES_X * NB_SPRITES_Y ) / NB_SPRITES_X );
        if ( BmMap.Create( hDC, TAILLE_X_MAP, TAILLE_Y_MAP ) )
            {
            m_HscrollMap.SetScrollRange( 0, NB_ELT_MAP_X - TAILLE_X_MAP / TAILLE_SPR_X );
            m_VscrollMap.SetScrollRange( 0, NB_ELT_MAP_Y - TAILLE_Y_MAP / TAILLE_SPR_Y );
            if ( BmSelSprite.Create( hDC, TAILLE_SPR_X, TAILLE_SPR_Y ) )
                {
                SetIcon( m_hIcon, TRUE);
                SetIcon( m_hIcon, FALSE );
                }
            }
        }
    return( TRUE );
}


void CCreateCpcMapDlg::OnPaint()
{
    if ( IsIconic() )
        {
        CPaintDC dc( this );
        SendMessage( WM_ICONERASEBKGND, ( WPARAM )dc.GetSafeHdc(), 0 );
        CRect rect;
        GetClientRect(&rect);
        dc.DrawIcon( ( rect.Width() - GetSystemMetrics( SM_CXICON ) + 1 ) / 2
                   , ( rect.Height() - GetSystemMetrics( SM_CYICON ) + 1 ) / 2
                   , m_hIcon
                   );
        }
    else
        {
        RedrawSprites();
        RedrawMap();
        UpdateSpriteSel();
        AffichePalette();
        CDialog::OnPaint();
        }
}


void CCreateCpcMapDlg::DrawSprite( int x, int y, int n )
{
    int * MemSprites = BmSprites.GetMemBitmap();
    MemSprites += 1 + x * ( TAILLE_SPR_X + 2 )
               + ( 1 + y * ( TAILLE_SPR_Y + 2 ) ) * TAILLE_X_SPR;
    TabSprites[ n ].Render( ( StRVB * )MemSprites
                          , TAILLE_X_SPR
                          , 0
                          , Palette
                          , 16
                          , 4
                          , m_CpcPlus.GetCheck()
                          );
}


void CCreateCpcMapDlg::RedrawSprites( void )
{
    int n = OffsetNumSprite * NB_SPRITES_X;
    for ( int y = 0; y < NB_SPRITES_Y; y++ )
        for ( int x = 0; x < NB_SPRITES_X; x++ )
            {
            DrawSprite( x, y, n++ );
            }
    BmSprites.Render( hDC->m_hDC, OFFSET_X_SPR, OFFSET_Y_SPR, 2, 2 );
}


void CCreateCpcMapDlg::RedrawMap( void )
{
    for ( int y = 0; y < TAILLE_Y_MAP / TAILLE_SPR_Y; y++  )
        for ( int x = 0; x < TAILLE_X_MAP / TAILLE_SPR_X ; x++ )
            {
            int * MemSprites = BmMap.GetMemBitmap();
            MemSprites += x * TAILLE_SPR_X + y * TAILLE_X_MAP * TAILLE_SPR_Y;
            int n = Map[ OffsetMapY + y ][ OffsetMapX + x ];
            if ( n < MAX_SPRITES )
                TabSprites[ n ].Render( ( StRVB * )MemSprites
                                      , TAILLE_X_MAP
                                      , 0
                                      , Palette
                                      , 16
                                      , 4
                                      , m_CpcPlus.GetCheck()
                                      );
            }
    BmMap.Render( hDC->m_hDC, OFFSET_X_MAP, OFFSET_Y_MAP, 2, 2 );
}


void CCreateCpcMapDlg::SelectSprite( int x, int y )
{
    int xReel = x * ( TAILLE_SPR_X + 2 );
    int yReel = y * ( TAILLE_SPR_Y + 2 );
    if ( xReel != xSel || yReel != ySel )
        {
        HPEN StylotNoir = CreatePen( PS_SOLID, 1, RGB( 0x00, 0x00, 0x00 ) );
        HPEN StylotBlanc = CreatePen( PS_SOLID, 1, RGB( 0xFF, 0xFF, 0xFF ) );

        if ( xSel >= 0 && ySel >= 0 )
            {
            SelectObject( BmSprites.GetDC(), StylotNoir );
            Rectangle( BmSprites.GetDC(), xSel, ySel, xSel + 18, ySel + 18 );
            }
        if ( xReel >= 0 && yReel >= 0 )
            {
            SelectObject( BmSprites.GetDC(), StylotBlanc );
            Rectangle( BmSprites.GetDC(), xReel, yReel, xReel + 18, yReel + 18 );
            NumSpriteSel = x + NB_SPRITES_X * ( y + OffsetNumSprite );
            }
        else
            NumSpriteSel = -1;

        xSel = xReel;
        ySel = yReel;
        DeleteObject( StylotNoir );
        DeleteObject( StylotBlanc );
        UpdateSpriteSel();
        }
    RedrawSprites();
}


void CCreateCpcMapDlg::UpdateSpriteSel( void )
{
    if ( NumSpriteSel >= 0 && NumSpriteSel < MAX_SPRITES )
        {
        wsprintf( Tmp, "%d", NumSpriteSel );
        m_NumSprite.SetWindowText( Tmp );
        TabSprites[ NumSpriteSel ].Render( ( StRVB * )BmSelSprite.GetMemBitmap()
                                         , TAILLE_SPR_X
                                         , 0
                                         , Palette
                                         , 16
                                         , 4
                                         , m_CpcPlus.GetCheck()
                                         );
        }
    else
        {
        m_NumSprite.SetWindowText( "" );
        memset( BmSelSprite.GetMemBitmap(), 210, 1024 );
        }
    BmSelSprite.Render( hDC->m_hDC, OFFSET_X_SPSEL, OFFSET_Y_SPSEL, 2, 2 );
}


HCURSOR CCreateCpcMapDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}


void CCreateCpcMapDlg::OnCancel()
{
    ReleaseDC( hDC );
    CDialog::OnCancel();
}


void CCreateCpcMapDlg::OnOK()
{
}


void CCreateCpcMapDlg::OnVScroll( UINT nSBCode
                                , UINT nPos
                                , CScrollBar * pScrollBar
                                )
{
    int RangeMin, RangeMax, i;

    if ( pScrollBar == &m_VscrollMap )
        {
        i = OffsetMapY;
        switch( nSBCode )
            {
            case SB_BOTTOM :
                pScrollBar->GetScrollRange( &RangeMin, &RangeMax );
                OffsetMapY = RangeMax;
                break;

            case SB_LINEDOWN :
                pScrollBar->GetScrollRange( &RangeMin, &RangeMax );
                if ( OffsetMapY < RangeMax )
                    OffsetMapY++;

                break;

            case SB_LINEUP :
                if ( OffsetMapY > 0 )
                    OffsetMapY--;

                break;

            case SB_PAGEUP :
                pScrollBar->GetScrollRange( &RangeMin, &RangeMax );
                OffsetMapY -= ( NB_ELT_MAP_Y - RangeMax + RangeMin );
                if ( OffsetMapY < 0 )
                    OffsetMapY = 0;

                break;

            case SB_PAGEDOWN :
                pScrollBar->GetScrollRange( &RangeMin, &RangeMax );
                OffsetMapY += ( NB_ELT_MAP_Y - RangeMax + RangeMin );
                if ( OffsetMapY > RangeMax )
                    OffsetMapY = RangeMax;

                break;

            case SB_THUMBPOSITION :
            case SB_THUMBTRACK :
                OffsetMapY = nPos;
                break;

            case SB_TOP :
                OffsetMapY = 0;
                break;
            }
        if ( i != OffsetMapY )
            {
            pScrollBar->SetScrollPos( OffsetMapY );
            RedrawMap();
            }
        }
    else
        {
        i = OffsetNumSprite;
        switch( nSBCode )
            {
            case SB_BOTTOM :
                pScrollBar->GetScrollRange( &RangeMin, &RangeMax );
                OffsetNumSprite = RangeMax;
                break;

            case SB_LINEDOWN :
                pScrollBar->GetScrollRange( &RangeMin, &RangeMax );
                if ( OffsetNumSprite < RangeMax )
                    OffsetNumSprite++;

                break;

            case SB_LINEUP :
                if ( OffsetNumSprite > 0 )
                    OffsetNumSprite--;

                break;

            case SB_PAGEUP :
                pScrollBar->GetScrollRange( &RangeMin, &RangeMax );
                OffsetNumSprite -= NB_SPRITES_Y;
                if ( OffsetNumSprite < 0 )
                    OffsetNumSprite = 0;

                break;

            case SB_PAGEDOWN :
                pScrollBar->GetScrollRange( &RangeMin, &RangeMax );
                OffsetNumSprite += NB_SPRITES_Y;
                if ( OffsetNumSprite > RangeMax )
                    OffsetNumSprite = RangeMax;

                break;

            case SB_THUMBPOSITION :
            case SB_THUMBTRACK :
                OffsetNumSprite = nPos;
                break;

            case SB_TOP :
                OffsetNumSprite = 0;
                break;
            }
        if ( i != OffsetNumSprite )
            {
            pScrollBar->SetScrollPos( OffsetNumSprite );
            SelectSprite( -1, -1 );
            }

        }
    CDialog::OnVScroll( nSBCode, nPos, pScrollBar );
}


void CCreateCpcMapDlg::OnHScroll( UINT nSBCode
                                , UINT nPos
                                , CScrollBar * pScrollBar
                                )
{

    int RangeMin, RangeMax, i = OffsetMapX;

    switch( nSBCode )
        {
        case SB_BOTTOM :
            pScrollBar->GetScrollRange( &RangeMin, &RangeMax );
            OffsetMapX = RangeMax;
            break;

        case SB_LINEDOWN :
            pScrollBar->GetScrollRange( &RangeMin, &RangeMax );
            if ( OffsetMapX < RangeMax )
                OffsetMapX++;

            break;

        case SB_LINEUP :
            if ( OffsetMapX > 0 )
                OffsetMapX--;

            break;

        case SB_PAGEUP :
            pScrollBar->GetScrollRange( &RangeMin, &RangeMax );
            OffsetMapX -= TAILLE_X_MAP / TAILLE_SPR_X; //( NB_ELT_MAP_X - RangeMax + RangeMin );
            if ( OffsetMapX < 0 )
                OffsetMapX = 0;

            break;

        case SB_PAGEDOWN :
            pScrollBar->GetScrollRange( &RangeMin, &RangeMax );
            OffsetMapX += TAILLE_X_MAP / TAILLE_SPR_X; //( NB_ELT_MAP_X - RangeMax + RangeMin );
            if ( OffsetMapX > RangeMax )
                OffsetMapX = RangeMax;

            break;

        case SB_THUMBPOSITION :
        case SB_THUMBTRACK :
            OffsetMapX = nPos;
            break;

        case SB_TOP :
            OffsetMapX = 0;
            break;
        }
    if ( i != OffsetMapX )
        {
        pScrollBar->SetScrollPos( OffsetMapX );
        RedrawMap();
        }

    CDialog::OnHScroll( nSBCode, nPos, pScrollBar );
}


//
// Relache le bouton droit de la souris
//
void CCreateCpcMapDlg::OnRButtonUp( UINT nFlags, CPoint point )
{
    RedrawMap();
    if ( xMultiEnd < xMulti )
        {
        int tmp = xMulti;
        xMulti = xMultiEnd;
        xMultiEnd = tmp - 2;
        }
    if ( yMultiEnd < yMulti )
        {
        int tmp = yMulti;
        yMulti = yMultiEnd;
        yMultiEnd = tmp - 2;
        }
    xMultiEnd++;
    yMultiEnd++;
    if ( xMulti != xMultiEnd && yMulti != yMultiEnd )
        {
        // Mémorisation "bloc" à copier pour collage futur
        MemoBloc = TRUE;
        SelectSprite( -1, -1 );
        CopyMapX = xMultiEnd - xMulti;
        CopyMapY = yMultiEnd - yMulti;
        wsprintf( Tmp, "Bloc(%d,%d)", CopyMapX, CopyMapY );
        m_MemoBloc.SetWindowText( Tmp );
        int Pos = 0;
        for ( int y = yMulti; y < yMultiEnd; y++ )
            for ( int x = xMulti; x < xMultiEnd; x++ )
                CopyMap[ Pos++ ] = Map[ y + OffsetMapY ][ x + OffsetMapX ];
        }
    xMulti = -1;
    yMulti = -1;
}


//
// Appui sur le bouton droit de la souris
//
void CCreateCpcMapDlg::OnRButtonDown( UINT nFlags, CPoint point )
{
    if (  point.x >= OFFSET_X_MAP
       && point.y >= OFFSET_Y_MAP
       && point.x < OFFSET_X_MAP + TAILLE_X_MAP * 2
       && point.y < OFFSET_Y_MAP + TAILLE_Y_MAP * 2
       )
        {
        int x = ( point.x - OFFSET_X_MAP ) / ( 2 * TAILLE_SPR_X );
        int y = ( point.y - OFFSET_Y_MAP ) / ( 2 * TAILLE_SPR_Y );
        if ( xMulti == -1 && yMulti == -1 )
            {
            xMulti = x;
            yMulti = y;
            xMultiEnd = x;
            yMultiEnd = y;
            }
        else
            {
            if ( xMultiEnd != x || yMultiEnd != y )
                {
                RedrawMap();

                xMultiEnd = x;
                yMultiEnd = y;

                // Trace un rectangle autour de la sélection
                int xd = OFFSET_X_MAP + xMulti * 32;
                int yd = OFFSET_Y_MAP + yMulti * 32;
                int xa = 32 + OFFSET_X_MAP + xMultiEnd * 32;
                int ya = 32 + OFFSET_Y_MAP + yMultiEnd * 32;
                HPEN p = CreatePen( PS_SOLID, 1, RGB( 0xFF, 0xFF, 0xFF ) );
                SelectObject( hDC->m_hDC, p );
                hDC->MoveTo( xd, yd );
                hDC->LineTo( xa, yd );
                hDC->LineTo( xa, ya );
                hDC->LineTo( xd, ya );
                hDC->LineTo( xd, yd );
                DeleteObject( p );
                }
            }
        }
    CDialog::OnRButtonDown( nFlags, point );
}


//
// Appui sur le bouton gauche de la souris
//
void CCreateCpcMapDlg::OnLButtonDown( UINT nFlags, CPoint point )
{
    if (  point.x >= OFFSET_X_SPR
       && point.y >= OFFSET_Y_SPR
       && point.x < OFFSET_X_SPR + TAILLE_X_SPR * 2
       && point.y < OFFSET_Y_SPR + TAILLE_Y_SPR * 2
       )
        {
        int x = ( point.x - OFFSET_X_SPR ) / ( 2 * ( TAILLE_SPR_X + 2 ) );
        int y = ( point.y - OFFSET_Y_SPR ) / ( 2 * ( TAILLE_SPR_Y + 2 ) );
        SelectSprite( x, y );
        if ( MemoBloc )
            {
            MemoBloc = FALSE;
            m_MemoBloc.SetWindowText( "" );
            }
        }
    else
        if (  point.x >= OFFSET_X_MAP
           && point.y >= OFFSET_Y_MAP
           && point.x < OFFSET_X_MAP + TAILLE_X_MAP * 2
           && point.y < OFFSET_Y_MAP + TAILLE_Y_MAP * 2
           )
           {
            int x = ( point.x - OFFSET_X_MAP ) / ( 2 * TAILLE_SPR_X );
            int y = ( point.y - OFFSET_Y_MAP ) / ( 2 * TAILLE_SPR_Y );
            if ( MemoBloc )
                {
                // #### Coller le bloc
                int Pos = 0;
                for ( int yy = OffsetMapY; yy < OffsetMapY + CopyMapY; yy++ )
                    for ( int xx = OffsetMapX; xx < OffsetMapX + CopyMapX; xx++ )
                        Map[ y + yy ][ x + xx ] = CopyMap[ Pos++ ];

                RedrawMap();
                }
            else
                {
                if ( NumSpriteSel >= 0 && NumSpriteSel < MAX_SPRITES )
                    {
                    Map[ y + OffsetMapY ][ x + OffsetMapX ] = ( BYTE )NumSpriteSel;
                    RedrawMap();
                    }
                }
           }
    CDialog::OnLButtonDown( nFlags, point );
}


//
// fonction appelée lorsque l'utilisateur déplace la souris
//
void CCreateCpcMapDlg::OnMouseMove(UINT nFlags, CPoint point)
{
    if (  point.x >= OFFSET_X_MAP
       && point.y >= OFFSET_Y_MAP
       && point.x < OFFSET_X_MAP + TAILLE_X_MAP * 2
       && point.y < OFFSET_Y_MAP + TAILLE_Y_MAP * 2
       )
       {
        int x = ( point.x - OFFSET_X_MAP ) / ( 2 * TAILLE_SPR_X );
        int y = ( point.y - OFFSET_Y_MAP ) / ( 2 * TAILLE_SPR_Y );
        int NumSprite = Map[ y + OffsetMapY ][ x + OffsetMapX ];
        wsprintf( Tmp, "%d", x + OffsetMapX );
        m_PosXMap.SetWindowText( Tmp );
        wsprintf( Tmp, "%d", y + OffsetMapY );
        m_PosYMap.SetWindowText( Tmp );
        wsprintf( Tmp, "%d", NumSprite );
        m_SpriteMap.SetWindowText( Tmp );
       }
    else
        {
        m_PosXMap.SetWindowText( "" );
        m_PosYMap.SetWindowText( "" );
        m_SpriteMap.SetWindowText( "" );
        }
    switch( nFlags )
        {
        case MK_LBUTTON :
            OnLButtonDown( nFlags, point );
            break;

        case MK_RBUTTON :
            OnRButtonDown( nFlags, point );
            break;
        }
    CDialog::OnMouseMove( nFlags, point );
}


//
// Lecture des sprites
//
void CCreateCpcMapDlg::OnLireSprites()
{
    static BYTE Entete[ 0x80 ];
    static BYTE Data[ 64 ];

    CFileDialog f( TRUE
                 , "SPR"
                 , NULL
                 , OFN_PATHMUSTEXIST
                 , "Fichiers sprites (*.SPR)|*.SPR||"
                 , this
                 );
    if ( f.DoModal() == IDOK )
        {
        strcpy( Tmp, f.GetPathName() );
        FILE * fp = fopen( Tmp, "rb" );
        if ( fp )
            {
            fread( Entete, sizeof( Entete ), 1, fp );
            if ( CheckAmsdos( Entete ) )
                {
                for ( int i = 0; i < MAX_SPRITES; i++ )
                    {
                    fread( Data, sizeof( Data ), 1, fp );
                    TabSprites[ i ].SetDatas( Data, sizeof( Data ) );
                    }
                }
            fclose( fp );
            RedrawSprites();
            RedrawMap();
            }
        }
}


//
// Importation de sprites via un fichier .SCR
//
void CCreateCpcMapDlg::OnImportSprites()
{
    CImportSpritesScr Import( Palette, m_CpcPlus.GetCheck(), this );
    Import.DoModal();
    if ( Import.IsImport() )
        {
        m_CpcPlus.SetCheck( Import.IsPlus() );
        memcpy( Palette, Import.GetPalette(), sizeof( Palette ) );
        RedrawSprites();
        RedrawMap();
        }
}


//
// Sauvegarde des sprites
//
void CCreateCpcMapDlg::OnSauverSprites()
{
    CFileDialog f( FALSE
                 , "SPR"
                 , NULL
                 , OFN_PATHMUSTEXIST
                 , "Fichiers sprites (*.SPR)|*.SPR||"
                 , this
                 );
    if ( f.DoModal() == IDOK )
        {
        strcpy( Tmp, f.GetPathName() );
        FILE * fp = fopen( Tmp, "wb" );
        if ( fp )
            {
            CreeEntete( fp, Tmp, 0x4000, 0x8000, 0 );
            for ( int i = 0; i < MAX_SPRITES; i++ )
                fwrite( TabSprites[ i ].GetDatas(), 64, 1, fp );

            fclose( fp );
            }
        }
}


//
// Edition des sprites
//
void CCreateCpcMapDlg::OnEditSprites()
{
    CEditSprites Edit( Palette, m_CpcPlus.GetCheck() );
    Edit.DoModal();
    RedrawSprites();
    RedrawMap();
    UpdateSpriteSel();
}


//
// Effacement de tous les sprites
//
void CCreateCpcMapDlg::OnRazSprites()
{
    static BYTE Data[ 64 ];

    if ( MessageBox( "Etes-vous sur ?", NULL, MB_YESNO ) == IDYES )
        {
        memset( Data, 0, sizeof( Data ) );
        for ( int i = 0; i < MAX_SPRITES; i++ )
            TabSprites[ i ].SetDatas( Data, sizeof( Data ) );

        RedrawSprites();
        RedrawMap();
        UpdateSpriteSel();
        }
}


//
// Lecture de la map
//
void CCreateCpcMapDlg::OnLireMap()
{
    static BYTE Entete[ 0x80 ];
    static BYTE Data[ 64 ];

    CFileDialog f( TRUE
                 , "MAP"
                 , NULL
                 , OFN_PATHMUSTEXIST
                 , "Fichiers map (*.MAP)|*.MAP||"
                 , this
                 );
    if ( f.DoModal() == IDOK )
        {
        strcpy( Tmp, f.GetPathName() );
        FILE * fp = fopen( Tmp, "rb" );
        if ( fp )
            {
            fread( Entete, sizeof( Entete ), 1, fp );
            if ( CheckAmsdos( Entete ) )
                {
                fread( Map, sizeof( Map ), 1, fp );
                RedrawMap();
                }
            fclose( fp );
            }
        }
}


//
// Importation de la map depuis un fichier .SCR
//
void CCreateCpcMapDlg::OnImportMap()
{
    CImportMapScr Import( Palette, m_CpcPlus.GetCheck(), this );
    Import.DoModal();
    if ( Import.IsImport() )
        {
        m_CpcPlus.SetCheck( Import.IsPlus() );
        RedrawMap();
        }
}


//
// Sauvegarde de la map
//
void CCreateCpcMapDlg::OnSauverMap()
{
    CFileDialog f( FALSE
                 , "MAP"
                 , NULL
                 , OFN_PATHMUSTEXIST
                 , "Fichiers map (*.MAP)|*.MAP||"
                 , this
                 );
    if ( f.DoModal() == IDOK )
        {
        strcpy( Tmp, f.GetPathName() );
        FILE * fp = fopen( Tmp, "wb" );
        if ( fp )
            {
            CreeEntete( fp, Tmp, 0x4000, sizeof( Map ), 0 );
            fwrite( Map, sizeof( Map ), 1, fp );
            fclose( fp );
            }
        }
}


//
// Effacer la map entière
//
void CCreateCpcMapDlg::OnRazMap()
{
    if ( MessageBox( "Etes-vous sur ?", NULL, MB_YESNO ) == IDYES )
        {
        memset( Map, 0, sizeof( Map ) );
        RedrawMap();
        }
}


//
// Affichage de la palette CPC (16 couleurs max)
//
void CCreateCpcMapDlg::AffichePalette( void )
{
    CRect rect;
    CDC * TempDC;
    for ( int i = 0; i < 16; i++ )
        {
        m_Col[ i ].GetClientRect( rect );
        TempDC = m_Col[ i ].GetDC();
//        TempDC->FillSolidRect( rect, GetRgbCPC( Palette[ i ] ) );
        TempDC->FillSolidRect( rect
                             , GetRgbCPC( Palette[ i ], m_CpcPlus.GetCheck() )
                             );
        m_Col[ i ].ReleaseDC( TempDC );
        }


}


//
// Gestion du click sur une couleur de la palette : ouverture
// de la fenêtre de choix de couleur
//
void CCreateCpcMapDlg::ClickCol( int NumCol )
{
    if ( ! m_CpcPlus.GetCheck() )
        {
        CChoixCouleur c( Palette[ NumCol ], this );
        c.DoModal();
        if ( c.GetRetour() )
            {
            Palette[ NumCol ] = c.GetCouleur(); // Changement de couleur
            RedrawSprites();
            RedrawMap();
            UpdateSpriteSel();
            }
        }
    else
        {
        CChoixColPlus c( Palette[ NumCol ], this );
        c.DoModal();
        if ( c.GetRetour() )
            {
            Palette[ NumCol ] = c.GetCouleur(); // Changement de couleur
            RedrawSprites();
            RedrawMap();
            UpdateSpriteSel();
            }
        }
    AffichePalette();
}


//
// 16 fonctions pour le choix des 16 couleurs...
//


void CCreateCpcMapDlg::OnCol00( void )
{
    ClickCol( 0 );
}


void CCreateCpcMapDlg::OnCol01( void )
{
    ClickCol( 1 );
}


void CCreateCpcMapDlg::OnCol02( void )
{
    ClickCol( 2 );
}


void CCreateCpcMapDlg::OnCol03( void )
{
    ClickCol( 3 );
}


void CCreateCpcMapDlg::OnCol04( void )
{
    ClickCol( 4 );
}


void CCreateCpcMapDlg::OnCol05( void )
{
    ClickCol( 5 );
}


void CCreateCpcMapDlg::OnCol06( void )
{
    ClickCol( 6 );
}


void CCreateCpcMapDlg::OnCol07( void )
{
    ClickCol( 7 );
}


void CCreateCpcMapDlg::OnCol08( void )
{
    ClickCol( 8 );
}


void CCreateCpcMapDlg::OnCol09( void )
{
    ClickCol( 9 );
}


void CCreateCpcMapDlg::OnCol10( void )
{
    ClickCol( 10 );
}


void CCreateCpcMapDlg::OnCol11( void )
{
    ClickCol( 11 );
}


void CCreateCpcMapDlg::OnCol12( void )
{
    ClickCol( 12 );
}


void CCreateCpcMapDlg::OnCol13( void )
{
    ClickCol( 13 );
}


void CCreateCpcMapDlg::OnCol14( void )
{
    ClickCol( 14 );
}


void CCreateCpcMapDlg::OnCol15( void )
{
    ClickCol( 15 );
}


void CCreateCpcMapDlg::OnCpcPlus( void )
{
    RedrawSprites();
    RedrawMap();
    UpdateSpriteSel();
    AffichePalette();
}


//
// Lecture du fichier palette et application aux sprites
//
void CCreateCpcMapDlg::OnLirePalette()
{
    static char Entete[ 0x80 ];
    StPal Pal;

    CFileDialog f( TRUE
                 , "MAP"
                 , NULL
                 , OFN_PATHMUSTEXIST
                 , "Fichiers palette (*.PAL)|*.PAL||"
                 , this
                 );
    if ( f.DoModal() == IDOK )
        {
        strcpy( Tmp, f.GetPathName() );
        FILE * fp = fopen( Tmp, "rb" );
        if ( fp )
            {
            fread( &Entete, sizeof( Entete ), 1, fp );
            fread( &Pal, sizeof( Pal ), 1, fp );
            fclose( fp );
            if ( CheckAmsdos( ( BYTE * )&Entete ) )
                {
                if ( Pal.Mode < 3 )
                    {
                    if ( m_CpcPlus.GetCheck() )
                        {
                        for ( int i = 0; i < 16; i++ )
                            {
                            int r = 0, v = 0, b = 0;
                            for ( int k = 26; k--; )
                                {
                                if ( Pal.Palette[ i ][ 0 ] == CpcVGA[ k ] )
                                    r = ( 26 - k ) << 4;

                                if ( Pal.Palette[ i ][ 1 ] == CpcVGA[ k ] )
                                    b = 26 - k;

                                if ( Pal.Palette[ i ][ 2 ] == CpcVGA[ k ] )
                                    v = ( 26 - k ) << 8;
                                }
                            Palette[ i ] = r + v + b;
                            }
                        }
                    else
                        {
                        for ( int i = 0; i < 16; i++ )
                            for ( int j = 0; j < 27; j++ )
                                if ( Pal.Palette[ i ][ 0 ] == CpcVGA[ j ] )
                                    Palette[ i ] = j;
                        }
                    RedrawSprites();
                    RedrawMap();
                    UpdateSpriteSel();
                    AffichePalette();
                    }
                }
            }
        }
}


//
// Sauvegarde fichier palette
//
void CCreateCpcMapDlg::OnSauverPalette()
{
    StPal Pal;
    int i;

    CFileDialog f( FALSE
                 , "MAP"
                 , NULL
                 , OFN_PATHMUSTEXIST
                 , "Fichiers palette (*.PAL)|*.PAL||"
                 , this
                 );
    if ( f.DoModal() == IDOK )
        {
        strcpy( Tmp, f.GetPathName() );
        memset( &Pal, 0, sizeof( Pal ) );
        if ( m_CpcPlus.GetCheck() )
            {
            for ( int i = 0; i < 16; i++ )
                {
                Pal.Palette[ i ][ 0 ] = CpcVGA[ 26 - ( ( Palette[ i ] >> 4 ) & 0x0F ) ];
                Pal.Palette[ i ][ 1 ] = CpcVGA[ 26 - ( Palette[ i ] & 0x0F ) ];
                Pal.Palette[ i ][ 2 ] = CpcVGA[ 26 - ( ( Palette[ i ] >> 8 ) & 0x0F ) ];
                }
            Pal.Border[ 0 ] = Pal.Palette[ 0 ][ 0 ];
            Pal.Border[ 1 ] = Pal.Palette[ 0 ][ 1 ];
            Pal.Border[ 2 ] = Pal.Palette[ 0 ][ 2 ];
            }
        else
            {
            for ( i = 0; i < 16; i++ )
                for ( int j = 0; j < 12; j++ )
                    Pal.Palette[ i ][ j ] = CpcVGA[ Palette[ i ] ];

            for ( i = 0; i < 12; i++ )
                Pal.Border[ i ] = Pal.Palette[ 0 ][ i ];
            }
        FILE * fp = fopen( Tmp, "wb" );
        if ( fp )
            {
            CreeEntete( fp, Tmp, 0x8809, sizeof( Pal ), 0x8809 );
            fwrite( &Pal, sizeof( Pal ), 1, fp );
            fclose( fp );
            }
        }
}


