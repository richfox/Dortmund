
// UIblockView.h : interface of the CUIblockView class
//

#pragma once

typedef std::shared_ptr<Gdiplus::Bitmap> BitmapPtr;

class CUIblockView : public CListView
{
protected: // create from serialization only
	CUIblockView();
	DECLARE_DYNCREATE(CUIblockView)

// Attributes
public:
	CUIblockDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

protected:
	// Draws the Mandelbrot fractal to the specified Bitmap object.
	void DrawMandelbrot(BitmapPtr);

protected:
	ULONG_PTR m_gdiplusToken;

	Concurrency::task_group m_DrawingTasks;
	Concurrency::unbounded_buffer<BitmapPtr> m_MandelbrotImages;


// Implementation
public:
	virtual ~CUIblockView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT, int, int);
	afx_msg void OnSizing(UINT, LPRECT); 
	afx_msg void OnDestroy();
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in UIblockView.cpp
inline CUIblockDoc* CUIblockView::GetDocument() const
   { return reinterpret_cast<CUIblockDoc*>(m_pDocument); }
#endif

