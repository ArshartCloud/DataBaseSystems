#include "data_rw.h"
#define PAGE_SIZE 8 * 1024
#define storeFile "data.dat"

void store(char * dataStr) {
	FILE * dataFile;
	dataFile = fopen(storeFile, "wb");
	char buffer[PAGE_SIZE * 2];
	buffer[0] = '[';
	int bufferSize = 1;
	// translate every row
	// find \n \0
	char newline[] = "\n{count:";
	char * index = dataStr, *temp = NULL;
	bool over = false;
	while(!over) {
		index = strstr(index, newline);
		// find a line
		{
			temp = index + 1;
			temp = strstr(temp, newline);  // find next newline
			if (temp == NULL) {  // not found ==> it's the last record
				// find the last record
				char lastFlag[] = "},\n]\n";
				temp = index;
				temp = strstr(temp, lastFlag) + 2;  // can find next \n
				over = true; // break
			}
			// translate the record of this line, add to buffer
			xStr xstr = transLine(index, temp);
			my_strcpy(buffer + bufferSize, xstr.content, xstr.size);  // buffer += translated str
			delete [] xstr.content;
			bufferSize += xstr.size;
			// if buffer length >= 8k: write 8k; cut off the written data;
			if (bufferSize >= PAGE_SIZE) {
				fwrite(buffer, sizeof(char), PAGE_SIZE, dataFile);
				bufferSize -= PAGE_SIZE;
				my_strcpy(buffer, buffer + PAGE_SIZE, bufferSize);  // cut off 8k, compact the str to the its header.
			}
		}
		++index;
	}
	
	char tail[] = "\n]\n";
	my_strcpy(buffer + bufferSize, tail, 3);  // buffer += tail
	bufferSize += 3;
	// if buffer length >= 8k: write 8k; cut off the written data;
	if (bufferSize >= PAGE_SIZE) {
		fwrite(buffer, sizeof(char), PAGE_SIZE, dataFile);
		bufferSize -= PAGE_SIZE;
		my_strcpy(buffer, buffer + PAGE_SIZE, bufferSize);  // cut off 8k, compact the str to the its header.
	}
	//printf("ss: %d\n", bufferSize);
	// if buffer still has data, it shouldn't excess 8k, write all
	if (bufferSize != 0) {
		fwrite(buffer, sizeof(char), bufferSize, dataFile);
	}
	
	fclose(dataFile);
}
void my_strcpy(char* des, char* src, int size) {
	for (int i = 0; i < size; i++) {
		*(des + i) = *(src + i);
	}
}
int str2int(char * start, char * end) {
	// str to int
	int result = 0;
	for (char *t = start; t != end; t++) {
		result = result * 10 + (*t - '0');
	}
	return result;
}
bool isNum(char * start, char * end) {
	if (start == end) return false;
	for (char *t = start; t != end; t++) {
		if (*t < '0' || *t > '9')
			return false;
	}
	return true;
}
xStr transLine(char * start, char * end) {
	char *temp, *index = NULL, *ic;
	temp = new char[2000];
	int sep[100];  // sep[] is used to record offset & len
	int sepCount = 0, i = 0, num = 0;
	bool arriveData = false;
	for (char *t = start; t != end; ) {
		// for every record, starts with {
		if (*t == '{') {
			// initial sep & sepCount
			sepCount = 0;
			temp[i++] = *t;
			t++;
			arriveData = false;
		}
		else if (*t == 'd' && *(t+1) == 'a') {  // if "da" data
			strncpy(&temp[i], t, 6);  // copy "data: "
			i += 6;
			t += 6;  // t point to datastr[0]
			arriveData = true;
		}
		else if ((*t == 'o' && *(t+1) == 'f') || (*t == 'l')) {  // if "of" offset or "l" len
			index = strstr(t, " ");  // the first space
			strncpy(&temp[i], t, index - t + 1); // copy "keyname: " including space
			i = i + index - t + 1;
			t = index + 1;  // t point to num
			//  t point to num, find num's end, translate to int,
			index = strstr(t, ",");  // the first ',' is the end of num; index point to ','
			num = str2int(t, index);
			sep[sepCount++] = num;  // add to sep, increase sepCount;
			// trans to char*, add to temp
			ic = (char*) &num;
			for (int k = 0; k < 4; k++) {
				temp[i++] = ic[k];
			}
			t = index;  // t point to ","
		}
		else if (*t == 'c' || *t == 'a') {  // count or aidxx
			index = strstr(t, " ");  // the first space
			strncpy(&temp[i], t, index - t + 1); // copy "keyname: " including space
			i = i + index - t + 1;
			t = index + 1;  // t point to num
			//  t point to num, find num's end, translate to int,
			index = strstr(t, ",");  // the first ',' is the end of num; index point to ','
			num = str2int(t, index);
			// trans to char*, add to temp
			ic = (char*) &num;
			for (int k = 0; k < 4; k++) {
				temp[i++] = ic[k];
			}
			t = index;  // t point to  ","
		}
		else {
			temp[i++] = *t;
			t++;
		}

		if (arriveData) {
			// translate data field
			int number = 0;
			for (int l = 0; l < sepCount - 1; l++) {
				if (sep[l+1] > sep[l]) {
                    if (isNum(t + sep[l], t + sep[l+1])) {
                        number = str2int(t + sep[l], t + sep[l+1]); // trans to int, add to temp
                        ic = (char*) &number;
                        for (int k = 0; k < 4; k++) {
                            temp[i++] = ic[k];
                        }
                    } else {  // not number, add to temp
                        my_strcpy(&temp[i], t + sep[l], sep[l+1] - sep[l]);
                        i = i + sep[l+1] - sep[l];
                    }
                }
			}
			// add t, t += len
			t += sep[sepCount - 1]; // t point to }
			arriveData = false;   // end of data field
		}
	}



	xStr result(i, temp);  // need to delete []result.content
	return result;
}

