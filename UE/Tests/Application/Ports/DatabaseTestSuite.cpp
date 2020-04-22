#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <QDebug>

#include "Database/SmsDatabase.hpp"

namespace ue
{
using namespace ::testing;

class DatabaseTestSuite : public Test
{
public:
    SmsDatabase db;
};
TEST_F(DatabaseTestSuite, NewDatabaseEmpty)
{
    EXPECT_EQ(0,db.size());
}
TEST_F(DatabaseTestSuite, CreateTest)
{
    int temp=db.size();
    Sms newsms;
    db.create(newsms);
    EXPECT_EQ(temp+1,db.size());
    EXPECT_EQ(db.get(db.size()-1)->messageId,db.size()-1);
}
TEST_F(DatabaseTestSuite, RemoveTest)
{
    int temp=db.size();
    Sms newsms;
    db.create(newsms);
    db.remove(0);
    EXPECT_EQ(temp,db.size());
}
TEST_F(DatabaseTestSuite, RemoveAllTest)
{
    Sms newsms;
    db.create(newsms);
    db.removeAll();
    EXPECT_EQ(0,db.size());
}
TEST_F(DatabaseTestSuite, UpdateTest)
{
    db.removeAll();
    Sms newSms;
    newSms.message="Old Message";
    db.insert(newSms);
    Sms updatingSms;
    updatingSms.message="New Message";
    db.update(updatingSms,0);
    EXPECT_EQ(db.get(0)->message,"New Message");
}
}
