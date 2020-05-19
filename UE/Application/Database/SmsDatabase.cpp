#include "Database/SmsDatabase.hpp"
#include "Sms/Sms.hpp"
#include <memory>
namespace ue
{
SmsDatabase::SmsDatabase(){}
Sms* SmsDatabase::get(int id)
{
    try
    {
        return &obiekty.at(id);
    }
    catch (const std::out_of_range& oor)
    {
        return &obiekty.at(obiekty.size()-1);
    }

}
std::vector<Sms> SmsDatabase::getAll()
{
    return obiekty;
}
void SmsDatabase::update(Sms sms, int id)
{
    Sms* temp=this->get(id);
    temp->message=sms.message;
    temp->messageId=id;
}
void SmsDatabase::remove(int id)
{
    obiekty.erase(obiekty.begin() + id);
        for(int i=id;i<this->size();i++)
        {
            obiekty.at(i).messageId--;
        }
}
void SmsDatabase::removeAll()
{
    obiekty.clear();
}
void SmsDatabase::insert(Sms sms)
{
    sms.messageId=obiekty.size();
    obiekty.push_back(sms);
}
size_t SmsDatabase::size()
{
    return obiekty.size();
}
}
