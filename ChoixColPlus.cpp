// ChoixColPlus.cpp : implementation file
//

#include  <afxwin.h>
#include  <afxcmn.h>

#include  "Resource.h"
#include  "ChoixColPlus.h"
#include  "Locale.h"


extern int Locale;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChoixColPlus dialog


CChoixColPlus::CChoixColPlus( int ValRVB, CWnd* pParent /*=NULL*/)
    : CDialog(CChoixColPlus::IDD, pParent)
{
    //{{AFX_DATA_INIT(CChoixColPlus)
    //}}AFX_DATA_INIT
    Couleur = ValRVB;
    v = ( ValRVB & 0xF00 ) >> 8;
    r = ( ValRVB & 0x0F0 ) >> 4;
    b = ValRVB & 0x00F;
}


void CChoixColPlus::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CChoixColPlus)
    DDX_Control(pDX, IDC_SLIDER_V, m_SliderV);
    DDX_Control(pDX, IDC_SLIDER_R, m_SliderR);
    DDX_Control(pDX, IDC_SLIDER_B, m_SliderB);
    DDX_Control(pDX, IDOK, m_BpOk);
    DDX_Control(pDX, IDCANCEL, m_BpCancel);
    DDX_Control(pDX, IDC_VAL_HEX, m_ValHex);
    DDX_Control(pDX, IDC_COLCHOIX1, m_ColChoix);
    DDX_Control(pDX, IDC_VAL_V, m_ValV);
    DDX_Control(pDX, IDC_VAL_B, m_ValB);
    DDX_Control(pDX, IDC_VAL_R, m_ValR);
    DDX_Control(pDX, IDC_TEXT_V, m_TextV);
    DDX_Control(pDX, IDC_TEXT_R, m_TextR);
    DDX_Control(pDX, IDC_TEXT_B, m_TextB);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChoixColPlus, CDialog)
    //{{AFX_MSG_MAP(CChoixColPlus)
    ON_WM_PAINT()
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_B, OnCustomdrawSliderB)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_R, OnCustomdrawSliderR)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_V, OnCustomdrawSliderV)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChoixColPlus message handlers

BOOL CChoixColPlus::OnInitDialog()
{
    CDialog::OnInitDialog();

    Update();
    m_SliderR.SetRange( 0, 15 );
    m_SliderR.SetPos( r );
    m_SliderV.SetRange( 0, 15 );
    m_SliderV.SetPos( v );
    m_SliderB.SetRange( 0, 15 );
    m_SliderB.SetPos( b );
    return( TRUE );
}


void CChoixColPlus::OnPaint()
{
    CPaintDC dc( this ); // device context for painting
    Update();
}


void CChoixColPlus::Update( void )
{
    char Tmp[ 16 ];
    CRect rect;
    CDC * TempDC;

    m_ValR.SetWindowText( itoa( r, Tmp, 10 ) );
    m_ValV.SetWindowText( itoa( v, Tmp, 10 ) );
    m_ValB.SetWindowText( itoa( b, Tmp, 10 ) );
    m_ColChoix.GetClientRect( rect );
    TempDC = m_ColChoix.GetDC();
    TempDC->FillSolidRect( rect, RGB( r * 17, v * 17, b * 17 ) );
    m_ColChoix.ReleaseDC( TempDC );
    Couleur = ( v << 8 ) + ( r << 4 ) + b;
    wsprintf( Tmp, "#%03X", Couleur );
    m_ValHex.SetWindowText( Tmp );
}


void CChoixColPlus::OnOK()
{
    Retour = TRUE;
    CDialog::OnOK();
}


void CChoixColPlus::OnCancel()
{
    Retour = FALSE;
    CDialog::OnCancel();
}


void CChoixColPlus::OnCustomdrawSliderR( NMHDR * pNMHDR, LRESULT * pResult )
{
    r = m_SliderR.GetPos();
    Update();
    * pResult = 0;
}


void CChoixColPlus::OnCustomdrawSliderV( NMHDR * pNMHDR, LRESULT * pResult )
{
    v = m_SliderV.GetPos();
    Update();
    * pResult = 0;
}


void CChoixColPlus::OnCustomdrawSliderB( NMHDR * pNMHDR, LRESULT * pResult )
{
    b = m_SliderB.GetPos();
    Update();
    * pResult = 0;
}
