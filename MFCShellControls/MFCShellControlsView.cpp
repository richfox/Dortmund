
// MFCShellControlsView.cpp : implementation of the CMFCShellControlsView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCShellControls.h"
#endif

#include "MFCShellControlsDoc.h"
#include "MFCShellControlsView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCShellControlsView

IMPLEMENT_DYNCREATE(CMFCShellControlsView, CView)

BEGIN_MESSAGE_MAP(CMFCShellControlsView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMFCShellControlsView construction/destruction

CMFCShellControlsView::CMFCShellControlsView()
{
	// TODO: add construction code here

}

CMFCShellControlsView::~CMFCShellControlsView()
{
}

BOOL CMFCShellControlsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCShellControlsView drawing

void CMFCShellControlsView::OnDraw(CDC* /*pDC*/)
{
	CMFCShellControlsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CMFCShellControlsView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCShellControlsView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCShellControlsView diagnostics

#ifdef _DEBUG
void CMFCShellControlsView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCShellControlsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCShellControlsDoc* CMFCShellControlsView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCShellControlsDoc)));
	return (CMFCShellControlsDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCShellControlsView message handlers


int CMFCShellControlsView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy (0, 0, 0, 0);
	m_wndList.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT,rectDummy, this, 1);

	return 0;
}


void CMFCShellControlsView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	m_wndList.SetWindowPos(NULL, -1, -1, cx, cy,SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
}

void CMFCShellControlsView::OnActivateView(BOOL bActivate,
	CView* pActivateView,
	CView* pDeactiveView) 
{
	if (bActivate && AfxGetMainWnd() != NULL)
	{
		((CMainFrame*)AfxGetMainWnd())->GetShellTreeCtrl().SetRelatedList(&m_wndList);
	}

	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}