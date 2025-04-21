#include <string>
#include <vector>


std::vector<std::string> readDB(const std::string& filePath);

void writeDB(const std::string& filePath, const std::vector<std::string>& lines);

void appendDB(const std::string& filePath, const std::string& line);

std::vector<std::string> parser(std::string stringToParse, char separator);

