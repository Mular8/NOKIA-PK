#include "Sms.hpp"

namespace ue
{

Sms::Sms()
{
}

Sms::Sms(PhoneNumber from, PhoneNumber to) : Sms()
{
    this->from=from;
    this->to=to;
}

std::string Sms::decryption()
{
    for(int i=0;i<message.size();i++)
    {
        message[i]+=encrypion_code;
    }
}

std::string Sms::encryption()
{
    for(int i=0;i<message.size();i++)
    {
        message[i]-=encrypion_code;
    }
}

}
