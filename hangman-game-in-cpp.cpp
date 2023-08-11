/* 222014771 ISHIMWE lucie Karlise
 * 222005571 TUYISHIME Ephron 
 * 222002227 MUGISHA Elvis
*/


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <set>
using namespace std;

bool isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main() {
    srand(time(0));
    string words[] = {"apple", "banana", "cherry", "date", "elderberry", "fig", "grape"};
    int numWords = sizeof(words) / sizeof(words[0]);
    
    string secretWord = words[rand() % numWords];
    int wordLength = secretWord.length();
    string guessedWord(wordLength, '-');
    
    set<char> guessedLetters;
    int remainingGuesses = 6;
    int warnings = 3;

    cout << "Welcome to Hangman!\n";
    cout << "I have selected a word. It has " << wordLength << " letters.\n";

    while (remainingGuesses > 0 && guessedWord != secretWord) {
        cout << "Guesses remaining: " << remainingGuesses << "\n";
        cout << "Warnings remaining: " << warnings << "\n";
        cout << "Letters not yet guessed: ";
        for (char c = 'a'; c <= 'z'; ++c) {
            if (guessedLetters.find(c) == guessedLetters.end()) {
                cout << c << " ";
            }
        }
        cout << "\n";
        
        cout << "Current guessed word: " << guessedWord << "\n";
        char guess;
        cout << "Enter your guess: ";
        cin >> guess;
        guess = tolower(guess);

        if (!isalpha(guess)) {
            cout << "Please enter a valid letter.\n";
            if (warnings > 0) {
                cout << "You have " << warnings << " warnings left.\n";
                --warnings;
            } else {
                cout << "You have no warnings left. You lose a guess.\n";
                --remainingGuesses;
            }
        } else if (guessedLetters.find(guess) != guessedLetters.end()) {
            cout << "You have already guessed that letter.\n";
            if (warnings > 0) {
                cout << "You have " << warnings << " warnings left.\n";
                --warnings;
            } else {
                cout << "You have no warnings left. You lose a guess.\n";
                --remainingGuesses;
            }
        } else {
            guessedLetters.insert(guess);
            if (secretWord.find(guess) != string::npos) {
                cout << "Good guess!\n";
                for (int i = 0; i < wordLength; ++i) {
                    if (secretWord[i] == guess) {
                        guessedWord[i] = guess;
                    }
                }
            } else {
                cout << "Bad guess!\n";
                if (isVowel(guess)) {
                    remainingGuesses -= 2;
                } else {
                    --remainingGuesses;
                }
            }
        }
    }

    if (guessedWord == secretWord) {
        int score = remainingGuesses * set<char>(guessedLetters.begin(), guessedLetters.end()).size();
        cout << "Congratulations! You won!\n";
        cout << "Your score: " << score << "\n";
    } else {
        cout << "Sorry, you've run out of guesses. The word was: " << secretWord << "\n";
    }

    return 0;
}
