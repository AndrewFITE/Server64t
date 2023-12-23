/**
 * @file interface.cpp
 * @author Окороков А.С. 22ПТ2
 * @version 1.0
 * @date 22.12.2023
 */
#include <unistd.h>
#include <iostream>

#include "interface.h"


bool Interface::get_options_from_comline(int argc, char* argv[]) {
    if(argc == 1) {
        cout << "\n   Arithmetic mean server"  << endl;
        cout << "*Сервер среднего арифметического*\n"  << endl;
        cout << "-h — руководство по запуску сервера\n" << endl;
        return false;
    }

    int opt;
    while ((opt = getopt(argc, argv, "hl:p:j:" ))!=-1 ) {
        switch(opt) {
        case 'h':
            cout << "\n      Arithmetic mean server"  << endl;
            cout << "\nВы открыли руководство по запуску сервера\nОсновные параметры и их предназначение указаны ниже:\n"  << endl;
            cout << "-l — параметр для последующего ввода имени файла с БД пользователей" << endl;
            cout << "-p — параметр для последующего ввода порта" << endl;
            cout << "-j — параметр для последующего ввода имени файла-журнала ошибок" << endl;
            cout << "\nДля запуска сервера вам необходимо ввести следующее:\n./main -l *БД пользователей* (logpas.txt) -p *порт* (33333) -j *файл-журнал ошибок* (error.txt)" << endl;
            cout << "\nПосле запуска команды сервер начнёт свою работу" << endl;
            cout << "Далее вам необходимо открыть новое окно терминала и запустить в нём обработку клиента с помощью следующей команды: *например* ./client64" << endl;
            cout << "\nДля остановки сервера закройте окно с обработкой клиентов и воспользуйтесь сочетанием клавиш 'Ctrl+C'\n" << endl;
            return false;
        case 'l':
            file_name = string(optarg);
            break;
        case 'p':
            port = stoi(string(optarg));
            break;
        case 'j':
            file_error = string(optarg);
            break;
        default:
            cout << "-h — руководство по запуску сервера\n";
            return false;
        }
    }

    return true;
}
