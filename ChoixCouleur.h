#if !defined(AFX_CHOIXCOULEUR_H__371A52F0_9260_4C92_9913_D3F8A4EFC5B1__INCLUDED_)
#define AFX_CHOIXCOULEUR_H__371A52F0_9260_4C92_9913_D3F8A4EFC5B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChoixCouleur.h : header file
//

#include  "Resource.h"


/////////////////////////////////////////////////////////////////////////////
// CChoixCouleur dialog

class CChoixCouleur : public CDialog
{
// Construction
public:
    CChoixCouleur( int OldCol, CWnd * pParent = NULL );   // standard constructor
    BOOL GetRetour( void ) { return( Retour ); }
    int GetCouleur( void ) { return( Couleur ); }

// Dialog Data
    //{{AFX_DATA(CChoixCouleur)
    enum { IDD = IDD_CHOIXCOULEUR };
    CButton     m_BpOk;
    CButton     m_BpCancel;
    CStatic     m_NumCol;
    CStatic     m_ColChoix;
    CStatic     m_TxtColChoix;
    CStatic     m_Col[ 27 ];
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CChoixCouleur)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    void AffichePalette( void );

    // Generated message map functions
    //{{AFX_MSG(CChoixCouleur)
    virtual BOOL OnInitDialog();
    afx_msg void OnCol00();
    afx_msg void OnCol01();
    afx_msg void OnCol02();
    afx_msg void OnCol03();
    afx_msg void OnCol04();
    afx_msg void OnCol05();
    afx_msg void OnCol06();
    afx_msg void OnCol07();
    afx_msg void OnCol08();
    afx_msg void OnCol09();
    afx_msg void OnCol10();
    afx_msg void OnCol11();
    afx_msg void OnCol12();
    afx_msg void OnCol13();
    afx_msg void OnCol14();
    afx_msg void OnCol15();
    afx_msg void OnCol16();
    afx_msg void OnCol17();
    afx_msg void OnCol18();
    afx_msg void OnCol19();
    afx_msg void OnCol20();
    afx_msg void OnCol21();
    afx_msg void OnCol22();
    afx_msg void OnCol23();
    afx_msg void OnCol24();
    afx_msg void OnCol25();
    afx_msg void OnCol26();
    virtual void OnCancel();
    virtual void OnOK();
    afx_msg void OnPaint();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private :
    int Couleur;
    BOOL Retour;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOIXCOULEUR_H__371A52F0_9260_4C92_9913_D3F8A4EFC5B1__INCLUDED_)
