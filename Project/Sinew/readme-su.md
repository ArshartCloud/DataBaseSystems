修改了涉及到文件读写的代码

在page_rw.h定义了两个类
page_r:
	void reset();
	void my_fread(char * dataStr, int size, int count, FILE * rFile);
	void my_fread(int * integer, int size, int count, FILE * rFile);
	void my_fseek(FILE * rFile, int n, int mode);
	char my_fgetc(FILE * rFile);
page_w:
	void reset();
	void my_fwrite(char * dataStr, int size, int count, FILE * wFile);
	void my_fwrite(int * integer, int size, int count, FILE * wFile);
	void flush(FILE * wFile);

按8k读写。
由于类的变量为static, 读写另外一个文件的时候，必须调用reset。
写文件的最后，在关闭文件之前，要调用flush，把剩余的数据写入文件。

