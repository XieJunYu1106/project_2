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
	//�ҵ���iflag-1������
	if (NULL == szLine && NULL == szData)
	{
		cout << "error! fun:Get_Data: the wrong line";
		return 0;
	}
	while (iflag != 1)
	{
		while (1)//��ת����һ������
		{
			if (*(szLine + i) == ',')//������ֶ�����break
			{
				break;
			}
			else if (*(szLine + i) == '\0')//��������Ѿ���β�ˣ�˵��iflag����������szline����
			{
				cout << "error! fun:Get_Data: the wrong input str" << endl;
				system("PAUSE");
				return 0;
			}
			i++;
		}
		i++;//������ǰ����
		iflag--;
	}
	int j = 0;
	//������������֮������ݵ�szData��
	while (*(szLine + i) != ',' && *(szLine + i) != '\0')
	{
		*(szData + j) = *(szLine + i);
		i++;
		j++;
	}
	*(szData + j) = '\0';//����ַ�����β����
	return szData;
}
//�õ��ļ���ĳ�е�iflag����Ϣ����szData
int Infor_Operator::Cmp_Password( IN_PARAM char* szID, IN_PARAM char* szPS)//�Ա�����
{
	fstream file("User_Information.csv", ios::in);
	if (file.fail())
	{
		cout << "�ļ���ʧ��!" << endl;
		system("PAUSE");
		exit(1);
	}

	//��������
	file.seekg(0);
	char cLine[100];//�洢һ����Ϣ
	char cStr[20];//�洢�˺�
	int SuccessID = 0;//�ж��˺��Ƿ����
	while (!file.eof())//���ļ�δ����β
	{
		file.getline(cLine, 100);
		Get_Data(1, cLine, cStr);
		if (strcmp(cStr, szID) == 0)
		{
			Get_Data(2, cLine, cStr);//�����˺Ŷ�Ӧ�������cStr�����˳�ѭ��
			SuccessID = 1;//��Ǹ��˺Ŵ���
			break;//����
		}
	}
	//0 : �˺Ų����ڻ����������
	//1��2��3��4 ��ӦȨ��
	if (SuccessID == 0)
	{
		cout << "�˺Ų����ڣ�" << endl;
		return 0;
	}
	else if (strcmp(szPS, cStr) == 0)//�˶�����
	{
		char c[2];
		Get_Data(3, cLine, c);
		int Rights = c[0] - '0';//�õ�Ȩ�޺��벢����
		return Rights;
	}
	file.close();
	cout << "�������" << endl;
	return 0;
}//��֤��½��Ϣ

