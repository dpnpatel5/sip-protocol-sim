#include "SIPParser.h"

std::string get_method_from_sip_message(const std::string& raw_message) {
    osip_message_t *sip_message = nullptr;
    int result = osip_message_init(&sip_message);
    if (result != 0 || sip_message == nullptr) {
        std::cerr << "Failed to initialize SIP message" << std::endl;
        return "";
    }

    if ((parser_init()) < 0) {
	    fprintf(stderr, "Cannot initialise osip parser.\n");
	    osip_message_free(sip_message);
	    return "";
    }

    result = osip_message_parse(sip_message, raw_message.c_str(), raw_message.size());
    if (result != 0) {
        std::cerr << "Failed to parse SIP message" << std::endl;
        osip_message_free(sip_message);
        return "";
    }

    const char* method = osip_message_get_method(sip_message);
    std::string method_name = method ? method : "";

    osip_message_free(sip_message);
    return method_name;
}
