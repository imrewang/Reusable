#include <stdio.h>
#include"sql.h"

#define BUFFER_SIZE 1024

int main() {
	SQL sql("127.0.0.1", "root", "root", "EMS", 3306);
	//localhost=127.0.0.1,ǰһ��rootΪ�û�������һ��rootΪ�û����룬EMS���Լ����������ݿ�����
	//Ҫ���ĵľ��� "root", "root", "EMS"

	cout << "�������û�����";
	string name;
	cin >> name;
	
	char* cmd = (char*)malloc(1024);
	memset(cmd, 0, 1024);

	sprintf_s(cmd, BUFFER_SIZE, "select name from employee where name=\"%s\"", name.c_str());
	//employee��EMS���ݿ��еı�

	int seln = sql.select(cmd);

	if (seln > 0)
	{
		cout << "�ɹ���ѯ����Ա��" << endl;

		cout << "���������룺";
		string pw;
		cin >> pw;

		sprintf_s(cmd, BUFFER_SIZE, "select id,name,age from employee where name=\"%s\" and password=\"%s\"", name.c_str(), pw.c_str());

		int selpw = sql.select(cmd);

		if (selpw > 0)
		{
			cout << "��֤�ɹ�" << endl;
			cout << "_-_-_-_-_-id_-_";
			cout << "        ����   ";
			cout << "        ����" << endl;
			sql.showResult();

			free(cmd);
			return 0;
		}
		else if(selpw==0){
			cout << "�������" << endl;
			
		}
		else if (selpw == -1) {
			cout << "��֤����" << endl;
		}
	}
	else if (seln == 0) {
		cout << "δ��ѯ����Ա��" << endl;
	}
	else if (seln == -1) {
		cout << "��ѯ����" << endl;
	}

	free(cmd);
	return 0;
}