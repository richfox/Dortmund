// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MFCRibbonAppView.cpp : implementation of the CMFCRibbonAppView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCRibbonApp.h"
#endif

#include "MFCRibbonAppDoc.h"
#include "MFCRibbonAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCRibbonAppView

IMPLEMENT_DYNCREATE(CMFCRibbonAppView, CView)

BEGIN_MESSAGE_MAP(CMFCRibbonAppView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCRibbonAppView construction/destruction

CMFCRibbonAppView::CMFCRibbonAppView()
{
	// TODO: add construction code here

}

CMFCRibbonAppView::~CMFCRibbonAppView()
{
}

BOOL CMFCRibbonAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCRibbonAppView drawing

void CMFCRibbonAppView::OnDraw(CDC* /*pDC*/)
{
	CMFCRibbonAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CMFCRibbonAppView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCRibbonAppView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCRibbonAppView diagnostics

#ifdef _DEBUG
void CMFCRibbonAppView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCRibbonAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCRibbonAppDoc* CMFCRibbonAppView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCRibbonAppDoc)));
	return (CMFCRibbonAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCRibbonAppView message handlers
