// ImportSpritesScr.cpp : implementation file
//

#include  <afxwin.h>
#include  <afxdlgs.h>

#include  "CreateCpcMap.h"
#include  "Constantes.h"
#include  "Bitmap.h"
#include  "BitmapCPC.h"
#include  "CreateCpcMapDlg.h"
#include  "ImportSpritesScr.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportSpritesScr dialog


CImportSpritesScr::CImportSpritesScr( int p[ 16 ], int Plus, CWnd * pParent /*=NULL*/)
    : CDialog(CImportSpritesScr::IDD, pParent)
{
    memcpy( PalOrigine, p, sizeof( PalOrigine ) );
    Import = FALSE;
    OffsetX = OffsetY = 0;
    NbSpritesX = 20;
    NbSpritesY = 12;
    PremSprite = 1;
    CpcPlus = Plus;

    // Zelda : off(40, 24) nb(15,11)

    //{{AFX_DATA_INIT(CImportSpritesScr)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void CImportSpritesScr::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CImportSpritesScr)
    DDX_Control(pDX, IDC_PREMSPRITE, m_PremSprite);
    DDX_Control(pDX, IDC_NBSPRITESY, m_NbSpritesY);
    DDX_Control(pDX, IDC_NBSPRITESX, m_NbSpritesX);
    DDX_Control(pDX, IDC_OFFSETY, m_OffsetY);
    DDX_Control(pDX, IDC_OFFSETX, m_OffsetX);
    DDX_Control(pDX, IDC_IMPORTPAL, m_ImportPal);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportSpritesScr, CDialog)
    //{{AFX_MSG_MAP(CImportSpritesScr)
    ON_WM_PAINT()
    ON_BN_CLICKED(IDC_LIRE, OnLire)
    ON_BN_CLICKED(IDC_APPLIQUE, OnApplique)
    ON_BN_CLICKED(IDC_ANNULE, OnAnnule)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportSpritesScr message handlers


BOOL CImportSpritesScr::OnInitDialog()
{
    CDialog::OnInitDialog();
    hDC = GetDC();
    if ( Scr.Create( hDC, TAILLE_BITMAP_X, TAILLE_BITMAP_Y ) )
        {
        }
    return( TRUE );
}


void CImportSpritesScr::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    DrawScreen();
    MajBornes();
}


void CImportSpritesScr::DrawScreen( void )
{
    Scr.Render( hDC->m_hDC, OFFSET_X_SCR, OFFSET_Y_SCR, 1, 1 );
    CPen p( PS_SOLID, 1, RGB( 0xFF, 0xFF, 0xFF ) );
    hDC->SelectObject( p );
    int y = OffsetY * 2;
    for ( int i = 0; i < NbSpritesY && y <= TAILLE_BITMAP_Y - TAILLE_SPR_Y * 2; i++ )
        {
        int x = OffsetX * 2;
        for ( int j = 0; j < NbSpritesX && x <= TAILLE_BITMAP_X - TAILLE_SPR_X * 2; j++ )
            {
            int xd = x + OFFSET_X_SCR;
            int yd = y + OFFSET_Y_SCR;
            int xa = xd + TAILLE_SPR_X * 2;
            int ya = yd + TAILLE_SPR_X * 2;
            hDC->MoveTo( xd, yd );
            hDC->LineTo( xa, yd );
            hDC->LineTo( xa, ya );
            hDC->LineTo( xd, ya );
            hDC->LineTo( xd, yd );
            x += TAILLE_SPR_X * 2;
            }
        y+= TAILLE_SPR_Y * 2;
        }
}


void CImportSpritesScr::OnLire()
{
    CFileDialog f( TRUE
                 , "SCR"
                 , NULL
                 , OFN_PATHMUSTEXIST
                 , "Fichiers écrans CPC (*.SCR)|*.SCR||"
                 , this
                 );
    if ( f.DoModal() == IDOK )
        {
        int Mode = 0;
        char Nom[ 256 ];
        strcpy( Nom, f.GetPathName() );
        if ( ScrCpc.CreateImageFile( Nom
                                   , &Mode
                                   , PalOrigine
                                   , &CpcPlus
                                   , m_ImportPal.GetCheck()
                                   )
           )
            {
            ScrCpc.Render( ( StRVB * )Scr.GetMemBitmap(), Mode, CpcPlus );
            OnApplique();
            DrawScreen();
            }
        }
}


