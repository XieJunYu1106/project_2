#ifndef MYHEAD_H
#define MYHEAD_H

#include "myhead.h"
#include<iostream>
#include<fstream>
#include<cstring>
#include<sstream>
#include<string>
#endif

using namespace std;

char * Infor_Operator::Get_Data(IN_PARAM int iflag, IN_PARAM char *szLine, OUT_PARAM char *szData)
{
	int i = 0;
	//找到第iflag-1个逗号
	if (NULL == szLine && NULL == szData)
	{
		cout << "error! fun:Get_Data: the wrong line";
		return 0;
	}
	while (iflag != 1)
	{
		while (1)//跳转到下一个逗号
		{
			if (*(szLine + i) == ',')//如果发现逗号则break
			{
				break;
			}
			else if (*(szLine + i) == '\0')//如果发现已经结尾了，说明iflag输入错误或者szline出错
			{
				cout << "error! fun:Get_Data: the wrong input str" << endl;
				system("PAUSE");
				return 0;
			}
			i++;
		}
		i++;//跳过当前逗号
		iflag--;
	}
	int j = 0;
	//复制两个逗号之间的内容到szData中
	while (*(szLine + i) != ',' && *(szLine + i) != '\0')
	{
		*(szData + j) = *(szLine + i);
		i++;
		j++;
	}
	*(szData + j) = '\0';//添加字符串结尾符号
	return szData;
}
//得到文件中某行第iflag个信息存至szData
int Infor_Operator::Cmp_Password( IN_PARAM char* szID, IN_PARAM char* szPS)//对比密码
{
	fstream file("User_Information.csv", ios::in);
	if (file.fail())
	{
		cout << "文件打开失败!" << endl;
		system("PAUSE");
		exit(1);
	}

	//遍历查找
	file.seekg(0);
	char cLine[100];//存储一行信息
	char cStr[20];//存储账号
	int SuccessID = 0;//判断账号是否存在
	while (!file.eof())//当文件未到结尾
	{
		file.getline(cLine, 100);
		Get_Data(1, cLine, cStr);
		if (strcmp(cStr, szID) == 0)
		{
			Get_Data(2, cLine, cStr);//将该账号对应密码存至cStr，并退出循环
			SuccessID = 1;//标记该账号存在
			break;//跳出
		}
	}
	//0 : 账号不存在或者密码错误
	//1，2，3，4 对应权限
	if (SuccessID == 0)
	{
		cout << "账号不存在！" << endl;
		return 0;
	}
	else if (strcmp(szPS, cStr) == 0)//核对密码
	{
		char c[2];
		Get_Data(3, cLine, c);
		int Rights = c[0] - '0';//得到权限号码并返回
		return Rights;
	}
	file.close();
	cout << "密码错误！" << endl;
	return 0;
}//验证登陆信息

