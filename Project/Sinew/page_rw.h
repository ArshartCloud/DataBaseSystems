#ifndef PAGE_RW_H
#define PAGE_RW_H

#include <cstdio>
#include <cstring>
class page_r
{
public:
	void reset();
	void my_fread(char * dataStr, int size, int count, FILE * rFile);
	void my_fread(int * integer, int size, int count, FILE * rFile);
	void my_fseek(FILE * rFile, int n, int mode);
	char my_fgetc(FILE * rFile);
private:
	static char buffer[10000 * 1024];
	static int size;
	static int cursor;
	static int page_number;
};

class page_w
{
public:
	void reset();
	void my_fwrite(char * dataStr, int size, int count, FILE * wFile);
	void my_fwrite(int * integer, int size, int count, FILE * wFile);
	void flush(FILE * wFile) ;
private:
	static char buffer[10000 * 1024];
	static int cursor;
	static int page_number;
};

#endif