/* The game logistic
The game is a simple guess the 
word based on a Mastermind
*/
#pragma once
#include <string>
#include <map>

//To make syntax unreal friendly
#define TMap std::map
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullsCowsGame
{
public:
	FBullsCowsGame();
	~FBullsCowsGame();

	bool IsGameWon() const;
	int32 GetCurrentTry() const;
	int32 GetMaxTry();
	int32 GetHiddenWorldLen() const;
	EWordStatus CheckGuessValidity(FString) const;

	void ResetGame();
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 CurrentTry;
	FString HiddenWord;
	bool bGameWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
