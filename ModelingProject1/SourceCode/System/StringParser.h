#pragma once

#include <string>
#include <sstream>

template <typename DataType>
std::string parseDataToString(DataType data)
{
  std::string outData;
  std::stringstream out;

  out.str(std::string());
  out << data;

  outData = out.str();

  return outData;
}
