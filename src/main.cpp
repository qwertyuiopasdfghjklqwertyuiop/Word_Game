#include "word_game.h"
#include "high_score.h"


int main(const int argc, const char ** argv) {
  const int NUMBER_LETTERS = 5;
  std::string DICTIONARY = "";
  if( argc == 2 ) 
    DICTIONARY = argv[1];

  WordGame(DICTIONARY, NUMBER_LETTERS);



  return 0;
}
