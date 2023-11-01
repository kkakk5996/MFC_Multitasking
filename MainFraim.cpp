// MainFrm.h

#pragma once

class CMainFrame : public CFrameWnd {
protected: // create from serialization only
    CMainFrame() noexcept;
    DECLARE_DYNCREATE(CMainFrame)

    // Attributes
public:

    // Operations
public:

    // Overrides
public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

    // Implementation
public:
    virtual ~CMainFrame();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected: // control bar embedded members
    CStatusBar m_wndStatusBar;
    CToolBar m_wndToolBar;

    // Generated message map functions
protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnNewWindow();
    DECLARE_MESSAGE_MAP()
};

// MainFrm.cpp

#include "stdafx.h"
#include "MultiTasking.h"

#include "MainFrm.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    ON_WM_CREATE()
    ON_COMMAND(ID_WINDOW_NEW, &CMainFrame::OnNewWindow)
END_MESSAGE_MAP()

CMainFrame::CMainFrame() noexcept {
}

CMainFrame::~CMainFrame() {
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs) {
    if (!CFrameWnd::PreCreateWindow(cs))
        return FALSE;

    return TRUE;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
    if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT,
        WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
        !m_wndToolBar.LoadToolBar(IDR_MAINFRAME)) {
        TRACE0("Failed to create toolbar\n");
        return -1; // fail to create
    }

    if (!m_wndStatusBar.Create(this)) {
        TRACE0("Failed to create status bar\n");
        return -1; // fail to create
    }

    return 0;
}

void CMainFrame::OnNewWindow() {
    AfxBeginThread(RUNTIME_CLASS(CChildFrame));
}
