#ifndef _high_score_h
#define _high_score_h

#include <fstream>
#include <map>

class HighScore {
  // Compare function
private:
  struct compare { 
    bool operator()( const int& x, const int& y ) { return y<x; }
  };

  // Members
private:
  std::multimap<int,std::string,HighScore::compare> scores_;
  int numToTrack_;
  std::string managedFile_;

  // Static variables
private:
  static int LINE_PRINT_LENGTH;
  static int NAME_MAX_PRINT_LENGTH;

  // Constructor
public:
  HighScore(int num_to_track, std::string location = "");
  ~HighScore();

  // Mutators
public:
  bool newScore(const std::string& name, const int& score);
  static void SET_LINE_PRINT_LENGTH(int x) { LINE_PRINT_LENGTH = x; }
  static void SET_NAME_MAX_PRINT_LENGTH(int x) { NAME_MAX_PRINT_LENGTH = x;}

  // Accessors
public:
  int getLowestScore() const;

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

#endif

