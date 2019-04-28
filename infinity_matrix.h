#pragma once
#include <map>
#include <iostream>
#include <memory>
#include <cstring>
#include <vector>

using map_key = std::tuple<int, int>;


template <typename T = int>
struct Buff
{
    int x = -1;
    int y = -1;
    T value = -1;
};

template <typename T, int U>
class Matrix
{

private:

    class Iterator
    {

    public:

        Buff<T>* _data_buf;
        Buff<>* _input_buf;
        std::map<map_key, T>* _map;

        Iterator(Buff<T>* data_buf_, Buff<>* input_buf_, std::map<map_key, T>* map_) :
        _data_buf(data_buf_),
        _input_buf(input_buf_),
        _map(map_) {}

        int& operator[](int y);
    };

    void do_init();

    void do_move(Matrix &&other) noexcept;

    void flush_data_buf(); // need to trigger movement from data_buf to matrix_data

    std::unique_ptr<Buff<>> _input_buf = nullptr;

    std::unique_ptr<Buff<T>> _data_buf = nullptr;

    std::unique_ptr<Iterator> _iterator = nullptr;

    std::unique_ptr<std::map<map_key, T>> _matrix_data = nullptr;

public:

    Matrix();

    ~Matrix() = default;

    Matrix(Matrix& other);

    Matrix& operator= (Matrix& other);

    Matrix(Matrix&& other) noexcept;

    Matrix& operator=(Matrix&& other) noexcept;

    size_t get_size() const
    {
        return _matrix_data->size();
    }

    // no const because of flush_data_buf()
    void get_elements(std::vector<std::tuple<int, int, T>>& elements);
    void print_elements();

    Iterator& operator[] (int x);
};


#include "infinity_matrix.cpp"