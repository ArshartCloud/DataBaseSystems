#include <cstdio>
#include <cstring>

struct xStr {
	int size;
	char * content;
	xStr(int s, char * c) {
		size = s;
		content = c;
	};
};
/*
**以堆文件形式存储转化后的记录。
**会把纯数字的字段转化为int，再存储
*/
void store(char * dataStr);
/*
**分页读取文件, n为页码
*/
char* require(int n);

xStr transLine(char * start, char * end);
bool isNum(char * start, char * end);
int str2int(char * start, char * end);

int addInt(char * des, char * src);
bool isInt(char * start);
int getIntLen(char * start);


void my_strcpy(char* des, char* src, int size);
char * my_find_subStr(char * src, char * sub, int srcSize, int subSize);