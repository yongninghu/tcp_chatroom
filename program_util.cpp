#include <string>
#include <stdexcept>

#include "program_util.h"

arg_runtime_error::arg_runtime_error(const std::string& what) :
  std::invalid_argument(what) {}

connect_runtime_error::connect_runtime_error(const std::string& what) :
  std::runtime_error(what) {}

chat_runtime_error::chat_runtime_error(const std::string& what) :
  std::runtime_error(what) {}
