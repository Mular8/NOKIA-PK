#pragma once
#include <gmock/gmock.h>
#include "Ports/ISmsDatabasePort.hpp"
#include "SmsForDatabase/Sms.hpp"
namespace ue
{


class ISmsDatabaseMock : public ISmsDatabase
{
public:
    ISmsDatabaseMock();
    ~ISmsDatabaseMock() override;
    MOCK_METHOD(Sms*, get, (int), (final));
    MOCK_METHOD(std::vector<Sms>, getAll, (), (final));
    MOCK_METHOD(void, remove, (int), (final));
    MOCK_METHOD(void, removeAll, (), (final));
    MOCK_METHOD(void, insert, (Sms), (final));
    MOCK_METHOD(long, size, (), (final));
};

}
