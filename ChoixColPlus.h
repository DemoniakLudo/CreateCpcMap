#if !defined(AFX_CHOIXCOLPLUS_H__69EBA853_69C4_4F09_8F75_4AA5DE97F68E__INCLUDED_)
#define AFX_CHOIXCOLPLUS_H__69EBA853_69C4_4F09_8F75_4AA5DE97F68E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChoixColPlus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChoixColPlus dialog

class CChoixColPlus : public CDialog
{
// Construction
public:
    CChoixColPlus( int ValRVB, CWnd* pParent = NULL);   // standard constructor
    BOOL GetRetour( void ) { return( Retour ); }
    int GetCouleur( void ) { return( Couleur ); }

// Dialog Data
    //{{AFX_DATA(CChoixColPlus)
    enum { IDD = IDD_CHOIXCOULPLUS };
    CSliderCtrl     m_SliderV;
    CSliderCtrl     m_SliderR;
    CSliderCtrl     m_SliderB;
    CButton         m_BpOk;
    CButton         m_BpCancel;
    CStatic         m_ValHex;
    CStatic         m_ColChoix;
    CEdit           m_ValV;
    CEdit           m_ValB;
    CEdit           m_ValR;
    CStatic         m_TextV;
    CStatic         m_TextR;
    CStatic         m_TextB;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CChoixColPlus)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CChoixColPlus)
    virtual BOOL OnInitDialog();
    virtual void OnCancel();
    virtual void OnOK();
    afx_msg void OnPaint();
    afx_msg void OnCustomdrawSliderB(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnCustomdrawSliderR(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnCustomdrawSliderV(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private :
    void Update( void );

    int r, v, b, Couleur;
    BOOL Retour;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOIXCOLPLUS_H__69EBA853_69C4_4F09_8F75_4AA5DE97F68E__INCLUDED_)
