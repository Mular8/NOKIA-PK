#pragma once
#include <gmock/gmock.h>
#include "Database/ISmsDatabase.hpp"
#include <Sms/Sms.hpp>
namespace ue
{


class ISmsDatabaseMock : public ISmsDatabase
{
public:
    ISmsDatabaseMock() = default;
    ~ISmsDatabaseMock() = default;
    MOCK_METHOD(Sms*, get, (int), (final));
    MOCK_METHOD(std::vector<Sms>, getAll, (), (final));
    MOCK_METHOD(void, update,(Sms,int), (final));
    MOCK_METHOD(void, remove, (int), (final));
    MOCK_METHOD(void, removeAll, (), (final));
    MOCK_METHOD(void, insert, (Sms), (final));
    MOCK_METHOD(long, size, (), (final));
};

}
