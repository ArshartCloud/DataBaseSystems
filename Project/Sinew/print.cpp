#include "print.h"

using namespace std;
void print(FILE *in, FILE *out, catalog* CATALOG) {
    fprintf(out, "[\n");
    char ch;
    ch = fgetc(in);
    ch = fgetc(in);
    while(ch != ']') {
        form j2;
        tran a;
        a.write(in, out, CATALOG, j2);
        j2.data.vector_release();

        j2.aid.vector_release();

        j2.name.vector_release();

        j2.offset.vector_release();

        ch = fgetc(in);
        if (ch != ']') fprintf(out, ",\n");
        else fprintf(out, "\n");
    }
    fprintf(out, "]\n");
}

