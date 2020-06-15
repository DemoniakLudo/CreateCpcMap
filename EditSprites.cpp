// EditSprites.cpp : implementation file
//

#include  <afxwin.h>

#include  "CreateCpcMapDlg.h"
#include  "CreateCpcMap.h"
#include  "EditSprites.h"
#include  "Constantes.h"
#include  "SpriteCPC.h"
#include  "Bitmap.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CEditSprites dialog


CEditSprites::CEditSprites( int * p, BOOL Plus, CWnd * pParent /*=NULL*/ )
    : CDialog(CEditSprites::IDD, pParent)
{
    memcpy( Palette, p, sizeof( Palette ) );
    NumSpriteSel = 0;
    CpcPlus = Plus;
    //{{AFX_DATA_INIT(CEditSprites)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void CEditSprites::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CEditSprites)
    DDX_Control(pDX, IDC_COLCHOIX, m_ColChoix);
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
    DDX_Control(pDX, IDC_GRILLE, m_BpGrille );
    DDX_Control(pDX, IDC_SCROLLSPRITE, m_HscrollSprite);
    DDX_Control(pDX, IDC_NUMSPRITE, m_NumSprite);
    DDX_Control(pDX, IDC_STATIC_POSX, m_PosX);
    DDX_Control(pDX, IDC_STATIC_POSY, m_PosY);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditSprites, CDialog)
    //{{AFX_MSG_MAP(CEditSprites)
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
    ON_BN_CLICKED(IDC_GRILLE, OnGrille)
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDOWN()
    ON_WM_RBUTTONDOWN()
    ON_WM_PAINT()
    ON_WM_HSCROLL()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditSprites message handlers

BOOL CEditSprites::OnInitDialog()
{
    CDialog::OnInitDialog();
    hDC = GetDC();
    if ( BmSprite.Create( hDC, TAILLE_SPR_X, TAILLE_SPR_Y ) )
        {
        if ( BmPrevNext.Create( hDC
                              , TAILLE_X_SPPREVNEXT
                              , TAILLE_Y_SPPREVNEXT
                              )
           )
            {
            if ( BmTmp.Create( hDC, TAILLE_SPR_X * 16, TAILLE_SPR_Y * 16 ) )
                {
                OnCol00();
                m_HscrollSprite.SetScrollRange( 0, MAX_SPRITES - 1 );
                }
            }
        }
    return( TRUE );
}


void CEditSprites::OnPaint()
{
    CPaintDC dc( this );
    CRect rect;
    CDC * TempDC;

    for ( int i = 0; i < 16; i++ )
        {
        m_Col[ i ].GetClientRect( rect );
        TempDC = m_Col[ i ].GetDC();
        TempDC->FillSolidRect( rect, GetRgbCPC( Palette[ i ], CpcPlus ) );
        m_Col[ i ].ReleaseDC( TempDC );
        }
    AffichePalette();
    UpdateSprite();
    OnNewSelSprite();
}


void CEditSprites::UpdateSprite( void )
{
    CurSprite.Render( ( StRVB * )BmSprite.GetMemBitmap()
                    , TAILLE_SPR_X
                    , 0
                    , Palette
                    , 16
                    , 4
                    , CpcPlus
                    );
    HDC DcTmp = BmTmp.GetDC();
    BmSprite.Render( DcTmp, 0, 0, 16, 16 );
    HPEN p = CreatePen( PS_SOLID, 1, RGB( 0xC0, 0xC0, 0xC0 ) );
    SelectObject( DcTmp, p );
    if ( m_BpGrille.GetCheck() )
        {
        for ( int i = 0; i < 16; i++ )
            {
            for ( int j = 0; j < 8; j++ )
                {
                MoveToEx( DcTmp, j * 32, i * 16, NULL );
                LineTo( DcTmp, ( j + 1 ) * 32, i * 16 );
                LineTo( DcTmp, ( j + 1 ) * 32 , ( i + 1 ) * 16 );
                LineTo( DcTmp, j * 32, ( i + 1 ) * 16 );
                LineTo( DcTmp, j * 32, i * 16 );
                }
            }
        }
    BmTmp.Render( hDC->m_hDC, OFFSET_X_SPCUR, OFFSET_Y_SPCUR, 1, 1 );
    DeleteObject( p );
}


