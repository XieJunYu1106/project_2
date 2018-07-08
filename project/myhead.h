#include <iostream>
#define IN_PARAM
#define OUT_PARAM
using namespace std;
struct Books_Imformation//书信息
{
	char cBook_Name[40];
	char cBook_Number[10];
	int iBook_Price;
	int iBook_N;//该类书数量
};

struct Stu_Imformation//学生信息
{
	char cStudent_Number[20];
	char cStudent_Password[20];
	int iStudent_Rent;//借书数量
	char *szStudent_Book[10];//借书序号
};

struct Tea_Imformation//教师信息
{
	char cTeacher_Number[20];
	char cTeacher_Password[20];
	int iTeacher_Rent;//借书数量
	char *szStudent_Book[30];//借书序号
};

struct Admin_Imformation//管理员信息
{
	char cAdmin_Number[20];
	char cAdmin_Password[20];
	int iAdmin_Rent;//借书数量
	int iAdmin_Book[30];//借书序号
};

class Book_Operator
{

};

class Infor_Operator
{
public:
	//用于得到第iflag个数据
	char *Get_Data(IN_PARAM int iflag, IN_PARAM char *szLine, OUT_PARAM char *szData);
	//用于修改第iflag个数据
	char *Change_Data(IN_PARAM int iflag, IN_PARAM char * szLine, IN_PARAM char * szChange, OUT_PARAM char * outLine);
	//输入账号，和密码，比较密码正确性
	int Cmp_Password(IN_PARAM char* szID, IN_PARAM char* szPS);
	//增加用户
	void Add_User(IN_PARAM char * ID, IN_PARAM char * Password, IN_PARAM int right);
	//更新用户信息，iflag用于指定修改某一内容，ID用于寻找用户信息，Nnmber是书的借取或者返回
	int Reset_User(IN_PARAM int iflag, IN_PARAM char * szID, IN_PARAM char * szChange=NULL, int IN_PARAM iBook = 0);
};

class User_Operator //用户基类
{
public:
	virtual void Run();//调用以下函数
	void Borrow_Book();
	void Return_Book();
	void Search_Book();

};

class Book_Admin : public User_Operator
{
public:
	void Run();
	void Add_Book();//增加文件里的书
	void Delete_Book();//删除文件里的书
	void Revise_Book();//修改文件里的书
};

class Sys_Admin : public Book_Admin
{
public:
	void Run();
	//用于管理账号密码
	void Add_User(int flag);//增加用户信息
	void Delete_User(int flag);//删除用户信息
	void Revise_User(int flag);//修改用户信息
};

void Login();
void Show(int iflag, char ID[20], char  PS[20]);




