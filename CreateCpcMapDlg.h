// CreateCpcMapDlg.h : header file
//

#if !defined(AFX_CREATECPCMAPDLG_H__CD8D8BBD_9860_424D_9E67_462C20C17C15__INCLUDED_)
#define AFX_CREATECPCMAPDLG_H__CD8D8BBD_9860_424D_9E67_462C20C17C15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCreateCpcMapDlg dialog

#include  "Constantes.h"
#include  "Bitmap.h"
#include  "SpriteCPC.h"
#include  "Resource.h"


extern SpriteCPC TabSprites[ MAX_SPRITES ];

extern WORD Map[ NB_ELT_MAP_Y ][ NB_ELT_MAP_X ];


class CCreateCpcMapDlg : public CDialog
{
// Construction
public:
    CCreateCpcMapDlg(CWnd* pParent = NULL);    // standard constructor

// Dialog Data
    //{{AFX_DATA(CCreateCpcMapDlg)
    enum { IDD = IDD_CREATECPCMAP_DIALOG };
    CStatic     m_Col[ 16 ];
    CStatic     m_MemoBloc;
    CEdit       m_NumSprite;
    CEdit       m_PosXMap, m_PosYMap, m_SpriteMap;
    CButton     m_CpcPlus;
    CScrollBar  m_VscrollMap;
    CScrollBar  m_HscrollMap;
    CScrollBar  m_ScrollSprite;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CCreateCpcMapDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    //{{AFX_MSG(CCreateCpcMapDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar * pScrollBar );
    afx_msg void OnHScroll( UINT nSBCode, UINT nPos, CScrollBar * pScrollBar );
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLireSprites();
    afx_msg void OnImportSprites();
    afx_msg void OnSauverSprites();
    afx_msg void OnEditSprites();
    afx_msg void OnRazSprites();
    afx_msg void OnLireMap();
    afx_msg void OnImportMap();
    afx_msg void OnSauverMap();
    afx_msg void OnRazMap();
    afx_msg void OnCol00( void );
    afx_msg void OnCol01( void );
    afx_msg void OnCol02( void );
    afx_msg void OnCol03( void );
    afx_msg void OnCol04( void );
    afx_msg void OnCol05( void );
    afx_msg void OnCol06( void );
    afx_msg void OnCol07( void );
    afx_msg void OnCol08( void );
    afx_msg void OnCol09( void );
    afx_msg void OnCol10( void );
    afx_msg void OnCol11( void );
    afx_msg void OnCol12( void );
    afx_msg void OnCol13( void );
    afx_msg void OnCol14( void );
    afx_msg void OnCol15( void );
    afx_msg void OnSauverPalette();
    afx_msg void OnLirePalette();
    afx_msg void OnCpcPlus();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private :
    void RedrawSprites( void );
    void RedrawMap( void );
    void DrawSprite( int x, int y, int n );
    void SelectSprite( int x, int y );
    void UpdateSpriteSel( void );
    void AffichePalette( void );
    void ClickCol( int NumCol );

    char Tmp[ 128 ];
    int Palette[ 16 ];
    int OffsetNumSprite;
    int NumSpriteSel;
    int xSel, ySel;
    int OffsetMapX, OffsetMapY;
    int CopyMapX, CopyMapY;
    MonBitmap BmSprites, BmMap, BmSelSprite;
    CDC * hDC;
    int xMulti, yMulti, xMultiEnd, yMultiEnd;
    BOOL MemoBloc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATECPCMAPDLG_H__CD8D8BBD_9860_424D_9E67_462C20C17C15__INCLUDED_)
