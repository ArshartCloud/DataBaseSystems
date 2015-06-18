心得体会：
在本次实验中负责文件按页读写的部分。
通过这次实验，我对C语言的指针、字符串数组、和文件读写有了更多的了解。
起初做错了任务，写了将序列化后的字符串转为二进制，并按页读写。从这次失误认识到确认需求的重要性。

模块说明：
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

读操作：
每次读取8k的字符串到buffer数组，用cursor来定位下一个未读字符的位置，用size存储字符串的大小。
由于在多个函数读取同一文件，我将page_rw的变量设为static，以保证不同函数内部能读取同一个文件，因此，当想操作另外一个文件的时候，必须使用reset。
其余函数与C的文件读写函数功能和接口相似。

写操作：
每次写的时候，都把字符串复制到buffer数组，并用指针记录buffer的头尾。
当buffer超过8k，就写8k的数据进入文件。
在关闭文件之前，要调用flush，把剩余的数据写入文件。

