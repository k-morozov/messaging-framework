//
// Created by focus on 27.04.2021.
//

#include "gtest/gtest.h"
#include <protocol.h>

using namespace goodok;

TEST(request, RegistrationRequest) {
    std::string login = "login";
    std::string password = "123";

    auto res = MsgFactory::serialize<command::TypeCommand::RegistrationRequest>(login, password);
    Serialize::Header header;
    header.ParseFromArray(res.data(), goodok::SIZE_HEADER);
    EXPECT_EQ(static_cast<command::TypeCommand>(header.command()), command::TypeCommand::RegistrationRequest);

    std::size_t length = header.length();
    Serialize::Request request;
    request.ParseFromArray(res.data() + goodok::SIZE_HEADER, static_cast<int>(length));

    EXPECT_TRUE(request.has_registration_request());
    EXPECT_EQ(request.registration_request().login(), login);
    EXPECT_EQ(request.registration_request().password(), password);
}

TEST(request, AuthorisationRequest) {
    std::string login = "login";
    std::string password = "123";

    auto res = MsgFactory::serialize<command::TypeCommand::AuthorisationRequest>(login, password);
    Serialize::Header header;
    header.ParseFromArray(res.data(), goodok::SIZE_HEADER);
    EXPECT_EQ(static_cast<command::TypeCommand>(header.command()), command::TypeCommand::AuthorisationRequest);

    std::size_t length = header.length();
    Serialize::Request request;
    request.ParseFromArray(res.data() + goodok::SIZE_HEADER, static_cast<int>(length));

    EXPECT_TRUE(request.has_authorisation_request());
    EXPECT_EQ(request.authorisation_request().login(), login);
    EXPECT_EQ(request.authorisation_request().password(), password);
}

TEST(request, JoinRoomRequest) {
    int client_id = 1;
    std::string channel_name = "nameChannel";

    auto res = MsgFactory::serialize<command::TypeCommand::JoinRoomRequest>(client_id, channel_name);
    Serialize::Header header;
    header.ParseFromArray(res.data(), goodok::SIZE_HEADER);
    EXPECT_EQ(static_cast<command::TypeCommand>(header.command()), command::TypeCommand::JoinRoomRequest);

    std::size_t length = header.length();
    Serialize::Request request;
    request.ParseFromArray(res.data() + goodok::SIZE_HEADER, static_cast<int>(length));

    EXPECT_TRUE(request.has_join_room_request());
    EXPECT_EQ(request.join_room_request().client_id() , client_id);
    EXPECT_EQ(request.join_room_request().channel_name(), channel_name);
}

TEST(request, TextRequest) {
    std::string login = "login";
    int room_id = 2;
    std::string channel_name = "channelName";
    std::string text = "message";
    goodok::DateTime datetime = goodok::DateTime();

    auto res = MsgFactory::serialize<command::TypeCommand::SendTextRequest>(goodok::command::ClientTextMsg{login,text, channel_name, datetime});
    Serialize::Header header;
    header.ParseFromArray(res.data(), goodok::SIZE_HEADER);
    EXPECT_EQ(static_cast<command::TypeCommand>(header.command()), command::TypeCommand::SendTextRequest);

    std::size_t length = header.length();
    Serialize::Request request;
    request.ParseFromArray(res.data() + goodok::SIZE_HEADER, static_cast<int>(length));

    EXPECT_TRUE(request.has_text_request());
    EXPECT_EQ(request.text_request().login() , login);
    EXPECT_EQ(request.text_request().channel_name() , channel_name);
    EXPECT_EQ(request.text_request().text() , text);
}

TEST(request, HistoryRequest) {
    int client_id = 1;
    std::string channel_name = "channelName";
    goodok::DateTime datetime = goodok::DateTime();

    auto res = MsgFactory::serialize<command::TypeCommand::HistoryRequest>(client_id, channel_name, datetime);
    Serialize::Header header;
    header.ParseFromArray(res.data(), goodok::SIZE_HEADER);
    EXPECT_EQ(static_cast<command::TypeCommand>(header.command()), command::TypeCommand::HistoryRequest);

    std::size_t length = header.length();
    Serialize::Request request;
    request.ParseFromArray(res.data() + goodok::SIZE_HEADER, static_cast<int>(length));

    EXPECT_TRUE(request.has_history_request());
    EXPECT_EQ(request.history_request().client_id(), client_id);
    EXPECT_EQ(request.history_request().channel_name() , channel_name);
}

TEST(request, ChannelsRequest) {
    int client_id = 1;

    auto res = MsgFactory::serialize<command::TypeCommand::ChannelsRequest>(client_id);
    Serialize::Header header;
    header.ParseFromArray(res.data(), goodok::SIZE_HEADER);
    EXPECT_EQ(static_cast<command::TypeCommand>(header.command()), command::TypeCommand::ChannelsRequest);

    std::size_t length = header.length();
    Serialize::Request request;
    request.ParseFromArray(res.data() + goodok::SIZE_HEADER, static_cast<int>(length));

    EXPECT_TRUE(request.has_channels_request());
    EXPECT_EQ(request.channels_request().client_id(), client_id);
}

