#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "ui.h"
using namespace std;

int main(int argc, char *argv[]) {
    catalog CATALOG;
    my_string _command;

    cout << endl;
    cout << "Type \"command\" or \"help\" for more information." << endl;
    brief();

    while (1) {
        cout << ">>> ";
        char com[20];
        scanf("%s", com);
        _command = com;
        if (_command == "command")  {
            brief();
        } else if (_command == "check") {
            check_catalog(CATALOG);
        } else if (_command ==  "insert") {
            insert(CATALOG);
        } else if (_command == "find") {
            find(CATALOG);
        } else if (_command == "ls") {
            ls(_command);
        } else if (_command == "help") {
            manual();
        } else if (_command == "exit") {
            cout << endl;
            break;
        } else {
            cout << endl << "Invalid Command! Try again." << endl << endl;
        }
    }
    return 0;
}






