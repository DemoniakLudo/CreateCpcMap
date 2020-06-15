#if !defined(AFX_EDITSPRITES_H__BE2AAF59_2EDF_466D_919E_318E7BAB4BCD__INCLUDED_)
#define AFX_EDITSPRITES_H__BE2AAF59_2EDF_466D_919E_318E7BAB4BCD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditSprites.h : header file
//

#include  "Resource.h"
#include  "SpriteCPC.h"
#include  "Bitmap.h"


/////////////////////////////////////////////////////////////////////////////
// CEditSprites dialog

class CEditSprites : public CDialog
{
// Construction
public:
    CEditSprites( int * p, BOOL Plus, CWnd * pParent = NULL );   // standard constructor

// Dialog Data
    //{{AFX_DATA(CEditSprites)
    enum { IDD = IDD_EDIT_SPRITES };
    CStatic         m_Col[ 16 ];
    CStatic         m_ColChoix;
    CButton         m_BpGrille;
    CScrollBar      m_HscrollSprite;
    CEdit           m_NumSprite;
    CStatic         m_PosX, m_PosY;
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CEditSprites)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CEditSprites)
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
    afx_msg void OnGrille();
    virtual void OnCancel();
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnHScroll( UINT nSBCode, UINT nPos, CScrollBar * pScrollBar );
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnPaint();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private :
    void OnNewSelSprite( void );
    void UpdateSprite( void );
    void AffichePalette( void );
    void SetPoint( int x, int y, int Col );

    char Tmp[ 128 ];
    int NumSpriteSel;
    int Stylot;
    MonBitmap BmSprite, BmPrevNext, BmTmp;
    int Palette[ 16 ];
    SpriteCPC CurSprite;
    BOOL CpcPlus;
    CDC * hDC;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITSPRITES_H__BE2AAF59_2EDF_466D_919E_318E7BAB4BCD__INCLUDED_)
