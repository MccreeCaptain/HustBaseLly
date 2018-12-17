#include "stdafx.h"
#include "EditArea.h"
#include "SYS_Manager.h"
#include "QU_Manager.h"
#include "RM_Manager.h"
#include <string>
#include <iostream>
#include <Windows.h>
#include "RC.h"
#include <vector>
//����һ��vector����������*filehandle
std::vector<RM_FileHandle *> vec;
/*
vec.push_back(E e);//����
for(std::vector<RM_FileHandle *>::size_type i = 0; i < vec.size(); i++){//����
	RM_CloseFile(vec[i]);
}
*/
void ExecuteAndMessage(char * sql,CEditArea* editArea){//����ִ�е���������ڽ�������ʾִ�н�����˺������޸�
	std::string s_sql = sql;
	if(s_sql.find("select") == 0){
		SelResult res;
		Init_Result(&res);
		//rc = Query(sql,&res);
		//����ѯ�������һ�£����������������ʽ
		//����editArea->ShowSelResult(col_num,row_num,fields,rows);
		int col_num = 5;
		int row_num = 3;
		char ** fields = new char *[5];
		for(int i = 0;i<col_num;i++){
			fields[i] = new char[20];
			memset(fields[i],0,20);
			fields[i][0] = 'f';
			fields[i][1] = i+'0';
		}
		char *** rows = new char**[row_num];
		for(int i = 0;i<row_num;i++){
			rows[i] = new char*[col_num];
			for(int j = 0;j<col_num;j++){
				rows[i][j] = new char[20];
				memset(rows[i][j],0,20);
				rows[i][j][0] = 'r';
				rows[i][j][1] = i + '0';
				rows[i][j][2] = '+';
				rows[i][j][3] = j + '0';
			}
		}
		editArea->ShowSelResult(col_num,row_num,fields,rows);
		for(int i = 0;i<5;i++){
			delete[] fields[i];
		}
		delete[] fields;
		Destory_Result(&res);
		return;
	}
	RC rc = execute(sql);
	int row_num = 0;
	char**messages;
	switch(rc){
	case SUCCESS:
		row_num = 1;
		messages = new char*[row_num];
		messages[0] = "�����ɹ�";
		editArea->ShowMessage(row_num,messages);
		delete[] messages;
		break;
	case SQL_SYNTAX:
		row_num = 1;
		messages = new char*[row_num];
		messages[0] = "���﷨����";
		editArea->ShowMessage(row_num,messages);
		delete[] messages;
		break;
	default:
		row_num = 1;
		messages = new char*[row_num];
		messages[0] = "����δʵ��";
		editArea->ShowMessage(row_num,messages);
	delete[] messages;
		break;
	}
}

RC execute(char * sql){
	sqlstr *sql_str = NULL;
	RC rc;
	sql_str = get_sqlstr();
  	rc = parse(sql, sql_str);//ֻ�����ַ��ؽ��SUCCESS��SQL_SYNTAX
	
	if (rc == SUCCESS)
	{
		int i = 0;
		switch (sql_str->flag)
		{
			case 1:
			////�ж�SQL���Ϊselect���

			break;

			case 2:
			//�ж�SQL���Ϊinsert���

			break;

			case 3:	
			//�ж�SQL���Ϊupdate���
			break;

			case 4:					
			//�ж�SQL���Ϊdelete���
			break;

			case 5:
			//�ж�SQL���ΪcreateTable���
			break;

			case 6:	
			//�ж�SQL���ΪdropTable���
			break;

			case 7:
			//�ж�SQL���ΪcreateIndex���
			break;
	
			case 8:	
			//�ж�SQL���ΪdropIndex���
			break;
			
			case 9:
			//�ж�Ϊhelp��䣬���Ը���������ʾ
			break;
		
			case 10: 
			//�ж�Ϊexit��䣬�����ɴ˽����˳�����
			break;

		}
	}
	else{
		AfxMessageBox(sql_str->sstr.errors);//���������sql���ʷ�����������Ϣ
		return rc;
	}
	return rc;
}

