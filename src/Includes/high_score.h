#ifndef _high_score_h
#define _high_score_h

#include <fstream>
#include <list>

class HighScore {
  // Members
private:
  std::list<std::string> names_;
  std::list<int> points_;
  int numToTrack_;
  std::string managedFile_;

  // Constructor
public:
  HighScore(int num_to_track, std::string location = "");
  ~HighScore() throw();

  // Mutators
  bool newScore(const std::string& name, const int& score);

  // Accessors
  int getLowestScore();

  // Helpers
private:
  void load_scores(std::ifstream& iStream);
  void write_scores(std::ofstream& oStream);

  // Operators
public:
  friend std::ostream& operator<<(std::ostream& out, HighScore& hScore);

  // Exceptions
public:
  struct UNABLE_TO_OPEN_OUTFILE : std::exception {
    const char * what() const noexcept { return "HighScore::UNABLE_TO_OPEN_OUTFILE"; }
  };
  struct INVALID_HIGH_SCORE_FILE : std::exception {
    const char *what() const noexcept { return "HighScore::INVALID_HIGH_SCORE_FILE"; }
  };
  struct NUMBER_NAMES_AND_POINTS_NOT_EQUAL : std::exception {
    const char *what() const noexcept { return "HighScore::NUMBER_NAMES_AND_POINTS_NOT_EQUAL"; }
  };

};

std::ostream& operator<<(std::ostream& out, HighScore& hScore);

#endif

