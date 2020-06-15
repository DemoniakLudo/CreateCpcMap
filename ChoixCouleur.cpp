// ChoixCouleur.cpp : implementation file
//

#include  <afxcmn.h>


#include  "Constantes.h"
#include  "BitmapCPC.h"
#include  "ChoixCouleur.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChoixCouleur dialog


CChoixCouleur::CChoixCouleur( int OldCol, CWnd* pParent /*=NULL*/)
    : CDialog(CChoixCouleur::IDD, pParent)
{
    //{{AFX_DATA_INIT(CChoixCouleur)
    //}}AFX_DATA_INIT
    Couleur = OldCol;
}


void CChoixCouleur::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CChoixCouleur)
    DDX_Control(pDX, IDOK, m_BpOk);
    DDX_Control(pDX, IDCANCEL, m_BpCancel);
    DDX_Control(pDX, IDC_NUMCOL, m_NumCol);
    DDX_Control(pDX, IDC_COLCHOIX, m_ColChoix);
    DDX_Control(pDX, IDC_COL26, m_Col[ 26 ] );
    DDX_Control(pDX, IDC_COL25, m_Col[ 25 ] );
    DDX_Control(pDX, IDC_COL24, m_Col[ 24 ] );
    DDX_Control(pDX, IDC_COL23, m_Col[ 23 ] );
    DDX_Control(pDX, IDC_COL22, m_Col[ 22 ] );
    DDX_Control(pDX, IDC_COL21, m_Col[ 21 ] );
    DDX_Control(pDX, IDC_COL20, m_Col[ 20 ] );
    DDX_Control(pDX, IDC_COL19, m_Col[ 19 ] );
    DDX_Control(pDX, IDC_COL18, m_Col[ 18 ] );
    DDX_Control(pDX, IDC_COL17, m_Col[ 17 ] );
    DDX_Control(pDX, IDC_COL16, m_Col[ 16 ] );
    DDX_Control(pDX, IDC_COL15, m_Col[ 15 ] );
    DDX_Control(pDX, IDC_COL14, m_Col[ 14 ] );
    DDX_Control(pDX, IDC_COL13, m_Col[ 13 ] );
    DDX_Control(pDX, IDC_COL12, m_Col[ 12 ] );
    DDX_Control(pDX, IDC_COL11, m_Col[ 11 ] );
    DDX_Control(pDX, IDC_COL10, m_Col[ 10 ] );
    DDX_Control(pDX, IDC_COL08, m_Col[ 8 ] );
    DDX_Control(pDX, IDC_COL09, m_Col[ 9 ] );
    DDX_Control(pDX, IDC_COL07, m_Col[ 7 ] );
    DDX_Control(pDX, IDC_COL06, m_Col[ 6 ] );
    DDX_Control(pDX, IDC_COL05, m_Col[ 5 ] );
    DDX_Control(pDX, IDC_COL04, m_Col[ 4 ] );
    DDX_Control(pDX, IDC_COL03, m_Col[ 3 ] );
    DDX_Control(pDX, IDC_COL02, m_Col[ 2 ] );
    DDX_Control(pDX, IDC_COL01, m_Col[ 1 ] );
    DDX_Control(pDX, IDC_COL00, m_Col[ 0 ] );
    DDX_Control(pDX, IDC_STATIC_COLCHOIX, m_TxtColChoix );
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChoixCouleur, CDialog)
    //{{AFX_MSG_MAP(CChoixCouleur)
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
    ON_BN_CLICKED(IDC_COL16, OnCol16)
    ON_BN_CLICKED(IDC_COL17, OnCol17)
    ON_BN_CLICKED(IDC_COL18, OnCol18)
    ON_BN_CLICKED(IDC_COL19, OnCol19)
    ON_BN_CLICKED(IDC_COL20, OnCol20)
    ON_BN_CLICKED(IDC_COL21, OnCol21)
    ON_BN_CLICKED(IDC_COL22, OnCol22)
    ON_BN_CLICKED(IDC_COL23, OnCol23)
    ON_BN_CLICKED(IDC_COL24, OnCol24)
    ON_BN_CLICKED(IDC_COL25, OnCol25)
    ON_BN_CLICKED(IDC_COL26, OnCol26)
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChoixCouleur message handlers

