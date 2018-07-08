#include <iostream>
#define IN_PARAM
#define OUT_PARAM
using namespace std;
struct Books_Imformation//����Ϣ
{
	char cBook_Name[40];
	char cBook_Number[10];
	int iBook_Price;
	int iBook_N;//����������
};

struct Stu_Imformation//ѧ����Ϣ
{
	char cStudent_Number[20];
	char cStudent_Password[20];
	int iStudent_Rent;//��������
	char *szStudent_Book[10];//�������
};

struct Tea_Imformation//��ʦ��Ϣ
{
	char cTeacher_Number[20];
	char cTeacher_Password[20];
	int iTeacher_Rent;//��������
	char *szStudent_Book[30];//�������
};

struct Admin_Imformation//����Ա��Ϣ
{
	char cAdmin_Number[20];
	char cAdmin_Password[20];
	int iAdmin_Rent;//��������
	int iAdmin_Book[30];//�������
};

class Book_Operator
{

};

class Infor_Operator
{
public:
	//���ڵõ���iflag������
	char *Get_Data(IN_PARAM int iflag, IN_PARAM char *szLine, OUT_PARAM char *szData);
	//�����޸ĵ�iflag������
	char *Change_Data(IN_PARAM int iflag, IN_PARAM char * szLine, IN_PARAM char * szChange, OUT_PARAM char * outLine);
	//�����˺ţ������룬�Ƚ�������ȷ��
	int Cmp_Password(IN_PARAM char* szID, IN_PARAM char* szPS);
	//�����û�
	void Add_User(IN_PARAM char * ID, IN_PARAM char * Password, IN_PARAM int right);
	//�����û���Ϣ��iflag����ָ���޸�ĳһ���ݣ�ID����Ѱ���û���Ϣ��Nnmber����Ľ�ȡ���߷���
	int Reset_User(IN_PARAM int iflag, IN_PARAM char * szID, IN_PARAM char * szChange=NULL, int IN_PARAM iBook = 0);
};

class User_Operator //�û�����
{
public:
	virtual void Run();//�������º���
	void Borrow_Book();
	void Return_Book();
	void Search_Book();

};

class Book_Admin : public User_Operator
{
public:
	void Run();
	void Add_Book();//�����ļ������
	void Delete_Book();//ɾ���ļ������
	void Revise_Book();//�޸��ļ������
};

class Sys_Admin : public Book_Admin
{
public:
	void Run();
	//���ڹ����˺�����
	void Add_User(int flag);//�����û���Ϣ
	void Delete_User(int flag);//ɾ���û���Ϣ
	void Revise_User(int flag);//�޸��û���Ϣ
};

void Login();
void Show(int iflag, char ID[20], char  PS[20]);




