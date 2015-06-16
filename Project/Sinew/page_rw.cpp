#include "page_rw.h"
#define PAGE_SIZE 8 * 1024

int page_r::size = 0;
int page_r::cursor = 0;   // point to the first unread char
int page_r::page_number = 0;  // point ot next page;
char page_r::buffer[10000 * 1024] = {'\0'};


void page_r::reset() {
	size = 0;
	cursor = 0;   // point to the first unread char
	page_number = 0;  // point ot next page;
}
//fread(str, count, 1, fp);
void page_r::my_fread(char * dataStr, int size, int count, FILE * rFile) {
	// ignore File
	int length = size * count;
	for (int i = 0 ; i < length; i++) {
		dataStr[i] = my_fgetc(rFile);
	}
}
void page_r::my_fread(int * integer, int size, int count, FILE * rFile) {
	// ignore File
	char * dataStr = (char *) integer;
	my_fread(dataStr, size, count, rFile);
}
void page_r::my_fseek(FILE * rFile, int n, int mode) {
	if (mode == SEEK_CUR) {
		cursor += n;
		while (cursor >= size) {  // may cause dead loop, if file comes to an end.
			fseek(rFile, page_number * PAGE_SIZE, SEEK_SET);  // read from n-th page
			int realLen = fread(buffer + page_number * PAGE_SIZE, sizeof(char), PAGE_SIZE, rFile);
			size += realLen;
			page_number++;
		}
	}
}
char page_r::my_fgetc(FILE * rFile) {
	if (cursor == size) {  // one whole page is read -> read a new page	
		fseek(rFile, page_number * PAGE_SIZE, SEEK_SET);  // read from n-th page
		int realLen = fread(buffer + page_number * PAGE_SIZE, sizeof(char), PAGE_SIZE, rFile);
		size += realLen;
		page_number++;
	}
	if (cursor < size) {
		char ch = buffer[cursor];
		cursor++;
		return ch;
	}
	return '\0';
}



int page_w::cursor = 0;   // point to the first unread char
int page_w::page_number = 0;  // point ot next page;
char page_w::buffer[10000 * 1024] = {'\0'};
void page_w::reset() {
	cursor = 0;   // point to the first unread char
	page_number = 0;  // point ot next page;
}
void page_w::my_fwrite(char * dataStr, int size, int count, FILE * wFile) {
	int length = size * count;
	for (int i = 0; i < length; i++) {
		buffer[cursor++] = dataStr[i];
	}
	if (cursor - page_number * PAGE_SIZE >= PAGE_SIZE) {
		fwrite(buffer + page_number * PAGE_SIZE, sizeof(char), PAGE_SIZE, wFile);
		page_number++;
	}
}
void page_w::my_fwrite(int * integer, int size, int count, FILE * wFile) {
	char * dataStr = (char *) integer;
	my_fwrite(dataStr, size, count, wFile);
}

void page_w::flush(FILE * wFile) {
	int leftLength = cursor - page_number * PAGE_SIZE;
	fwrite(buffer + page_number * PAGE_SIZE, sizeof(char), leftLength, wFile);
	page_number++;
}