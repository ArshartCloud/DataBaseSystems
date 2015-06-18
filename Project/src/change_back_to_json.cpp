#include <iostream>
#include "change_back_to_json.h"
#include "print.h"
#include "page_rw.h"
using namespace std;

int tran::add_num(FILE *in, form &json) {
    page_r Read;
    int x = 0;
    char ch = Read.my_fgetc(in);
    while (ch != ',') {
        ch = Read.my_fgetc(in);
        if (ch == ',') {
            ch = Read.my_fgetc(in);
            if (ch == ' ')
            ch = ',';
        }
    }
    Read.my_fseek(in, -6, SEEK_CUR);
    Read.my_fread(&x, sizeof(int), 1, in);
    return x;
}

void tran::read_detail(FILE *in, catalog* CATALOG, form &json) {
    page_r Read;
    Read.my_fseek(in, 3, SEEK_CUR);
    Read.my_fgetc(in);
    json.count = add_num(in, json);  // get count
    get_aid(in, json);
    get_offset(in, json);
    get_data(in, json);
    get_name(CATALOG, json);
    return;
}

void tran::write(FILE *in, FILE *out, catalog *CATALOG, form &json) {
    read_detail(in, CATALOG, json);
    char s1[] = "{";
    fwrite(s1, strlen(s1), 1, out);
    int i = 0, k = 0, len = json.offset.getSize(), size_d = json.data.getSize();
    for (; i < json.aid.getSize();i++) {
        char s2[] = "\"", s3[] = "\": ";
        fwrite(s2,strlen(s2), 1 , out);
        fwrite(json.name[i],strlen(json.name[i]),1,out);
        fwrite(s3, strlen(s3), 1, out);
        if (i + 1 >= len || i >= len) {
            break;
        }
        k = json.offset[i];
        if (k >= size_d) break;
        int off = json.offset[i + 1] - json.offset[i];
        if (strcmp(json.name[i], "nested_arr") == 0){ // 嵌套数组分开处理
            write_arr(out, json, k, i);
        }
        else if (off == 0) { // 这里递归调用
            form j1;
            write(in, out, CATALOG, j1);
            //char s1[] = ", ";
            //fwrite(s1, sizeof(s1), 1, out);
            fprintf(out, ", ");
            j1.data.vector_release();
            j1.aid.vector_release();
            j1.name.vector_release();
            j1.offset.vector_release();
        }
        else if(json.data[k] == 'T' || json.data[k] == 'F'){ // bool 类型的数
            write_bool(out, json, k);
        } else { // 处理int 类型和 字符串
            write_text(out, json, k, i);
        }
    }
    fprintf(out, "}");
}

void tran::write_bool(FILE *out, form &json, int &k) {
    if (json.data[k] == 'T') fprintf(out, "true, "); // 因为bool 类型偏移值只可能为1，要么是T，或者是F，所以就取巧了
    else fprintf(out, "false, ");
}

void tran::write_text(FILE *out, form &json, int &k, int &z) {
    int off = json.offset[z + 1] - json.offset[z];
    if (json.data[k] >= '0' && json.data[k] <= '9') {
        for (int j = 0; j < off; j++) {
            fprintf(out, "%c", json.data[k++]);
        }
    } else {
        fprintf(out, "\"");
        for (int j = 0; j < off; j++) {
            fprintf(out, "%c", json.data[k++]);
        }
        fprintf(out, "\"");
    }
	if (z < json.aid.getSize() - 1) fprintf(out, ", ");
}

void tran::write_arr(FILE *out, form &json, int &k, int &z) {
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
    if (nest[cal_num].getSize() == 0) fprintf(out, "\"\", ");
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

void tran::get_aid(FILE *in, form &json) {
    page_r Read;
    for (int i = 0; i < json.count; i++) {
        char c = Read.my_fgetc(in);
        while (c != ' ') {
            c = Read.my_fgetc(in);
        }
        c = Read.my_fgetc(in);
        int x = add_num(in, json);
        json.aid.add(x);
    }
}

void tran::get_offset(FILE *in, form &json) {
    page_r Read;
    for (int i = 0; i < json.count; i++) {
        char c = Read.my_fgetc(in);
        while (c != ' ') {
            c = Read.my_fgetc(in);
        }
        c = Read.my_fgetc(in);
        int x = add_num(in, json);
        json.offset.add(x);
    }
    char c = Read.my_fgetc(in);
    while (c != ' ') {
        c = Read.my_fgetc(in);
    }
    c = Read.my_fgetc(in);
    int x = add_num(in, json);
    json.offset.add(x);
}

void tran::get_data(FILE *in, form &json) {
    page_r Read;
    int size = json.offset.getSize();
    int len = json.offset[size - 1];
    char c = Read.my_fgetc(in);
    Read.my_fseek(in, 3, SEEK_CUR);
    while (c != ' ') c = Read.my_fgetc(in);
    for (int i = 0; i < len; i++) {
        char ch = Read.my_fgetc(in);
        json.data.add(ch);
    }
    json.data.add('}');
    json.data.add(',');
    c = Read.my_fgetc(in);
    c = Read.my_fgetc(in);
    c = Read.my_fgetc(in);
}

void tran::get_name(catalog *CATALOG, form &json) {
    int size = json.aid.getSize();
    for(int i = 0; i < size; i++) {
        char* n = CATALOG -> search_id(json.aid[i]);
        json.name.add(n);
    }
}

