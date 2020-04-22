#pragma once

#include <gmock/gmock.h>
#include "Ports/ITimerPort.hpp"
#include "Database/ISmsDatabase.hpp"
#include <Sms/Sms.hpp>
namespace ue
{


class ISmsDatabaseMock : public ISmsDatabase
{
public:
    ISmsDatabaseMock();
    ~ISmsDatabaseMock() override;
    MOCK_METHOD(std::shared_ptr<Sms>, get, (int), (final));
    MOCK_METHOD(std::vector<Sms>, getAll, (), (final));
    MOCK_METHOD(void, update,(Sms,int), (final));
    MOCK_METHOD(void, remove, (int), (final));
    MOCK_METHOD(void, removeAll, (), (final));
    MOCK_METHOD(void, create, (Sms), (final));
};

}
