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
	MYSQL* conn;//数据库句柄
	//**该结构代表1个数据库连接的句柄。**几乎所有的MySQL函数均使用它。不应尝试拷贝MYSQL结构。不保证这类拷贝结果会有用。
	bool isAutoCommit;
	vector<vector<string> > result;

public:
	SQL(void);

	SQL(const char* ip, const char* user, const char* passwd, const char* database, uint16_t port);

	~SQL(void);

	bool connect(const char* ip, const char* user, const char* passwd, const char* database, uint16_t port);

	//返回查询/影响的行数//错误返回-1//没有被影响的行返回0
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
