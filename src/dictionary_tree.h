#ifndef _dictionary_tree_h
#define _dictionary_tree_h

#include <fstream>
#include <memory>

class Dictionary {
 
private:
  // Sub Classes
//==============================================================================
  class LetterNode {
  private:
  // Members
    std::unique_ptr<LetterNode> children_[26];
    bool isWord_;

  // Mutators
    bool newLetter( char letter, bool word = false );
    void setIsWord( bool word ) { this->isWord_= word; }

  // Constructors
    LetterNode( bool word = false ) : isWord_(word) { }

  // Acessors
    bool isWord() { return this->isWord_; }
    LetterNode* getNextLetter( char letter );

  // Helper
    static bool isValidLetter( char letter);

    friend Dictionary;
  };
//==============================================================================

private:
  // Members
  std::unique_ptr<LetterNode> root_;

  // Constructor
  Dictionary(std::string dictionary);

  // Accessors
  bool isWord( std::string word );

  // Mutators
  void load_dictionary( std::ifstream& dict_stream );
  bool addWord( std::string word );

  // Exceptions
  struct invalid_word {
    const char * what() { return "INVALID_WORD"; }
  };

  struct no_dict_stream {
    const char * what() { return "COULD_NOT_OPEN_DICTIONARY_STREAM"; }
  };
};


#endif
