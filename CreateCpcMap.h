// CreateCpcMap.h : main header file for the CREATECPCMAP application
//

#if !defined(AFX_CREATECPCMAP_H__6FDD573F_365B_486B_BA47_24952182CD64__INCLUDED_)
#define AFX_CREATECPCMAP_H__6FDD573F_365B_486B_BA47_24952182CD64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"        // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCreateCpcMapApp:
// See CreateCpcMap.cpp for the implementation of this class
//

class CCreateCpcMapApp : public CWinApp
{
public:
    CCreateCpcMapApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CCreateCpcMapApp)
    public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// Implementation

    //{{AFX_MSG(CCreateCpcMapApp)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATECPCMAP_H__6FDD573F_365B_486B_BA47_24952182CD64__INCLUDED_)
