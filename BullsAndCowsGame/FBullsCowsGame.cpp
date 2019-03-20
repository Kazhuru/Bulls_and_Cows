#pragma once
#include "FBullsCowsGame.h"

FBullsCowsGame::FBullsCowsGame() { ResetGame(); }
FBullsCowsGame::~FBullsCowsGame() {}

void FBullsCowsGame::ResetGame()
{
	const FString MISTERY_WORD = "planet";

	CurrentTry = 1;
	HiddenWord = MISTERY_WORD;
	bGameWon = false;
	return;
}

EWordStatus FBullsCowsGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
		return EWordStatus::Not_Isogram;
	else if (!IsLowercase(Guess))
		return EWordStatus::Not_Lowercase;
	else if (Guess.length() != GetHiddenWorldLen())
		return EWordStatus::Wrong_Length;
	else
		return EWordStatus::OK;	
}

//recieves a Valid guess, then increments
FBullCowCount FBullsCowsGame::SubmitValidGuess(FString Guess)
{
	CurrentTry++;
	FBullCowCount SubmitBCounter;
	int32 HiddenWordLen = GetHiddenWorldLen();
	//loop through all letters in the hidden word
	for (int32 GChar = 0; GChar < HiddenWordLen; GChar++)
	{
		if (Guess[GChar] == HiddenWord[GChar])
			SubmitBCounter.Bulls++;
		else
			for (int32 HWChar = 0; HWChar < HiddenWordLen; HWChar++)
				if (Guess[GChar] == HiddenWord[HWChar])
				{
					SubmitBCounter.Cows++;
					HWChar = HiddenWordLen;
				}
	}
	if (SubmitBCounter.Bulls == HiddenWordLen)
		bGameWon = true;
	else
		bGameWon = false;
		
	return SubmitBCounter;
}

bool FBullsCowsGame::IsIsogram(FString Guess) const
{
	//Isograms of 1 or 0 letters its true
	if (Guess.length() <= 1)
		return true;
	TMap <char,bool> LetterSeen;
	for (auto Letter : Guess) //iterator for all the letters of the word
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) //Init with false the Letter of the map
			return false;
		else
			LetterSeen[Letter] = true;
	}
	return true;
}

bool FBullsCowsGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (islower(Letter) || Letter == '\0'){}
		else
			return false;
	}
	return true;
}

int32 FBullsCowsGame::GetMaxTry()  
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, { 4,7 }, { 5,10 }, { 6,15 }, { 7,20 } };
	return WordLengthToMaxTries[HiddenWord.length()];
}

bool FBullsCowsGame::IsGameWon() const { return bGameWon; }
int32 FBullsCowsGame::GetCurrentTry() const { return CurrentTry; }
int32 FBullsCowsGame::GetHiddenWorldLen() const { return HiddenWord.length(); }


