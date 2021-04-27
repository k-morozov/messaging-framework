#ifndef MSGFACTORY_H
#define MSGFACTORY_H

#include "command_table.h"
#include "proto/messages.pb.h"
#include "typecommand_traits.h"

#include <deque>

namespace goodok {

using ptr_proto_request_t   = std::unique_ptr<Serialize::Request>;
using ptr_header_t          = std::unique_ptr<Serialize::Header>;
using ptr_proto_response_t  = std::unique_ptr<Serialize::Response>;
using ptr_datetime_t        = std::unique_ptr<Serialize::Datetime>;

constexpr std::size_t SIZE_HEADER = 2*(sizeof(uint32_t)+1) + (sizeof(uint64_t)+1);

class MsgFactory
{
public:
    MsgFactory() = default;

    template <command::TypeCommand To, class... Args>
    static std::vector<uint8_t> serialize(Args&&...);

    static command::ClientTextMsg parse_text_req(Serialize::Request);
    static command::ClientTextMsg parse_text_res(Serialize::Response);
    static command::ClientTextMsg parse_text_res(const Serialize::TextResponse& );

protected:
    static ptr_datetime_t create_datetime(command::ClientTextMsg const&);

    [[nodiscard]]
    static ptr_header_t create_header(command::TypeCommand command, std::size_t length);
      
    [[nodiscard]]
    static std::vector<uint8_t> serialize_response(ptr_header_t&& header_ptr, ptr_proto_response_t&& response_ptr);

    [[nodiscard]]
    static std::vector<uint8_t> serialize_request(ptr_header_t&& header_ptr, ptr_proto_request_t&& request_ptr);
    
    // Response
    [[nodiscard]]
    static ptr_proto_response_t create_response(Traits::TypeCommandTag::Registration, int client_id);
    
    [[nodiscard]]
    static ptr_proto_response_t create_response(Traits::TypeCommandTag::Authorisation, int client_id);
    
    [[nodiscard]]
    static ptr_proto_response_t create_response(Traits::TypeCommandTag::Echo, const command::msg_text_t& msg);
    
    [[nodiscard]]
    static ptr_proto_response_t create_response(Traits::TypeCommandTag::JoinRoom,
        const std::string& channel_name, bool flag);
    
    [[nodiscard]]
    static ptr_proto_response_t create_response(Traits::TypeCommandTag::History,
        const std::string& channel_name, const std::deque<command::msg_text_t>& messages);

    [[nodiscard]]
    static ptr_proto_response_t create_response(Traits::TypeCommandTag::Channels,
        const std::deque<std::string>& channels);


    // Request
    [[nodiscard]]
    static ptr_proto_request_t create_request(Traits::TypeCommandTag::Registration,
        const std::string& login, const std::string& password);

    [[nodiscard]]
    static ptr_proto_request_t create_request(Traits::TypeCommandTag::Authorisation,
        const std::string& login, const std::string& password);

    [[nodiscard]]
    static ptr_proto_request_t create_request(Traits::TypeCommandTag::Echo, const command::msg_text_t& msg);

    [[nodiscard]]
    static ptr_proto_request_t create_request(Traits::TypeCommandTag::JoinRoom,
        command::identifier_t client_id, const std::string& channel_name);

    [[nodiscard]]
    static ptr_proto_request_t create_request(Traits::TypeCommandTag::History,
        command::identifier_t client_id, const std::string& channel_name, DateTime since);

    [[nodiscard]]
    static ptr_proto_request_t create_request(Traits::TypeCommandTag::Channels, command::identifier_t client_id);
};

} // namespace goodok

inline std::ostream& operator<<(std::ostream& stream, const Serialize::Header msg) {
    stream << "header size: "   << msg.ByteSizeLong() << " bytes" << std::endl;
    stream << "version:"        << msg.version() << std::endl;
    stream << "command:"        << msg.command() << std::endl;
//    stream << "time:"           << msg.time() << std::endl;
    stream << "length:"         << msg.length() << std::endl;

    return stream;
}

inline std::ostream& operator<<(std::ostream& stream, const Serialize::InRequest msg) {
    stream << "read InputRequest: " << msg.ByteSizeLong() << " bytes" << std::endl;
    stream << "login:"              << msg.login() << std::endl;
    stream << "password:"           << msg.password() << std::endl;

    return stream;
}

inline std::ostream& operator<<(std::ostream& stream, const Serialize::Request msg) {
    if (msg.has_input_request()) {
        stream << msg;
    }

    return stream;
}

namespace goodok {

template <command::TypeCommand To, class... Args>
auto MsgFactory::serialize(Args&&... args) -> std::vector<uint8_t>
{
    using category = typename Traits::TypeCommandTraits<To>::Category;
    using value = typename Traits::TypeCommandTraits<To>::Value;
    using Unknown = Traits::TypeCommandTag::Unknown;

    if constexpr (std::is_same_v<category, Unknown> || std::is_same_v<value, Unknown>)
    {
        throw std::logic_error("Unable to define traits for TypeCommand::" + get_command_str(To));  
    } else if constexpr (std::is_same_v<category, Traits::TypeCommandTag::Response>)
    {
        auto response = create_response(value{}, std::forward<Args>(args)...);
        auto header = create_header(To, response->ByteSizeLong());
        return serialize_response(std::move(header), std::move(response));
    } else if constexpr (std::is_same_v<category, Traits::TypeCommandTag::Request>)
    {
        auto request = create_request(value{}, std::forward<Args>(args)...);
        auto header = create_header(To, request->ByteSizeLong());
        return serialize_request(std::move(header), std::move(request));
    }
}


} // namespace goodok

#endif // MSGFACTORY_H
