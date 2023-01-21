#include "sql.h"
#include <iomanip>

SQL::SQL(void)
{
	isAutoCommit = true;//MySQLĬ��ʹ��autocommitģʽ��Ҳ����˵������ִ��һ�����²�����MySQL�����̽���������ύ��

	conn = mysql_init(NULL);//��ȡ���ʼ��MYSQL�ṹ��
	if (NULL == conn)
	{
		printf("errno:%d error:%s\n", mysql_errno(conn), mysql_error(conn));
		//�����ϴε��õ�MySQL�����Ĵ����š�
		//�����ϴε��õ�MySQL�����Ĵ�����Ϣ��
	}
}

SQL::SQL(const char* ip, const char* user, const char* passwd, const char* database, uint16_t port)
{
	isAutoCommit = true;//MySQLĬ��ʹ��autocommitģʽ��Ҳ����˵������ִ��һ�����²�����MySQL�����̽���������ύ��

	conn = mysql_init(NULL);//��ȡ���ʼ��MYSQL�ṹ��
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
	if (NULL == mysql_real_connect(conn, ip, user, passwd, database, port, NULL, 0))//���ӵ�MySQL��������
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
			cout << setw(12) << *j << "   ";//set()����������ŵ�����ֶγ���С��n��ʱ���ڸ��ֶ�ǰ���ÿո��룻������ֶγ��ȴ���nʱ��ȫ�����������
			//ֻ�Խ����ŵ������Ч
			//�����ּ���3���ո�����һ��15���ֶγ���
			//һ������ռ�����ֶγ��ȣ�һ����ĸռһ���ֶγ���
		}
		cout << endl;
	}
}

int SQL::insert(const char* cmd)
{
	if (mysql_query(conn, cmd) != 0)//ִ��ָ��Ϊ����Null�ս���ַ�������SQL��ѯ��
	{
		printf("errno:%d error:%s\n", mysql_errno(conn), mysql_error(conn));
		return -1;
	}

	return mysql_affected_rows(conn);//	�����ϴ�UPDATE��DELETE��INSERT��ѯ���ģ�ɾ���������������
}

int SQL::remove(const char* cmd)
{
	if (mysql_query(conn, cmd) != 0)//ִ��ָ��Ϊ����Null�ս���ַ�������SQL��ѯ��
	{
		printf("errno:%d error:%s\n", mysql_errno(conn), mysql_error(conn));
		return -1;
	}

	return mysql_affected_rows(conn);//	�����ϴ�UPDATE��DELETE��INSERT��ѯ���ģ�ɾ���������������
}

int SQL::update(const char* cmd)
{
	if (mysql_query(conn, cmd) != 0)//ִ��ָ��Ϊ����Null�ս���ַ�������SQL��ѯ��
	{
		printf("errno:%d error:%s\n", mysql_errno(conn), mysql_error(conn));
		return -1;
	}

	return mysql_affected_rows(conn);//	�����ϴ�UPDATE��DELETE��INSERT��ѯ���ģ�ɾ���������������
}

int SQL::select(const char* cmd)
{
	MYSQL_RES* res;//��ѯ�����
	//**�ýṹ�������еĲ�ѯ���**��SELECT, SHOW, DESCRIBE, EXPLAIN�����ڱ��ڵ�ʣ�ಿ�֣�����ѯ���ص���Ϣ��Ϊ�����������
	MYSQL_ROW row;//��¼�ṹ��
	//**����1�����ݵġ����Ͱ�ȫ����ʾ��**
	//��Ŀǰ�ǰ��ռ����ֽ��ַ���������ʵʩ�ġ�
	//������ֶ�ֵ���ܰ������������ݣ����ܽ��䵱����Null�ս���ַ����Դ���������Ϊ����ֵ���ܻ����Null�ֽڣ���
	//����ͨ������mysql_fetch_row()��õġ�

	if (mysql_query(conn, cmd) != 0)
	{
		printf("errno:%d error:%s\n", mysql_errno(conn), mysql_error(conn));
		return -1;
	}

	int num_fields = mysql_field_count(conn);//�����ϴ�ִ�����Ľ���е���Ŀ��
	if (num_fields == 0)
	{
		printf("errno:%d error:%s\n", mysql_errno(conn), mysql_error(conn));
		return -1;
	}

	res = mysql_store_result(conn);//���������Ľ�������ͻ��ˡ�
	if (NULL == res)
	{
		printf("errno:%d error:%s\n", mysql_errno(conn), mysql_error(conn));
		return -1;
	}

	clearResult();

	int count = 0;
	while ((row = mysql_fetch_row(res)))//�ӽ�����л�ȡ��һ��
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

	mysql_free_result(res);//�ͷŽ����ʹ�õ��ڴ档
	return count;
}

bool SQL::offAutoCommit(void)
{
	isAutoCommit = false;
	return mysql_autocommit(conn, isAutoCommit);//�л� autocommitģʽ��ON/OFF
	//���Է���һ��������ִ���ύ��Ҫôȫ��ִ��Ҫôȫ����ִ��
}

bool SQL::onAutoCommit(void)
{
	isAutoCommit = true;
	return mysql_autocommit(conn, isAutoCommit);//�л� autocommitģʽ��ON/OFF
}

bool SQL::getAutoCommit(void)
{
	return isAutoCommit;
}
