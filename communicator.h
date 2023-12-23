/**
 * @file communicator.h
 * @author Окороков А.С. 22ПТ2
 * @brief Файл с описанием класса Communicator
 * @version 1.0
 * @date 22.12.2023
 */
#pragma once

#include <string>
#include <memory>
#include <vector>

#include <netinet/in.h>

#include "err_writer.h"

using namespace std;

/**
 * @brief Класс для управления сервером.
 */
class Communicator {
#ifdef MY_UNIT_TEST
public:
    Communicator() {}; // Для тестирования
#else
private:
#endif
    int sock;                                  ///< Сокет сервера
    int queue_length_;                         ///< Длина очереди клиентов
    unique_ptr< sockaddr_in > self_addr_;      ///< Данные сервера
    unique_ptr< sockaddr_in > remote_addr_;    ///< Данные клиента
    ErrWriter writer;       ///< Объект класса ErrWriter
    string client_file;     ///< Имя файла с базой клиентов

    int client_socket;      ///< Сокет, через который происходит взаимодействие с клиентом.

    /**
     * @brief Аутентифицировать клиента.
     *
     * @return int 0 в случае успеха и 1 в случае неудачи.
     */
    int autorized();
    /**
     * @brief Принять векторы и отправить результаты.
     *
     * @return int 0 в случае успеха и 1 в случае неудачи.
     */
    int math();
    /**
     * @brief Вычислить среднее арифметическое для вектора vect.
     * @details Вычисляет среднее арифметическое для получаемого вектора.
     * Если вектор пустой или в процессе вычислений происходит переполнение,
     * то возвращается 0 или максимальное число для uint64_t соответственно.
     *
     * @param [in] vect Полученный от клиента вектор.
     * @return uint64_t Среднее арифметическое.
     */
    uint64_t calculate(const vector<uint64_t>& vect);
    /**
     * @brief Хэшировать строку.
     *
     * @param [in] sah Строка для хэширования.
     * @return string Полученный хэш.
     */
    string MD(string sah);
    /**
     * @brief Отправить строку клиенту.
     *
     * @param [in] mess Отправляемая строка.
     */
    void msgsend(string mess);
public:
    /**
     * @brief Конструктор для функций сетевого взаимодействия сервера с клиентом.
     *
     * @param [in] port             ///< Номер порта, на котором будет работать сервер.
     * @param [in] queue_length     ///< Длина очереди клиентов на подключение.
     * @param [in] errors           ///< Объект класса ErrWriter.
     * @param [in] clients          ///< Имя файла с базой клиентов.
     */
    Communicator(int port, int queue_length, ErrWriter& errors, string clients);

    /**
     * @brief Принимать запросы от клиентов.
     * @details Содержит внутри себя бесконечный цикл
     * подключения и разрыва соединения с клиентами.
     */
    void run();
};
