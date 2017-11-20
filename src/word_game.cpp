#include "word_game.h"

WordGame::WordGame( std::string dictionary )
{
}

int WordGame::playRound()
{
}

int submitWord(std::string submission)
{
}

void WordGame::everyWordCombination(std::string& letters, std::vector<std::string>& combinations)
{
}

void WordGame::getMaxPossibleScore(WordGame& game, std::vector<std::string>& correct_answers, int& x)
{
}

int WordGame::getMaxPossibleScore(WordGame& game, std::vector<std::string>& correct_answers)
{
  std::string letters = game.letters();
  std::vector<std::string> combinations; 
  combinations.push_back("");

  for(int i = 0; i < letters.length(); i++)
  {
    int vecSize = combinations.size();
    for(int k = 0; k < vecSize; k++)
    {
    }
  }
}
