#ifndef _word_game_h
#define _word_game_h

#include <iostream>
#include <list>
#include <set>
#include "dictionary_tree.h"

class WordGame {
  // Members
private:
  int score_;
  std::string letters_;
  Dictionary dict_;
  Dictionary user_history_;

  // Static variables
private:
  static const std::string vowels;
  static const std::string consonants;

  // Constructors
public:
  WordGame( std::string dictionary = "", int letSize = 5 );

  // Methods
public:
  void playRound();

  // Accessors
public:
  int score() const { return this->score_; }
  std::string letters() const { return this->letters_; }

  // Helpers
public:
  static void getMaxPossibleScore(const WordGame& game, std::list<std::string>& correct_answers, int& x);
private:
  static std::string genRandomString(int size);
  static std::set<std::string> everyWordCombination(std::string letters);
  static int getWordScore(std::string word);

  // Exceptions
  struct invalid_word : std::exception {
    const char * what() const noexcept { return "WordGame::INVALID_WORD"; }
  };
  struct invalid_user_input : std::exception {
    const char * what() const noexcept { return "WordGame::INVALID_USER_INPUT"; }
  };

  
};
#endif
  