RC CreateDB(char *dbpath,char *dbname){//�������ݿ�
	RC rc1, rc2, rc3;
	rc1 = SUCCESS;//δ���
	//"D:\DBMS\student","student"
	//char *ת string
	std::string str_dbpath(dbpath);
	std::string str_dbname(dbname);

	//ͨ���ַ�����������ļ�·�����ļ���
	std::string str1 = str_dbpath + "\\" + str_dbname + ".xx"; 
	std::string str2 = str_dbpath + "\\SYSTABLES.xx";
	std::string str3 = str_dbpath + "\\SYSCOLUMNS.xx";

	//stringתconst char *
	const char* c_s1 = str1.c_str();
	const char* c_s2 = str2.c_str();
	const char* c_s3 = str3.c_str();

	//const char *תchar *
	char * c1 = new char[1000];
	char * c2 = new char[1000];
	char * c3 = new char[1000];
	//strcpy(c1, c_s1);
	strcpy(c2, c_s2);
	strcpy(c3, c_s3);

	//�����ļ�
	rc2 = RM_CreateFile(c2, 25);
	rc3 = RM_CreateFile(c3, 76);
	// 	FILE *fp=NULL;
	// 	FILE *fp2 = NULL;
	// 	FILE *fp3 = NULL;
	//     fopen_s(&fp,c_s1,"w");
	// 	fopen_s(&fp2,c_s2,"w");
	// 	fopen_s(&fp3,c_s3,"w");
	// 	fclose(fp);
	// 	fclose(fp2);
	// 	fclose(fp3);

	if(rc1 != SUCCESS){
		return rc1;
	}
	else if(rc2 != SUCCESS){
		return rc2;
	}
	else if (rc3 != SUCCESS){
		return rc3;
	}
	else{
		return SUCCESS;
	}
}

RC DropDB(const char * dbpath){
	if(RemoveDir(dbpath) == true)
		return SUCCESS;
	else
		return (RC)32;//FAIL
}

RC OpenDB(const char *dbpath){
	
	if(SetCurrentDirectory(dbpath))//����ָ��·��Ϊ����·��
		return SUCCESS;
	else return (RC)32;//FAIL
}


RC CloseDB(){
	for(std::vector<RM_FileHandle *>::size_type i = 0; i < vec.size(); i++){//����vector�еľ���ر�ÿһ���򿪵ļ�¼�ļ�
		if(vec[i] != NULL)
			RM_CloseFile(vec[i]);
	}
	vec.clear();
	return SUCCESS;
}

bool CanButtonClick(){//��Ҫ����ʵ��
	//�����ǰ�����ݿ��Ѿ���
	if(!vec.empty())//vector�ǿ�
		return true;
	//�����ǰû�����ݿ��
	else return false;
}

bool RemoveDir(const char* szFileDir)
{
	std::string strDir = szFileDir;
	if (strDir.at(strDir.length()-1) != '\\')
		strDir += '\\';
	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile((strDir + "*.*").c_str(),&wfd);
	if (hFind == INVALID_HANDLE_VALUE)
		return false;
	do
	{
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (stricmp(wfd.cFileName,".") != 0 &&
				stricmp(wfd.cFileName,"..") != 0)
				RemoveDir( (strDir + wfd.cFileName).c_str());
		}
		else
		{
			DeleteFile( (strDir + wfd.cFileName).c_str());
		}
	}
	while (FindNextFile(hFind,&wfd));
	FindClose(hFind);
	RemoveDirectory(szFileDir);
	return true;
}

RC CreateTable(char *relName,int attrCount,AttrInfo *attributes){
/*����һ����ΪrelName�ı�����attrCount��ʾ��ϵ�����Ե�������ȡֵΪ1��MAXATTRS֮�䣩��
����attributes��һ������ΪattrCount�����顣
�����¹�ϵ�е�i�����ԣ�attributes�����еĵ�i��Ԫ�ذ������ơ����ͺ����Եĳ���
*/
	//��ȡ��ǰ����·��
	char buf[1000];
	GetCurrentDirectory(1000,buf);  //ʹ��windows api�õ���ǰ����·��
	CString s;
	s.Format("��ǰ����·������Ϊ�� %s", buf);
	AfxMessageBox(s);

	//����ǰ����·���������ϣ�����RM_CreateFile()������¼�ļ�����
	//char * ת string
	std::string strRel(relName);
	std::string strPath = buf;
	std::string strRelPath = strPath + "\\" + strRel + ".xx";
	//string ת char *����תΪconst char *����תΪchar *
	char cRelPath[1000];
	strcpy(cRelPath, strRelPath.c_str());
	//�����¼�ļ�ÿһ����¼�ĳ���
	int len = 0;
	int i;
	for(i = 0; i < attrCount; i++){
		len += attributes[i].attrLength;
	}
	//����RM_CreateFile()������¼�ļ�����
	RM_CreateFile(cRelPath,len);

	//�޸�SYSTABLES.xx��SYSCOLUMNS.xx�ļ�
	RM_FileHandle *SYSTABLESFileHandle = NULL;
	RM_FileHandle *SYSCOLUMNSFileHandle = NULL;
	//����vector����ѯ�Ƿ��Ѿ����ڸü�¼�ļ����
	for(std::vector<RM_FileHandle *>::size_type i = 0; i < vec.size(); i++){//����vector�еľ��
		if(vec[i] != NULL){
			//if(vec[i]->fileName)
		}
	}
}

RC DropTable(char *relName){
//������ΪrelName�ı��Լ��ڸñ��Ͻ���������������
	//ɾ�����ϵ�ÿһ������


	//ɾ����
}