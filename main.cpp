#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

void MakeAGuess(vector<char>& blankWord, string randomWord, int& correctGuesses, int& incorrectGuesses);
bool CheckForCompletion(vector<char> incompleteWord);
bool AskToPlayAgain();
vector<char> InitializeWord(vector<string> listOfWords, string& randomWord);

int main() {
    const int NUMBER_OF_WORDS = 10;
    int correctGuesses = 0;
    int incorrectGuesses= 0;
    vector<string> listOfWords(NUMBER_OF_WORDS);
    listOfWords.at(0) = "unfortunate";
    listOfWords.at(1) = "journey";
    listOfWords.at(2) = "kazakhstan";
    listOfWords.at(3) = "aardvark";
    listOfWords.at(4) = "pencil";
    listOfWords.at(5) = "zoo";
    listOfWords.at(6) = "quilt";
    listOfWords.at(7) = "abilities";
    listOfWords.at(8) = "thanksgiving";
    listOfWords.at(9) = "fail";
    srand(time(0));
    string randomWord;
    cout << "Welcome to Hangman!! You know the rules (I hope)..." << endl << endl;
    do {
        vector<char> blankWord = InitializeWord(listOfWords, randomWord);
        MakeAGuess(blankWord, randomWord, correctGuesses, incorrectGuesses);
        correctGuesses = 0;
        incorrectGuesses = 0;
    } while (AskToPlayAgain());
    cout << "Thanks for playing!" << endl;
    return 0;
}

void MakeAGuess(vector<char>& blankWord, string randomWord, int& correctGuesses, int& incorrectGuesses) {
    int i;
    char guessMade;
    bool letterFound = false;
    cout << "Guess a letter:";
    cin >> guessMade;
    guessMade = tolower(guessMade);
    while (!isalpha(guessMade)) {
        cout << "Invalid entry, try again" << endl;
        cin >> guessMade;
    }
    for (i = 0; i < randomWord.length(); ++i) {
        if (randomWord[i] == guessMade) {
            blankWord.at(i) = guessMade;
            letterFound = true;
        }
        cout << blankWord.at(i);
    }
    cout << endl;
    if (!letterFound) {
        cout << "There is no '" << guessMade << "' in your word." << endl;
        ++incorrectGuesses;
    }
    else {
        ++correctGuesses;
    }
    cout << "Correct guesses: " << correctGuesses << ", incorrect guesses: " << incorrectGuesses << endl << endl;
    if (!CheckForCompletion(blankWord)) {
        MakeAGuess(blankWord, randomWord, correctGuesses, incorrectGuesses);
    }
    else {
        cout << "Congratulations!!! You guessed the word: " << randomWord << endl;
        cout << "It only took you " << correctGuesses + incorrectGuesses << " guesses!" << endl << endl;
    }
}

bool CheckForCompletion(vector<char> incompleteWord) {
    for (int i = 0; i < incompleteWord.size(); ++i) {
        if (incompleteWord.at(i) == '_') {
            return false;
        }
    }
    return true;
}

bool AskToPlayAgain() {
    char answer;
    cout << "Would you like to play again? (y/n)";
    cin >> answer;
    while (answer != 'y' && answer != 'n') {
        cout << endl << "That is not a valid response, please try again (y/n)";
        cin >> answer;
    }
    cout << endl;
    if (answer == 'y') {
        return true;
    }
    else {
        return false;
    }
}

vector<char> InitializeWord(vector<string> listOfWords, string& randomWord) {
    randomWord = listOfWords.at(rand() % listOfWords.size());
    int wordLength = randomWord.length();
    vector<char> blankWord(wordLength);
    for (int i = 0; i < wordLength; ++i) {
        blankWord.at(i) = '_';
    }
    cout << "Your word has " << wordLength << " letters." << endl << endl;
    return blankWord;
}