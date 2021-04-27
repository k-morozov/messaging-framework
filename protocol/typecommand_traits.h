#pragma once

#include "command_table.h"

namespace goodok {
    namespace Traits::TypeCommandTag {

        struct Unknown {
        };

        struct Request {
        };
        struct Response {
        };

        struct Registration {
        };
        struct Authorisation {
        };
        struct Echo {
        };
        struct JoinRoom {
        };
        struct History {
        };
        struct Channels {
        };

    } // namespace Traits::TypeCommandTag

    namespace Traits {

        template<command::TypeCommand T>
        struct TypeCommandTraits {
            using Category = TypeCommandTag::Unknown;
            using Value = TypeCommandTag::Unknown;
        };


        template<>
        struct TypeCommandTraits<command::TypeCommand::RegistrationResponse> {
            using Category = TypeCommandTag::Response;
            using Value = TypeCommandTag::Registration;
        };

        template<>
        struct TypeCommandTraits<command::TypeCommand::RegistrationRequest> {
            using Category = TypeCommandTag::Request;
            using Value = TypeCommandTag::Registration;
        };

        template<>
        struct TypeCommandTraits<command::TypeCommand::AuthorisationResponse> {
            using Category = TypeCommandTag::Response;
            using Value = TypeCommandTag::Authorisation;
        };

        template<>
        struct TypeCommandTraits<command::TypeCommand::AuthorisationRequest> {
            using Category = TypeCommandTag::Request;
            using Value = TypeCommandTag::Authorisation;
        };

        template<>
        struct TypeCommandTraits<command::TypeCommand::EchoResponse> {
            using Category = TypeCommandTag::Response;
            using Value = TypeCommandTag::Echo;
        };

        template<>
        struct TypeCommandTraits<command::TypeCommand::EchoRequest> {
            using Category = TypeCommandTag::Request;
            using Value = TypeCommandTag::Echo;
        };

        template<>
        struct TypeCommandTraits<command::TypeCommand::JoinRoomResponse> {
            using Category = TypeCommandTag::Response;
            using Value = TypeCommandTag::JoinRoom;
        };

        template<>
        struct TypeCommandTraits<command::TypeCommand::JoinRoomRequest> {
            using Category = TypeCommandTag::Request;
            using Value = TypeCommandTag::JoinRoom;
        };

        template<>
        struct TypeCommandTraits<command::TypeCommand::HistoryResponse> {
            using Category = TypeCommandTag::Response;
            using Value = TypeCommandTag::History;
        };

        template<>
        struct TypeCommandTraits<command::TypeCommand::HistoryRequest> {
            using Category = TypeCommandTag::Request;
            using Value = TypeCommandTag::History;
        };

        template<>
        struct TypeCommandTraits<command::TypeCommand::ChannelsResponse> {
            using Category = TypeCommandTag::Response;
            using Value = TypeCommandTag::Channels;
        };

        template<>
        struct TypeCommandTraits<command::TypeCommand::ChannelsRequest> {
            using Category = TypeCommandTag::Request;
            using Value = TypeCommandTag::Channels;
        };

    } // namespace Traits
} // namespace goodok