#ifndef CHANGE_BACK_TO_JSON_H
#define CHANGE_BACK_TO_JSON_H

#include <iostream>
#include "serial.h"
#include "my_string.h"
#include "my_vector.cpp"
#include "catalog.h"
#include <cstdio>
#include <cstring>
using namespace std;

int id; 
struct form {
    int count; // the total
    int cur;
    my_vector<char> data;
    my_vector<int> aid; // the number of aid
    my_vector<char*> name; // to save each aid's name
    my_vector<int> offset; // record the offsets
    my_vector<char> str;
    //my_vactor<my_vector<char>> nest_arr;
};

class tran {
	public:
	void read_detail(catalog* CATALOG, form &json); // read the information from serial
	void write(FILE *in, FILE *out, catalog* CATALOG, form &json);
        void get_aid(int &cur, form &json);
        void get_offset(int &cur, form &json);
        void get_data(int &cur, form &json);
        void get_name(catalog * CATALOG, form &json);
        void write_arr(FILE *out, form json, int&k, int &z);
        void write_bool(FILE *out, form json, int &k);
        void write_text(FILE *out, form json, int&k, int &z);
};

void print(FILE *in, FILE *out, catalog* CATALOG) {
id = 0;
    fprintf(out, "[\n");
    char ch;
    ch = fgetc(in);
    ch = fgetc(in);
    while(ch != ']') {
      form j2;
      while(1) {
        ch = fgetc(in);
        if (ch == EOF || ch == '\n') break;
        else j2.str.add(ch);
      }
      tran a;
      if (j2.str.getSize() > 10) {
        a.write(in, out, CATALOG, j2);
      }
     j2.data.vector_release();
     j2.aid.vector_release();
        //int size = name.getSize();
        //for (int i = 0; i < size; i++) name[i] = NULL;
     j2.name.vector_release();
     j2.offset.vector_release();
     j2.str.vector_release();
     ch = fgetc(in);
     if (ch != ']') fprintf(out, ",\n");
     else fprintf(out, "\n");
   }
   fprintf(out, "]\n");
}

void tran::read_detail(catalog* CATALOG, form &json) {
    int cur = 0, next = 0, size = json.str.getSize();
    while (cur < size && json.str[cur] != ':')  cur++;
    cur++;
    cur++;
    while (cur < size && json.str[cur] >= '0' && json.str[cur] <= '9')
      next = next * 10 + (json.str[cur++] - '0');
    json.count = next;
    get_aid(cur, json);
    get_offset(cur, json);
    get_data(cur, json);
    get_name(CATALOG, json);
}

void tran::write(FILE *in, FILE *out, catalog *CATALOG, form &json) {
    read_detail(CATALOG, json);
    fprintf(out, "{");
    int i = 0, z = 0, k = 0, len = json.offset.getSize(), size = json.str.getSize(), size_d = json.data.getSize();
    for (; i < json.aid.getSize();i++) {
        fprintf(out, "\"");
//cout << "name: " << i << " " << json.name[i] << endl;
        fprintf(out, "%s", json.name[i]);
        fprintf(out, "\": ");
        if (i + 1 >= len || i >= len) {
	   cout << "error\n";
           break;
        }
        k = json.offset[i];
        if (k >= size_d) break;
//cout << "offset[i]: " << i << " " << json.offset[i] << endl;
        int off = json.offset[i + 1] - json.offset[i];
        if (strcmp(json.name[i], "nested_arr") == 0){ // 嵌套数组分开处理
            write_arr(out, json, k, i);
        }
	else if (off == 0) { // 这里递归调用
            form j1;
            z++;
            int cur = json.cur;
            while (cur < size && json.str[cur] != '}') {
                j1.str.add(json.str[cur++]);
            }
            j1.str.add(json.str[cur]);
            tran::write(in, out, CATALOG, j1);
            j1.data.vector_release();
            j1.aid.vector_release();
     	    j1.name.vector_release();
            j1.offset.vector_release();
            j1.str.vector_release();
	    fprintf(out, ", ");
        }
        else if(json.data[k] == 'T' || json.data[k] == 'F'){ // bool 类型的数
            write_bool(out, json, k);
        } else { // 处理int 类型和 字符串
            write_text(out, json, k, i);       
	}
    }
    fprintf(out, "}");
}

