// CreateDBDialog.cpp : implementation file
//

#include "stdafx.h"
#include "HustBase.h"
#include "CreateDBDialog.h"
#include "afxdialogex.h"
#include <direct.h>    //ͷ�ļ�  
#include <string>
#include "SYS_Manager.h"

CString strss;

// CreateDBDialog dialog

IMPLEMENT_DYNAMIC(CreateDBDialog, CDialogEx)

CreateDBDialog::CreateDBDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CreateDBDialog::IDD, pParent)
{

}

CreateDBDialog::~CreateDBDialog()
{
}

void CreateDBDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CreateDBDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CreateDBDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CreateDBDialog::OnBnClickedButton1)
END_MESSAGE_MAP()


// CreateDBDialog message handlers


void CreateDBDialog::OnBnClickedOk()
{
	
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

	//��ȡ�ļ�·�������ݿ���
	CString cstrDbPath;
	CString cstrDbName;
	//��ȡ�ļ�·��
	cstrDbPath = strss;//����"D:\DBMS"
	//��ȡ���ݿ���
	GetDlgItemText(IDC_EDIT2,cstrDbName); //ȡ������ֵ��������cstrDbName;

	//CString ת String
	std::string strDbPath = CT2A(cstrDbPath.GetBuffer());//����"D:\DBMS"
	std::string strDbName = CT2A(cstrDbName.GetBuffer());//����"student"

	//�����ļ���
	//string dirName = "D:\\test";    
	//_mkdir(dirName.c_str());  
	std::string str1 = strDbPath + "\\" + strDbName;//����"D:\DBMS\student"
	_mkdir(str1.c_str());
	
	//string ת char *
	char * c1, * c2;
	const int len1 = str1.length();
	c1 = new char[len1 + 1];
	strcpy(c1, str1.c_str());
	const int len2 = strDbName.length();
	c2 = new char[len2 + 1];
	strcpy(c2, strDbName.c_str());

	//���ô������ݿ⺯��
	CreateDB(c1, c2);//��������"D:\DBMS\student","student"

	AfxMessageBox("�����ɹ�");
}


void CreateDBDialog::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	char szPath[MAX_PATH];     //���ѡ���Ŀ¼·�� 
	CString str;

	ZeroMemory(szPath, sizeof(szPath));   

	BROWSEINFO bi;   
	bi.hwndOwner = NULL;   
	bi.pidlRoot = NULL;   
	bi.pszDisplayName = szPath;   
	bi.lpszTitle = "��ѡ����Ҫ�����Ŀ¼��";   
	bi.ulFlags = 0;   
	bi.lpfn = NULL;   
	bi.lParam = 0;   
	bi.iImage = 0;   
	//����ѡ��Ŀ¼�Ի���
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);   

	if(lp && SHGetPathFromIDList(lp, szPath))   
	{
		strss.Format("%s", szPath);
		str.Format("ѡ���Ŀ¼Ϊ %s",  szPath);
		AfxMessageBox(str); 
		SetDlgItemText( IDC_EDIT3, TEXT(strss) );

	}
	else   
		AfxMessageBox("��Ч��Ŀ¼��������ѡ��");
}