void Infor_Operator::Add_User( IN_PARAM char * ID, IN_PARAM char * Password, IN_PARAM int right)
{

	fstream File("User_Information.csv", ios::in | ios::app);
	if (File.fail())
	{
		cout << "�ļ���ʧ��!" << endl;
		system("PAUSE");
		exit(1);
	}
	File.seekp(ios::end);
	File<<ID << "," << Password << ","<<right << '\n';
	File.close();

}
char * Infor_Operator::Change_Data(IN_PARAM int iflag, IN_PARAM char * szLine, IN_PARAM char * szChange, OUT_PARAM char * szOutline)
{
	int i_L = 0;//szLineָ��λ��
	int i_O = 0;//Outineָ��λ��
	int i_C = 0;//Changeָ��λ��
	if (NULL == szLine && NULL == szChange)
	{
		cout << "error! fun:Get_Data: the wrong line";
		return 0;
	}
	//�ҵ���iflag-1������,���Ѷ���ǰ������д���ַ���
	while (iflag != 1)
	{
		while (1)//��ת����һ������
		{
			szOutline[i_O] = szLine[i_L];//д������ַ���
			if (*(szLine + i_L) == ',')//������ֶ�����break
			{
				break;
			}
			else if (*(szLine + i_L) == '\0')//��������Ѿ���β�ˣ�˵��iflag����������szline����
			{
				cout << "error! fun:Get_Data: the wrong input str" << endl;
				system("PAUSE");
				return 0;
			}

			i_L++;
			i_O++;
		}
		i_L++;//������ǰ����
		i_O++;
		iflag--;
	}
	//�����Ҫ�޸ĵ��ַ���
	while (szChange[i_C] != '\0')
	{
		szOutline[i_O] = szChange[i_C];
		i_O++;
		i_C++;

	}
	//��szLineָ��λ���Ƶ���һ������
	while (1)//��ת����һ������
	{
		if (*(szLine + i_L) == ',')//������ֶ�����break
		{
			break;
		}
		else if (*(szLine + i_L) == '\0')//��������Ѿ���β�ˣ�˵�������һ�����ݣ��������������
		{
			break;
		}
		i_L++;
	}
	//д��֮����ַ�
	while (szLine[i_L] != '\0' && szLine[i_L] != '\n')
	{
		szOutline[i_O] = szLine[i_L];
		i_O++;
		i_L++;
	}
	//���ĩβ�Ļس��ͽ�β
	szOutline[i_O] = '\n';
	szOutline[i_O] = '\0';
	return szOutline;
}
//iflag = 0��ɾ���û���1������ID��2���������롣3����ɾ���������
int Infor_Operator::Reset_User(IN_PARAM int iflag, IN_PARAM char * szID, IN_PARAM char * szChange, int IN_PARAM iBook)
{
	fstream Old_File("User_Information.csv", ios::in);
	//���ļ�
	if (Old_File.fail())
	{
		cout << "�ļ���ʧ��!" << endl;
		system("PAUSE");
		exit(1);
	}
	fstream Trans_File("User_Information_Trans.csv", ios::out);
	if (Trans_File.fail())
	{
		cout << "�ļ���ʧ��!" << endl;
		system("PAUSE");
		exit(1);
	}

	//�ҵ���Ҫ�ҵ����û�,����ǰ����û���Ϣд����ת�ļ�
	Old_File.seekg(0);
	Trans_File.seekp(0);
	char cLine[1024];//�洢һ����Ϣ
	char cStr[40];//�洢�˺�
	int findif = 0;//�ж��Ƿ��ҵ��û�ID
	while (!Old_File.eof())
	{
		Old_File.getline(cLine, 1024);
		Get_Data(1, cLine, cStr);
		if (strcmp(cStr, szID) == 0)//����ҵ����û���Ϣ������
		{
			findif = 1;
			break;
		}
		Trans_File << cLine << '\n';
	}

	if (findif == 0)
	{
		cout << "�Ҳ���ID" << endl;
		return 0;
	}

	//�Եõ���һ�н����޸�
	if (iflag == 0)//ɾ��������Ϣ
	{
		Old_File.getline(cLine, 1024);
	}
	else if (iflag == 4)//�ı������Ϣ
	{
		Get_Data(4, cLine, cStr);//�õ�������Ϣ
								 //ת�������ϢΪ���Ͳ����мӼ�
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
		//����δ����
	}
	else//�ı�ָ����Ϣ
	{
		char cLine_changed[1024];//���ڴ洢�ı���cLine
		Change_Data(iflag, cLine, szChange, cLine_changed);//�ı�ָ������
		Trans_File << cLine_changed << '\n';//���뵽��ת�ļ�
		Old_File.getline(cLine, 1024);//��ȡ��һ��
	}
	//��֮����û���Ϣд����ת�ļ�
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

	//����ת�ļ�д��ԭ�ļ�
	Old_File.open("User_Information.csv", ios::out);
	if (Old_File.fail())
	{
		cout << "�ļ���ʧ��!" << endl;
		system("PAUSE");
		exit(1);
	}
	Trans_File.open("User_Information_Trans.csv", ios::in);
	if (Trans_File.fail())
	{
		cout << "�ļ���ʧ��!" << endl;
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
	cout << "�������˺���Ϣ��" << endl;
	cout << "�˺ţ�";
	cin >> ID;
	cout << "���룺";
	cin >> PS;
	flag = C.Cmp_Password(ID, PS);
	if (flag == 0)return;
	for (int i = 0; i < 1000; i++)
	{
		Show(flag,ID, PS);
		cout << "�Ƿ񷵻���һ�����������(Y/N)" << endl;
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
			cout <<"0.�޸�����" << endl<<"1.����" << endl << "2.����" << endl << "3.�ڿ��в�ѯ�鼮" << endl << "4.��ѯ�Լ������鼮Ŀ¼" << endl ;
			break;
		case 2:
			cout << "0.�޸�����" << endl << "1.����" << endl << "2.����" << endl << "3.�ڿ��в�ѯ�鼮" << endl << "4.��ѯ�Լ������鼮Ŀ¼" << endl ;
			break;
		case 3:
			cout << "0.�޸�����" << endl << "1.����" << endl << "2.����" << endl << "3.�ڿ��в�ѯ�鼮" << endl << "4.��ѯ�Լ������鼮Ŀ¼" << endl << "5.�����鼮" << endl << "6.ɾ���鼮" << endl << "7.�޸��鼮��Ŀ" <<  endl;
			break;
		case 4:
			cout << "0.�޸�����" << endl << "1.����" << endl << "2.����" << endl << "3.�ڿ��в�ѯ�鼮" << endl << "4.��ѯ�Լ������鼮Ŀ¼" << endl << "5.�����鼮" << endl << "6.ɾ���鼮" << endl << "7.�޸��鼮��Ŀ" << endl << "8.�������û� " << endl << "9.ɾ���û���Ϣ" <<   endl;
			break;
		}
		cout << "������������(0,1,2,3...):";
		cin >> oper;
		switch (oper)
		{
		case 0:
			system("cls");
			cout << "�������µ����룺";
			cin >> PS;
			C.Reset_User(2, ID, PS);
			cout << "�޸ĳɹ�!" << endl;
			break;
		case 5:
			system("cls");
		case 8:
			system("cls");
			cout << "�������½��˺ţ�";
			cin >> nID;
			cout << "�������½����룺";
			cin >> nPS;
			cout << "�������û�Ȩ�ޣ�1.ѧ�� 2.��ʦ 3.ͼ�����Ա 4.ϵͳ����Ա��";
			cin >> oper;
			C.Add_User(nID, nPS, oper);
			cout << "�½��ɹ�!" << endl;
			break;
		case 9:
			system("cls");
			cout << "������Ҫɾ�����˺ţ�";
			cin >> nID;
			if(C.Reset_User(0, nID)==1)
			cout << "ɾ���ɹ���" << endl;
			break;
		}
	}
}
