#pragma once

#include "command_table.h"

namespace goodok {
    namespace TypeCommand::Tag {

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
        struct SendText {
        };
        struct JoinRoom {
        };
        struct History {
        };
        struct Channels {
        };

    } // namespace Traits::Tag

    namespace TypeCommand {

        template<command::TypeCommand T>
        struct TypeCommandTraits {
            using Category = Tag::Unknown;
            using Value = Tag::Unknown;
        };


        template<>
        struct TypeCommandTraits<command::TypeCommand::RegistrationResponse> {
            using Category = Tag::Response;
            using Value = Tag::Registration;
        };

        template<>
        struct TypeCommandTraits<command::TypeCommand::RegistrationRequest> {
            using Category = Tag::Request;
            using Value = Tag::Registration;
        };

        template<>
        struct TypeCommandTraits<command::TypeCommand::AuthorisationResponse> {
            using Category = Tag::Response;
            using Value = Tag::Authorisation;
        };

        template<>
        struct TypeCommandTraits<command::TypeCommand::AuthorisationRequest> {
            using Category = Tag::Request;
            using Value = Tag::Authorisation;
        };

        template<>
        struct TypeCommandTraits<command::TypeCommand::EchoResponse> {
            using Category = Tag::Response;
            using Value = Tag::SendText;
        };

        template<>
        struct TypeCommandTraits<command::TypeCommand::SendTextRequest> {
            using Category = Tag::Request;
            using Value = Tag::SendText;
        };

        template<>
        struct TypeCommandTraits<command::TypeCommand::JoinRoomResponse> {
            using Category = Tag::Response;
            using Value = Tag::JoinRoom;
        };

        template<>
        struct TypeCommandTraits<command::TypeCommand::JoinRoomRequest> {
            using Category = Tag::Request;
            using Value = Tag::JoinRoom;
        };

        template<>
        struct TypeCommandTraits<command::TypeCommand::HistoryResponse> {
            using Category = Tag::Response;
            using Value = Tag::History;
        };

        template<>
        struct TypeCommandTraits<command::TypeCommand::HistoryRequest> {
            using Category = Tag::Request;
            using Value = Tag::History;
        };

        template<>
        struct TypeCommandTraits<command::TypeCommand::ChannelsResponse> {
            using Category = Tag::Response;
            using Value = Tag::Channels;
        };

        template<>
        struct TypeCommandTraits<command::TypeCommand::ChannelsRequest> {
            using Category = Tag::Request;
            using Value = Tag::Channels;
        };

    } // namespace Traits
} // namespace goodok