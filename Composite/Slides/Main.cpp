#include <afxwin.h>

#define IDC_MYBUTTON 100
#define IDC_MYEDIT 102

class CMyButton : public CButton
{
public:
	afx_msg void OnLButtonDblClk(UINT, CPoint);
	afx_msg void OnRButtonDblClk(UINT, CPoint);
private:
	DECLARE_MESSAGE_MAP(); // ������� �������� ������
};

void CMyButton::OnLButtonDblClk(UINT, CPoint)
{
	MoveWindow(CRect(120, 100, 220, 150), TRUE);
}

void CMyButton::OnRButtonDblClk(UINT, CPoint)
{
	MoveWindow(CRect(120, 10, 220, 50), TRUE);
}

BEGIN_MESSAGE_MAP(CMyButton, CButton) // ������� �������� �� ���������
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
END_MESSAGE_MAP()

class CMainWnd : public CFrameWnd
{
public:
	CMainWnd()
	{
		Create(NULL, _T("Slides"), WS_OVERLAPPEDWINDOW, rectDefault, NULL, NULL);
		m_static = new CStatic;
		if (m_static != nullptr)
		{
			m_static->Create(_T("static"), WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(10, 10, 100, 50), this);
		}
		m_button = new CMyButton;
		if (m_button != nullptr)
		{
			m_button->Create(_T("button"), WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(120, 10, 220, 50), this, IDC_MYBUTTON);
		}
		m_edit = new CEdit;
		if (m_edit != nullptr)
		{
			m_edit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(240, 10, 340, 50), this, IDC_MYEDIT);
		}
	}

	~CMainWnd()
	{
		if (m_static) delete m_static;
		if (m_button) delete m_button;
		if (m_edit) delete m_edit;
	}

	afx_msg void CMainWnd::OnKeyDown(UINT, UINT, UINT)
	{
		AfxMessageBox(_T(" Key Button Down "));
	}
	afx_msg void CMainWnd::OnRButtonDblClk(UINT, CPoint)
	{
		AfxMessageBox(_T(" Rigth Button Click "));
	}
	afx_msg void CMainWnd::OnLButtonDblClk(UINT, CPoint)
	{
		AfxMessageBox(_T(" Left Button Click "));
	}

	DECLARE_MESSAGE_MAP(); // ������� ��������

private:
	CStatic* m_static;
	CMyButton* m_button;
	CEdit* m_edit;
};

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)	// ������� �������� �� ���������
	ON_WM_LBUTTONDBLCLK(OnLeftButtonDoubleClick)		// ������� �� ������� ����� ������ ����
	ON_WM_RBUTTONDBLCLK()		// ������� �� ������� ������ ������ �����
	ON_WM_KEYDOWN()			// ������� �� ������� �������
END_MESSAGE_MAP()

class CMyApp : public CWinApp
{
public:
	CMyApp()
	{
	}

	BOOL InitInstance()override
	{
		m_pMainWnd = new CMainWnd();
		ASSERT(m_pMainWnd);
		m_pMainWnd->ShowWindow(SW_SHOW);
		m_pMainWnd->UpdateWindow();
		return TRUE;
	}
};

CMyApp app;
