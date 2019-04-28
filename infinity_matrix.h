#pragma once

#include "infinity_matrix.h"
#include <map>
#include <iostream>
#include <memory>

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

        int& operator[](int y)
        {
            _input_buf[Buf::y] = y;

            if(_data_buf[Buf::value] != MATRIX_DEFAULT_VALUE)
            {
                _map->operator[](std::make_tuple(
                        _data_buf[Buf::x],
                        _data_buf[Buf::y])) = _data_buf[Buf::value];
            }
            else
            {
                auto f_result = _map->find(std::make_tuple(
                        _data_buf[Buf::x],_data_buf[Buf::y]));
                if(f_result != _map->end())
                    _map->erase(f_result);
            }

            auto find_result = _map->find(std::make_tuple(
                    _input_buf[Buf::x],_input_buf[Buf::y]));

            if(find_result == _map->end())
                _data_buf[Buf::value] = MATRIX_DEFAULT_VALUE;
            else
                _data_buf[Buf::value] = find_result->second;

            _data_buf[Buf::x] = _input_buf[Buf::x];
            _data_buf[Buf::y] = _input_buf[Buf::y];

            return _data_buf[Buf::value];
        }
    };

    std::unique_ptr<int[]> _input_buf;

    std::unique_ptr<int[]> _matrix_buf;

public:


    Matrix() // todo add constructors &&
    {
        _matrix_buf = std::make_unique<int[]>(3); //todo change to std::array

        _matrix_buf[0] = -1;
        _matrix_buf[1] = -1;
        _matrix_buf[2] = -1;

        _input_buf = std::make_unique<int[]>(2);

        _matrix_data = std::make_unique<std::map<map_key, int>>();

        _iterator  = std::make_unique<Iterator>(_matrix_buf.get(), _input_buf.get(), _matrix_data.get());

    }

    size_t get_size()
    {
        return _matrix_data->size();
    }

    Iterator& operator[] (int x)
    {
        _input_buf[Buf::x] = x;
        return *_iterator;
    }

};
