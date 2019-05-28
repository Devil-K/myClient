// MySQL_DIALOG.cpp : implementation file
//

#include "stdafx.h"
#include "CUS_OPCClient.h"
#include "MySQL_DIALOG.h"
//#include "string"

//数据库连接所用头文件
#include"winsock.h"
#include <string.h>
#include"C:\Program Files\MySQL\MySQL Server 5.5\include\mysql.h"
#pragma comment(lib,"libmySQL.lib")
#include "stdio.h"
#include <string.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


struct conn_info
{
  /*  char *host;
    char *user;
    char *password;
    char *db;*/
};
MYSQL*  mysql_conn_setup(conn_info con)
{
 MYSQL *mysql = mysql_init(NULL);
 if (!mysql_real_connect(mysql,"localhost","root","root","MySQL1",3306,NULL,0))//测试过 密码账号 写入错误的也能脸上数据库
 { 
 } //去除if循环 程序会卡退
 return mysql;
}
MYSQL_RES* mysql_conn_sqlQuery(MYSQL *mysql,char *sql_Query)
{
    if(mysql_query(mysql,sql_Query))
    {}
    return mysql_use_result(mysql);
}

/////////////////////////////////////////////////////////////////////////////
// MySQL_DIALOG dialog


MySQL_DIALOG::MySQL_DIALOG(CWnd* pParent /*=NULL*/): CDialog(MySQL_DIALOG::IDD, pParent)
{
	//{{AFX_DATA_INIT(MySQL_DIALOG)
//	he=0;
//	nnnname=0;
//	M_MySQL=0;
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MySQL_DIALOG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MySQL_DIALOG)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MySQL_DIALOG, CDialog)
	//{{AFX_MSG_MAP(MySQL_DIALOG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MySQL_DIALOG message handlers

void MySQL_DIALOG::OnOK() //按下connect键 执行的功能类
{
	MYSQL *com;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char sql_query[100];
    memset(sql_query,'\0',100);
	struct conn_info info;
     UpdateData(true);//窗口函数用来刷新数据
	 CString name,pwd;
     GetDlgItemText(IDC_EDIT1,name);//定义文本框名称 密码 用户名
	 GetDlgItemText(IDC_EDIT2,pwd);
	
    com=mysql_conn_setup(info);
    res=mysql_conn_sqlQuery(com,sql_query);
    
	MYSQL *mysql = mysql_init(NULL);		//  mysql_init():初始化数据库

	if (!mysql_real_connect(mysql,"localhost",name,pwd,"mysql",0,NULL,0))
 {	
		//char errMsg[200]={0};
		//sprintf(errMsg,"Conection error : %s/n",mysql_error(mysql));
	  //  MessageBox(errMsg);
		//cout << "Conection error : %s/n", mysql_error(mysql); 
    MessageBox("Connect Fail");   //数据库连接失败
 } else{ 
		mysql_real_connect(mysql,"localhost",name,pwd,"mysql",0,NULL,0);
		 MessageBox("Connect Success");//连接数据库成功\n
 }
    mysql_free_result(res);
    mysql_close(com);

}


void MySQL_DIALOG::InsertDB(const char* name,float flv, const char* time) //插入数据库的类 ,char time
{
    MYSQL *com;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char sql_query[100];
    memset(sql_query,'\0',100);
	struct conn_info info;   
    com=mysql_conn_setup(info);
    res=mysql_conn_sqlQuery(com,sql_query);

    MYSQL *mysql = mysql_init(NULL);
	if (mysql_real_connect(mysql,"localhost","root","root","mysql",0,NULL,0))
	{
			sprintf(sql_query,"insert into item_values  VALUES(\"%s\",%f,\"%s\")",name,flv,time);//  ,%s  ,time
		//	sprintf(sql_query,"insert into item_test VALUES(\"%s\",%f)",name,flv);
		mysql_query(mysql,sql_query);
	} 
	else
	{ 
  	}
    mysql_free_result(res);
    mysql_close(com);
}

//DEL void MySQL_DIALOG::OnInsertDB() 
//DEL { //实现点击InsertDB才上传数据到数据库   （待实现）
//DEL 
//DEL 	// TODO: Add your control notification handler code here
//DEL 	
//DEL }
