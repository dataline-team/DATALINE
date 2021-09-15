#include "Table.h"


Table::Table() = default;


Table::Table(const std::string& table_name) : table_name_(table_name)
{
    // pass
}

Table::Table(const std::string& table_name, const config_t& table_config)
        : table_name_(table_name), table_config_(table_config)
{
    // pass
}

Table::Table(const std::string& table_name, const config_t& table_config, const table_t& sortedTables)
        : table_name_(table_name), table_config_(table_config), table_(sortedTables)
{
    // pass
}


void Table::setTName(const std::string &new_table_name)
{
    table_name_ = new_table_name;
}


const std::string &Table::getTName() const
{
    return table_name_;
}


void Table::setTConfig(const config_t& new_table_config)
{
    if (!table_config_.empty())
    {
        throw std::invalid_argument("Error! Config has been already set.");
    }

    table_config_ = new_table_config;
}


const config_t& Table::getTConfig() const
{
    return table_config_;
}


bool Table::empty() const
{
    return table_.empty();
}


void Table::addRow(const Row& row)
{
    auto cfg_iter = table_config_.cbegin();
    auto new_row_iter = row.getRow().cbegin();
    for (;cfg_iter != table_config_.cend() && new_row_iter != row.getRow().cend(); cfg_iter++, new_row_iter++)
    {
        if (cfg_iter->second != new_row_iter->datatype())
        {
            throw std::range_error("Row data types don't match");
        }
    }

    table_.insert({row.id(), row});
}

template<typename T>
std::vector<Row> Table::select(Operator op, const std::vector<std::string>& cols_to_select, const std::string& col_to_sort_by) const
{
    if (op != Operator::ALL)
    {
        throw std::invalid_argument("Error! Select for option `ALL`.");
    }

    std::vector<Row> result_table;
    std::vector<int> indexes;
    auto select_iter = cols_to_select.cbegin();
    int i_select = 0, i_sort = 0;
    for (const auto& cfg_iter : table_config_)
    {
        if (*select_iter == cfg_iter.first)
        {
            indexes.push_back(i_select);
            select_iter++;
        }

        if (!col_to_sort_by.empty() && (col_to_sort_by == cfg_iter.first))
        {
            i_sort = i_select;
        }
        i_select++;
    }

    for (const auto& row: table_)
    {
        Row temp_row;
        for (int i: indexes)
        {
            temp_row.addCell(row.second.getCell(i));
        }
        temp_row.setId(row.first);
        result_table.push_back(temp_row);
    }

    if (!col_to_sort_by.empty())
    {
        std::sort(result_table.begin(), result_table.end(), [&](const Row& row1, const Row& row2)
        {
            return (boost::get<T>(row1.getCell(i_sort).getData()) < boost::get<T>(row2.getCell(i_sort).getData()));
        });
    }

    return result_table;
}


template<typename T>
std::vector<Row> Table::select(Operator op, const std::string& col_name, const T& value,
                               const std::vector<std::string>& cols_to_select, const std::string& col_to_sort_by) const
{
    if (op != Operator::EQUALS_TO && op != Operator::NOT_EQUALS_TO && op != Operator::BIGGER_THAN_VALUE && op != Operator::LESS_THAN_VALUE)
    {
        throw std::invalid_argument("Error! Select for options `EQUALS_TO`, `NOT_EQUALS_TO`, `BIGGER_THAN_VALUE` or `LESS_THAN_VALUE`.");
    }

    std::vector<Row> result_table;
    std::vector<int> indexes;
    auto select_iter = cols_to_select.cbegin();
    int i_select = 0, i_column = 0, i_sort = 0;
    for (const auto& cfg_iter : table_config_)
    {
        if (*select_iter == cfg_iter.first)
        {
            indexes.push_back(i_select);
            select_iter++;
        }

        if (col_name == cfg_iter.first)
        {
            i_column = i_select;
        }

        if (!col_to_sort_by.empty() && (col_to_sort_by == cfg_iter.first))
        {
            i_sort = i_select;
        }

        i_select++;
    }


    for (const auto& row: table_)
    {
        auto dataToCheck = boost::get<T>(row.second.getRow().at(i_column).getData());
        if (dataToCheck == boost::get<T>(data_t(value)) && op == Operator::EQUALS_TO)
        {
            result_table.push_back(handleRow(row, indexes));
        }
        else if (dataToCheck != boost::get<T>(data_t(value)) && op == Operator::NOT_EQUALS_TO)
        {
            result_table.push_back(handleRow(row, indexes));
        }
        else if (dataToCheck > boost::get<T>(data_t(value)) && op == Operator::BIGGER_THAN_VALUE)
        {
            result_table.push_back(handleRow(row, indexes));
        }
        else if (dataToCheck < boost::get<T>(data_t(value)) && op == Operator::LESS_THAN_VALUE)
        {
            result_table.push_back(handleRow(row, indexes));
        }
    }


    if (!col_to_sort_by.empty())
    {
        std::sort(result_table.begin(), result_table.end(), [&](const Row& row1, const Row& row2)
        {
            return (boost::get<T>(row1.getCell(i_sort).getData()) < boost::get<T>(row2.getCell(i_sort).getData()));
        });
    }

    return result_table;
}


