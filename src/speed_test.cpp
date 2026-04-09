#include "speed_test.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <iomanip>

#include <ctime>
#include <chrono>

#include "term.hpp"
#include "phrase.hpp"

using namespace std;
using namespace chrono;

void print_result(speedTest test) {
    test.setup();
    cout << "Phase: " << test.phrase << "\n" 
         << "Accurency: " << std::setprecision(4) << (test.accurency < 0 ? 0 : test.accurency) << "%\n"
         << "WPM: " << std::setprecision(4) << test.wpm << '\n'
         << "Length: " << test.phrase.size() << " symbols\n"
         << "Words: " << test.wordsNum << '\n'
         << "Total errors: " << test.totalErrors << '\n'
         << "Errors when you ended your race: " << test.errors << '\n';
}

speedTest run_test(const string& phrase, const int& words_num) {
	speedTest currentTest;
	if (words_num < 0)
		return currentTest;
	currentTest.setDefault();
	currentTest.phrase = phrase;
	currentTest.wordsNum = words_num;
	currentTest.colors.resize(currentTest.phrase.size(), 'd');

	// Creating timer for wpm
	time_point<system_clock> start, end;
	start = system_clock::now();

	// Starting test
	for (; currentTest.phraseIndex < currentTest.phrase.size() ;) {
		Terminal::clear_console();

		// Printing current phrase (red errors, underlined current symbol, gray correct symbols)
		print_phrase(currentTest.phrase, currentTest.phraseIndex, currentTest.colors);

		// Reading symbol
		char ch = Terminal::getch();

		// User wrote backspace(127 in ASCII)
		if (ch == 127) {
			if (currentTest.phraseIndex > 0) {
				--currentTest.phraseIndex;
				currentTest.colors[currentTest.phraseIndex] = 'd';
			}
			continue;
		}

		// Checking if user input correct symbol
		if (ch != currentTest.phrase[currentTest.phraseIndex]) {
			++currentTest.totalErrors;
			currentTest.colors[currentTest.phraseIndex] = 'r';
		} else
			currentTest.colors[currentTest.phraseIndex] = 'g';

		++currentTest.phraseIndex;
	}
	// Calculating time
	end = system_clock::now();
	Terminal::clear_console();
	currentTest.timeElapsed = end - start;
	currentTest.setup();

	return currentTest;
}
