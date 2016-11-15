#ifndef _UTILS_H_
#define _UTILS_H_
#include <string>

bool str_equals(const std::string &first, const std::string &second);
bool str_equals(const char* first, const std::string& second);
bool str_equals(const std::string& first, const char* second);
bool str_equals(const char *first, const char *second);

void complete_direction(std::string& direction);

int randomize(int min, int max);

#endif // _UTILS_H_
