//
// Created by Alexey Shishkov on 08.10.2023.
//

#ifndef CHECKERS_REQUESTS_H
#define CHECKERS_REQUESTS_H


#include <iostream>
#include <string>
#include <istream>
#include <ostream>
#include <boost/asio.hpp>
#include <curl/curl.h>
#include <stdexcept>

using boost::asio::ip::tcp;

namespace Requests {
    std::string get(const std::string &url, int maxRetry=5, int sleepTimeout=2);
}

#endif //CHECKERS_REQUESTS_H
