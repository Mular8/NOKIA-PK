#pragma once

#include <gmock/gmock.h>
#include "Ports/IUserPort.hpp"

namespace ue
{

class IUserEventsHandlerMock : public IUserEventsHandler
{
public:
    IUserEventsHandlerMock();
    ~IUserEventsHandlerMock() override;
    MOCK_METHOD(void, handleSendSms, (common::PhoneNumber, std::string), (final));
    MOCK_METHOD(void, handleSendCallRequest, (common::PhoneNumber), (final));
    MOCK_METHOD(void, handleSendCallAccept, (common::PhoneNumber), (final));
    MOCK_METHOD(void, handleSendCallDropped, (common::PhoneNumber), (final));
    MOCK_METHOD(void, handleSendCallDrop, (common::PhoneNumber,common::PhoneNumber), (final));
    MOCK_METHOD(void, handleSendTalkMessage, (const std::string), (final));
};

class IUserPortMock : public IUserPort
{
public:
    IUserPortMock();
    ~IUserPortMock() override;

    MOCK_METHOD(void, showNotConnected, (), (final));
    MOCK_METHOD(void, showConnecting, (), (final));
    MOCK_METHOD(void, showConnected, (), (final));
    MOCK_METHOD(void, showNewSms, (), (final));
    MOCK_METHOD(void, showSmsList, (), (final));
    MOCK_METHOD(void, showMenu, (), (final));
    MOCK_METHOD(void, showSms, (int),(final));
    MOCK_METHOD(void, showComposeSmsMode,(),(final));
    MOCK_METHOD(void, showSmsReceived,(),(final));
    MOCK_METHOD(void, showSentSMSList,(),(final));
    MOCK_METHOD(void, showSentSMS,(int),(final));
    MOCK_METHOD(std::string, encrypted,(std::string),(final));
    MOCK_METHOD(std::string, decrypted,(std::string),(final));
    MOCK_METHOD(void, showPeerConnected, (common::PhoneNumber),(final));
    MOCK_METHOD(void, showCallDropped, (common::PhoneNumber),(final));
    MOCK_METHOD(void, callTimeout, (),(final));
    MOCK_METHOD(void, clearCallMessages, (),(final));
    MOCK_METHOD(void, showCallRequest, (common::PhoneNumber), (final));
    MOCK_METHOD(void, showPeerUserDisconnected, (), (final));
    MOCK_METHOD(void, showNotAvailable, (common::PhoneNumber), (final));
    MOCK_METHOD(void, showPeerNotConnected, (common::PhoneNumber),(final));
    MOCK_METHOD(void, showStartDialView, (), (final));
    MOCK_METHOD(void, showCallView, (const std::string), (final));
    MOCK_METHOD(void, showDialingView, (common::PhoneNumber), (final));
    MOCK_METHOD(void, showPeerUeBecomesUnknown, (common::PhoneNumber), (final));

};

}
