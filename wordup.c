//Avner Mamauag
//Project 10
//5-6-25

#include <stdio.h>
#include <stdbool.h>

#define READ_FILENAME "mystery.txt"
#define WORD_LEN 6
#define NUM_GUESSES 6
#define STR_CAP 100

bool checkLength(char arr[]);
bool checkLetters(char arr[]);
void getGuess(int num, char input[]);
char makeLower(char letter);
char makeUpper(char letter);
void setAllLower(char str[]);
void compareAns(int num, const char ans[], char input[], char results[][WORD_LEN]);
bool checkWin(char ans[], char input[]);
void endgame(int num, char ans[]);

int main(){
	FILE* wordFilePtr;
	char word[WORD_LEN];
	
	wordFilePtr = fopen(READ_FILENAME, "r");
	if(wordFilePtr == NULL){
		printf("Cannot open file for reading.\n");
		return 1;
	}
	
	fscanf(wordFilePtr, "%s", word);
	fclose(wordFilePtr);
	
	char guess[STR_CAP], guessResults[NUM_GUESSES * 2][WORD_LEN];
	int guessCount = 1;
	bool victory = false;
	
	do{
		getGuess(guessCount, guess);
		printf("================================\n");
		compareAns(guessCount, word, guess, guessResults);
		victory = checkWin(word, guess);
		if(!victory){
			for(int rowInd = 0; rowInd < guessCount * 2; rowInd++){
				printf("%s\n", guessResults[rowInd]);
			}
			guessCount++;
		}
	}while(guessCount <= NUM_GUESSES && !victory);
	
	int finalResultIndex = (guessCount - 1) * 2;
	endgame(guessCount, guessResults[finalResultIndex]);
	
	return 0;
}

bool checkLength(char arr[]){
	bool invalidWord = false;
	int count;
	for(count = 0; arr[count] != '\0'; count++){}
	if(count != WORD_LEN - 1){
		invalidWord = true;
	}
	return invalidWord;
}

bool checkLetters(char arr[]){
	bool invalidWord = false;
	for(int i = 0; arr[i] != '\0'; i++){
		if(arr[i] < 'a' || arr[i] > 'z'){
			invalidWord = true;
		}
	}
	return invalidWord;
}

char makeLower(char letter){
	if(letter >= 'A' && letter <= 'Z'){
		letter += 32;
	}
	return letter;
}

char makeUpper(char letter){
	if(letter >= 'a' && letter <= 'z'){
		letter -= 32;
	}
	return letter;
}

void setAllLower(char str[]){
	for(int i = 0; str[i] != '\0'; i++){
		str[i] = makeLower(str[i]);
	}
}

void getGuess(int num, char input[]){
	bool wrongSize, notLetters;
	if(num == NUM_GUESSES){
		printf("FINAL GUESS: ");
	}
	else{
		printf("GUESS %d! Enter your guess: ", num);
	}
	scanf("%s", input);
	setAllLower(input);
	wrongSize = checkLength(input);
	notLetters = checkLetters(input);
	while(wrongSize || notLetters){
		if(wrongSize){
			printf("Your guess must be %d letters long.\n", WORD_LEN - 1);
		}
		if(notLetters){
			printf("Your guess must contain only letters.\n");
		}
		printf("Please try again: ");
		scanf("%s", input);
		setAllLower(input);
		wrongSize = checkLength(input);
		notLetters = checkLetters(input);
	}
	
}

void compareAns(int num, const char ans[], char input[], char results[][WORD_LEN]){
	int row = 2 * (num - 1);
	bool isYellow;		//like in Wordle - correct letter, wrong place
	bool isGreen;		//correct letter, correct place
	char letterBank[STR_CAP], greenBank[STR_CAP];
	int bankSize = 0, gBankSize = 0;
	bool inBank;
	for(int cInd = 0; input[cInd] != '\0'; cInd++){
		isYellow = false;
		isGreen = false;
		inBank = false;
		for(int ansInd = 0; ans[ansInd] != '\0'; ansInd++){
			if(input[cInd] == ans[ansInd]){
				isYellow = true;
			}
		}
		if(input[cInd] == ans[cInd]){
			isGreen = true;
		}
		for(int i = 0; i < bankSize; i++){
			if(letterBank[i] == input[cInd]){
				inBank = true;
			}
		}
		if(isYellow && !inBank){
			results[row + 1][cInd] = '^';
			letterBank[bankSize] = input[cInd];
			bankSize++;
		}
		else{
			results[row + 1][cInd] = ' ';
		}
		if(isGreen){
			results[row][cInd] = makeUpper(input[cInd]);
			greenBank[gBankSize] = input[cInd];
			gBankSize++;
		}
		else{
			results[row][cInd] = input[cInd];
		}
	}
	
	for(int cInd = 0; input[cInd] != '\0'; cInd++){
		for(int i = 0; i < gBankSize; i++){
			if(input[cInd] == greenBank[i]){
				results[row + 1][cInd] = ' ';
			}
		}
	}
}

bool checkWin(char ans[], char input[]){
	bool gg = true;
	for(int i = 0; input[i] != '\0'; i++){
		if(input[i] != ans[i]){
			gg = false;
		}
	}
	return gg;
}

void endgame(int num, char ans[]){
	switch(num){
		case 1:
			printf("\t\t%s\n", ans);
			printf("\tYou won in %d guess!\n", num);
			printf("\t\tGOATED!\n");
			break;
		case 2:
		case 3:
			printf("\t\t%s\n", ans);
			printf("\tYou won in %d guesses!\n", num);
			printf("\t\tAmazing!\n");
			break;
		case 4:
		case 5:
			printf("\t\t%s\n", ans);
			printf("\tYou won in %d guesses!\n", num);
			printf("\t\tNice!\n");
			break;
		case NUM_GUESSES + 1:
			printf("You lost, better luck next time!\n");
			break;
		default:
			printf("\t\t%s\n", ans);
			printf("\tYou won in %d guesses!\n", num);
			break;
	}
}
