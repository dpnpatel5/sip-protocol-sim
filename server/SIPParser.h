
#ifndef SIPPARSER_H
#define SIPPARSER_H

#include <iostream>
#include <string>
#include <osip2/osip.h>

// Function to extract the method from a raw SIP message using osip2 library
std::string get_method_from_sip_message(const std::string& raw_message);

#endif // SIPPARSER_H
