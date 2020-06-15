#pragma once

#include <gmock/gmock.h>
#include "Ports/IBtsPort.hpp"

namespace ue
{

class IBtsEventsHandlerMock : public IBtsEventsHandler
{
public:
    IBtsEventsHandlerMock();
    ~IBtsEventsHandlerMock() override;
    MOCK_METHOD(void, handleDisconnected, (), (final));
    MOCK_METHOD(void, handleSib, (common::BtsId), (final));
    MOCK_METHOD(void, handleAttachAccept, (), (final));
    MOCK_METHOD(void, handleAttachReject, (), (final));
    MOCK_METHOD(void, handleSmsReceived, (common::PhoneNumber, std::string), (final));
    MOCK_METHOD(void, handleReceivedCallRequest, (common::PhoneNumber), (final));
    MOCK_METHOD(void, handleReceivedCallAccepted, (common::PhoneNumber), (final));
    MOCK_METHOD(void, handleReceivedCallDropped, (common::PhoneNumber), (final));
    MOCK_METHOD(void, handlePeerNotConnected, (common::PhoneNumber), (final));
    MOCK_METHOD(void, handleTalkMessage, (const std::string), (final));
    MOCK_METHOD(void, handlePeerUeBecomesUnknown, (), (final));
    MOCK_METHOD(void, handleCallDrop, (), (final));
};

class IBtsPortMock : public IBtsPort
{
public:

    IBtsPortMock();
    ~IBtsPortMock() override;
    MOCK_METHOD(void, sendSms, (common::PhoneNumber, std::string), (final));
    MOCK_METHOD(void, sendAttachRequest, (common::BtsId), (final));
    MOCK_METHOD(void, sendCallAccept, (common::PhoneNumber), (final));
    MOCK_METHOD(void, sendCallDropped, (common::PhoneNumber), (final));
    MOCK_METHOD(void, sendCallRequest, (common::PhoneNumber), (final));
    MOCK_METHOD(void, sendTalkMessage, (const std::string, const common::PhoneNumber), (final));
    MOCK_METHOD(void, sendCallDrop, (common::PhoneNumber, common::PhoneNumber),(final));
};

}
