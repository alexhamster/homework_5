
#include "infinity_matrix.h"

template <typename T, T U>
typename Matrix<T, U>::Iterator&  Matrix<T, U>::operator[] (int x)
{
    _requested_cell.get()->x = x;
    return *_iterator;
}

template <typename T, T U>
T& Matrix<T, U>::Iterator::operator[](int y)
{
    _parent->_requested_cell->y = y;
    return _parent->get_cell_value();
}

template <typename T, T U>
void Matrix<T, U>::do_member_init()
{
    try {
        _uncommitted_cell = std::make_unique<MatrixCell<T,U>>();
        _requested_cell = std::make_unique<MatrixCell<T,U>>();
        _matrix_data = std::make_unique<std::map<map_key, T>>();
        _iterator = std::make_unique<Iterator>(this);
    }
    catch(std::bad_alloc& e)
    {
        std::cout << __FUNCTION__ << e.what() << std::endl;
    }
}

template <typename T, T U>
Matrix<T, U>::Matrix()
{
    do_member_init();
    _uncommitted_cell->value = U;
    _uncommitted_cell->x = U;
    _uncommitted_cell->y = U;
}
template <typename T, T U>
Matrix<T, U>::Matrix(Matrix<T, U>& other)
{
    do_member_init();
    std::memcpy(_uncommitted_cell.get(), other._uncommitted_cell.get(), sizeof(MatrixCell<T,U>));
    std::memcpy(_requested_cell.get(), other._requested_cell.get(), sizeof(MatrixCell<T,U>));
    _matrix_data->insert(other._matrix_data->begin(), other._matrix_data->end());
}
template <typename T, T U>
Matrix<T, U> &Matrix<T, U>::operator=(Matrix<T, U> &other)
{
    do_member_init();
    std::memcpy(_uncommitted_cell.get(), other._uncommitted_cell.get(), sizeof(MatrixCell<T,U>));
    std::memcpy(_requested_cell.get(), other._requested_cell.get(), sizeof(MatrixCell<T,U>));
    _matrix_data->insert(other._matrix_data->begin(), other._matrix_data->end());
    return *this;
}

template <typename T, T U>
void Matrix<T, U>::do_member_move(Matrix<T, U> &&other) noexcept
{
    _matrix_data = std::move(other._matrix_data);
    _uncommitted_cell = std::move(other._uncommitted_cell);
    _requested_cell = std::move(other._requested_cell);
    _iterator = std::make_unique<Iterator>(this);
    other.~Matrix();
}

template <typename T, T U>
Matrix<T, U>::Matrix(Matrix<T, U>&& other) noexcept
{
    do_member_move(std::forward<Matrix<T, U>>(other));
}

template <typename T, T U>
Matrix<T, U>& Matrix<T, U>::operator=(Matrix<T, U>&& other) noexcept
{
    do_member_move(std::forward<Matrix<T, U>>(other));
    return *this;
}

template <typename T, T U>
void Matrix<T, U>::get_elements(std::vector<std::tuple<int, int, T>>& elements)
{
    sync_uncommitted_cell();
    for(auto i: *_matrix_data)
    {
        elements.emplace_back(std::make_tuple(
                std::get<0>(i.first),
                std::get<1>(i.first),
                i.second));
    }
}

template <typename T, T U>
void Matrix<T, U>::print_elements()
{
    std::vector<std::tuple<int, int, T>> elements;
    elements.reserve(get_size());
    get_elements(elements);

    for(auto i: elements)
        std::cout << "X: " << std::get<0>(i) << " Y: " << std::get<1>(i) << " value: " << std::get<2>(i) << std::endl;
    std::cout << "Total number: " << get_size() << std::endl;
}

template<typename T, T U>
T& Matrix<T, U>::get_cell_value()
{
    sync_uncommitted_cell();
    rewrite_uncommitted_cell();
    return _uncommitted_cell->value;
}

template<typename T, T U>
void Matrix<T, U>::sync_uncommitted_cell()
{
    if(_uncommitted_cell->is_default())
    {
        auto default_cell = _matrix_data->find(
                std::make_tuple(_uncommitted_cell->x,_uncommitted_cell->y));

        if(default_cell != _matrix_data->end())
            _matrix_data->erase(default_cell);
    }
    else
    {
        _matrix_data->operator[](std::make_tuple(
                _uncommitted_cell->x,
                _uncommitted_cell->y)) = _uncommitted_cell->value;
    }
}

template<typename T, T U>
void Matrix<T, U>::rewrite_uncommitted_cell()
{
    auto requested_cell = _matrix_data->find(
            std::make_tuple(_requested_cell->x,_requested_cell->y));

    if(requested_cell == _matrix_data->end())
        _uncommitted_cell->value = U;
    else
        _uncommitted_cell->value = requested_cell->second;

    _uncommitted_cell->x = _requested_cell->x;
    _uncommitted_cell->y = _requested_cell->y;
}