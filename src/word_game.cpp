#include "word_game.h"

WordGame::WordGame( std::string dictionary, int letSize ) : dict_(dictionary), score_(0)
{
  this->letters_ = genRandomString(letSize);
}

int WordGame::playRound()
{
}

int submitWord(std::string submission)
{
}

std::set<std::string> WordGame::everyWordCombination(std::string letters)
{
  std::set<std::string> myset;

  if(letters.length() == 1)
    myset.insert(letters);
  else
  {
    for( int k = 0; k < letters.length(); k++ )
    {
      std::string before = letters.substr(0,k);
      std::string after = letters.substr(k+1);
      std::string remaining = before+after;

      for(std::string permutation : everyWordCombination(remaining))
      {
        myset.insert( letters[k] + permutation );
      }
    }
  }

  return myset;
}

void WordGame::getMaxPossibleScore(const WordGame& game, std::vector<std::string>& correct_answers, int& x)
{
  WordGame perfect_game(game);
  correct_answers.clear();
  x = 0;
  
  for(std::string iter : WordGame::everyWordCombination(perfect_game.letters_))
    if(perfect_game.dict_.isWord(iter))
      x += perfect_game.submitWord(iter);
}

std::string genRandomString(int size)
{
}
