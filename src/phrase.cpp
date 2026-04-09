#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include "term.hpp"
#include "phrase.hpp"

using namespace std;

string generate_random_phraze(const vector<string>& words, const int& end, const int& cols) {
    if (end > words.size())
        return "";
    string result = "";
    unordered_set<int> used;
    int rand_index;
    int prev_line_size = 0;
    for (int i = 0; i < end; ++i) {
        rand_index = rand() % words.size();
        if (used.find(rand_index) == used.end()) // Already used that word
            used.insert(rand_index);
        else
            continue;

        if (((result.size() - prev_line_size) + words[rand_index].size()) >= cols) {
            prev_line_size = result.size();
            result[result.size() - 1] = '\n';
        }
        result += words[rand_index] + ' ';
    }

    result.pop_back();

    return result;
}

void print_phrase(const string& phrase, const int& phraseIndex, const vector<char>& colors) {
    // Printing part that already typed correctly (gray) and uncorrectly (red)
    for (int i=0; i<phraseIndex && i<colors.size(); ++i) {
        string printGray = "";
        if (colors[i] == 'g') {
            printGray += phrase[i];
            int j=i+1;
            for (; colors[j] == 'g' && j < phraseIndex; ++j) {
                if (colors[j] == 'g')
                    printGray += phrase[j];
            }
            Colors::gray(printGray);
            i = j - 1;
            printGray = "";
        }
        else {
			if (phrase[i] == ' ') {
				Colors::red_block();
			}
			else {
				// If symbol
				Colors::red(phrase[i]);
			}
		}
    }

    Colors::underline(phrase[phraseIndex]);

    // Printing remaining part (without changes)
    printf("%s\n", phrase.substr(phraseIndex + 1).c_str());
}


string pickup_phrase(const vector<string>& words, const int words_num) {
	int rows, cols;
	Terminal::get_terminal_size(rows, cols); // Using for create \n at the end of line

	char likePhrase = 'r';
	string phrase = "";
	for (; likePhrase == 'r' ;) {
		Terminal::clear_console();
		phrase = generate_random_phraze(words, words_num, cols);
		cout << phrase << '\n'
			 << '\n'
			 << "To regenerate phrase press \'r\'\n"
			 << "To continue press any button\n";
		likePhrase = Terminal::getch();
	}
	return phrase;
}
