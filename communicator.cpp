/**
 * @file communicator.cpp
 * @author Окороков А.С. 22ПТ2
 * @version 1.0
 * @date 22.12.2023
 */
#include <iostream>
#include <fstream>
#include <limits>

//#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>

#include <unistd.h>

#include "communicator.h"

Communicator::Communicator(int port, int queue_length, ErrWriter& err_wr, string clients):
    sock(socket(AF_INET, SOCK_STREAM, 0)),
    queue_length_(queue_length),
    self_addr_(new sockaddr_in),
    remote_addr_(new sockaddr_in),
    writer(err_wr),
    client_file(clients) {

    if( sock == -1 ) {
        cout << "Ошибка сокета!" << endl;
        exit(1);
    }

    const int enable = 1;

    if( setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof enable) == -1 ) {
        cout << "Установка повторного использования не удалась!" << endl;
    }

    self_addr_->sin_family = AF_INET;
    self_addr_->sin_port = htons(port);
    self_addr_->sin_addr.s_addr = htonl(INADDR_ANY);

    if( bind(sock, reinterpret_cast< const sockaddr* >(self_addr_.get()), sizeof(sockaddr_in)) == -1 ) {
        cout << "Ошибка сокета (критическая)" << endl;
        exit(1);
    }
}

void Communicator::run() {
    if( listen(sock, queue_length_) == -1 ) {
        cout << "Ошибка сокета (критическая)" << endl;
        exit(1);
    }
    cout << "Сервер запущен!\nОжидается подключение клиента...\n" << endl;

    socklen_t addr_len = sizeof(sockaddr_in);

    while( true ) {
        client_socket = accept(sock, reinterpret_cast< sockaddr* >(remote_addr_.get()), &addr_len);
        if( client_socket == -1 ) {
            cout << "Ошибка подключения клиента (критическая)" << endl;
            continue;
        }

        struct timeval timeout {
            30, 0
        };
        if( setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout) == -1 ) {
            continue;
        }

        if (autorized() != 1)
            math();
        cout << "Операция, заданная серверу, выполнена!\n" <<endl;
        close(client_socket);
    }
}

int Communicator::autorized() {

    cout << "Запуск подключения клиента..." << endl;

    string ok = "OK";
    string salt = "0011CF334455DA66";
    string err = "ERR";
    string error;
    char msg[255];

    int msg_size;
    msg_size = recv(client_socket, &msg, sizeof(msg), 0);
    string message(msg, msg_size);
    string login, hashq;
    fstream file;
    file.open(client_file);
    getline (file, login, ':');
    getline (file, hashq);
    file.close();

    if (message != login) {
        msgsend(err);
        error = "Ошибка логина (не критическая)";
        writer.write_err(error);
        close(client_socket);
        return 1;
    } else {
        msgsend(salt);
        msg_size = recv(client_socket, msg, sizeof(msg), 0);
        string HASH(msg, msg_size);
        string sah = salt + hashq;
        string digest;
        digest = MD(sah);

        if (digest != HASH) {
            cout << digest << endl;
            cout << HASH << endl;
            msgsend(err);
            error = "Ошибка пароля (не критическая)";
            writer.write_err(error);
            close(client_socket);
            return 1;
        } else {
            msgsend(ok);
        }
    }
    return 0;
}

int Communicator::math() {
    string error;
    uint32_t quantity;
    uint32_t number;
    recv(client_socket, &quantity, sizeof(quantity), 0);

    for(uint32_t j=0; j<quantity; j++) {
        recv(client_socket, &number, sizeof(number), 0);

        std::unique_ptr< uint64_t[] > v(new uint64_t[number]);
        int v_size;
        if( (v_size = recv(client_socket, (void*)v.get(), sizeof(uint64_t)*number, 0)) == -1 ) {
            error = "Не удалось получить вектор (критическая)";
            writer.write_err(error);
            return 1;
        }
        if( sizeof(uint64_t)*number != (uint32_t)v_size ) {
            error = "Не удалось получить вектор (критическая)";
            writer.write_err(error);
            return 1;
        }

        std::vector<uint64_t> vect(number);
        for (uint32_t i=0; i<number; ++i) {
            vect.at(i) = v[i];
        }

        uint64_t average = calculate(vect);
        send(client_socket, &average, sizeof(average), 0);
    }
    return 0;
}

uint64_t Communicator::calculate(const vector<uint64_t>& vect) {
    int number = vect.size();
    uint64_t sum = 0;
    bool flag = false;
    for(int i=0; i<number; i++) {
        if (sum > (numeric_limits < uint64_t > ::max() - vect.at(i))) {
            sum = numeric_limits < uint64_t > ::max();
            flag = true;
            break;
        }
        sum = sum+vect.at(i);
    }

    uint64_t average;
    if( flag or number == 0)
        average = sum;
    else
        average = sum/number;

    return average;
}

void Communicator::msgsend(string mess) {
    char *buffer = new char[4096];
    strcpy(buffer, mess.c_str());
    send(client_socket, buffer, mess.length(), 0);
}

string Communicator::MD(string sah) {
    using namespace CryptoPP;
    Weak::MD5 hash;
    string digest;
    StringSource(sah, true,  new HashFilter(hash, new HexEncoder(new StringSink(digest))));
    return digest;
}
