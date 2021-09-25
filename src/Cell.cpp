#include "Cell.h"



Cell::Cell() : datatype_(typeid(Blank))
{
    // pass
}


Cell::Cell(datatype_t dt) : datatype_(dt)
{
    // pass
}


template<class T>
Cell::Cell(const T& data) : data_(data), datatype_(typeid(T))
{
    // pass
}


Cell::~Cell() = default;


const data_t &Cell::getData() const
{
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

template<class Archive>
void Cell::save(Archive &ar, const unsigned int version) {
    ar << data_;
    ar << SerializeTypeIndexHandler::name_for_type(datatype_);
}

template<class Archive>
void Cell::load(Archive &ar, const unsigned int version) {
    ar >> data_;

    std::string s;
    ar >> s;
    datatype_ = SerializeTypeIndexHandler::type_for_name(s);
}
