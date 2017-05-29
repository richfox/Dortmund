
// MFCShellControlsView.h : interface of the CMFCShellControlsView class
//

#pragma once

#include <afxShellListCtrl.h>


class CMFCShellControlsView : public CView
{
protected: // create from serialization only
	CMFCShellControlsView();
	DECLARE_DYNCREATE(CMFCShellControlsView)

// Attributes
public:
	CMFCShellControlsDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMFCShellControlsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void OnActivateView(BOOL bActivate,CView* pActivateView,CView* pDeactiveView);

private:
	CMFCShellListCtrl m_wndList;

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // debug version in MFCShellControlsView.cpp
inline CMFCShellControlsDoc* CMFCShellControlsView::GetDocument() const
   { return reinterpret_cast<CMFCShellControlsDoc*>(m_pDocument); }
#endif

