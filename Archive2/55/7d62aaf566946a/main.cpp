#ifndef MY_HEADER
#define MY_HEADER

#include <string>
#include <iosfwd>

extern template std::istream& std::getline(std::istream&, std::string&, char);

#endif //MY_HEADER