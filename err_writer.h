/**
 * @file err_writer.h
 * @author Окороков А.С. 22ПТ2
 * @brief Файл с описанием класса ErrWriter
 * @version 1.0
 * @date 22.12.2023
 */
#pragma once

#include <string>

using namespace std;

/**
 * @brief Класс для записи ошибок в журнал.
 */
class ErrWriter {
private:
    string err_file;    ///< Имя файла с журналом ошибок.
public:
    /**
     * @brief Конструктор без параметров для функции записи в журнал.
     */
    ErrWriter():err_file() {};
    /**
     * @brief Конструктор с именем файла для функции записи в журнал.
     *
     * @param [in] errors Имя файла с журналом ошибок.
     */
    ErrWriter(const string& errors):err_file(errors) {};
    /**
     * @brief Конструктор копирования.
     *
     * @param [in] other Другой объект класса ErrWriter.
     */
    ErrWriter(const ErrWriter& other):err_file(other.err_file) {};
    /**
     * @brief Записать ошибку в журнал.
     * @details Записывает в журнал ошибку и время, когда произошла ошибка.
     * @param [in] err Строка с сообщением об ошибке.
     */
    void write_err(string& err);
};
