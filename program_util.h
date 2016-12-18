#ifndef __PROGRAM_UTIL__
#define __PROGRAM_UTIL__

#include <stdexcept>
#include <netdb.h>
#include <string>

#ifndef __PROGRAM_SPEC__
#define __PROGRAM_SPEC__
#define PROGRAM_ARGSIZE 3
#define UNDEFINEDFD -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#endif


typedef struct hostent hostent;

class arg_runtime_error : public std::invalid_argument {
  public:
    explicit arg_runtime_error(const std::string& what);
};

class connect_runtime_error : public std::runtime_error {
  public:
    explicit connect_runtime_error(const std::string& what);
};

class chat_runtime_error : public std::runtime_error {
  public:
    explicit chat_runtime_error(const std::string& what);
};

#endif
