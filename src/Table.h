#ifndef TABLE_H_
#define TABLE_H_

#include "Row.h"
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>



class Table
{
public:
    Table() {}
    Table(const std::string& table_name) : table_name_(table_name) {}
    explicit Table(const std::string& table_name, const std::map<std::string, DataTypes>& col_cfg) : table_name_(table_name), col_cfg_(col_cfg) {}
    ~Table() {};

    void setConfig(const std::map<std::string, DataTypes>& col_cfg);

    void addRow(const Row& row);
    void setRow(const Row& row, std::function<void()>);  // `std::function<...>` signature hasn't been defined yet
    void removeRow(std::function<void()>);

    void setTableName(const std::string& new_table_name) { table_name_ = new_table_name; }
    const std::string& getTableName() { return table_name_; }

    bool getBoolItem(std::function<void()>);  // `std::function<...>` signature hasn't been defined yet
    int getIntItem(std::function<void()>);
    float getFloatItem(std::function<void()>);
    const std::string& getStringItem(std::function<void()>);

    void setItem(bool data, std::function<void()>);  // `std::function<...>` signature hasn't been defined yet
    void setItem(int data, std::function<void()>);
    void setItem(float data, std::function<void()>);
    void setItem(const std::string& data, std::function<void()>);

    bool empty();

    void save() const;
    void load();

private:
    std::string table_name_;

    // config : pairs of {column_name, datatype}
    std::map<std::string, DataTypes> col_cfg_;

    // std::string - name of column the table sorted by
    // unordered_map<data type of column, ...> - table sorted by coluшmn
    std::map<std::string, std::unordered_map<bool, Row>> b_rows_;
    std::map<std::string, std::unordered_map<int, Row>> i_rows_;
    std::map<std::string, std::unordered_map<float, Row>> f_rows_;
    std::map<std::string, std::unordered_map<std::string, Row>> s_rows_;
};



#endif  // TABLE_H_