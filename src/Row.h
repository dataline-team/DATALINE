#ifndef ROW_H_
#define ROW_H_

#include "Cell.h"
#include <vector>


class Row
{
public:
    Row();
    explicit Row(const std::vector<Cell>& cells);

    [[nodiscard]] unsigned int id() const;
    void setId(unsigned int new_id);

    void addCell(const Cell& cell);
    void removeCell(int pos);
    template<class T>
    void setCell(const Cell& cell, int pos);
    [[nodiscard]] const Cell& getCell(int pos) const;

    void setRow(const std::vector<Cell>& cells);
    [[nodiscard]] const std::vector<Cell>& getRow() const;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);

private:
    unsigned id_;
    std::vector<Cell> cells_;
    static unsigned int top_;
};


#endif // ROW_H_
