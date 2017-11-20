#ifndef _word_game_h
#define _word_game_h

#include <vector>
#include "dictionary_tree.h"

class WordGame {
  // Members
private:
  int score_;
  std::string letters_;
  Dictionary dict_;

  // Constructors
public:
  WordGame( std::string dictionary = "" );

  // Methods
public:
  int playRound();
private:
  int submitWord(std::string submission);

  // Accessors
public:
  int score() { return this->score_; }
  std::string letters() { return this->letters_; }

  // Helpers
public:
  static void everyWordCombination(std::string& letters, std::vector<std::string>& combinations);
  static void getMaxPossibleScore(WordGame& game, std::vector<std::string>& correct_answers, int& x);
  static int getMaxPossibleScore(WordGame& game, std::vector<std::string>& correct_answers);

  
};



#endif

