#include "Table.h"


Table::Table() = default;


Table::Table(std::string_view table_name) : table_name_(table_name)
{
    // pass
}

Table::Table(std::string_view table_name, const config_t& table_config)
        : table_name_(table_name), table_config_(table_config)
{
    // pass
}

Table::Table(std::string_view table_name, const config_t& table_config, const table_t& sortedTables)
        : table_name_(table_name), table_config_(table_config), table_(sortedTables)
{
    // pass
}


void Table::setName(std::string_view new_table_name)
{
    table_name_ = new_table_name;
}


std::string_view Table::getName() const
{
    return table_name_;
}


void Table::setConfig(const config_t& new_table_config)
{
    if (!table_config_.empty())
    {
        BOOST_LOG_TRIVIAL(error) << "[Table::setConfig] Config has been already set.";
        return;
    }

    table_config_ = new_table_config;
}


const config_t& Table::getConfig() const
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
            BOOST_LOG_TRIVIAL(warning) << "[Table::addRow] Row data types don't match";
            return;
        }
    }

    table_.try_emplace(row.id(), row);
}

std::vector<Row> Table::select(Operator op, const std::vector<std::string>& cols_to_select, const std::string& col_to_sort_by, bool reversed) const
{
    if (op != Operator::ALL)
    {
        BOOST_LOG_TRIVIAL(warning) << "[Table::select] Select for option `ALL`.";
        return {};
    }

    std::vector<Row> result_table;
    std::vector<int> indexes;
    auto select_iter = cols_to_select.cbegin();
    int i_select = 0, i_sort = 0;
    for (const auto& [key, value]: table_config_)
    {
        if (*select_iter == key)
        {
            indexes.push_back(i_select);
            select_iter++;
        }

        if (!col_to_sort_by.empty() && (col_to_sort_by == key))
        {
            i_sort = i_select;
        }
        i_select++;
    }

    for (const auto& [key, value]: table_)
    {
        Row temp_row;
        for (int i: indexes)
        {
            temp_row.addCell(value.getCell(i));
        }
        temp_row.setId(key);
        result_table.push_back(temp_row);
    }

    if (!col_to_sort_by.empty())
    {
        result_table = sort(result_table, col_to_sort_by, i_sort, reversed);
    }

    return result_table;
}


template<typename T>
std::vector<Row> Table::select(Operator op, std::string_view col_name, const T& value,
                               const std::vector<std::string>& cols_to_select, const std::string& col_to_sort_by,
                               bool reversed) const
{
    if (op != Operator::EQUALS_TO && op != Operator::NOT_EQUALS_TO && op != Operator::BIGGER_THAN_VALUE && op != Operator::LESS_THAN_VALUE)
    {
        BOOST_LOG_TRIVIAL(warning) << "[Table::select] Select for options `EQUALS_TO`, `NOT_EQUALS_TO`, `BIGGER_THAN_VALUE` or `LESS_THAN_VALUE`.";
        return {};
    }

    std::vector<Row> result_table;
    std::vector<int> indexes;
    auto select_iter = cols_to_select.cbegin();
    int i_select = 0, i_column = 0, i_sort = 0;
    for (const auto& [key, val]: table_config_)
    {
        if (*select_iter == key)
        {
            indexes.push_back(i_select);
            select_iter++;
        }

        if (col_name == key)
        {
            i_column = i_select;
        }

        if (!col_to_sort_by.empty() && (col_to_sort_by == key))
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
        result_table = sort(result_table, col_to_sort_by, i_sort, reversed);
    }

    return result_table;
}