template<typename T>
std::vector<Row> Table::select(Operator op, const std::string& col_name, const T& value1, const T& value2,
                               const std::vector<std::string>& cols_to_select, std::string col_to_sort_by) const
{
    if (op != Operator::BETWEEN_VALUES && op != Operator::OUTSIDE_VALUES)
    {
        throw std::invalid_argument("Error! Select for operators `BETWEEN_VALUES` or `OUTSIDE_VALUES`.");
    }

    std::vector<Row> result_table;
    std::vector<int> indexes;
    auto select_iter = cols_to_select.cbegin();
    int i_select = 0, i_column = 0, i_sort = 0;
    for (const auto& cfg_iter : table_config_)
    {
        if (*select_iter == cfg_iter.first)
        {
            indexes.push_back(i_select);
            select_iter++;
        }

        if (col_name == cfg_iter.first)
        {
            i_column = i_select;
        }

        if (!col_to_sort_by.empty() && (col_to_sort_by == cfg_iter.first))
        {
            i_sort = i_select;
        }

        i_select++;
    }

    for (const auto& row: table_)
    {
        auto dataToCheck = boost::get<T>(row.second.getRow().at(i_column).getData());
        if ((dataToCheck > boost::get<T>(data_t(value1))) && (dataToCheck < boost::get<T>(data_t(value2))) && op == Operator::BETWEEN_VALUES)
        {
            result_table.push_back(handleRow(row, indexes));
        }
        else if (((dataToCheck < boost::get<T>(data_t(value1))) || (dataToCheck > boost::get<T>(data_t(value2)))) && op == Operator::OUTSIDE_VALUES)
        {
            result_table.push_back(handleRow(row, indexes));
        }
    }

    if (!col_to_sort_by.empty())
    {
        std::sort(result_table.begin(), result_table.end(), [&](const Row& row1, const Row& row2)
        {
            return (boost::get<T>(row1.getCell(i_sort).getData()) < boost::get<T>(row2.getCell(i_sort).getData()));
        });
    }

    return result_table;
}



Row Table::handleRow(const std::pair<const int, Row>& row, const std::vector<int>& indexes)
{
    Row temp_row;
    for (int i: indexes)
    {
        temp_row.addCell(row.second.getCell(i));
    }
    temp_row.setId(row.first);

    return temp_row;
}

const table_t &Table::getTable() const
{
    return table_;
}


void Table::update(Operator op, const Table& table)
{
    if (op != Operator::ALL)
    {
        throw std::invalid_argument("Update for operator `ALL` only.");
    }


    if (table.getTConfig() == table_config_)
    {
        table_ = table.getTable();
    }
}


template<typename T>
void Table::update(Operator op, const std::string& col_name, const T& value, const Row& new_row)
{
    if (op != Operator::EQUALS_TO)
    {
        throw std::invalid_argument("Update for operator `EQUALS_TO` only.");
    }

    int pos = 0;
    for (const auto& cfg_iter : table_config_)
    {
        if(cfg_iter.first == col_name)
        {
            break;
        }

        pos++;
    }

    for (auto& row: table_)
    {
        if (boost::get<T>(row.second.getCell(pos).getData()) == value)
        {
            row.second.setRow(new_row.getRow());
        }
    }
}


void Table::remove(Operator op)
{
    if (op != Operator::ALL)
    {
        throw std::invalid_argument("Remove for operator `ALL` only.");
    }

    table_ = table_t();
}


template<typename T>
void Table::remove(Operator op, const std::string& col_name, const T& value)
{
    if (op != Operator::EQUALS_TO && op != Operator::NOT_EQUALS_TO && op != Operator::BIGGER_THAN_VALUE && op != Operator::LESS_THAN_VALUE)
    {
        throw std::invalid_argument("Remove for operator `EQUALS_TO`, `NOT_EQUALS_TO`, `BIGGER_THAN_VALUE` or `LESS_THAN_VALUE`.");
    }

    int pos = 0;
    for (const auto& cfg_iter : table_config_)
    {
        if(cfg_iter.first == col_name)
        {
            break;
        }

        pos++;
    }

    for (auto table_iter = table_.cbegin(); table_iter != table_.cend();)
    {
        auto dataToCheck = boost::get<T>(table_iter->second.getCell(pos).getData());
        if ((dataToCheck == value) && op == Operator::EQUALS_TO)
        {
            table_iter = table_.erase(table_iter);
        }
        else if ((dataToCheck != value) && op == Operator::NOT_EQUALS_TO)
        {
            table_iter = table_.erase(table_iter);
        }
        else if ((dataToCheck < value) && op == Operator::LESS_THAN_VALUE)
        {
            table_iter = table_.erase(table_iter);
        }
        else if ((dataToCheck > value) && op == Operator::BIGGER_THAN_VALUE)
        {
            table_iter = table_.erase(table_iter);
        }
        else
        {
            ++table_iter;
        }
    }
}


template<typename T>
void Table::remove(Operator op, const std::string& col_name, const T& value1, const T& value2)
{
    if (op != Operator::BETWEEN_VALUES && op != Operator::OUTSIDE_VALUES)
    {
        throw std::invalid_argument("Remove for operators `BETWEEN_VALUES` or `OUTSIDE_VALUES`.");
    }

    int pos = 0;
    for (const auto& cfg_iter : table_config_)
    {
        if(cfg_iter.first == col_name)
        {
            break;
        }

        pos++;
    }

    for (auto table_iter = table_.cbegin(); table_iter != table_.cend();)
    {
        auto dataToCheck = boost::get<T>(table_iter->second.getCell(pos).getData());
        if ((dataToCheck > value1 && dataToCheck < value2) && op == Operator::BETWEEN_VALUES)
        {
            table_iter = table_.erase(table_iter);
        }
        else if ((dataToCheck < value1 || dataToCheck > value2) && op == Operator::OUTSIDE_VALUES)
        {
            table_iter = table_.erase(table_iter);
        }
        else
        {
            ++table_iter;
        }
    }
}
