/**
 * @file err_writer.cpp
 * @author Окороков А.С. 22ПТ2
 * @version 1.0
 * @date 22.12.2023
 */
#include <fstream>
#include <iostream>

#include "err_writer.h"

void ErrWriter::write_err(string &err) {
    ofstream file;
    file.open(err_file, ios::app);
    if(file.is_open()) {
        time_t seconds = time(NULL);
        tm* timeinfo = localtime(&seconds);
        file << err << ':' << asctime(timeinfo) << endl;
        cout << "Обнаруженная ошибка: " << err << endl;
    }
}
