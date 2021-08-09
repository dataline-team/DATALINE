#include "Variant.h"



Variant::Variant(const Variant& variant)
{
    b_ = nullptr;
    i_ = nullptr;
    d_ = nullptr;
    s_ = nullptr;

    switch (variant.getDatatype())
    {
        case DataTypes::NULL_T:
            datatype = DataTypes::NULL_T;
            break;
        case DataTypes::BOOL:
            datatype = DataTypes::BOOL;
            setData(variant.toBool());
            break;
        case DataTypes::INT:
            datatype = DataTypes::INT;
            setData(variant.toInt());
            break;
        case DataTypes::DOUBLE:
            datatype = DataTypes::DOUBLE;
            setData(variant.toDouble());
            break;
        case DataTypes::STRING:
            datatype = DataTypes::STRING;
            setData(variant.toString());
            break;
    }
}


Variant &Variant::operator=(const Variant &variant) {
    if (this == &variant)
    {
        return *this;
    }

    switch (variant.getDatatype())
    {
        case DataTypes::NULL_T:
            datatype = DataTypes::NULL_T;
            break;
        case DataTypes::BOOL:
            datatype = DataTypes::BOOL;
            setData(variant.toBool());
            break;
        case DataTypes::INT:
            datatype = DataTypes::INT;
            setData(variant.toInt());
            break;
        case DataTypes::DOUBLE:
            datatype = DataTypes::DOUBLE;
            setData(variant.toDouble());
            break;
        case DataTypes::STRING:
            datatype = DataTypes::STRING;
            setData(variant.toString());
            break;
    }

    return *this;
}


Variant::~Variant()
{
    delete b_;
    delete i_;
    delete d_;
    delete s_;
}


bool Variant::toBool() const
{
    switch (datatype)
    {
        case DataTypes::NULL_T:
            return bool();
        case DataTypes::BOOL:
            return *b_;
        case DataTypes::INT:
            return static_cast<bool>(*i_);
        case DataTypes::DOUBLE:
            return static_cast<bool>(*d_);
        case DataTypes::STRING:
            return !s_->empty();
    }
}


int Variant::toInt() const
{
    switch (datatype)
    {
        case DataTypes::NULL_T:
            return int();
        case DataTypes::BOOL:
            return static_cast<int>(*b_);
        case DataTypes::INT:
            return *i_;
        case DataTypes::DOUBLE:
            return static_cast<int>(*d_);
        case DataTypes::STRING:
            try
            {
                return lexical_cast<int>(*s_);
            }
            catch (const bad_lexical_cast& blc)
            {
                return int();
            }
    }
}


double Variant::toDouble() const
{
    switch (datatype)
    {
        case DataTypes::NULL_T:
            return double();
        case DataTypes::BOOL:
            return static_cast<double>(*b_);
        case DataTypes::INT:
            return static_cast<double>(*i_);
        case DataTypes::DOUBLE:
            return *d_;
        case DataTypes::STRING:
            try
            {
                return lexical_cast<double>(*s_);
            }
            catch (const bad_lexical_cast& blc)
            {
                return double();
            }
    }
}


std::string Variant::toString() const
{
    switch (datatype)
    {
        case DataTypes::NULL_T:
            return {};
        case DataTypes::BOOL:
            return lexical_cast<std::string>(*b_);
        case DataTypes::INT:
            return lexical_cast<std::string>(*i_);
        case DataTypes::DOUBLE:
            return lexical_cast<std::string>(*d_);
        case DataTypes::STRING:
            return *s_;
    }
}


void Variant::setData(bool b)
{
    if (datatype == DataTypes::NULL_T)
    {
        b_ = new bool(b);
        datatype = DataTypes::STRING;
    }
    else if (datatype == DataTypes::BOOL)
    {
        delete b_;
        b_ = new bool(b);
    }
}


void Variant::setData(int i)
{
    if (datatype == DataTypes::NULL_T)
    {
        i_ = new int(i);
        datatype = DataTypes::INT;
    }
    else if (datatype == DataTypes::INT)
    {
        delete i_;
        i_ = new int(i);
    }
}


void Variant::setData(double d)
{
    if (datatype == DataTypes::NULL_T)
    {
        d_ = new double(d);
        datatype = DataTypes::DOUBLE;
    }
    else if (datatype == DataTypes::DOUBLE)
    {
        delete d_;
        d_ = new double(d);
    }
}


void Variant::setData(const std::string& s)
{
    if (datatype == DataTypes::NULL_T)
    {
        s_ = new std::string(s);
        datatype = DataTypes::STRING;
    }
    else if (datatype == DataTypes::STRING)
    {
        delete s_;
        s_ = new std::string(s);
    }
}


DataTypes Variant::getDatatype() const
{
    return datatype;
}
