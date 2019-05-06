#pragma once
#include <map>
#include <iostream>
#include <memory>
#include <cstring>
#include <vector>

using map_key = std::tuple<int, int>;

template <typename T, T U>
struct MatrixCell
{
    int x = -1;
    int y = -1;
    T value = U;

    bool is_default()
    {
        return value == U;
    }
};

template <typename T, T U>
class Matrix
{

private:

    struct Iterator
    {
        Matrix<T,U>* _parent = nullptr;
        Iterator(Matrix<T,U>* parent_) : _parent(parent_) {}
        T& operator[](int y);
    };

    void do_member_init();
    void do_deep_copy(Matrix &&other) noexcept;

    std::unique_ptr<MatrixCell<T, U>> _requested_cell = nullptr;
    std::unique_ptr<MatrixCell<T, U>> _uncommitted_cell = nullptr;
    std::unique_ptr<Iterator> _iterator = nullptr;
    std::unique_ptr<std::map<map_key, T>> _matrix_data = nullptr;

    T& get_cell_value();
    void sync_uncommitted_cell();
    void rewrite_uncommitted_cell();

public:

    Matrix();
    ~Matrix() = default;
    Matrix(Matrix& other);
    Matrix& operator= (Matrix& other);
    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(Matrix&& other) noexcept;

    size_t get_size()
    {
        sync_uncommitted_cell();
        return _matrix_data->size();
    }

    // no const because of sync_uncommitted_cell()
    void get_elements(std::vector<std::tuple<int, int, T>>& elements);
    void print_elements();

    Iterator& operator[] (int x);
};

#include "infinity_matrix.cpp"