void tran::write_bool(FILE *out, form json, int &k) {
    if (json.data[k] == 'T') fprintf(out, "true, "); // 因为bool 类型偏移值只可能为1，要么是T，或者是F，所以就取巧了
    else fprintf(out, "false, ");
}

void tran::write_text(FILE *out, form json, int &k, int &z) {
    int off = json.offset[z + 1] - json.offset[z];
    if (json.data[k] >= '0' && json.data[k] <= '9') {
        for (int j = 0; j < off; j++) {
            //if (json.data[k] >= 0 && json.data[k] < 9) json.data[k] += '0';
            fprintf(out, "%c", json.data[k++]);
        }
    } else {
	fprintf(out, "\"");
        for (int j = 0; j < off; j++) {
            //if (json.data[k] >= 0 && json.data[k] < 9) json.data[k] += '0';
            fprintf(out, "%c", json.data[k++]);
        }
        fprintf(out, "\"");
    }
	if (z < json.aid.getSize() - 1) fprintf(out, ", ");
}

void tran::write_arr(FILE *out, form json, int &k, int &z) {
    int off = json.offset[z + 1] - json.offset[z], cal_num = 0;
    my_vector<char> nest[50];
    if (off == 0) {
      fprintf(out, "[], ");
      return;
    }
    fprintf(out, "[");
    for (int i = 0; i < off; i++) {
      if (json.data[k] == '|') {
         cal_num++;  
         k++;
      } else {
        nest[cal_num].add(json.data[k++]);
      }
    }
    for (int i = 0; i < cal_num; i++) {
      int size = nest[i].getSize();
      if (size == 0) fprintf(out, "\"\", ");
      else {
        fprintf(out, "\"");
        for (int j = 0; j < size; j++) {
          fprintf(out, "%c", nest[i][j]);
        }
        fprintf(out, "\", ");
      }
    }
    if (nest[cal_num].getSize() == 0) cout << "\"\", ";
    else {
      fprintf(out, "\"");
      int size = nest[cal_num].getSize();
      for (int j = 0; j < size; j++) fprintf(out, "%c", nest[cal_num][j]);
      fprintf(out, "\"");
    }
    fprintf(out, "], ");

// release memory
    for (int i = 0; i < 50; i++) {
      nest[i].vector_release();
    }
}

void tran::get_aid(int &cur, form &json) {
    int size = json.str.getSize();
    while(cur + 2 < size && json.str[cur + 2] == 'a') {
       cur += 2;
       int x = 0;
       while (cur < size && json.str[cur] != ' ') cur++;
       cur++;
       while (cur < size && json.str[cur] >= '0' && json.str[cur] <= '9') x = x * 10 + (json.str[cur++] - '0');
       json.aid.add(x);
    }
}

void tran::get_offset(int &cur, form &json) {
    int size = json.str.getSize();
    while (cur + 2 < size && json.str[cur + 2] == 'o') {
      cur += 2;
      int x = 0;
      while (cur< size && json.str[cur] != ' ') cur++;
      cur++;
      while (cur < size && json.str[cur] >= '0' && json.str[cur] <= '9') x= x * 10 + (json.str[cur++] - '0');
      json.offset.add(x);
    }
    cur += 7;
    int x = 0;
    while (cur < size && json.str[cur] >= '0' && json.str[cur] <= '9') {
        x = x * 10 + (json.str[cur++] - '0');
    }
    json.offset.add(x);
}

void tran::get_data(int &cur, form &json) {
    int size = json.str.getSize();
    cur += 8;
    while (cur < size && json.str[cur] != '}') {
       // if (json.str[cur] > 0 && json.str[cur] < 9) json.str[cur] += '0';
        json.data.add(json.str[cur++]);
    }
    if (cur < size) {
      json.data.add(json.str[cur]);
      json.cur = cur + 1;
    }
}

void tran::get_name(catalog *CATALOG, form &json) {
    int size = json.aid.getSize();
    for(int i = 0; i < size; i++) {
        char* n = CATALOG -> search_id(json.aid[i]);
        json.name.add(n);
        n = NULL;
    }
}

#endif
