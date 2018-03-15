#include <regex>

#include "funcollection.h"

bool metricspp::is_var_valid(const std::string &variable) {
  static const std::regex tag_regex("^[\\w\\.]+$");
  return std::regex_match(variable, tag_regex);
}
