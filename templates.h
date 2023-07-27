#ifndef TEMPLATES_HE
#define TEMPLATES_HE

#include <string>
#include <vector>
#include <array>

typedef std::vector<std::array<std::string, 2>> selectore;


std::string render(std::string body, selectore values);

#endif