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
    bool isWord() const { return this->isWord_; }
    LetterNode* getNextLetter( char letter ) const;

  // Helper
    static bool isValidLetter( char letter);

    friend Dictionary;
  };
//==============================================================================

  // Members
private:
  std::unique_ptr<LetterNode> root_;

  // Constructor
public:
  Dictionary( std::string dictionary = "");
  Dictionary( const Dictionary& copy );

  // Accessors
  bool isWord( std::string word ) const;

  // Mutators
  bool addWord( std::string word );
  void load_dictionary( std::ifstream& dict_stream );

  // Exceptions
public:
  struct invalid_word : std::exception {
    const char * what() const noexcept { return "INVALID_WORD"; }
  };

  struct no_dict_stream : std::exception {
    const char * what() const noexcept { return "COULD_NOT_OPEN_DICTIONARY_STREAM"; }
  };
};


#endif
