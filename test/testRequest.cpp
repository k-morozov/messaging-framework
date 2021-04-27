//
// Created by focus on 27.04.2021.
//

#include "gtest/gtest.h"
#include <protocol.h>

using namespace goodok;

TEST(request, ExampleTest1) {
    std::string login = "login";
    std::string password = "123";

    auto res = MsgFactory::serialize<command::TypeCommand::RegistrationRequest>(login, password);
    Serialize::Header header;
    header.ParseFromArray(res.data(), goodok::SIZE_HEADER);
    EXPECT_EQ(static_cast<command::TypeCommand>(header.command()), command::TypeCommand::RegistrationRequest);

    std::size_t length = header.length();
    Serialize::Request request;
    request.ParseFromArray(res.data() + goodok::SIZE_HEADER, static_cast<int>(length));

    EXPECT_TRUE(request.has_register_request());
    EXPECT_EQ(request.register_request().login(), login);
    EXPECT_EQ(request.register_request().password(), password);

}
