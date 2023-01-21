#include "sql.h"
#include <iomanip>

SQL::SQL(void)
{
	isAutoCommit = true;//MySQL默认使用autocommit模式，也就是说，当你执行一个更新操作后，MySQL会立刻将结果进行提交。

	conn = mysql_init(NULL);//获取或初始化MYSQL结构。
	if (NULL == conn)
	{
		printf("errno:%d error:%s\n", mysql_errno(conn), mysql_error(conn));
		//返回上次调用的MySQL函数的错误编号。
		//返回上次调用的MySQL函数的错误消息。
	}
}

SQL::SQL(const char* ip, const char* user, const char* passwd, const char* database, uint16_t port)
{
	isAutoCommit = true;//MySQL默认使用autocommit模式，也就是说，当你执行一个更新操作后，MySQL会立刻将结果进行提交。

	conn = mysql_init(NULL);//获取或初始化MYSQL结构。
	if (NULL == conn)
	{
		printf("errno:%d error:%s\n", mysql_errno(conn), mysql_error(conn));
		return;
	}

	connect(ip, user, passwd, database, port);
}

SQL::~SQL(void)
{

}

bool SQL::connect(const char* ip, const char* user, const char* passwd, const char* database, uint16_t port)
{
	if (NULL == mysql_real_connect(conn, ip, user, passwd, database, port, NULL, 0))//连接到MySQL服务器。
	{
		printf("---errno:%d error:%s\n", mysql_errno(conn), mysql_error(conn));
		return false;
	}

	onAutoCommit();

	return true;
}

void SQL::clearResult(void)
{
	for (vector<vector<string> >::iterator it = result.begin(); it != result.end(); it++)
	{
		it->clear();
	}

	result.clear();
}

void SQL::showResult(void)
{
	for (vector<vector<string> >::iterator i = result.begin(); i != result.end(); i++)
	{
		for (vector<string>::iterator j = i->begin(); j != i->end(); j++)
		{
			cout << setw(12) << *j << "   ";//set()当后面紧跟着的输出字段长度小于n的时候，在该字段前面用空格补齐；当输出字段长度大于n时，全部整体输出。
			//只对紧接着的输出有效
			//后面又加了3个空格，所以一共15个字段长度
			//一个汉字占两个字段长度，一个字母占一个字段长度
		}
		cout << endl;
	}
}

int SQL::insert(const char* cmd)
{
	if (mysql_query(conn, cmd) != 0)//执行指定为“以Null终结的字符串”的SQL查询。
	{
		printf("errno:%d error:%s\n", mysql_errno(conn), mysql_error(conn));
		return -1;
	}

	return mysql_affected_rows(conn);//	返回上次UPDATE、DELETE或INSERT查询更改／删除／插入的行数。
}

int SQL::remove(const char* cmd)
{
	if (mysql_query(conn, cmd) != 0)//执行指定为“以Null终结的字符串”的SQL查询。
	{
		printf("errno:%d error:%s\n", mysql_errno(conn), mysql_error(conn));
		return -1;
	}

	return mysql_affected_rows(conn);//	返回上次UPDATE、DELETE或INSERT查询更改／删除／插入的行数。
}

int SQL::update(const char* cmd)
{
	if (mysql_query(conn, cmd) != 0)//执行指定为“以Null终结的字符串”的SQL查询。
	{
		printf("errno:%d error:%s\n", mysql_errno(conn), mysql_error(conn));
		return -1;
	}

	return mysql_affected_rows(conn);//	返回上次UPDATE、DELETE或INSERT查询更改／删除／插入的行数。
}

int SQL::select(const char* cmd)
{
	MYSQL_RES* res;//查询结果集
	//**该结构代表返回行的查询结果**（SELECT, SHOW, DESCRIBE, EXPLAIN）。在本节的剩余部分，将查询返回的信息称为“结果集”。
	MYSQL_ROW row;//记录结构体
	//**这是1行数据的“类型安全”表示。**
	//它目前是按照计数字节字符串的数组实施的。
	//（如果字段值可能包含二进制数据，不能将其当作由Null终结的字符串对待，这是因为这类值可能会包含Null字节）。
	//行是通过调用mysql_fetch_row()获得的。

	if (mysql_query(conn, cmd) != 0)
	{
		printf("errno:%d error:%s\n", mysql_errno(conn), mysql_error(conn));
		return -1;
	}

	int num_fields = mysql_field_count(conn);//返回上次执行语句的结果列的数目。
	if (num_fields == 0)
	{
		printf("errno:%d error:%s\n", mysql_errno(conn), mysql_error(conn));
		return -1;
	}

	res = mysql_store_result(conn);//检索完整的结果集至客户端。
	if (NULL == res)
	{
		printf("errno:%d error:%s\n", mysql_errno(conn), mysql_error(conn));
		return -1;
	}

	clearResult();

	int count = 0;
	while ((row = mysql_fetch_row(res)))//从结果集中获取下一行
	{
		vector<string> arr;
		for (int i = 0; i < num_fields; i++)
		{
			string str(row[i]);
			arr.push_back(str);
		}
		result.push_back(arr);
		count++;
	}

	mysql_free_result(res);//释放结果集使用的内存。
	return count;
}

bool SQL::offAutoCommit(void)
{
	isAutoCommit = false;
	return mysql_autocommit(conn, isAutoCommit);//切换 autocommit模式，ON/OFF
	//可以放在一个事务中执行提交，要么全部执行要么全部不执行
}

bool SQL::onAutoCommit(void)
{
	isAutoCommit = true;
	return mysql_autocommit(conn, isAutoCommit);//切换 autocommit模式，ON/OFF
}

bool SQL::getAutoCommit(void)
{
	return isAutoCommit;
}
