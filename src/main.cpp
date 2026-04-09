#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <chrono>
#include <unordered_set>
#include <unistd.h>

#include "term.hpp"
#include "speed_test.hpp"
#include "file_utils.hpp"
#include "phrase.hpp"

using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) {
	srand(time(NULL));

	vector<string> words = parse_words("../words/keybr");
	vector<speedTest> results;
	bool toContinue = true;
	for (; toContinue ;) {
		Terminal::clear_console();

		int words_num = 0;
		if (argc > 1) {
			words_num = atoi(argv[1]);
		} else {
			cout << "How many words do you want to type? (default is 15) : ";
			cin >> words_num;
		}

		// Generating random phrase
		string phrase = "";
		if (words_num <= 0 || words_num > words.size()) {
			cout << "I cant generate phrase like that :(\n"
				<< "Max size of phraze is " << words.size() << '\n';
			sleep(5);
			continue;
		}
		else
			phrase = pickup_phrase(words, words_num);

		// Starting our test
		speedTest current_test = run_test(phrase, words_num);

		if (current_test.wordsNum > 0)
			print_result(current_test);

		results.push_back(current_test);

		// Asking if user want to continue
		cout << "\nDo you want to continue? (1): ";
		char next = Terminal::getch();
		toContinue = (next == '1' ? true : false);
	}

	cout << "\nDo you want to get your all stats? (1): ";
	char stats = Terminal::getch();
	if (stats == '1') {
		cout << "\n\n";
		for (int i=0; i<results.size(); ++i) {
			cout << '\n' << i+1;
			string to_print = " -----------------------\n";
			Colors::green(to_print);
			print_result(results[i]);
		}
		cout << "-------------------------\n\n";

		char best = '1';
		cout << "\nDo you want to see your best result? (1): ";
		for (; best == '1' ;) {
			char best = Terminal::getch();
			if (best == '1') {
				cout << "\nGet best...\n"
					<< "(1) Accurency\n"
					<< "(2) WPM\n"
					<< ": ";
				char choise = Terminal::getch();
				double maxi = 0;
				int index = 0;
				switch (choise) {
					case '1':
						for (int i=0; i<results.size(); ++i)
							if (results[i].accurency > maxi) {
								maxi = results[i].accurency;
								index = i+1;
							}
						cout << "\n\nYour best result result with accurence was " << maxi << ", that was " << index << " game.";
						break;
					case '2':
						for (int i=0; i<results.size(); ++i) 
							if (results[i].wpm > maxi) {
								maxi = results[i].wpm;
								index = i+1;
							}
						cout << "\n\nYour best result result with WPM was " << maxi << ", that was " << index << " game.";
						break;
					default:
						cout << "You entered wrong symbol!";
				}
				cout << "\nShow menu again? (1): "; // Getting symbol at top of this for
			}
			else
				break;
		}

	}

	Terminal::clear_console();
	cout << "Have a great time!\n";

	return 0;
}
