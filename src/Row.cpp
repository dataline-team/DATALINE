#include "Row.h"


Row::Row()
{
    id_ = top_;
    top_++;
}

Row::Row(const std::vector<Cell>& cells) : cells_(cells)
{
    id_ = top_;
    top_++;
}


unsigned int Row::id() const
{
    return id_;
}


void Row::setId(unsigned int new_id)
{
    id_ = new_id;
}


unsigned int Row::top_ = 1;


void Row::addCell(const Cell& cell)
{
    cells_.push_back(cell);
}


void Row::removeCell(int pos)
{
    cells_.erase(cells_.begin() + pos);
}


template<class T>
void Row::setCell(const Cell& cell, int pos)
{
    if (cells_.at(pos).datatype() != cell.datatype())
    {
        throw std::invalid_argument("Error! Data types don't match.");
    }

    cells_.at(pos) = cell;
}


const Cell &Row::getCell(int pos) const
{
    return cells_.at(pos);
}


void Row::setRow(const std::vector<Cell>& cells)
{
    auto current_row_iter = cells_.begin();
    auto new_row_iter     = cells.begin();
    for (;current_row_iter != cells_.end() && new_row_iter != cells.end(); current_row_iter++, new_row_iter++)
    {
        if (current_row_iter->datatype() != new_row_iter->datatype())
        {
            throw std::range_error("Row data types don't match");
        }
    }

    cells_ = cells;
}


const std::vector<Cell> &Row::getRow() const
{
    return cells_;
}
