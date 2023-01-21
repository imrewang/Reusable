#include <stdio.h>
#include"sql.h"

#define BUFFER_SIZE 1024

int main() {
	SQL sql("127.0.0.1", "root", "root", "EMS", 3306);
	//localhost=127.0.0.1,前一个root为用户名，后一个root为用户密码，EMS是自己创建的数据库名称
	//要更改的就是 "root", "root", "EMS"

	cout << "请输入用户名：";
	string name;
	cin >> name;
	
	char* cmd = (char*)malloc(1024);
	memset(cmd, 0, 1024);

	sprintf_s(cmd, BUFFER_SIZE, "select name from employee where name=\"%s\"", name.c_str());
	//employee是EMS数据库中的表

	int seln = sql.select(cmd);

	if (seln > 0)
	{
		cout << "成功查询到此员工" << endl;

		cout << "请输入密码：";
		string pw;
		cin >> pw;

		sprintf_s(cmd, BUFFER_SIZE, "select id,name,age from employee where name=\"%s\" and password=\"%s\"", name.c_str(), pw.c_str());

		int selpw = sql.select(cmd);

		if (selpw > 0)
		{
			cout << "认证成功" << endl;
			cout << "_-_-_-_-_-id_-_";
			cout << "        姓名   ";
			cout << "        年龄" << endl;
			sql.showResult();

			free(cmd);
			return 0;
		}
		else if(selpw==0){
			cout << "密码错误" << endl;
			
		}
		else if (selpw == -1) {
			cout << "认证出错" << endl;
		}
	}
	else if (seln == 0) {
		cout << "未查询到此员工" << endl;
	}
	else if (seln == -1) {
		cout << "查询出错" << endl;
	}

	free(cmd);
	return 0;
}