#pragma once


// �������ݿ� dialog

class �������ݿ� : public CDialogEx
{
	DECLARE_DYNAMIC(�������ݿ�)

public:
	�������ݿ�(CWnd* pParent = NULL);   // standard constructor
	virtual ~�������ݿ�();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
