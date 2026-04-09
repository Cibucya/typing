#include "file_utils.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>

std::string get_file_data(std::string path) {
    std::ifstream file(path);
    std::string fileData = "";
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return "";
    }

    std::copy(std::istream_iterator<char>(file >> std::noskipws), std::istream_iterator<char>(), back_inserter(fileData));
    file.close();

    return fileData;
}

std::vector<std::string> parse_words(const std::string& path) {
	std::string all_words = get_file_data(path);
	std::string temp;
	std::vector<std::string> words;
	for (const char& ch : all_words) {
		if (ch == '\n') {
			words.push_back(temp);
			temp = "";
		}
		else
			temp += ch;
	}
	return words;
}
