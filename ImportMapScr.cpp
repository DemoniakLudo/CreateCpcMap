// ImportMapScr.cpp : implementation file
//

#include  <afxwin.h>
#include  <afxdlgs.h>

#include  "CreateCpcMap.h"
#include  "Constantes.h"
#include  "Bitmap.h"
#include  "BitmapCPC.h"
#include  "CreateCpcMapDlg.h"
#include  "ImportMapScr.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportMapScr dialog


CImportMapScr::CImportMapScr( int p[ 16 ], int Plus, CWnd * pParent /*=NULL*/)
    : CDialog(CImportMapScr::IDD, pParent)
{
    memcpy( PalOrigine, p, sizeof( PalOrigine ) );
    Import = FALSE;
    OffsetX = OffsetY = 0;
    CpcPlus = Plus;

    //{{AFX_DATA_INIT(CImportMapScr)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void CImportMapScr::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CImportMapScr)
    DDX_Control(pDX, IDC_OFFSETY, m_OffsetY);
    DDX_Control(pDX, IDC_OFFSETX, m_OffsetX);
    DDX_Control(pDX, IDC_IMPORTPAL, m_ImportPal);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportMapScr, CDialog)
    //{{AFX_MSG_MAP(CImportMapScr)
    ON_WM_PAINT()
    ON_BN_CLICKED(IDC_LIRE, OnLire)
    ON_BN_CLICKED(IDC_APPLIQUE, OnApplique)
    ON_BN_CLICKED(IDC_ANNULE, OnAnnule)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportMapScr message handlers


BOOL CImportMapScr::OnInitDialog()
{
    CDialog::OnInitDialog();
    hDC = GetDC();
    if ( Scr.Create( hDC, TAILLE_BITMAP_X, TAILLE_BITMAP_Y ) )
        {
        }
    return( TRUE );
}


void CImportMapScr::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    DrawScreen();
    MajBornes();
}


void CImportMapScr::DrawScreen( void )
{
    Scr.Render( hDC->m_hDC, OFFSET_X_SCR, OFFSET_Y_SCR, 1, 1 );
    CPen p( PS_SOLID, 1, RGB( 0xFF, 0xFF, 0xFF ) );
    hDC->SelectObject( p );
    for ( int i = 0; i < 12; i++ )
        for ( int j = 0; j < 20; j++ )
            {
            int xd = j * TAILLE_SPR_X * 2 + OFFSET_X_SCR;
            int yd = i * TAILLE_SPR_Y * 2 + OFFSET_Y_SCR;
            int xa = xd + TAILLE_SPR_X * 2;
            int ya = yd + TAILLE_SPR_X * 2;
            hDC->MoveTo( xd, yd );
            hDC->LineTo( xa, yd );
            hDC->LineTo( xa, ya );
            hDC->LineTo( xd, ya );
            hDC->LineTo( xd, yd );
            }
}


void CImportMapScr::OnLire()
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


void CImportMapScr::MajBornes( void )
{
    wsprintf( Tmp, "%d", OffsetX );
    m_OffsetX.SetWindowText( Tmp );
    wsprintf( Tmp, "%d", OffsetY );
    m_OffsetY.SetWindowText( Tmp );
}


void CImportMapScr::OnApplique()
{
    m_OffsetX.GetWindowText( Tmp, sizeof( Tmp ) );
    OffsetX = atoi( Tmp ) & 0x1FC;
    if ( OffsetX > 304 )
        OffsetX = 304;

    m_OffsetY.GetWindowText( Tmp, sizeof( Tmp ) );
    OffsetY = atoi( Tmp );
    if ( OffsetY > 184 )
        OffsetY = 184;

    MajBornes();
}


void CImportMapScr::OnCancel()
{
    ReleaseDC( hDC );
    CDialog::OnCancel();
}


void CImportMapScr::OnAnnule()
{
    OnCancel();
}


void CImportMapScr::OnOK()
{
    BYTE Data[ 64 ];

    OnApplique();
    BYTE * AdrEcr = ScrCpc.GetBitmapCPC();
    for ( int y = 0; y < 12; y++ )
        {
        for ( int x = 0; x < 20 ; x++ )
            {
            for ( int l = 0; l < 16; l++ )
                {
                int r = y * 16 + l;
                int a = x * 4 + ( r >> 3 ) * 80 + ( r & 7 ) * 0x800;
                for ( int c = 0; c < 4; c++ )
                    Data[ l * 4 + c ] = AdrEcr[ a++ ];
                }
            int Trouve = -1;
            for ( int i = 0; i < MAX_SPRITES; i++ )
                if ( DejaSprite( &TabSprites[ i ], Data ) )
                    {
                    Trouve = i;
                    break;
                    }
            if ( Trouve > -1 )
                Map[ y + OffsetY ][ x + OffsetX ] = ( WORD )Trouve;
            }
        }
    Import = TRUE;
    CDialog::OnOK();
}
