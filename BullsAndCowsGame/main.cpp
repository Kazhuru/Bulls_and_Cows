/*
This is the console executable, that makes use of the BullsCows class
this acts as the view in a MVC pattern, and is responsible for all 
user interaction. for game logic see the FBullsCowsGame class
*/
#include <iostream>
#include <string>
#include "FBullsCowsGame.h"

using FText = std::string;
using int32 = int;

//functions
void PrintIntro();
int32 main();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullsCowsGame BCGame;


//cons

int main()
{
	BCGame = FBullsCowsGame::FBullsCowsGame();
	//intro message
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());

	std::cout << "Press any key to skip";
	std::cin; return 0;
}

void PlayGame()
{
	BCGame.ResetGame();
	FText Guess = "";
	int32 MaxTries = BCGame.GetMaxTry();
	int32 CurrentTry = BCGame.GetCurrentTry();
	
	while (!BCGame.IsGameWon() && (CurrentTry <= MaxTries))
	{
		//get a guess from the player
		Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Your guess N #" << CurrentTry << " was: " << Guess << " \n";
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ", Cows = " << BullCowCount.Cows << "\n";
	}

	PrintGameSummary();
}

void PrintIntro() 
{
	int LenWord = BCGame.GetHiddenWorldLen();
	//Intro message
	std::cout << "\n\nWelcome to Bulls and Cows! \n";
	std::cout << "Can you guess the " << LenWord << " letter isogram i'm thinking of? \n";
	std::cout << std::endl;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "\nYAS! You win Bulls and Cows! \n";

	}
	else
	{
		std::cout << "\nToo bad! you run out of tries, try again. \n";
	}
}

FText GetValidGuess()
{
	EWordStatus status = EWordStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		//get the user guess
		
		std::cout << "Enter your #" << BCGame.GetCurrentTry() << " guess: \n";
		std::getline(std::cin, Guess);

		//check if is a valid guess
		status = BCGame.CheckGuessValidity(Guess);
		switch (status)
		{
		case EWordStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWorldLen() << " letter word. \n";
			break;
		case EWordStatus::Not_Isogram:
			std::cout << "Please enter word witout repeating letters. \n";
			break;
		case EWordStatus::Not_Lowercase:
			std::cout << "Please enter all lower case letters. \n";
			break;
		}
		std::cout << std::endl;
	} while (status != EWordStatus::OK);

	return Guess;

}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}
