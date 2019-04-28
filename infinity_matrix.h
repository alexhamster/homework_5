#pragma once

#include "infinity_matrix.h"
#include <map>
#include <iostream>
#include <memory>
#include <cstring>


#define MATRIX_DEFAULT_VALUE -1

using map_key = std::tuple<int, int>;

enum Buf
{
    x, y, value
};

struct Matrix
{

private:

    class Iterator;

    std::unique_ptr<Iterator> _iterator;

    std::unique_ptr<std::map<map_key, int>> _matrix_data;

    class Iterator
    {

    public:

        int* _data_buf;
        int* _input_buf;
        std::map<map_key, int>* _map;

        Iterator(int* data_buf_, int* input_buf_, std::map<map_key, int>* map_) :
        _data_buf(data_buf_),
        _input_buf(input_buf_),
        _map(map_) {}

        int& operator[](int y);

    };

    void do_init();

    std::unique_ptr<int[]> _input_buf;

    std::unique_ptr<int[]> _data_buf;

public:

    Matrix();

    Matrix(Matrix& other);

    Matrix& operator= (Matrix& other);

    Matrix(Matrix&& other) noexcept;

    Matrix& operator=(Matrix&& other) noexcept;

    void do_move(Matrix &&other) noexcept;


    size_t get_size() const
    {
        return _matrix_data->size();
    }

    Iterator& operator[] (int x);
};

