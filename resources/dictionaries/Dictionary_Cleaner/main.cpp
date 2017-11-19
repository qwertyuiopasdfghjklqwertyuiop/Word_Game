#include <iostream>
#include <fstream>
#include <list>

bool isValidWord(const std::string& word);

int main(const int argc, const char ** argv) {
  if(argc != 3) { std::cerr << "./main INPUTFILE.txt OUTPUTFILE.txt" << std::endl; exit(1); }
  std::ifstream input(*(argv+1));
  std::ofstream output(*(argv+2));

  if(!input.is_open()) { std::cerr << "Could not open INPUTFILE" << std::endl; exit(2); }
  if(!output.is_open()) { std::cerr << "Could not open OUTPUTFILE" << std::endl; exit(3); }

  std::list<std::string> validWords;

  while(input)
  {
    std::string buffer;
    getline(input,buffer);
    if(input)
    {
      if(isValidWord(buffer))
        validWords.push_back(buffer);
    }
  }
  
  for(typename std::list<std::string>::iterator iter = validWords.begin() ; iter != validWords.end() ; iter++) 
  {
    output << *iter;
    if(iter != validWords.end()--)
      output << '\n';
  }
  
  return 0;
}

bool isValidWord( const std::string& word )
{
  for ( int k = 0; k < word.length(); k++ )
    if( !isalpha(word[k]) )
      return false;
  return true;
}
