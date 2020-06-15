// CreateCpcMap.cpp : Defines the class behaviors for the application.
//

#include  <afxwin.h>

#include  "CreateCpcMap.h"
#include  "CreateCpcMapDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateCpcMapApp

BEGIN_MESSAGE_MAP(CCreateCpcMapApp, CWinApp)
    //{{AFX_MSG_MAP(CCreateCpcMapApp)
    //}}AFX_MSG
    ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateCpcMapApp construction

CCreateCpcMapApp::CCreateCpcMapApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCreateCpcMapApp object

CCreateCpcMapApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCreateCpcMapApp initialization

BOOL CCreateCpcMapApp::InitInstance()
{
    // Standard initialization

    CCreateCpcMapDlg dlg;
    m_pMainWnd = &dlg;
    dlg.DoModal();
    return( FALSE );
}
