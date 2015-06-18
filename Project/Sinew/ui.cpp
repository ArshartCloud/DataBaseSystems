#include <iostream>
#include <cstdio>
#include <iomanip>
#include "ui.h"

const int padding_title = 29;
const int padding_break_line = 80;
const int padding_heading = 30;
const int padding_command = 15;
const int padding_term = 10;

const int length = 50;

void print_padding(int p, char c) {
    cout << setfill(c) << right << setw(p) << "";
    return;
}

void head(void) {
    // head
    print_padding(padding_title, ' ');
    cout << REVERSE << "Serializer v1.0" << RESET << endl;
    break_line();
    return;
}

void break_line(void) {
    // break line
    print_padding(padding_break_line, '-');
    cout << endl;
    return;
}

void report_bugs(void) {
    // REPORT BUGS
    cout << BOLD << "REPORTING BUGS" << RESET
         << endl;
    print_padding(padding_term, ' ');
    cout << "If you encounter and bugs while using this program, Please send us a "
         << endl;
    print_padding(padding_term, ' ');
    cout << "email <sptzxbbb@gmai.com>, and we will see what we can do."
         << endl;
    return;
}

void see_also(void) {
    // SEE_ALSO
    cout << BOLD << "SEE ALSO" << RESET
         << endl;
    print_padding(padding_term, ' ');
    cout << "Source code and full document are hosted at github:"
         << endl;
    print_padding(padding_term, ' ');
    cout <<"<https://github.com/sptzxbbb/DataBaseSystems>"
         << endl;
    cout << endl;
}

void command(void) {
    // heading
    print_padding(padding_heading, ' ');
    cout << RED << "User Commands" << RESET
         << endl << endl;
    // DESCRIPTION
    cout << BOLD << "DESCRIPTION" << RESET
         << endl;
    print_padding(padding_term, ' ');
    cout << "All the commands available and their usage are list below. Please"
         << endl;
    print_padding(padding_term, ' ');
    cout << "follow the instruction."
         << endl << endl;
    // insert filename
    print_padding(padding_term, ' ');
    cout << BOLD << "1.insert filename" << RESET
         << endl;
    print_padding(padding_command, ' ');
    cout << "Index a json file named \"filename\" and generate its"
         << endl;
    print_padding(padding_command, ' ');
    cout << "serialized file named \"filename_seiral\"."
         << endl << endl;
    // check catalog
    print_padding(padding_term, ' ');
    cout << BOLD << "2.check catalog" << RESET
         << endl;
    print_padding(padding_command, ' ');
    cout << "Print out all catalog's information."
         << endl << endl;
    // find A = B
    print_padding(padding_term, ' ');
    cout << BOLD << "3.find A = B" << RESET
         << endl;
    print_padding(padding_command, ' ');
    cout << "Show all the tuples that have been indexed conditional on"
         << endl;
    print_padding(padding_command, ' ');
    cout << UNDERLINE << "the key name A and key value B" << RESET << " entered"
         << endl << endl;
    // ls
    print_padding(padding_term, ' ');
    cout << BOLD << "4.ls path" << RESET
         << endl;
    print_padding(padding_command, ' ');
    cout << "Show the files in the path entered, current path by defaut."
         << endl << endl;
    // show prompt
    print_padding(padding_term, ' ');
    cout << BOLD << "5.help" << RESET
         << endl;
    print_padding(padding_command, ' ');
    cout << "Show full manual."
         << endl << endl;
    // exit
    print_padding(padding_term, ' ');
    cout << BOLD << "6.exit" << RESET
         << endl;
    print_padding(padding_command, ' ');
    cout << "End this program and return to terminal."
         << endl << endl;
    return;
}

void author(void) {
    // Author
    cout << BOLD << "Author" << RESET
         << endl;
    print_padding(padding_term, ' ');
    cout << "Written by team member Zhou Xiaobin, Tang Ziyang, Su Yimin and" << endl;
    print_padding(padding_term, ' ');
    cout << "Li Weiming."
         << endl << endl;
    return;
}

void copyright(void) {
    // copyright
    cout << BOLD << "COPYRIGHT" << RESET
         << endl;
    print_padding(padding_term, ' ');
    cout << "Copyright © 2015  Free Software Foundation, Inc. License GPLv3+:" << endl;
    print_padding(padding_term, ' ');
    cout << "GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>."
         << endl;
    print_padding(padding_term, ' ');
    cout << "This is free software: you are free to change and redistribute it."
         << endl;
     print_padding(padding_term, ' ');
    cout << "here is NO WARRANTY, to the extent permitted by law."
         << endl;
    cout << endl;
    return;
}


void insert(catalog& CATALOG) {
    FILE* in;
    FILE* out;
    page_r Read;
    page_w Write;
    char output[length] = "";
    char suffix1[] = "_serial";
    char suffix2[] = "_.json";
    char back_json[length] = "";
    char input[50];

    scanf("%s", input);
    cout << endl;
    strncpy(output, input, strlen(input) - 5);
    strncat(output, suffix1, strlen(suffix1));
    strncpy(back_json, input, strlen(input) - 5);
    strncat(back_json, suffix2, strlen(suffix2));

    // Transform json to serial
    in = fopen(input, "r");
    if (NULL == in) {
        cout << "Failed to open " << input << endl;
        cout << "Inserting Fails!" << endl;
        return;
    }
    out = fopen(output, "wb");
    if (NULL == out) {
        cout << "Failed to open" <<  output << endl;
        cout << "Inserting Fails!" << endl;
        return;
    }

    cout << "Creating " << output << "..." << endl;
    cout << "Please Wait..." << endl;
    write_file(in, out, &CATALOG);
    fclose(in);
    Write.flush(out);
    fclose(out);
    Read.reset();
    Write.reset();
    cout << "Done!" << endl << endl;

    // Transform serial back to json
    in = fopen(output, "rb");
    if (NULL == in) {
        cout << "Failed to open" << output << endl;
        cout << "Inserting Fails!" << endl;
        return;
    }
    out = fopen(back_json, "w");
    if (NULL == out) {
        cout << "Failed to open" << back_json << endl;
        cout << "Inserting Fails!" << endl;
        return;
    }

    cout << "Creating " << back_json << "..." << endl;
    cout << "Please Wait..." << endl;
    print(in, out, &CATALOG);
    fclose(in);
    Write.flush(out);
    fclose(out);
    cout << "Done!" << endl << endl;;

    cout << "Inserting Succeeds!" << endl << endl;
    return;
}

void brief(void) {
    cout << endl;
    break_line();
    cout << "   insert filename : Index a json file and transform it into serialized file." << endl;
    cout << "   check catalog   : Show the catalog." << endl;
    cout << "   find A = B      : Find the tuple containning the key." << endl;
    cout << "   ls path         : Show the directory." << endl;
    cout << "   help            : Show the man page." << endl;
    cout << "   command         : Show the brief command list." << endl;
    cout << "   exit            : End the program." << endl;
    break_line();
    cout << endl;
    return;
}

void check_catalog(catalog& CATALOG) {
    char com[20];
    scanf("%s", com);
    cout << endl;
    CATALOG.print();
    cout << endl;
    return;
}

void find(catalog& CATALOG) {
    cout << endl;
    CATALOG.Find();
    cout << endl;
    return;
}

void ls(my_string& _command) {
    char path[50];
    fgets(path, sizeof(path), stdin);
    _command = _command + path;
    cout << endl;
    system(_command.content());
    cout << endl;
    return;
}

void manual(void) {
    cout << endl;
    head();
    command();
    author();
    copyright();
    see_also();
    report_bugs();
    cout << endl;
    return;
}
