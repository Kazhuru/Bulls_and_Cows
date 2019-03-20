/*
This is the console executable, that makes use of the BullsCows class
this acts as the view in a MVC pattern, and is responsible for all 
user interaction. for game logic see the FBullsCowsGame class
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullsCowsGame.h"

//To make syntax unreal friendly
using FText = std::string;
using int32 = int;

//functions prototypes outside of the class
void PrintIntro();
int32 main();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

//instance of a new game 
FBullsCowsGame BCGame;

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

// plays a single game for a one player
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

		std::cout << "Your guess '" << Guess << "' has: \n";
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ", Cows = " << BullCowCount.Cows << "\n";
		std::cout << std::endl;
	}
	PrintGameSummary();
}

void PrintIntro() 
{
	int LenWord = BCGame.GetHiddenWorldLen();
	//Intro message

	std::cout << "\n\nWelcome to Bulls and Cows!! \n\n";
	std::cout <<"	((_,...,_))		((...)) \n";
	std::cout <<"	  | o o |		( O O ) \n";
	std::cout <<"	   \\   /		 \\   /\n";
	std::cout <<"	   (^_^)		 (`_`)	\n\n";
	std::cout << "Can you guess the " << LenWord << " letter isogram i'm thinking of? \n";
	std::cout << std::endl;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())

		std::cout << "\nYAS! You win Bulls and Cows! \n";
	else
		std::cout << "\nToo bad! you run out of tries, try again. \n";
}

FText GetValidGuess()
{
	EWordStatus status = EWordStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		//get the user guess
		std::cout << std::endl;
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTry();
		std::cout << ". Enter your guess:  ";
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
	} while (status != EWordStatus::OK);

	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Better luck next time ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}