char * my_find_subStr(char * src, char * sub, int srcSize, int subSize) {
	if (srcSize < subSize) return NULL;
	for (int i = 0; i <= srcSize - subSize; i++) {
		int k = 0;
		for (; k < subSize; k++) {
			if (src[i + k] != sub[k])
				break;
		}
		if (k == subSize) {
			return src + i;
		}
	}
	return NULL;
}

int addInt(char * des, char * src) {
	int * ip = (int * )src, temp;
	temp = *ip;
	if (temp == 0) {
		*des = '0';
		++des;
		return 1;
	}
	bool neg = false;
	if (temp < 0) {
		temp = -temp;
		neg = true;
	}
	char num[15];
	int len = 0;
	while (temp != 0) {
		num[len++] = temp % 10;
		temp /= 10;
	}
	if (neg) {
		*des = '-';
		des++;
	}
	for (int i = len - 1; i >= 0; i--) {
		*des = num[i] + '0';
		des++;
	}
	if (neg) len++;
	return len;
}

bool isInt(char * start) {
	for (int i = 0; i < 4; i++) {
		char c = *(start + i);
		if (c <= 31 || c == 127)
			return true;
		if (c == '|' || c == ';' || c == '~' || c == '!' || c == '@')
			return true;
		if (c == '#' || c == '^' || c == '&' || c == '+' || c == '\\')
			return true;
		if (c == '"' || c == '<' || c == '>' || c == '?')
			return true;
	}
	return false;
}

int getIntLen(char * start) {
	int * ip = (int * )start, temp;
	temp = *ip;
	if (temp == 0) {
		return 1;
	}
	bool neg = false;
	if (temp < 0) {
		temp = -temp;
		neg = true;
	}
	int len = 0;
	while (temp != 0) {
		temp /= 10;
	}
	if (neg) len++;
	return len;
}

