#ifndef SQL_H
#define SQL_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdint.h>
#include <mysql.h>

using namespace std;

class SQL
{
	MYSQL* conn;//���ݿ���
	//**�ýṹ����1�����ݿ����ӵľ����**�������е�MySQL������ʹ��������Ӧ���Կ���MYSQL�ṹ������֤���࿽����������á�
	bool isAutoCommit;
	vector<vector<string> > result;

public:
	SQL(void);

	SQL(const char* ip, const char* user, const char* passwd, const char* database, uint16_t port);

	~SQL(void);

	bool connect(const char* ip, const char* user, const char* passwd, const char* database, uint16_t port);

	//���ز�ѯ/Ӱ�������//���󷵻�-1//û�б�Ӱ����з���0
	int insert(const char* cmd);
	int remove(const char* cmd);
	int update(const char* cmd);
	int select(const char* cmd);

	void clearResult(void);

	void showResult(void);

	bool offAutoCommit(void);
	bool onAutoCommit(void);
	bool getAutoCommit(void);
};

#endif//SQL_H
