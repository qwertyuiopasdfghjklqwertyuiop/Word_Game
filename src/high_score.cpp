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
  if( this->names_.size() != this->points_.size() )
    throw NUMBER_NAMES_AND_POINTS_NOT_EQUAL();
  std::ofstream oStream(this->managedFile_);
  this->write_scores(oStream);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool HighScore::newScore(const std::string& name, const int& score)
{
  typename std::list<std::string>::iterator nameIter = this->names_.begin();
  typename std::list<int>::iterator scoreIter = this->points_.begin();

  for( ; nameIter != this->names_.end() && scoreIter != this->points_.end() ;
        scoreIter++, nameIter++)
  {
    if( score >= *scoreIter )
    {
      this->names_.insert(nameIter,name);
      this->points_.insert(scoreIter,score);
      return true;
    }
  }
  return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int HighScore::getLowestScore()
{
  std::list<int>::iterator scoreIter = this->points_.begin();
  for(int k = 0; scoreIter != this->points_.end() && k < numToTrack_; scoreIter++, k++)
    ;
  return *scoreIter;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void HighScore::load_scores(std::ifstream& iStream)
{
  if( !iStream.is_open()) // File Does Not Exist 
    for(int k = 0; k < this->numToTrack_; k++)
    {
      this->names_.push_back("NULL");
      this->points_.push_back(0);
    }

  // Load in file
  try
  {
    int counter = 0;
    while(iStream)
    {
      std::string buffer; 
      getline(iStream, buffer);
      if(iStream)
      {
        if( counter % 2 == 0 )
          this->names_.push_back(buffer);
        else
          this->points_.push_back(std::stoi( buffer ));
      }
      counter++;
    }
  }
  catch(...)
  {
    throw INVALID_HIGH_SCORE_FILE();
  }


  // Fill in remaining space
  while(this->names_.size() < this->numToTrack_ && this->points_.size() <this->numToTrack_)
  {
    this->names_.push_back("NULL");
    this->points_.push_back(0);
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void HighScore::write_scores(std::ofstream& oStream)
{
  std::list<std::string>::iterator nameIter = this->names_.begin();
  std::list<int>::iterator scoreIter = this->points_.begin();

  // "*scoreIter > 0" condition is to prevent a bunch of NULLS being written to file
  for( ; nameIter != this->names_.end() && scoreIter != this->points_.end() && *scoreIter > 0; nameIter++, scoreIter++ )
    oStream << *nameIter << '\n' << *scoreIter << '\n';
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

std::ostream& operator<<(std::ostream& out, HighScore& hScore)
{
  const int LINE_LENGTH = 24;
  const int NAME_MAX_LENGTH = 12;

  typename std::list<std::string>::iterator nameIter = hScore.names_.begin();
  typename std::list<int>::iterator scoreIter = hScore.points_.begin();

  for( int i = 0; i < hScore.numToTrack_; i++, nameIter++, scoreIter++ )
  {
    int nameLength = nameIter->length();
    int scoreLength=1;
    for(int score = *scoreIter; score >= 10; score /= 10, scoreLength++){;}

    for (int k = 0; k < LINE_LENGTH; k++)
    {
      if(k < NAME_MAX_LENGTH && k < nameLength) 
        out << (*nameIter)[k];
      else if( k == LINE_LENGTH - scoreLength )
      {
        out << *scoreIter << '\n';
        break;
      }
      else
        out << ' ';
    }
  }

  return out;
}