void CImportSpritesScr::MajBornes( void )
{
    wsprintf( Tmp, "%d", OffsetX );
    m_OffsetX.SetWindowText( Tmp );
    wsprintf( Tmp, "%d", OffsetY );
    m_OffsetY.SetWindowText( Tmp );
    wsprintf( Tmp, "%d", NbSpritesX );
    m_NbSpritesX.SetWindowText( Tmp );
    wsprintf( Tmp, "%d", NbSpritesY );
    m_NbSpritesY.SetWindowText( Tmp );
    wsprintf( Tmp, "%d", PremSprite );
    m_PremSprite.SetWindowText( Tmp );
}


void CImportSpritesScr::OnApplique()
{
    m_PremSprite.GetWindowText( Tmp, sizeof( Tmp ) );
    PremSprite = atoi( Tmp );
    if ( PremSprite > MAX_SPRITES - 1 )
        PremSprite = MAX_SPRITES - 1;

    m_OffsetX.GetWindowText( Tmp, sizeof( Tmp ) );
    OffsetX = atoi( Tmp ) & 0x1FC;
    if ( OffsetX > 304 )
        OffsetX = 304;

    m_OffsetY.GetWindowText( Tmp, sizeof( Tmp ) );
    OffsetY = atoi( Tmp );
    if ( OffsetY > 184 )
        OffsetY = 184;

    m_NbSpritesX.GetWindowText( Tmp, sizeof( Tmp ) );
    NbSpritesX = atoi( Tmp );
    if ( NbSpritesX < 1 )
        NbSpritesX = 1;
    else
        if ( NbSpritesX > 20 - ( OffsetX / 16 ) )
            NbSpritesX = 20 - ( OffsetX / 16 );

    m_NbSpritesY.GetWindowText( Tmp, sizeof( Tmp ) );
    NbSpritesY = atoi( Tmp );
    if ( NbSpritesY < 1 )
        NbSpritesY = 1;
    else
        if ( NbSpritesY > 12 - ( OffsetY / 16 ) )
            NbSpritesY = 12 - ( OffsetY / 16 );

    MajBornes();
    DrawScreen();
}


void CImportSpritesScr::OnCancel()
{
    ReleaseDC( hDC );
    CDialog::OnCancel();
}


void CImportSpritesScr::OnAnnule()
{
    OnCancel();
}


void CImportSpritesScr::OnOK()
{
    BYTE Data[ 64 ];

    OnApplique();
    m_PremSprite.GetWindowText( Tmp, sizeof( Tmp ) );
    PremSprite = atoi( Tmp );
    BYTE * AdrEcr = ScrCpc.GetBitmapCPC();
    for ( int y = 0; y < NbSpritesY; y++ )
        {
        for ( int x = 0; x < NbSpritesX; x++ )
            {
            for ( int l = 0; l < 16; l++ )
                {
                int r = y * 16 + OffsetY + l;
                int a = x * 4 + ( OffsetX >> 2 ) + ( r >> 3 ) * 80 + ( r & 7 ) * 0x800;
                for ( int c = 0; c < 4; c++ )
                    Data[ l * 4 + c ] = AdrEcr[ a++ ];
                }
            if ( PremSprite < MAX_SPRITES )
                {
                BOOL Trouve = FALSE;
                for ( int i = 0; i < PremSprite; i++ )
                    if ( DejaSprite( &TabSprites[ i ], Data ) )
                        Trouve = TRUE;

                if ( ! Trouve )
                    TabSprites[ PremSprite++ ].SetDatas( Data, sizeof( Data ) );
                }
            }
        }
    Import = TRUE;
    CDialog::OnOK();
}
