#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Ports/UserPort.hpp"
#include "Mocks/ILoggerMock.hpp"
#include "Mocks/IUserPortMock.hpp"
#include "Messages/PhoneNumber.hpp"
#include "Mocks/IUeGuiMock.hpp"
#include "Mocks/ISmsDatabaseMock.hpp"
namespace ue
{
using namespace ::testing;

class UserPortTestSuite : public Test
{
protected:
    const common::PhoneNumber PHONE_NUMBER{112};
    NiceMock<common::ILoggerMock> loggerMock;
    StrictMock<IUserEventsHandlerMock> handlerMock;
    StrictMock<IUeGuiMock> guiMock;
    StrictMock<IListViewModeMock> listViewModeMock;
    StrictMock<ITextModeMock> textModeMock;
    StrictMock<ISmsComposeModeMock> smsComposeModeMock;
    StrictMock<ISmsDatabaseMock> databaseMock;
    IUeGui::Callback rejectCallback;
    IUeGui::Callback acceptCallback;

    UserPort objectUnderTest{loggerMock, guiMock, PHONE_NUMBER, databaseMock, databaseMock};

    UserPortTestSuite()
    {
        EXPECT_CALL(guiMock, setTitle(HasSubstr(to_string(PHONE_NUMBER))));
        EXPECT_CALL(guiMock, setRejectCallback(_))
            .WillOnce(SaveArg<0>(&rejectCallback));
        EXPECT_CALL(guiMock, setAcceptCallback(_))
            .WillOnce(SaveArg<0>(&acceptCallback));

        objectUnderTest.start(handlerMock);
    }
    ~UserPortTestSuite()
    {
        EXPECT_CALL(guiMock, setRejectCallback(IsNull()));
        EXPECT_CALL(guiMock, setAcceptCallback(IsNull()));

        objectUnderTest.stop();
    }
};

TEST_F(UserPortTestSuite, shallStartStop)
{
}

TEST_F(UserPortTestSuite, shallShowNotConnected)
{
    EXPECT_CALL(guiMock, showNotConnected());
    objectUnderTest.showNotConnected();
}

TEST_F(UserPortTestSuite, shallShowConnecting)
{
    EXPECT_CALL(guiMock, showConnecting());
    objectUnderTest.showConnecting();
}

TEST_F(UserPortTestSuite, shallShowMenuWorkCorrectly)
{
    EXPECT_CALL(guiMock, setListViewMode()).WillOnce(ReturnRef(listViewModeMock));
    EXPECT_CALL(listViewModeMock, clearSelectionList());
    EXPECT_CALL(listViewModeMock, addSelectionListItem(_, _)).Times(AtLeast(1));
    EXPECT_CALL(guiMock, setAcceptCallback);
    objectUnderTest.showMenu();
}

TEST_F(UserPortTestSuite, shallShowSmsListWorkCorrectly)
{
    EXPECT_CALL(guiMock, setListViewMode()).WillOnce(ReturnRef(listViewModeMock));
    EXPECT_CALL(databaseMock, getAll());
    EXPECT_CALL(databaseMock, size());
    EXPECT_CALL(listViewModeMock, clearSelectionList());
    EXPECT_CALL(listViewModeMock, addSelectionListItem(_, _)).Times(AtLeast(1));
    objectUnderTest.showSmsList();
}

TEST_F(UserPortTestSuite, shallShowSentSmsListWorkCorrectly)
{
    EXPECT_CALL(guiMock, setListViewMode()).WillOnce(ReturnRef(listViewModeMock));
    EXPECT_CALL(databaseMock, getAll());
    EXPECT_CALL(databaseMock, size());
    EXPECT_CALL(listViewModeMock, clearSelectionList());
    EXPECT_CALL(listViewModeMock, addSelectionListItem(_, _)).Times(AtLeast(1));
    objectUnderTest.showSentSMSList();
}

TEST_F(UserPortTestSuite, shallShowComposeSmsModeCorrectly)
{
    EXPECT_CALL(guiMock, setSmsComposeMode()).WillOnce(ReturnRef(smsComposeModeMock));
    EXPECT_CALL(smsComposeModeMock, clearSmsText());
    EXPECT_CALL(guiMock, setAcceptCallback);
    objectUnderTest.showComposeSmsMode();
}

TEST_F(UserPortTestSuite, shallShowSmsReceivedCorrectly)
{
    EXPECT_CALL(guiMock, showSmsReceived());
    objectUnderTest.showSmsReceived();
}

TEST_F(UserPortTestSuite, shallshowNewSmsCorrectly)
{
    EXPECT_CALL(guiMock, showNewSms());
    objectUnderTest.showNewSms();
}

TEST_F(UserPortTestSuite, shallEncryptCorrectly)
{
std::string cos="aaa";
EXPECT_EQ("ddd",objectUnderTest.encrypted(cos));
}

TEST_F(UserPortTestSuite, shallDecryptCorrectly)
{
std::string cos="ddd";
EXPECT_EQ("aaa",objectUnderTest.decrypted(cos));
}

}
