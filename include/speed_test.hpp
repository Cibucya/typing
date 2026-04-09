#pragma once

#include <vector>
#include <string>
#include <chrono>

struct speedTest {
    std::string phrase;
    int wordsNum;
    int phraseIndex;
    int errors;
    int totalErrors;
    std::vector<char> colors;
    std::chrono::duration<double> timeElapsed;
    float wpm;
    float accurency;

    float getWPM() {
        this->wpm = wordsNum / (timeElapsed.count() / 60.0);
        return wpm;
    }
    float getAccurency() {
        this->accurency = (((double)phrase.size() - (double)totalErrors) / (double)phrase.size()) * 100.0;
        return accurency;
    }
    int getErrors() {
        errors = 0;
        for (const char& ch : colors) 
            if (ch != 'g')
                ++errors;

        return errors;
    }

    void setup() {
        errors = getErrors();
        wpm = getWPM();
        accurency = getAccurency();
    }

    void setDefault() {
        phrase = "";
        wordsNum = 15;
        phraseIndex = 0;
        errors = 0;
        totalErrors = 0;
        for (int i=0; i<colors.size(); ++i)
            colors[i] = 'd';
        wpm = 0;
        accurency = 0;
    }
};

void print_result(speedTest test);

speedTest run_test(const std::string& phrase, const int& words_num);
