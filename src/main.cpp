#include <iostream>
#include <fstream>

#include "dictionary_tree.h"
#include "word_game.h"


int main() {
  try {
  Dictionary dict("error");
  }
  catch( const std::exception& e ) {
    std::cout << "Exception: " << e.what() << std::endl;
  }

  std::string test = "abc";
  std::set<std::string>  myset = WordGame::everyWordCombination(test);

  for(std::string cur : myset)
    std::cout << cur << std::endl;


    return 0;
}
