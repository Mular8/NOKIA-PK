#include "Database/SmsDatabase.hpp"
#include "Sms/Sms.hpp"
#include <memory>
namespace ue
{
SmsDatabase::SmsDatabase(){}
SmsDatabase::SmsDatabase(std::vector<Sms> smsList):obiekty(smsList){}
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
long SmsDatabase::size()
{
    return obiekty.size();
}
}