char* require(int n) {
	FILE * dataFile;
	dataFile = fopen(storeFile, "rb");
	fseek(dataFile, n * PAGE_SIZE, SEEK_SET);  // read from n-th page
	char buffer[PAGE_SIZE * 2];
	int bufferSize = 0;

	int realLen = fread(buffer, sizeof(char), PAGE_SIZE, dataFile);
	bufferSize += realLen;
	if (realLen == 0) {  // page is out of range
		return NULL;
	}

	// find the first completed record
	// if the head record is splited, delete it
    char s1[] = "{count: ";
	char * index = my_find_subStr(buffer, s1, bufferSize, 8);  // assume can find
	while (*(index - 1) == ' ') {
		index = my_find_subStr(index + 1, s1, bufferSize - (index - buffer), 8);  // assume can find
	}
	bufferSize = bufferSize - (index - buffer);
	my_strcpy(buffer, index, bufferSize);  // compact to left

	// if tail record is splited into 2 page, read next page, add the addtional str of last record
	if (buffer[bufferSize - 3] != '}' && buffer[bufferSize - 2] != ',' && buffer[bufferSize - 1] != '\n') {
		// if the tail of buffer != "},\n"
		realLen = fread(buffer + bufferSize, sizeof(char), PAGE_SIZE, dataFile);
		bufferSize += realLen;
        char s2[] = "},\n";
		index = my_find_subStr(buffer + PAGE_SIZE - 2, s2, PAGE_SIZE + 2, 3);
		bufferSize = index - buffer + 3;
	}
	else if (buffer[bufferSize - 3] != '\n' && buffer[bufferSize - 2] != ']' && buffer[bufferSize - 1] != '\n') {
		// the last page. end with \n]\n
		bufferSize -= 2;
	}
	// buffer is clean... ex. \n{count: ...},\n{count: ...},\n

	char * result = new char[PAGE_SIZE * 2];
	// translate int to char
	index = buffer;
	int sep[100], sepCount = 0, resultLength = 0, intlen;
	bool issep = false;
	while(index < (buffer + bufferSize)) {
		if (*index == '{' && *(index + 1) == 'c' && *(index + 2) == 'o') {  // new (sub) rocord line, initial
			sepCount = 0;
			issep = false;
			//
			*(result + resultLength) = *index;
			resultLength++;
			index++;
		}
		else if (*index == 'd' && *(index+1) == 'a') {  // data: 
			// solve data
			// add "data: "
			for (int it = 0; it < 6; it++) {
				*(result + resultLength) = *index;
				index++;
				resultLength++;
			}
			// translate data field
			int cur = 0, datalen = 0;
			while(1) {
				for (; cur < sepCount; cur++) {
					if (sep[cur] >= datalen) {
						break;
					}
				}
				int len = getIntLen(index);
				if (sep[cur + 1] - sep[cur] == 0) {
					cur++;
					continue;
				}
				if (datalen == sep[cur] && isInt(index) && len == (sep[cur + 1] - sep[cur])) {
					len = addInt(result + resultLength, index);
					resultLength += len;
					index += 4;
					datalen += len;
				} else {
					*(result + resultLength) = *index;
					resultLength++;
					index++;
					datalen++;
				}
				if (*index == '}' && *(index + 1) == ',')
					break;
			}
		}
		else if (*index == 'e') {  // offset or len
			issep = true;
			//
			*(result + resultLength) = *index;
			resultLength++;
			index++;
		}
		else if (*index == ':') {  // int
			*(result + resultLength) = ':';
			resultLength++;
			*(result + resultLength) = ' ';
			resultLength++;
			index += 2;
			// add int
			intlen = addInt(result + resultLength, index);
			resultLength += intlen;
			if (issep) { // if offset or len, add to sep
				int *integerP = (int *)index;
				sep[sepCount++] = *integerP;
			}
			index += 4;
			issep = false;
		}
		else {
			*(result + resultLength) = *index;
			resultLength++;
			index++;
		}
	}
	fclose(dataFile);
	result[resultLength] = '\0';
	if (result[resultLength - 2] == ']') {
		resultLength -= 2;
		result[resultLength] = '\0';
	}
	return result;
}