#include "Word.h"

Word::Word()
{
}

Word::Word(std::string* _word, int _x, int _y)
{
	word = *_word;
	position.x = _x;
	position.y = _y;
}


Word::~Word()
{
}

string * Word::GetWord()
{
	return &word;
}
