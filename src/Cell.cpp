#include "Cell.h"



Cell::Cell(datatype_t dt) : datatype_(dt)
{
    // pass
}


template<class T>
Cell::Cell(const T& data) : data_(data), datatype_(boost::typeindex::type_id<T>())
{
    // pass
}


Cell::~Cell() = default;


const data_t &Cell::getData() const
{
    if (!data_.which())
    {
        throw std::invalid_argument("the cell is empty");
    }

    return data_;
}


datatype_t Cell::datatype() const
{
    return datatype_;
}


bool Cell::empty() const
{
    return !data_.which();
}
