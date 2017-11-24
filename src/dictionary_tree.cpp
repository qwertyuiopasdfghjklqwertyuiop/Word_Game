#include "dictionary_tree.h"

bool Dictionary::LetterNode::newLetter( char letter, bool word )
{
  if ( this->children_[ toupper(letter) - 'A' ] != NULL )
      return false;

  (this->children_[ toupper(letter) - 'A' ]).reset( new LetterNode( word ) );
  return true;

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

Dictionary::LetterNode* Dictionary::LetterNode::getNextLetter( char letter ) const
{
  return this->children_[ toupper(letter) - 'A' ].get();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool Dictionary::LetterNode::isValidLetter( char letter )
{
  return ( toupper(letter) < 'A' || toupper(letter) > 'Z' );
}

//==============================================================================

Dictionary::Dictionary(std::string dictionary )
{
  this->root_.reset( new LetterNode );

  std::ifstream dict_stream(dictionary);
  this->load_dictionary( dict_stream );
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool Dictionary::isWord( std::string word ) const
{
  Dictionary::LetterNode* letter = this->root_.get();
  for(int i = 0; i < word.length(); i++)
  {
    if( !isalpha(word[i]))
      return false;
    if( !letter )
      return false;

    letter = letter->getNextLetter( word[i] );
  }
  if(!letter)
    return false;
  return letter->isWord();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void Dictionary::load_dictionary( std::ifstream& dict_stream )
{
  if(!dict_stream.is_open())
    throw Dictionary::no_dict_stream();

  std::string buffer;
  while(dict_stream)
  {
    getline( dict_stream, buffer );
    if( dict_stream )
      if( !this->addWord(buffer) )
          throw Dictionary::invalid_word();
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool Dictionary::addWord( std::string word )
{
  for( int i = 0; i < word.length(); i++ )
    if( !isalpha(word[i]) )
      return false;

  LetterNode* letter = this->root_.get();
  for( int i = 0; i < word.length(); i++ )
  {
    letter->newLetter( word[i] );
    letter = letter->getNextLetter( word[i] );
  }
  letter->setIsWord( true );

  return true;
}
