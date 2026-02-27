#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <vector>


std::vector<std::pair<std::string, double>> parseMoviesCSV(const std::string& filename);
std::vector<std::string> parsePrefixesTXT(const std::string& filename);

#endif
