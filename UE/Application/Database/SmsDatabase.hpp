#pragma once
#include <vector>
#include <memory>
#include "Sms/Sms.hpp"
#include "ISmsDatabase.hpp"
namespace ue
{
class SmsDatabase : public ISmsDatabase
{
    std::vector<Sms> obiekty;
public:
    Sms* get(int id) override;
    std::vector<Sms> getAll() override;
    void update(Sms sms, int id) override;
    void remove(int id) override;
    void removeAll() override;
    void insert(Sms sms) override;
    size_t size();
};
}
