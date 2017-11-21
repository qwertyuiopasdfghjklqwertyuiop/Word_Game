#include "./Includes/word_game.h"
#include "./Includes/high_score.h"


int main(const int argc, const char ** argv) {
  const int NUMBER_LETTERS = 5;
  std::string DICTIONARY = "";
  if( argc == 2 ) 
    DICTIONARY = argv[1];

  WordGame(DICTIONARY, NUMBER_LETTERS);

  HighScore myScores(10, "../resources/scores.txt");
  myScores.newScore("jamaal",40);
  myScores.newScore("jose",20);
  myScores.newScore("john",12);
  std::cout << myScores << std::endl;




  return 0;
}