void CEditSprites::OnNewSelSprite( void )
{
    wsprintf( Tmp, "%d", NumSpriteSel );
    m_NumSprite.SetWindowText( Tmp );
    BmPrevNext.Clear( 0 );
    for ( int i = 0; i < 5; i++ )
        {
        int NumSprite = NumSpriteSel + i - 2;
        int * MemSprites = BmPrevNext.GetMemBitmap();
        MemSprites += 1 + ( 2 + TAILLE_SPR_X ) * i;
        if ( NumSprite>= 0 && NumSprite < MAX_SPRITES ) 
            TabSprites[ NumSprite ] .Render( ( StRVB * )MemSprites
                                           , TAILLE_X_SPPREVNEXT
                                           , 0
                                           , Palette
                                           , 16
                                           , 4
                                           , CpcPlus
                                           );
        }
    BmPrevNext.Render( hDC->m_hDC
                     , OFFSET_X_SPPREVNEXT, OFFSET_Y_SPPREVNEXT
                     , 2, 2
                     );
    CurSprite.SetDatas( TabSprites[ NumSpriteSel ].GetDatas(), 64 );
    UpdateSprite();
}


void CEditSprites::OnCancel()
{
    ReleaseDC( hDC );
    CDialog::OnCancel();
}


void CEditSprites::OnOK()
{
    CDialog::OnOK();
}


void CEditSprites::SetPoint( int x, int y, int Col )
{
    static BYTE Data[ 64 ];

    memcpy( Data, CurSprite.GetDatas(), sizeof( Data ) );
    int PosData = y * 4 + ( x >> 1 );

    if ( x & 1 )
        {
        Data[ PosData ] &= 0xAA;
        Data[ PosData ] |= ( ( Col & 1 ) << 6 )
                        |  ( ( Col & 2 ) << 1 )
                        |  ( ( Col & 4 ) << 2 )
                        |  ( ( Col & 8 ) >> 3 );
        }
    else
        {
        Data[ PosData ] &= 0x55;
        Data[ PosData ] |= ( ( Col & 1 ) << 7 )
                        |  ( ( Col & 2 ) << 2 )
                        |  ( ( Col & 4 ) << 3 )
                        |  ( ( Col & 8 ) >> 2 );
        }
    CurSprite.SetDatas( Data, sizeof( Data ) );
    TabSprites[ NumSpriteSel ].SetDatas( Data, sizeof( Data ) );
    UpdateSprite();
    OnNewSelSprite();
}


void CEditSprites::OnMouseMove( UINT nFlags, CPoint point )
{
    if (  point.x >= OFFSET_X_SPCUR
       && point.x < OFFSET_X_SPCUR + TAILLE_SPR_X * 16
       && point.y >= OFFSET_Y_SPCUR
       && point.y < OFFSET_Y_SPCUR + TAILLE_SPR_Y * 16
       )
        {
        int x = ( point.x - OFFSET_X_SPCUR ) / 32;
        int y = ( point.y - OFFSET_Y_SPCUR ) / 16;
        wsprintf( Tmp, "Position x : %d", x );
        m_PosX.SetWindowText( Tmp );
        wsprintf( Tmp, "Position y : %d", y );
        m_PosY.SetWindowText( Tmp );
        switch( nFlags )
            {
            case MK_LBUTTON :
                SetPoint( x, y, Stylot );
                break;

            case MK_RBUTTON :
                SetPoint( x, y, 0 );
                break;
            }
        }
    else
        {
        m_PosX.SetWindowText( "" );
        m_PosY.SetWindowText( "" );
        }
    CDialog::OnMouseMove( nFlags, point );
}


void CEditSprites::OnLButtonDown( UINT nFlags, CPoint point )
{
    if (  point.x >= OFFSET_X_SPCUR
       && point.x < OFFSET_X_SPCUR + TAILLE_SPR_X * 16
       && point.y >= OFFSET_Y_SPCUR
       && point.y < OFFSET_Y_SPCUR + TAILLE_SPR_Y * 16
       )
        {
        int x = ( point.x - OFFSET_X_SPCUR ) / 32;
        int y = ( point.y - OFFSET_Y_SPCUR ) / 16;
        SetPoint( x, y, Stylot );
        }
    CDialog::OnLButtonDown( nFlags, point );
}


