#include <thread>
#include <ctime>
#include <list>
#include "word_game.h"
#include "high_score.h"


int main(const int argc, const char ** argv) {
  std::string DICTIONARY = "../resources/dictionaries/DEFAULT_DICTIONARY.txt";
  std::string HIGH_SCORES = "../resources/scores/high_scores.txt";
  int NUMBER_LETTERS = 7;
  int game_time = 60;
  int num_scores = 5;

  if( argc >= 2 )
  {
    std::string param1 = argv[1];
    if(param1.find("help") != std::string::npos)
    {
      std::cerr << "./Word_Game  dictionary  high_scores  number_letters  game_time num_scores" << std::endl;
      exit(1);
    }
  }

  if( argc >= 6 )
    num_scores = std::stoi(argv[5]);
  if( argc >= 5 )
    game_time = std::stoi(argv[4]);
  if( argc >= 4 ) 
    NUMBER_LETTERS = std::stoi(argv[3]);
  if( argc >= 3 )
    HIGH_SCORES = argv[2];
  if( argc >= 2 )
    DICTIONARY = argv[1];

//==============================================================================
  WordGame myGame( DICTIONARY, NUMBER_LETTERS );
  HighScore myScores( num_scores, HIGH_SCORES );
  std::list<std::string> ALL_ANSWERS;
  int MAX_POSSIBLE_SCORE; 

  const time_t START_TIME = time(NULL);
  std::thread thread1(WordGame::getMaxPossibleScore, std::cref(myGame), std::ref(ALL_ANSWERS), std::ref(MAX_POSSIBLE_SCORE));

  int roundCounter = 0;
  while(game_time >= time(NULL) - START_TIME)
  {
    if(roundCounter % 5 == 0)
      std::cout << myGame.letters() << std::endl;
    std::cout << "Your input: ";
    myGame.playRound();
  }


  std::string userName;
  std::cout << "Your name: ";
  getline(std::cin,userName);
  myScores.newScore(userName,myGame.score());


  thread1.join();
  std::cout << time(NULL) - START_TIME << std::endl;
  for(const std::string& iter : ALL_ANSWERS)
    std::cout << iter << std::endl;

  std::cout << std::endl << myScores << std::endl;


  return 0;
}
