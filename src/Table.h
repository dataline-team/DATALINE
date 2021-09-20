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
    explicit Table(std::string_view table_name);
    explicit Table(std::string_view table_name, const config_t& table_config);
    explicit Table(std::string_view table_name, const config_t& table_config, const table_t& sortedTables);

    void setName(std::string_view new_table_name);
    [[nodiscard]] std::string_view getName() const;

    void setConfig(const config_t& new_table_config);
    [[nodiscard]] const config_t& getConfig() const;

    [[nodiscard]] const table_t& getTable() const;

    void addRow(const Row& row);

    [[nodiscard]] std::vector<Row> select(Operator op, const std::vector<std::string>& cols_to_select,
                                          const std::string& col_to_sort_by = std::string(),
                                          bool reversed = false) const;  // for Options: `ALL`
    template<typename T>
    [[nodiscard]] std::vector<Row> select(Operator op, std::string_view col_name, const T& value,
                                          const std::vector<std::string>& cols_to_select,
                                          const std::string& col_to_sort_by = std::string(),
                                          bool reversed = false) const;  // for Options: `EQUALS_TO`, `NOT_EQUALS_TO`, `BIGGER_THAN_VALUE`, `LESS_THAN_VALUE`
    template<typename T>
    [[nodiscard]] std::vector<Row> select(Operator op, std::string_view col_name, const T& value1, const T& value2,
                                          const std::vector<std::string>& cols_to_select,
                                          const std::string& col_to_sort_by = std::string(),
                                          bool reversed = false) const;  // for Options: `BETWEEN_VALUES`, `OUTSIDE_VALUES`


    void update(Operator op, const Table& table);  // for Options: `ALL`
    template<typename T>
    void update(Operator op, std::string_view col_name, const T& value, const Row& new_row, bool upd_each = false);  // for Options: `EQUALS_TO`


    void remove(Operator op);  // for Options: `ALL`
    template<typename T>
    bool remove(Operator op, std::string_view col_name, const T& value);  // for Options: `EQUALS_TO`
    template<typename T>
    void remove(Operator op, std::string_view col_name, const T& value1, const T& value2);  // for Options: `EQUALS_TO`

    [[nodiscard]] bool empty() const;


    template<class Archive>
    void save(Archive & ar, const unsigned int version);

    template<class Archive>
    void load(Archive & ar, const unsigned int version);

    BOOST_SERIALIZATION_SPLIT_MEMBER();


    void save(const std::string& filename = std::string()) const;
    void load(const std::string& filename = std::string());

private:
    std::string table_name_;
    config_t    table_config_;
    table_t     table_;

    static Row handleRow(const std::pair<const int, Row>& row, const std::vector<int>& indexes);
    [[nodiscard]] std::vector<Row> sort(std::vector<Row> table, const std::string&,
                                        int col_index, bool reversed) const;
};


#endif  // TABLE_H_
