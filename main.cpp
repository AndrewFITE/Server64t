/**
 * @file main.cpp
 * @author Окороков А.С. 22ПТ2
 * @version 1.0
 * @date 22.12.2023
 */
#include "err_writer.h"
#include "communicator.h"
#include "interface.h"
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
    Interface interface;

    if (!interface.get_options_from_comline(argc, argv)) {
        return 1;
    }

    int port = interface.get_port();
    string file_name = interface.get_file_name();
    string file_error = interface.get_file_error();

    fstream file;
    file.exceptions(ifstream::badbit | ifstream::failbit);
    try {
        file.open(file_name);
    } catch(const exception & ex) {
        string error = "Ошибка занесена в журнал ошибок!";
        return 1;
    }

    ErrWriter writer(file_error);

    Communicator com(port, 5, writer, file_name);

    com.run();

    return 0;
}
