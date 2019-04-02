#pragma once

class XUDPWatchPane;

class XUDPWatchPaneToolBar : public CMFCToolBar
{
public:

	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }

	virtual BOOL OnUserToolTip(CMFCToolBarButton* pButton, CString& strTTText ) const;

public:

	void SetPane(XUDPWatchPane* p)
	{
		m_Pane = p;
	}

private:

	XUDPWatchPane* m_Pane;
};

