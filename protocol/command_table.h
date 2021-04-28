#ifndef COMMAND_TABLE_H
#define COMMAND_TABLE_H

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <memory>
#include <unordered_map>
#include <deque>
#include <cassert>

#include "datetime.h"

namespace goodok {
namespace command {

    class TextSendData;
    class ClientTextMsg;
    class DataChat;

    using identifier_t = int32_t;
    using msg_text_t = ClientTextMsg;
    using messages_ptr = std::shared_ptr<std::deque<msg_text_t>>;
    using chat_t = DataChat;

    constexpr uint32_t PROTOCOL_VERSION = 2;
    constexpr unsigned short SERVER_DEFAULT_PORT = 7777;

    enum class TypeCommand : int {
        Unknown = 0xFFFF,
        RegistrationRequest = 0x0001,
        RegistrationResponse = 0x0002,
        AuthorisationRequest = 0x0003,
        AuthorisationResponse = 0x0004,
        SendTextRequest = 0x0005,
        EchoResponse = 0x0006,
        JoinRoomRequest = 0x0007,
        JoinRoomResponse = 0x0008,
        HistoryRequest = 0x0009,
        HistoryResponse = 0x000A,
        ChannelsRequest = 0x000B,
        ChannelsResponse = 0x000C
    };

    struct TextSendData {
        std::string channel_name;
        std::string login;
        std::string text;
    };

    struct ClientTextMsg {
        std::string author;
        std::string text;
        std::string channel_name;
        DateTime dt;
    };

    struct DataChat {
        std::string name;
        identifier_t id;
        int count_subs = 0;

        messages_ptr history_ptr;
    };

    enum class StatusCode : int {
        RegistrOK = 1,
        AutorOK,
        BusyRegistr,
        IncorrectAutor
    };

    inline const std::string& get_command_str(TypeCommand const& command) {
        static const std::unordered_map<TypeCommand, std::string> type_command_str = {
                {TypeCommand::RegistrationRequest,   "RegistrationRequest"},
                {TypeCommand::RegistrationResponse,  "RegistrationResponse"},
                {TypeCommand::AuthorisationRequest,  "AuthorisationRequest"},
                {TypeCommand::AuthorisationResponse, "AuthorisationResponse"},
                {TypeCommand::SendTextRequest,       "SendTextRequest"},
                {TypeCommand::EchoResponse,          "EchoResponse"},
                {TypeCommand::JoinRoomRequest,       "JoinRoomRequest"},
                {TypeCommand::JoinRoomResponse,      "JoinRoomResponse"},
                {TypeCommand::HistoryRequest,        "HistoryRequest"},
                {TypeCommand::HistoryResponse,       "HistoryResponse"},
                {TypeCommand::ChannelsRequest,       "ChannelsRequest"},
                {TypeCommand::ChannelsResponse,      "ChannelsResponse"},

                {TypeCommand::Unknown,               "Unknown"}
        };

        if (auto it = type_command_str.find(command); it != type_command_str.end()) {
            return it->second;
        }
        assert(type_command_str.at(TypeCommand::Unknown) == "Unknown");
        return type_command_str.at(TypeCommand::Unknown);
    }


    inline bool operator==(const ClientTextMsg &lhs, const ClientTextMsg &rhs) {
        // @TODO tuple
        return lhs.author == rhs.author &&
               lhs.text == rhs.text &&
               lhs.channel_name == rhs.channel_name &&
               lhs.dt == rhs.dt;
    }

    } // end namespace command
} // end namespace goodok

#endif // COMMAND_TABLE_H
