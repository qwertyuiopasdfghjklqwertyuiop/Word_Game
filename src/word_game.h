#ifndef _word_game_h
#define _word_game_h

#include <vector>
#include <set>
#include "dictionary_tree.h"

class WordGame {
  // Members
private:
  int score_;
  std::string letters_;
  Dictionary dict_;

  // Constructors
public:
  WordGame( std::string dictionary = "", int letSize = 5 );
  WordGame(const WordGame& copy) : score_(copy.score_),letters_(copy.letters_),dict_(copy.dict_) { };

  // Methods
public:
  int playRound();
private:
  int submitWord(std::string submission);

  // Accessors
public:
  int score() const { return this->score_; }
  std::string letters() const { return this->letters_; }

  // Helpers
public:
  static std::set<std::string> everyWordCombination(std::string letters);
  static void getMaxPossibleScore(const WordGame& game, std::vector<std::string>& correct_answers, int& x);
  static std::string genRandomString(int size);

  
};



#endif

