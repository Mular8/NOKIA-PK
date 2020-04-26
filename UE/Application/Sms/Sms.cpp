#include "Sms.hpp"

namespace ue
{

Sms::Sms()
{
}

Sms::Sms(PhoneNumber from, std::string text) : Sms()
{
    this->from=from;
    this->message=text;
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