void CEditSprites::OnRButtonDown( UINT nFlags, CPoint point )
{
    if (  point.x >= OFFSET_X_SPCUR
       && point.x < OFFSET_X_SPCUR + TAILLE_SPR_X * 16
       && point.y >= OFFSET_Y_SPCUR
       && point.y < OFFSET_Y_SPCUR + TAILLE_SPR_Y * 16
       )
        {
        int x = ( point.x - OFFSET_X_SPCUR ) / 32;
        int y = ( point.y - OFFSET_Y_SPCUR ) / 16;
        SetPoint( x, y, Stylot );
        }
    CDialog::OnLButtonDown( nFlags, point );
}


void CEditSprites::AffichePalette( void )
{
    CRect rect;
    CDC * TempDC;

    m_ColChoix.GetClientRect( rect );
    TempDC = m_ColChoix.GetDC();
    TempDC->FillSolidRect( rect, GetRgbCPC( Palette[ Stylot ], CpcPlus ) );
    m_ColChoix.ReleaseDC( TempDC );
}


void CEditSprites::OnCol00()
{
    Stylot = 0;
    AffichePalette();
}


void CEditSprites::OnCol01()
{
    Stylot = 1;
    AffichePalette();
}


void CEditSprites::OnCol02()
{
    Stylot = 2;
    AffichePalette();
}


void CEditSprites::OnCol03()
{
    Stylot = 3;
    AffichePalette();
}


void CEditSprites::OnCol04()
{
    Stylot = 4;
    AffichePalette();
}


void CEditSprites::OnCol05()
{
    Stylot = 5;
    AffichePalette();
}


void CEditSprites::OnCol06()
{
    Stylot = 6;
    AffichePalette();
}


void CEditSprites::OnCol07()
{
    Stylot = 7;
    AffichePalette();
}


void CEditSprites::OnCol08()
{
    Stylot = 8;
    AffichePalette();
}


void CEditSprites::OnCol09()
{
    Stylot = 9;
    AffichePalette();
}


void CEditSprites::OnCol10()
{
    Stylot = 10;
    AffichePalette();
}


void CEditSprites::OnCol11()
{
    Stylot = 11;
    AffichePalette();
}


void CEditSprites::OnCol12()
{
    Stylot = 12;
    AffichePalette();
}


void CEditSprites::OnCol13()
{
    Stylot = 13;
    AffichePalette();
}


void CEditSprites::OnCol14()
{
    Stylot = 14;
    AffichePalette();
}


void CEditSprites::OnCol15()
{
    Stylot = 15;
    AffichePalette();
}


void CEditSprites::OnGrille()
{
    UpdateSprite();
}


void CEditSprites::OnHScroll( UINT nSBCode, UINT nPos, CScrollBar * pScrollBar )
{

    int RangeMin, RangeMax, i = NumSpriteSel;

    switch( nSBCode )
        {
        case SB_BOTTOM :
            pScrollBar->GetScrollRange( &RangeMin, &RangeMax );
            NumSpriteSel = RangeMax;
            break;

        case SB_LINEDOWN :
            pScrollBar->GetScrollRange( &RangeMin, &RangeMax );
            if ( NumSpriteSel < RangeMax )
                NumSpriteSel++;

            break;

        case SB_LINEUP :
            if ( NumSpriteSel > 0 )
                NumSpriteSel--;

            break;

        case SB_PAGEUP :
            pScrollBar->GetScrollRange( &RangeMin, &RangeMax );
            NumSpriteSel -= 5;
            if ( NumSpriteSel < 0 )
                NumSpriteSel = 0;

            break;

        case SB_PAGEDOWN :
            pScrollBar->GetScrollRange( &RangeMin, &RangeMax );
            NumSpriteSel += 5;
            if ( NumSpriteSel > RangeMax )
                NumSpriteSel = RangeMax;

            break;

        case SB_THUMBPOSITION :
        case SB_THUMBTRACK :
            NumSpriteSel = nPos;
            break;

        case SB_TOP :
            NumSpriteSel = 0;
            break;
        }
    if ( i != NumSpriteSel )
        {
        pScrollBar->SetScrollPos( NumSpriteSel );
        OnNewSelSprite();
        }

    CDialog::OnHScroll( nSBCode, nPos, pScrollBar );
}