void Infor_Operator::Add_User( IN_PARAM char * ID, IN_PARAM char * Password, IN_PARAM int right)
{

	fstream File("User_Information.csv", ios::in | ios::app);
	if (File.fail())
	{
		cout << "文件打开失败!" << endl;
		system("PAUSE");
		exit(1);
	}
	File.seekp(ios::end);
	File<<ID << "," << Password << ","<<right << '\n';
	File.close();

}
char * Infor_Operator::Change_Data(IN_PARAM int iflag, IN_PARAM char * szLine, IN_PARAM char * szChange, OUT_PARAM char * szOutline)
{
	int i_L = 0;//szLine指针位置
	int i_O = 0;//Outine指针位置
	int i_C = 0;//Change指针位置
	if (NULL == szLine && NULL == szChange)
	{
		cout << "error! fun:Get_Data: the wrong line";
		return 0;
	}
	//找到第iflag-1个逗号,并把逗号前的内容写入字符串
	while (iflag != 1)
	{
		while (1)//跳转到下一个逗号
		{
			szOutline[i_O] = szLine[i_L];//写入输出字符串
			if (*(szLine + i_L) == ',')//如果发现逗号则break
			{
				break;
			}
			else if (*(szLine + i_L) == '\0')//如果发现已经结尾了，说明iflag输入错误或者szline出错
			{
				cout << "error! fun:Get_Data: the wrong input str" << endl;
				system("PAUSE");
				return 0;
			}

			i_L++;
			i_O++;
		}
		i_L++;//跳过当前逗号
		i_O++;
		iflag--;
	}
	//添加想要修改的字符串
	while (szChange[i_C] != '\0')
	{
		szOutline[i_O] = szChange[i_C];
		i_O++;
		i_C++;

	}
	//把szLine指针位置移到下一个逗号
	while (1)//跳转到下一个逗号
	{
		if (*(szLine + i_L) == ',')//如果发现逗号则break
		{
			break;
		}
		else if (*(szLine + i_L) == '\0')//如果发现已经结尾了，说明是最后一个数据，后面无须再添加
		{
			break;
		}
		i_L++;
	}
	//写入之后的字符
	while (szLine[i_L] != '\0' && szLine[i_L] != '\n')
	{
		szOutline[i_O] = szLine[i_L];
		i_O++;
		i_L++;
	}
	//添加末尾的回车和结尾
	szOutline[i_O] = '\n';
	szOutline[i_O] = '\0';
	return szOutline;
}
//iflag = 0：删除用户。1：更改ID。2：更改密码。3：增删借书情况。
int Infor_Operator::Reset_User(IN_PARAM int iflag, IN_PARAM char * szID, IN_PARAM char * szChange, int IN_PARAM iBook)
{
	fstream Old_File("User_Information.csv", ios::in);
	//打开文件
	if (Old_File.fail())
	{
		cout << "文件打开失败!" << endl;
		system("PAUSE");
		exit(1);
	}
	fstream Trans_File("User_Information_Trans.csv", ios::out);
	if (Trans_File.fail())
	{
		cout << "文件打开失败!" << endl;
		system("PAUSE");
		exit(1);
	}

	//找到想要找到的用户,并把前面的用户信息写入中转文件
	Old_File.seekg(0);
	Trans_File.seekp(0);
	char cLine[1024];//存储一行信息
	char cStr[40];//存储账号
	int findif = 0;//判断是否找到用户ID
	while (!Old_File.eof())
	{
		Old_File.getline(cLine, 1024);
		Get_Data(1, cLine, cStr);
		if (strcmp(cStr, szID) == 0)//如果找到该用户信息，跳出
		{
			findif = 1;
			break;
		}
		Trans_File << cLine << '\n';
	}

	if (findif == 0)
	{
		cout << "找不到ID" << endl;
		return 0;
	}

	//对得到的一行进行修改
	if (iflag == 0)//删除整行信息
	{
		Old_File.getline(cLine, 1024);
	}
	else if (iflag == 4)//改变书的信息
	{
		Get_Data(4, cLine, cStr);//得到借书信息
								 //转换书的信息为整型并进行加减
		string scStr = cStr;
		int isStr;
		stringstream ss1;
		ss1 << scStr;
		ss1 >> isStr;
		isStr += iBook;
		stringstream ss2;
		ss2 << isStr;
		ss2 >> scStr;
		strcpy_s(cStr, scStr.c_str());
		char cLine_changed[1024];
		Change_Data(iflag, cLine, cStr, cLine_changed);
		Trans_File << cLine_changed << ',' << szChange << '\n';
		Old_File.getline(cLine, 1024);
		//这里未完善
	}
	else//改变指定信息
	{
		char cLine_changed[1024];//用于存储改变后的cLine
		Change_Data(iflag, cLine, szChange, cLine_changed);//改变指定数据
		Trans_File << cLine_changed << '\n';//输入到中转文件
		Old_File.getline(cLine, 1024);//读取下一行
	}
	//把之后的用户信息写入中转文件
	if (!Old_File.eof())
	{
		Trans_File << cLine << '\n';
	}
	while (!Old_File.eof())
	{
		Old_File.getline(cLine, 1024);
		if (Old_File.eof())
		{
			break;
		}
		Trans_File << cLine << '\n';
	}
	Old_File.close();
	Trans_File.close();

	//从中转文件写入原文件
	Old_File.open("User_Information.csv", ios::out);
	if (Old_File.fail())
	{
		cout << "文件打开失败!" << endl;
		system("PAUSE");
		exit(1);
	}
	Trans_File.open("User_Information_Trans.csv", ios::in);
	if (Trans_File.fail())
	{
		cout << "文件打开失败!" << endl;
		system("PAUSE");
		exit(1);
	}
	Old_File.seekp(0);
	Trans_File.seekg(0);
	while (!Trans_File.eof())
	{
		Trans_File.getline(cLine, 1024);
		if (Trans_File.eof())
		{
			break;
		}
		Old_File << cLine << '\n';
	}
	Trans_File.close();
	Old_File.close();
	return 1;
}
void Login()
{
	Infor_Operator C;
	char ID[20], PS[20];
	char Continue;
	int flag;
	cout << "请输入账号信息：" << endl;
	cout << "账号：";
	cin >> ID;
	cout << "密码：";
	cin >> PS;
	flag = C.Cmp_Password(ID, PS);
	if (flag == 0)return;
	for (int i = 0; i < 1000; i++)
	{
		Show(flag,ID, PS);
		cout << "是否返回上一层继续操作？(Y/N)" << endl;
		cin >> Continue;
		if (Continue == 'Y');
		else break;
	}
}
void Show(int iflag, char ID[20], char  PS[20])
{
	Infor_Operator C;
	int oper;
	char nID[20], nPS[20];
	if (iflag != 0)
	{
		system("cls");
		switch (iflag)
		{
		case 1:
			cout <<"0.修改密码" << endl<<"1.借书" << endl << "2.还书" << endl << "3.在库中查询书籍" << endl << "4.查询自己所借书籍目录" << endl ;
			break;
		case 2:
			cout << "0.修改密码" << endl << "1.借书" << endl << "2.还书" << endl << "3.在库中查询书籍" << endl << "4.查询自己所借书籍目录" << endl ;
			break;
		case 3:
			cout << "0.修改密码" << endl << "1.借书" << endl << "2.还书" << endl << "3.在库中查询书籍" << endl << "4.查询自己所借书籍目录" << endl << "5.增加书籍" << endl << "6.删除书籍" << endl << "7.修改书籍数目" <<  endl;
			break;
		case 4:
			cout << "0.修改密码" << endl << "1.借书" << endl << "2.还书" << endl << "3.在库中查询书籍" << endl << "4.查询自己所借书籍目录" << endl << "5.增加书籍" << endl << "6.删除书籍" << endl << "7.修改书籍数目" << endl << "8.增添新用户 " << endl << "9.删除用户信息" <<   endl;
			break;
		}
		cout << "请输入操作编号(0,1,2,3...):";
		cin >> oper;
		switch (oper)
		{
		case 0:
			system("cls");
			cout << "请输入新的密码：";
			cin >> PS;
			C.Reset_User(2, ID, PS);
			cout << "修改成功!" << endl;
			break;
		case 5:
			system("cls");
		case 8:
			system("cls");
			cout << "请输入新建账号：";
			cin >> nID;
			cout << "请输入新建密码：";
			cin >> nPS;
			cout << "请输入用户权限，1.学生 2.老师 3.图书管理员 4.系统管理员：";
			cin >> oper;
			C.Add_User(nID, nPS, oper);
			cout << "新建成功!" << endl;
			break;
		case 9:
			system("cls");
			cout << "请输入要删除的账号：";
			cin >> nID;
			if(C.Reset_User(0, nID)==1)
			cout << "删除成功！" << endl;
			break;
		}
	}
}
