#ifndef TABLE_H_
#define TABLE_H_

#include "Row.h"
#include "Operator.h"
#include <map>
#include <algorithm>


using config_t = std::map<std::string, datatype_t, std::less<>>;
using table_t = std::map<int, Row>;



class Table
{
public:
    Table();
    explicit Table(const std::string& table_name);
    explicit Table(const std::string& table_name, const config_t& table_config);
    explicit Table(const std::string& table_name, const config_t& table_config, const table_t& sortedTables);

    void setTName(const std::string& new_table_name);
    [[nodiscard]] const std::string& getTName() const;

    void setTConfig(const config_t& new_table_config);
    [[nodiscard]] const config_t& getTConfig() const;

    [[nodiscard]] const table_t& getTable() const;

    void addRow(const Row& row);

    template<typename T>
    std::vector<Row> select(Operator op, const std::vector<std::string>& cols_to_select, const std::string& col_to_sort_by = std::string()) const;  // for Options: `ALL`
    template<typename T>
    std::vector<Row> select(Operator op, const std::string& col_name, const T& value,
                            const std::vector<std::string>& cols_to_select, const std::string& col_to_sort_by = std::string()) const;  // for Options: `EQUALS_TO`, `NOT_EQUALS_TO`, `BIGGER_THAN_VALUE`, `LESS_THAN_VALUE`
    template<typename T>
    std::vector<Row> select(Operator op, const std::string& col_name, const T& value1, const T& value2,
                            const std::vector<std::string>& cols_to_select, std::string col_to_sort_by) const;  // for Options: `BETWEEN_VALUES`, `OUTSIDE_VALUES`


    void update(Operator op, const Table& table);  // for Options: `ALL`
    template<typename T>
    void update(Operator op, const std::string& col_name, const T& value, const Row& new_row);  // for Options: `EQUALS_TO`


    void remove(Operator op);  // for Options: `ALL`
    template<typename T>
    void remove(Operator op, const std::string& col_name, const T& value);  // for Options: `EQUALS_TO`
    template<typename T>
    void remove(Operator op, const std::string& col_name, const T& value1, const T& value2);  // for Options: `EQUALS_TO`

    [[nodiscard]] bool empty() const;

//    void save();
//    void load();

private:
    std::string table_name_;
    config_t table_config_;
    table_t table_;

    static Row handleRow(const std::pair<const int, Row>& row, const std::vector<int>& indexes) ;
};


#endif  // TABLE_H_