template<typename T>
std::vector<Row> Table::select(Operator op, std::string_view col_name, const T& value1, const T& value2,
                               const std::vector<std::string>& cols_to_select, const std::string& col_to_sort_by,
                               bool reversed) const
{
    if (op != Operator::BETWEEN_VALUES && op != Operator::OUTSIDE_VALUES)
    {
        BOOST_LOG_TRIVIAL(warning) << "[Table::select] Select for operators `BETWEEN_VALUES` or `OUTSIDE_VALUES`.";
        return {};
    }

    std::vector<Row> result_table;
    std::vector<int> indexes;
    auto select_iter = cols_to_select.cbegin();
    int i_select = 0, i_column = 0, i_sort = 0;
    for (const auto& [key, value] : table_config_)
    {
        if (*select_iter == key)
        {
            indexes.push_back(i_select);
            select_iter++;
        }

        if (col_name == key)
        {
            i_column = i_select;
        }

        if (!col_to_sort_by.empty() && (col_to_sort_by == key))
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
        result_table = sort(result_table, col_to_sort_by, i_sort, reversed);
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


std::vector<Row> Table::sort(std::vector<Row> table, const std::string& col_to_sort_by, int col_index, bool reversed) const
{
    if (reversed)
    {
        std::sort(table.begin(), table.end(), [&](const Row& row1, const Row& row2)
        {
            if (table_config_.at(col_to_sort_by) == typeid(bool))
            {
                return (boost::get<bool>(row1.getCell(col_index).getData()) > boost::get<bool>(row2.getCell(col_index).getData()));
            }
            else if (table_config_.at(col_to_sort_by) == typeid(int))
            {
                return (boost::get<int>(row1.getCell(col_index).getData()) > boost::get<int>(row2.getCell(col_index).getData()));
            }
            else if (table_config_.at(col_to_sort_by) == typeid(double))
            {
                return (boost::get<double>(row1.getCell(col_index).getData()) > boost::get<double>(row2.getCell(col_index).getData()));
            }
            else if (table_config_.at(col_to_sort_by) == typeid(std::string))
            {
                return (boost::get<std::string>(row1.getCell(col_index).getData()) > boost::get<std::string>(row2.getCell(col_index).getData()));
            }
            else
            {
                BOOST_LOG_TRIVIAL(error) << "[Table::sort] Unknown data type";

            }
        });
    }
    else
    {
        std::sort(table.rbegin(), table.rend(), [&](const Row& row1, const Row& row2)
        {
            if (table_config_.at(col_to_sort_by) == typeid(bool))
            {
                return (boost::get<bool>(row1.getCell(col_index).getData()) > boost::get<bool>(row2.getCell(col_index).getData()));
            }
            else if (table_config_.at(col_to_sort_by) == typeid(int))
            {
                return (boost::get<int>(row1.getCell(col_index).getData()) > boost::get<int>(row2.getCell(col_index).getData()));
            }
            else if (table_config_.at(col_to_sort_by) == typeid(double))
            {
                return (boost::get<double>(row1.getCell(col_index).getData()) > boost::get<double>(row2.getCell(col_index).getData()));
            }
            else if (table_config_.at(col_to_sort_by) == typeid(std::string))
            {
                return (boost::get<std::string>(row1.getCell(col_index).getData()) > boost::get<std::string>(row2.getCell(col_index).getData()));
            }
            else
            {
                BOOST_LOG_TRIVIAL(error) << "[Table::sort] Unknown data type.";
            }
        });
    }


    return table;
}


void Table::update(Operator op, const Table& table)
{
    if (op != Operator::ALL)
    {
        BOOST_LOG_TRIVIAL(warning) << "[Table::update] Update for operator `ALL` only.";
        return;
    }


    if (table.getConfig() == table_config_)
    {
        table_ = table.getTable();
    }
}


template<typename T>
void Table::update(Operator op, std::string_view col_name, const T& value, const Row& new_row, bool upd_each)
{
    if (op != Operator::EQUALS_TO)
    {
        BOOST_LOG_TRIVIAL(warning) << "[Table::update] Update for operator `EQUALS_TO` only.";
        return;
    }

    int pos = 0;
    for (const auto& [key, val]: table_config_)
    {
        if(key == col_name)
        {
            break;
        }

        pos++;
    }

    for (auto& [key, val]: table_)
    {
        if (boost::get<T>(val.getCell(pos).getData()) == value)
        {
            val.setRow(new_row.getRow());

            if (!upd_each)
            {
                break;
            }
        }
    }
}


void Table::remove(Operator op)
{
    if (op != Operator::ALL)
    {
        BOOST_LOG_TRIVIAL(warning) << "[Table::remove] Remove for operator `ALL` only.";
        return;
    }

    table_ = table_t();
}


template<typename T>
bool Table::remove(Operator op, std::string_view col_name, const T& value)
{
    if (op != Operator::EQUALS_TO && op != Operator::NOT_EQUALS_TO && op != Operator::BIGGER_THAN_VALUE && op != Operator::LESS_THAN_VALUE)
    {
        BOOST_LOG_TRIVIAL(warning) << "[Table::remove] Remove for operator `EQUALS_TO`, `NOT_EQUALS_TO`, `BIGGER_THAN_VALUE` or `LESS_THAN_VALUE`.";
        return false;
    }

    int pos = 0;
    for (const auto& [key, val]: table_config_)
    {
        if(key == col_name)
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
            return true;
        }
        else if ((dataToCheck != value) && op == Operator::NOT_EQUALS_TO)
        {
            table_iter = table_.erase(table_iter);
            return true;
        }
        else if ((dataToCheck < value) && op == Operator::LESS_THAN_VALUE)
        {
            table_iter = table_.erase(table_iter);
            return true;
        }
        else if ((dataToCheck > value) && op == Operator::BIGGER_THAN_VALUE)
        {
            table_iter = table_.erase(table_iter);
            return true;
        }
        else
        {
            ++table_iter;
        }
    }

    return false;
}


template<typename T>
void Table::remove(Operator op, std::string_view col_name, const T& value1, const T& value2)
{
    if (op != Operator::BETWEEN_VALUES && op != Operator::OUTSIDE_VALUES)
    {
        BOOST_LOG_TRIVIAL(warning) << "[Table::remove] Remove for operators `BETWEEN_VALUES` or `OUTSIDE_VALUES`.";
        return;
    }

    int pos = 0;
    for (const auto& [key, value] : table_config_)
    {
        if(key == col_name)
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


template<class Archive>
void Table::save(Archive &ar, const unsigned int version) {
    ar << table_name_;
    ar << table_;

    std::map<std::string, std::string> cfg_to_str;
    for (const auto& [key, value]: table_config_)
    {
        cfg_to_str.try_emplace(key, SerializeTypeIndexHandler::name_for_type(value));
    }
    ar << cfg_to_str;
}

template<class Archive>
void Table::load(Archive &ar, const unsigned int version) {
    ar >> table_name_;
    ar >> table_;

    std::map<std::string, std::string> cfg_to_str;
    ar >> cfg_to_str;

    for (const auto& [key, value]: cfg_to_str)
    {
        table_config_.try_emplace(key, SerializeTypeIndexHandler::type_for_name(value));
    }
}



void Table::save(const std::string& filename) const
{
    if (filename.empty() && table_name_.empty())
    {
        BOOST_LOG_TRIVIAL(warning) << "[Table::save] Unknown name of a table.";
        return;
    }

    std::ofstream ofs;
    if (!filename.empty())
    {
        ofs = std::ofstream(filename);
    }
    else
    {
        ofs = std::ofstream(table_name_);
    }
    if (ofs.is_open())
    {
        boost::archive::text_oarchive oa(ofs);
        oa << *this;
        ofs.close();
    }
    else
    {
        BOOST_LOG_TRIVIAL(error) << "[Table::save] The file was not opened.";
    }
}


void Table::load(const std::string& filename)
{
    if (filename.empty() && table_name_.empty())
    {
        BOOST_LOG_TRIVIAL(error) << "[Table::load] Unknown name of a table.";
        return;
    }

    std::ifstream ifs;
    if (!filename.empty())
    {
        ifs = std::ifstream(filename, std::ios::binary);
    }
    else
    {
        ifs = std::ifstream(table_name_, std::ios::binary);
    }

    if (ifs.is_open())
    {
        boost::archive::text_iarchive ia(ifs);
        ia >> *this;
        ifs.close();
    }
    else
    {
        BOOST_LOG_TRIVIAL(error) << "[Table::load] The file was not opened.";
    }
}

