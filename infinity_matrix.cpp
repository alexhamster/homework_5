
template <typename T, int U>
typename Matrix<T, U>::Iterator&  Matrix<T, U>::operator[] (int x)
{
    _input_buf.get()->x = x;
    return *_iterator;
}

template <typename T, int U>
int& Matrix<T, U>::Iterator::operator[](int y)
{
    _input_buf->y = y;

    if(_data_buf->value != U)
    {
        _map->operator[](std::make_tuple(
                _data_buf->x,
                _data_buf->y)) = _data_buf->value;
    }
    else
    {
        auto f_result = _map->find(std::make_tuple(
                _data_buf->x,_data_buf->y));
        if(f_result != _map->end())
            _map->erase(f_result);
    }

    auto find_result = _map->find(std::make_tuple(
            _input_buf->x,_input_buf->y));

    if(find_result == _map->end())
        _data_buf->value = U;
    else
        _data_buf->value = find_result->second;

    _data_buf->x = _input_buf->x;
    _data_buf->y = _input_buf->y;
    return _data_buf->value;
}

template <typename T, int U>
void Matrix<T, U>::do_init()
{
    try {
        _data_buf = std::make_unique<Buff<T>>();
        _input_buf = std::make_unique<Buff<T>>();
        _matrix_data = std::make_shared<std::map<map_key, T>>();
        _iterator = std::make_unique<Iterator>(_data_buf, _input_buf, _matrix_data);
    }
    catch(std::bad_alloc& e)
    {
        std::cout << __FUNCTION__ << e.what() << std::endl;
    }
}

template <typename T, int U>
Matrix<T, U>::Matrix()
{
    do_init();
    _data_buf->value = U;
    _data_buf->x = U;
    _data_buf->y = U;
}
template <typename T, int U>
Matrix<T, U>::Matrix(Matrix<T, U>& other)
{
    do_init();
    std::memcpy(_data_buf.get(), other._data_buf.get(), sizeof(Buff<T>));
    std::memcpy(_input_buf.get(), other._input_buf.get(), sizeof(Buff<T>));
    _matrix_data->insert(other._matrix_data->begin(), other._matrix_data->end());
}
template <typename T, int U>
Matrix<T, U> &Matrix<T, U>::operator=(Matrix<T, U> &other)
{
    do_init();
    std::memcpy(_data_buf.get(), other._data_buf.get(), sizeof(Buff<T>));
    std::memcpy(_input_buf.get(), other._input_buf.get(), sizeof(Buff<T>));
    _matrix_data->insert(other._matrix_data->begin(), other._matrix_data->end());
    return *this;
}

template <typename T, int U>
void Matrix<T, U>::flush_data_buf() // need to trigger movement from data_buf to matrix_data
{
    operator[](0).operator[](0);
}
template <typename T, int U>
void Matrix<T, U>::do_move(Matrix<T, U> &&other) noexcept
{
    _matrix_data.swap(other._matrix_data);
    _data_buf.swap(other._data_buf);
    _input_buf.swap(other._input_buf);
    _iterator.swap(other._iterator);
    other.~Matrix();
}

template <typename T, int U>
Matrix<T, U>::Matrix(Matrix<T, U>&& other) noexcept
{
    do_move(std::forward<Matrix>(other));
}

template <typename T, int U>
Matrix<T, U>& Matrix<T, U>::operator=(Matrix&& other) noexcept
{
    do_move(std::forward<Matrix<T, U>>(other));
    return *this;
}

template <typename T, int U>
void Matrix<T, U>::get_elements(std::vector<std::tuple<int, int, T>>& elements)
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

template <typename T, int U>
void Matrix<T, U>::print_elements()
{
    std::vector<std::tuple<int, int, T>> elements;
    elements.reserve(get_size());
    get_elements(elements);

    for(auto i: elements)
        std::cout << "X: " << std::get<0>(i) << " Y: " << std::get<1>(i) << " value: " << std::get<2>(i) << std::endl;
    std::cout << "Total number: " << get_size() << std::endl;
}