#include "PatronColor.h"

PatronColor::PatronColor(int r, int g, int b) {
	brush = CreateSolidBrush(RGB(r, g, b)); 
}