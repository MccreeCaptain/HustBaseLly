// OpenDBDialog.cpp : implementation file
//

#include "stdafx.h"
#include "HustBase.h"
#include "OpenDBDialog.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "HustBaseDoc.h"
#include "HustBaseView.h"
#include "TreeList.h"
#include "SYS_Manager.h"
#include <string>


CString strss2;
// COpenDBDialog dialog

IMPLEMENT_DYNAMIC(COpenDBDialog, CDialogEx)

COpenDBDialog::COpenDBDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(COpenDBDialog::IDD, pParent)
{

}

COpenDBDialog::~COpenDBDialog()
{
}

void COpenDBDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COpenDBDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &COpenDBDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &COpenDBDialog::OnBnClickedButton1)
END_MESSAGE_MAP()


// COpenDBDialog message handlers


void COpenDBDialog::OnBnClickedOk()//ȷ��ѡ�񣬴����ݿ�
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
	std::string str = CT2A(strss2.GetBuffer());//���ݿ�·����CStringת��ΪString
	OpenDB(str.c_str());//���ݿ�·����Stringת��Ϊconst char *����Ϊ�������ݵ�OpenDB����

	//��ȡ��ǰ����·��
	char buf[1000];
	GetCurrentDirectory(1000,buf);  //ʹ��windows api�õ���ǰ����·��
	CString s;
	s.Format("��ǰ����·������Ϊ�� %s", buf);
	AfxMessageBox(s);

	//������
	CHustBaseDoc *pDoc;
	pDoc=CHustBaseDoc::GetDoc();
	CHustBaseApp::pathvalue=true;
	pDoc->m_pTreeView->PopulateTree();
}


void COpenDBDialog::OnBnClickedButton1()//������ݿ��ַ
{
	// TODO: Add your control notification handler code here
	char szPath[MAX_PATH];     //���ѡ���Ŀ¼·�� 
	CString str;

	ZeroMemory(szPath, sizeof(szPath));   

	//ѡ��Ŀ¼
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
		strss2.Format("%s", szPath);
		str.Format("ѡ���Ŀ¼Ϊ %s",  szPath);
		AfxMessageBox(str); 
		SetDlgItemText( IDC_EDIT1, TEXT(strss2) );

	}
	else   
		AfxMessageBox("��Ч��Ŀ¼��������ѡ��");
}
