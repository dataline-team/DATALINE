#ifndef VARIANT_H_
#define VARIANT_H_

#include <iostream>
#include "boost/lexical_cast.hpp"


using boost::lexical_cast;
using boost::bad_lexical_cast;


enum class DataTypes
{
    NULL_T, BOOL, INT, FLOAT, STRING
};


class Variant
{
public:
    Variant() :                 b_(bool()), i_(int()), f_(float()), datatype(DataTypes::NULL_T) {}
    explicit Variant(bool b) :  b_(b),      i_(int()), f_(float()), datatype(DataTypes::BOOL)   {}
    explicit Variant(int i) :   b_(bool()), i_(i),     f_(float()), datatype(DataTypes::INT)    {}
    explicit Variant(float f) : b_(bool()), i_(int()), f_(f),       datatype(DataTypes::FLOAT)  {}
    explicit Variant(const std::string& s) : b_(bool()), i_(int()), f_(float()), s_(s), datatype(DataTypes::STRING) {}

    bool toBool();
    int toInt();
    float toFloat();
    std::string toString();

    DataTypes get_datatype() const;

private:
    DataTypes datatype;

    bool b_;
    int i_;
    float f_;
    std::string s_;
};


#endif  // VARIANT_H_