// DropDBDialog.cpp : implementation file
//

#include "stdafx.h"
#include "HustBase.h"
#include "DropDBDialog.h"
#include "afxdialogex.h"
#include <windows.h>
#include <string>
#include "SYS_Manager.h"


CString strDirectory;
// DropDBDialog dialog

IMPLEMENT_DYNAMIC(DropDBDialog, CDialogEx)

DropDBDialog::DropDBDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(DropDBDialog::IDD, pParent)
{

}

DropDBDialog::~DropDBDialog()
{
}

void DropDBDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DropDBDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &DropDBDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &DropDBDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// DropDBDialog message handlers


void DropDBDialog::OnBnClickedButton1()//������ݿ���ɾ��
{
	// TODO: Add your control notification handler code here
	char szPath[MAX_PATH];     //���ѡ���Ŀ¼·�� 
	CString str;

	ZeroMemory(szPath, sizeof(szPath));   

	BROWSEINFO bi;   
	bi.hwndOwner = NULL;   
	bi.pidlRoot = NULL;   
	bi.pszDisplayName = szPath;   
	bi.lpszTitle = "��ѡ��Ŀ¼��";   
	bi.ulFlags = 0;   
	bi.lpfn = NULL;   
	bi.lParam = 0;   
	bi.iImage = 0;   
	//����ѡ��Ŀ¼�Ի���
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);   

	if(lp && SHGetPathFromIDList(lp, szPath))   
	{
		strDirectory.Format("%s", szPath);
		str.Format("ѡ���Ŀ¼Ϊ %s",  szPath);
		AfxMessageBox(str); 
		SetDlgItemText( IDC_EDIT1, TEXT(strDirectory) );

	}
	else   
		AfxMessageBox("��Ч��Ŀ¼��������ѡ��");
	
}


void DropDBDialog::OnBnClickedOk()//ȷ��ɾ��ѡ�е����ݿ�
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
	//CString ת String
	std::string str = CT2A(strDirectory.GetBuffer());//����"D:\DBMS\student"
	//String ת const char *������DropDB(const char *dbpath)ɾ���ļ���
	DropDB(str.c_str());
	AfxMessageBox("ɾ���ɹ�");
	
}

