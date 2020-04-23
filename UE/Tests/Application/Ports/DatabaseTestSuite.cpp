#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include "Database/SmsDatabase.hpp"
#include "Sms/Sms.hpp"
#include "Database/SmsDatabase.hpp"
#include "Mocks/SmsMock.hpp"
namespace ue
{
using namespace ::testing;

class DatabaseTestSuite : public Test
{
public:
    SmsDatabase db;
    SmsMock mock;

};
TEST_F(DatabaseTestSuite, TestOfAll)
{
    for(int i=0;i<10;i++)
        db.insert(mock.createSms());
    db.removeAll();
    for(int i=0;i<10;i++)
        db.insert(mock.createSms());
    Sms temp=mock.createSms();
    temp.message="New message";
    db.update(temp,2);
    db.remove(6);
    for(Sms sms : db.getAll())
        std::cout<<sms.messageId<<" "<<sms.to<<" "<<sms.from<<" "<<sms.message<<"\n";

    EXPECT_TRUE(true);
}
TEST_F(DatabaseTestSuite, NewDatabaseEmpty)
{
    EXPECT_EQ(0,db.size());
}

TEST_F(DatabaseTestSuite, CreateTest)
{
    int temp=db.size();
    Sms newsms;
    db.insert(newsms);
    EXPECT_EQ(temp+1,db.size());
    EXPECT_EQ(db.get(db.size()-1)->messageId,db.size()-1);
}
TEST_F(DatabaseTestSuite, RemoveTest)
{
    int temp=db.size();
    Sms newsms;
    db.insert(newsms);
    db.remove(0);
    EXPECT_EQ(temp,db.size());
}
TEST_F(DatabaseTestSuite, RemoveAllTest)
{
    Sms newsms;
    db.insert(newsms);
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
