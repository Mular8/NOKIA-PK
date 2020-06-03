#pragma once
#include <vector>
#include <memory>
#include "SmsForDatabase/Sms.hpp"
#include "ISmsDatabasePort.hpp"
namespace ue
{
class SmsDatabase : public ISmsDatabase
{
    std::vector<Sms> obiekty;

public:
    SmsDatabase();
    SmsDatabase(std::vector<Sms>);
    Sms* get(int id) override;
    std::vector<Sms> getAll() override;
    void remove(int id) override;
    void removeAll() override;
    void insert(Sms sms) override;
    long size() override;
};
}
