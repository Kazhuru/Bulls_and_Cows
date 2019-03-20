#include "FBullsCowsGame.h"

FBullsCowsGame::FBullsCowsGame() 
{
	ResetGame();
}

FBullsCowsGame::~FBullsCowsGame() {}

void FBullsCowsGame::ResetGame()
{

	constexpr int32 NUMBER_OF_TUNRS = 8;
	const FString MISTERY_WORD = "planet";

	CurrentTry = 1;
	MaxTry = NUMBER_OF_TUNRS;
	HiddenWord = MISTERY_WORD;
	bGameWon = false;
	return;
}

EWordStatus FBullsCowsGame::CheckGuessValidity(FString Guess) const
{
	if (false)
	{
		return EWordStatus::Not_Isogram;
	}
	else if (false)
	{
		return EWordStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWorldLen())
	{
		return EWordStatus::Wrong_Length;
	}
	else
	{
		return EWordStatus::OK;
	}
	
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
	{
		bGameWon = true;
	}
	else
	{
		bGameWon = false;
	}
		
	return SubmitBCounter;
}

bool FBullsCowsGame::IsGameWon() const { return bGameWon; }

int32 FBullsCowsGame::GetCurrentTry() const { return CurrentTry; }

int32 FBullsCowsGame::GetMaxTry() const { return MaxTry; }

int32 FBullsCowsGame::GetHiddenWorldLen() const { return HiddenWord.length(); }
