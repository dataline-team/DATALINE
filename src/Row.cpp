#include "Row.h"


const Variant Row::getItem(int pos) const
{
    return cells_.at(pos);
}


const std::vector<Variant>& Row::getRow() const
{
    return cells_;
}


void Row::setItem(const Variant& variant, int pos)
{
    if (cells_.at(pos).getDatatype() == variant.getDatatype())
    {
        cells_.at(pos) = variant;
    }
}


void Row::setRow(const std::vector<Variant>& row)
{
    cells_ = row;
}
