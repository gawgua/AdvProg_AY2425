#include "assessment.h"

using std::string;
using std::vector;

void updateMask(string& mask, const char ch, const string& word);
bool isCorrectChar(char ch, const string& mask);
bool isWholeWord(const string& mask);


void updateMask(string& mask, const char ch, const string& word)
{
	for (int i = 0; i < word.size(); ++i) {
		if (word[i] == ch) {
			mask[i] = ch;
		}
	}
}

int countMistakes(const string& word, HangmanGuesser& hmGuesser)
{
	hmGuesser.newGame(word.size(), MASK_CHAR);
	string mask = string(word.size(), MASK_CHAR);
	int incorrectGuess = 0;

	while (true) {
		char nextChar = hmGuesser.getChar(mask);
		if (nextChar == 0) {
			break;
		}
		updateMask(mask, nextChar, word);

		if (isCorrectChar(nextChar, mask)) {
			if (isWholeWord(mask)) {
				return incorrectGuess;
			}
		}
		else {
			incorrectGuess += 1;
		}
	}

	return -1;
}

void getMistakeByWordList(vector<MistakeByWord>& mistakeList, vector<string>& unsolvableList, const vector<string>& testWords, HangmanGuesser& hmGuesser)
{
	for (const string& word : testWords) {
		int mistakes = countMistakes(word, hmGuesser);
		if (mistakes == -1) {
			unsolvableList.push_back(word);
		} else {
			MistakeByWord mistake;
			mistake.count = mistakes;
			mistake.word = word;
			mistakeList.push_back(mistake);
		}
	}
}

bool isCorrectChar(char ch, const string& mask)
{
    return isCharInWord(ch, mask);
}

bool isWholeWord(const string& mask)
{
    return !isCharInWord(MASK_CHAR, mask);
}