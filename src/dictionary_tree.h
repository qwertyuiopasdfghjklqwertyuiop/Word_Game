#ifndef _dictionary_tree_h
#define _dictionary_tree_h
#include <memory>

class Dictionary {
 
private:
  // Sub Classes
//==============================================================================
  class LetterNode {
  private:
  // Members
    std::unique_ptr<LetterNode> children_[26];
    char letter_;
    bool isWord_;

  // Acessors
    bool isWord() { return this->isWord_; }

  };
//==============================================================================

private:
  // Members
  std::unique_ptr<LetterNode> root_;

  // Constructor
  Dictionary(std::string directory) : root_(new LetterNode) {
    
  }
};


#endif
