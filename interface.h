/**
 * @file interface.h
 * @author Окороков А.С. 22ПТ2
 * @brief Файл с описанием класса Interface
 * @version 1.0
 * @date 22.12.2023
 */
#pragma once

#include <string>

using namespace std;

/**
 * @brief Класс для разбора параметров командной строки.
 */
class Interface {
private:
    int port = 33333;                           ///< Порт, на котором будет работать сервер
    string file_name = "/ect/vcalc.conf";       ///< Имя файла с базой клиентов
    string file_error = "/var/log/vcalc.log";   ///< Имя файла с журналом ошибок
public:
    /**
     * @brief Получить параметры из командной строки.
     *
     * @param [in] argc Количество полей в командной строке.
     * @param [in] argv Массив строк с параметрами.
     * @return true Если при разборе не были обнаружены ошибки.
     * @return false Если при разборе были обнаружены ошибки.
     */
    bool get_options_from_comline(int argc, char* argv[]);
    /**
     * @brief Получить номер порта.
     *
     * @return int номер порта.
     */
    int get_port() {
        return port;
    }
    /**
     * @brief Получить имя файла с базой клиентов.
     *
     * @return string Имя файла.
     */
    string get_file_name() {
        return file_name;
    }
    /**
     * @brief Получить имя файла с журналом ошибок.
     *
     * @return string Имя файла.
     */
    string get_file_error() {
        return file_error;
    }
};
