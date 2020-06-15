#if !defined(AFX_IMPORTSPRITESSCR_H__8216B33B_D30B_4C7A_85C6_1B0231C22234__INCLUDED_)
#define AFX_IMPORTSPRITESSCR_H__8216B33B_D30B_4C7A_85C6_1B0231C22234__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImportSpritesScr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImportSpritesScr dialog

class CImportSpritesScr : public CDialog
{
// Construction
public:
    CImportSpritesScr( int p[ 16 ], int Plus, CWnd * pParent = NULL );   // standard constructor
    int * GetPalette( void ) { return( PalOrigine ); }
    BOOL IsImport( void ) { return( Import ); }
    BOOL IsPlus( void ) { return( CpcPlus ); }

// Dialog Data
    //{{AFX_DATA(CImportSpritesScr)
    enum { IDD = IDD_IMPORT_SPRITES };
    CEdit   m_PremSprite;
    CEdit   m_NbSpritesY;
    CEdit   m_NbSpritesX;
    CEdit   m_OffsetY;
    CEdit   m_OffsetX;
    CButton m_ImportPal;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CImportSpritesScr)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CImportSpritesScr)
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnLire();
    afx_msg void OnApplique();
    afx_msg void OnAnnule();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private :
    void DrawScreen( void );
    void MajBornes( void );

    char Tmp[ 128 ];
    BOOL Import;
    int OffsetX, OffsetY, NbSpritesX, NbSpritesY, PremSprite;
    MonBitmap Scr;
    CDC * hDC;
    CBitmapCPC ScrCpc;
    int CpcPlus;
    int PalOrigine[ 16 ];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTSPRITESSCR_H__8216B33B_D30B_4C7A_85C6_1B0231C22234__INCLUDED_)