BOOL CChoixCouleur::OnInitDialog()
{
    CDialog::OnInitDialog();
    return( TRUE );
}


void CChoixCouleur::OnPaint()
{
    AffichePalette();
    CDialog::OnPaint();
}


//
// Affichage de la palette CPC (27 couleurs)
//
void CChoixCouleur::AffichePalette( void )
{
    CRect rect;
    CDC * TempDC;

    for ( int i = 0; i < 27; i++ )
        {
        m_Col[ i ].GetClientRect( rect );
        TempDC = m_Col[ i ].GetDC();
        TempDC->FillSolidRect( rect, GetRgbCPC( i, FALSE ) );
        m_Col[ i ].ReleaseDC( TempDC );
        }
    m_ColChoix.GetClientRect( rect );
    TempDC = m_ColChoix.GetDC();
    TempDC->FillSolidRect( rect, GetRgbCPC( Couleur, FALSE ) );
    m_ColChoix.ReleaseDC( TempDC );
    char Msg[ 8 ];
    wsprintf( Msg, "%02d :", Couleur );
    m_NumCol.SetWindowText( Msg );
}


void CChoixCouleur::OnCol00()
{
    Couleur = 0;
    AffichePalette();
}


void CChoixCouleur::OnCol01()
{
    Couleur = 1;
    AffichePalette();
}


void CChoixCouleur::OnCol02()
{
    Couleur = 2;
    AffichePalette();
}


void CChoixCouleur::OnCol03()
{
    Couleur = 3;
    AffichePalette();
}


void CChoixCouleur::OnCol04()
{
    Couleur = 4;
    AffichePalette();
}


void CChoixCouleur::OnCol05()
{
    Couleur = 5;
    AffichePalette();
}


void CChoixCouleur::OnCol06()
{
    Couleur = 6;
    AffichePalette();
}


void CChoixCouleur::OnCol07()
{
    Couleur = 7;
    AffichePalette();
}


void CChoixCouleur::OnCol08()
{
    Couleur = 8;
    AffichePalette();
}


void CChoixCouleur::OnCol09()
{
    Couleur = 9;
    AffichePalette();
}


void CChoixCouleur::OnCol10()
{
    Couleur = 10;
    AffichePalette();
}


void CChoixCouleur::OnCol11()
{
    Couleur = 11;
    AffichePalette();
}


void CChoixCouleur::OnCol12()
{
    Couleur = 12;
    AffichePalette();
}


void CChoixCouleur::OnCol13()
{
    Couleur = 13;
    AffichePalette();
}


void CChoixCouleur::OnCol14()
{
    Couleur = 14;
    AffichePalette();
}


void CChoixCouleur::OnCol15()
{
    Couleur = 15;
    AffichePalette();
}


void CChoixCouleur::OnCol16()
{
    Couleur = 16;
    AffichePalette();
}


void CChoixCouleur::OnCol17()
{
    Couleur = 17;
    AffichePalette();
}


void CChoixCouleur::OnCol18()
{
    Couleur = 18;
    AffichePalette();
}


void CChoixCouleur::OnCol19()
{
    Couleur = 19;
    AffichePalette();
}


void CChoixCouleur::OnCol20()
{
    Couleur = 20;
    AffichePalette();
}


void CChoixCouleur::OnCol21()
{
    Couleur = 21;
    AffichePalette();
}


void CChoixCouleur::OnCol22()
{
    Couleur = 22;
    AffichePalette();
}


void CChoixCouleur::OnCol23()
{
    Couleur = 23;
    AffichePalette();
}


void CChoixCouleur::OnCol24()
{
    Couleur = 24;
    AffichePalette();
}


void CChoixCouleur::OnCol25()
{
    Couleur = 25;
    AffichePalette();
}


void CChoixCouleur::OnCol26()
{
    Couleur = 26;
    AffichePalette();
}


void CChoixCouleur::OnCancel()
{
    CDialog::OnCancel();
    Retour = FALSE;
}


void CChoixCouleur::OnOK()
{
    CDialog::OnOK();
    Retour = TRUE;
}
