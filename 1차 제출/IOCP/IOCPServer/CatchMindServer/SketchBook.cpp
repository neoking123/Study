#include "SketchBook.h"

SketchBook* SketchBook::instance = nullptr;

SketchBook::SketchBook()
{
}


SketchBook::~SketchBook()
{
}

void SketchBook::DrawToSketchBook(BRUSH_DATA* brushData)
{
	mouseTrack.push_back(brushData);
}
