#pragma once
#include <vector>
#include <memory>
#include "../Sms/Sms.hpp"
namespace ue
{
class ISmsDatabase
{
public:
    ~ISmsDatabase() = default;
    virtual Sms* get(int id)=0;
    virtual std::vector<Sms> getAll()=0;
    virtual void update(Sms sms, int id)=0;
    virtual void remove(int id)=0;
    virtual void removeAll()=0;
    virtual void insert(Sms sms)=0;
    virtual long size();
};
}
