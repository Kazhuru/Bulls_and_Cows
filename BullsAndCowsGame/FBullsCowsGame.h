#include <string>
using FString = std::string;
using int32 = int;

//two integers initialiced with zero
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
	int32 GetMaxTry() const;
	int32 GetHiddenWorldLen() const;
	EWordStatus CheckGuessValidity(FString) const;

	void ResetGame();
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 CurrentTry;
	int32 MaxTry;
	FString HiddenWord;
	bool bGameWon;
};
