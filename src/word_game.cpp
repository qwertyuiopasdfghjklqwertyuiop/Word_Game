#include "./Includes/word_game.h"

WordGame::WordGame( std::string dictionary, int letSize ) : score_(0) , dict_(dictionary) 
{
  srand(time(NULL));
  this->letters_ = genRandomString(letSize);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void WordGame::playRound()
{
  std::string userInput;
  getline(std::cin, userInput);
  int points = getWordScore(userInput); 

  if(user_history_.isWord( userInput ))
  {
    std::cout << "You used that word already.  ";
    points *= -1/4;
  }
  else if( !this->dict_.isWord(userInput) )
  {
    std::cout << "That is not a word.  ";
    points *= -1/2;
  }
  else if( this->dict_.isWord(userInput) )
    std::cout << "You made a word!  ";
  else
    throw invalid_user_input();

  this->score_ += points;

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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
        myset.insert( permutation );
      }
    }
  }

  return myset;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void WordGame::getMaxPossibleScore(const WordGame& game, std::list<std::string>& correct_answers, int& x)
{
  correct_answers.clear();
  x = 0;
  
  for(const std::string& iter : WordGame::everyWordCombination(game.letters_))
    if(game.dict_.isWord(iter))
    {
      x += game.getWordScore(iter);
      correct_answers.push_back(iter);
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

std::string WordGame::genRandomString(int size)
{
  std::string retVal = "";

  for( int i=0 ; i < size/2; i++ )
    retVal += WordGame::vowels[ rand() % WordGame::vowels.length() ];
  for( int i=0; i < size; i++ )
    retVal += WordGame::consonants[ rand() % WordGame::consonants.length() ];

  for( int i=0; i < retVal.size(); i++ )
    std::swap( retVal[i], retVal[rand() % retVal.size()] );

  return retVal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int WordGame::getWordScore(std::string word)
{
  int score = 0;
  for(const char& let : word)
  {
    if( WordGame::vowels.find( let ) != std::string::npos )
      score += 1;
    else if ( WordGame::consonants.find( let ) != std::string::npos )
      score += 2;
    else
      throw invalid_word();
  }
  return score;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const std::string WordGame::vowels="aeiou";
const std::string WordGame::consonants="bcdfghjklmnpqrstvwxyz";
