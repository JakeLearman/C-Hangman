#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std; //Program only uses standard namespace so made global

#define MAX_WORD_SIZE 10
#define GUESSES 10

int main(int argc, char* argv[]){

	int selection, wordLength, i, numberOfGuesses, validInput, toASCII;
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	char input, round, toCompare;
    bool guess;
	ifstream inputFile;
	string wordRead, selectedWord;

	
	//Checking argument count
   if(argc > 2){
		cout << "Too Many Arguments - Exiting";
		exit (EXIT_FAILURE); 
    }
	//Checking for extra file to be used as word list
    else if(argc == 2){
        srand(time(0));
		inputFile.open(argv[1]);
		if(!inputFile){
			cerr << "Error: Could not open file - Exiting";
			exit(1);
		}
    }
	//Uses included wordlist
	else{
        srand(time(0));
		inputFile.open("wordlist.txt");
		if(!inputFile){
			cerr << "Error: Could not open file - Exiting";
			exit(1);
		}
	}
	 vector<std::string> words;
	while (std::getline(inputFile, wordRead)){
		words.push_back(wordRead);
	}	
	//Chooses random word from array of words
	selection = rand() % 6;
	selectedWord = words.at(selection);
	string guessed(selectedWord); 
	string availableLetters(alphabet);
	wordLength = selectedWord.length();
	numberOfGuesses = GUESSES;
	validInput = 0;
	cout << "The word has " << wordLength << " letters\n";
    for(i = 0; i < wordLength; i++){  //Creates list of - of length of selected word
				guessed[i] = '-' ;
            }
	while(true){ 
		while(numberOfGuesses != 0){
			fflush(stdin);
            guess = false;        
			cout << "Available letters are:" << availableLetters <<"\nWord is:" << guessed;
			cout << "\nYou have " << numberOfGuesses << " guesses left and have guessed " << validInput << " letters out of " << wordLength << "\n";
			cout << "Please input a letters: ";
			cin >> input;
			cout << "\n";
           
			if((input < 'a' || input > 'z') && (input < 'A' || input > 'Z')){
					cout << "Invalid input, try another key\n";
			}
            else{
				if(input >= 'A' || input <= 'Z'){
					input = tolower(input);
				}
                for(i = 0; i < wordLength; i++){
					if(selectedWord[i] == input){
						guessed[i] = input;
						validInput++;
						guess = true;
						cout << input << " is in the word\n\n\n";
						toASCII = input;
						//Swaps letter in both word and available alphabet with -
						for(i = 0; i < 26; i++){ 
							toCompare = availableLetters[i];
							if(toASCII == toCompare){
								availableLetters[i] = '-';
							}
						}
					}
                    
                }
				//Removes letter from letters guessed if not found in word
                if(!guess){
                    numberOfGuesses--;
					cout << input << " is not in word\n\n";
					toASCII = input;
					for(i = 0; i < 26; i++){
						toCompare = availableLetters[i];
						if(toASCII == toCompare){
							availableLetters[i] = '-';
						}
					}
                }
            }
			if(validInput == wordLength){
				cout << "You win, the word was "<< selectedWord << "\n";
				break;
			}
			if(numberOfGuesses == 0){
				cout << "You lost the word was " << selectedWord << "\n";
				break;
			}
			
        }
		//Reset game for second round
		numberOfGuesses = 0;
		cout << "Play again? Input Y for another round or input any other key to quit\n";
		fflush(stdin);
		scanf("%c", &round);
		if(round == 'Y' || round == 'y'){
			cout << "Starting New Game...\n\n";
			selection = rand() % 6;
			selectedWord = words.at(selection);
			guessed = selectedWord;
			availableLetters = alphabet;
			wordLength = selectedWord.length();
			numberOfGuesses = GUESSES;
			validInput = 0;
			 for(i = 0; i < wordLength; i++){
				guessed[i] = '-' ;
            }
			cout << "The word has "<< wordLength << " letters\n";
		}
		else{
			cout << "Exiting...\n";
			break;
		}
    }
    return 0;
}