//
// Created by alex on 26.04.2019.
//

#include "infinity_matrix.h"

Matrix::Iterator& Matrix::operator[] (int x)
{
    _input_buf[Buf::x] = x;
    return *_iterator;
}

int& Matrix::Iterator::operator[](int y)
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

void Matrix::do_init()
{
    _data_buf = std::make_unique<int[]>(3);
    _input_buf = std::make_unique<int[]>(2);
    _matrix_data = std::make_unique<std::map<map_key, int>>();
    _iterator  = std::make_unique<Iterator>(_data_buf.get(), _input_buf.get(), _matrix_data.get());
}

Matrix::Matrix()
{
    do_init();
    _data_buf[Buf::value] = MATRIX_DEFAULT_VALUE;
    _data_buf[Buf::x] = MATRIX_DEFAULT_VALUE;
    _data_buf[Buf::y] = MATRIX_DEFAULT_VALUE;
}

Matrix::Matrix(Matrix& other)
{
    do_init();
    std::memcpy(_data_buf.get(), other._data_buf.get(), sizeof(int) * 3);
    std::memcpy(_input_buf.get(), other._input_buf.get(), sizeof(int) * 2);
    _matrix_data->insert(other._matrix_data->begin(), other._matrix_data->end());
}

Matrix &Matrix::operator=(Matrix &other)
{
    do_init();
    std::memcpy(_data_buf.get(), other._data_buf.get(), sizeof(int) * 3);
    std::memcpy(_input_buf.get(), other._input_buf.get(), sizeof(int) * 2);
    _matrix_data->insert(other._matrix_data->begin(), other._matrix_data->end());
    return *this;
}

void Matrix::flush_data_buf()
{
    operator[](0).operator[](0);
}

void Matrix::do_move(Matrix &&other) noexcept
{
    std::swap(_matrix_data, other._matrix_data);
    std::swap(_data_buf, other._data_buf);
    std::swap(_input_buf, other._input_buf);
    std::swap(_iterator, other._iterator);
    other.~Matrix();
}

Matrix::Matrix(Matrix&& other) noexcept
{
    do_move(std::forward<Matrix>(other));
}

Matrix& Matrix::operator=(Matrix&& other) noexcept
{
    do_move(std::forward<Matrix>(other));
    return *this;
}

void Matrix::get_elements(std::vector<std::tuple<int, int, int>>& elements)
{
    flush_data_buf();
    for(auto i: *_matrix_data)
    {
        elements.emplace_back(std::make_tuple(
                std::get<0>(i.first),
                std::get<1>(i.first),
                i.second));
    }
}

void Matrix::print_elements()
{
    std::vector<std::tuple<int, int, int>> elements;
    elements.reserve(get_size());
    get_elements(elements);

    for(auto i: elements)
        std::cout << "X: " << std::get<0>(i) << " Y: " << std::get<1>(i) << " value: " << std::get<2>(i) << std::endl;
    std::cout << "Total number: " << get_size() << std::endl;
}

