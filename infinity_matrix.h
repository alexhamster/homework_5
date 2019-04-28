#pragma once

#include "infinity_matrix.h"
#include <map>
#include <iostream>
#include <memory>
#include <cstring>
#include <vector>


#define MATRIX_DEFAULT_VALUE -1

using map_key = std::tuple<int, int>;

enum Buf
{
    x, y, value
};

struct Matrix
{

private:

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

    void do_move(Matrix &&other) noexcept;

    void flush_data_buf();

    std::unique_ptr<int[]> _input_buf = nullptr;

    std::unique_ptr<int[]> _data_buf = nullptr;

    std::unique_ptr<Iterator> _iterator = nullptr;

    std::unique_ptr<std::map<map_key, int>> _matrix_data = nullptr;

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
    void get_elements(std::vector<std::tuple<int, int, int>>& elements);
    void print_elements();

    Iterator& operator[] (int x);
};

