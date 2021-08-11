#ifndef ROW_H_
#define ROW_H_

#include <iostream>
#include <vector>
#include "Variant.h"


class Row
{
public:
    Row() {}
    explicit Row(const std::vector<Variant>& cells) : cells_(cells) {}

    const Variant getItem(int pos) const;
    const std::vector<Variant>& getRow() const;
    void setItem(const Variant& cell, int pos);
    void setRow(const std::vector<Variant>& row);

private:
    std::vector<Variant> cells_;
};


#endif // ROW_H_
