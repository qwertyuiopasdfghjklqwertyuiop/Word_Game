#include "./Includes/high_score.h"

HighScore::HighScore( int num_to_track, std::string location ): numToTrack_(num_to_track), 
                                                               managedFile_(location)
{
  std::ifstream iStream(location);
  this->load_scores(iStream);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

HighScore::~HighScore()
{
  std::ofstream oStream(this->managedFile_);
  this->write_scores(oStream);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool HighScore::newScore(const std::string& name, const int& score)
{
  if( this->getLowestScore() > score )
    return false;
  
  this->scores_.insert( std::pair<int,std::string>(score,name) );
  return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int HighScore::getLowestScore() const
{
  std::multimap< int, std::string >::const_iterator iter = this->scores_.cend();
  int counter = this->scores_.size();

  for( ; iter != this->scores_.cbegin() && counter > 0; counter--,iter-- )
    ;

  if( counter == 0 ) return 0;
  return iter->first;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void HighScore::load_scores(std::ifstream& iStream)
{
  // File Does Not Exist 
  if( !iStream.is_open())
    for(int k = 0; k < this->numToTrack_; k++)
      this->scores_.insert( std::pair<int,std::string>(0,"NULL") );

  // Load in file
  try
  {
    while(iStream)
    {
      std::string buffer;
      int pointBuffer;
      std::string nameBuffer; 
      for(int k = 0; k < 2; k++)
      {
        getline(iStream, buffer);
        if(!iStream) goto HighScore__load_scores__FILL_IN; // escape once file is done
        if(k==0)
          nameBuffer = buffer;
        else
          pointBuffer = std::stoi(buffer);
      }
      this->scores_.insert( std::pair<int,std::string>(pointBuffer,nameBuffer) );
    }
  }
  catch(...)
  {
    throw INVALID_HIGH_SCORE_FILE();
  }


  HighScore__load_scores__FILL_IN:
  // Fill in remaining space
  while(this->scores_.size() < this->numToTrack_)
    this->scores_.insert( std::pair<int,std::string>(0,"NULL") );
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void HighScore::write_scores(std::ofstream& oStream)
{
  std::multimap<int,std::string>::const_iterator iter = this->scores_.cbegin();
  for( ; iter != this->scores_.cend() && iter->first > 0; iter++ )
    oStream << iter->second << '\n' << iter->first << '\n';
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

std::ostream& operator<<(std::ostream& out, HighScore& hScore)
{
  std::multimap<int,std::string>::const_iterator iter = hScore.scores_.cbegin();

  for(int k = 0; k < hScore.numToTrack_ && iter != hScore.scores_.cend() ;k++, iter++)
  {
    int scoreLength = 1;
    for(int score = iter->first; score >= 10; score /= 10)
      scoreLength++;

    for(int i = 0; i < HighScore::LINE_PRINT_LENGTH; i++)
    {
      if(i < HighScore::NAME_MAX_PRINT_LENGTH && i < iter->second.length())
        out << iter->second[i];
      else if(scoreLength == HighScore::LINE_PRINT_LENGTH - i)
      {
        out << iter->first << '\n';
        break;
      }
      else
        out << ' ';
    }
  }
  return out;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int HighScore::LINE_PRINT_LENGTH = 24;
int HighScore::NAME_MAX_PRINT_LENGTH = 12;
