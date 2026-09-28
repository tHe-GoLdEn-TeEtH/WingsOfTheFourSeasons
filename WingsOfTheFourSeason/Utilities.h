#ifndef UTILITIES_H
#define UTILITIES_H

// Draws a rounded rectangle by combining a center rectangle with rounded corner circles
void drawRoundedRect(int x, int y, int width, int height, int radius)
{
	// Center cross - covers the middle in both directions
	iFilledRectangle(x + radius, y, width - (2 * radius), height);
	iFilledRectangle(x, y + radius, width, height - (2 * radius));

	// Four rounded corners
	iFilledCircle(x + radius, y + radius, radius);
	iFilledCircle(x + width - radius, y + radius, radius);
	iFilledCircle(x + radius, y + height - radius, radius);
	iFilledCircle(x + width - radius, y + height - radius, radius);
}

// Draws text with a soft glow behind it - just the same text drawn slightly offset in a dim color first
void drawGlowingText(int x, int y, char text[], int glowR, int glowG, int glowB, int mainR, int mainG, int mainB, void* font = GLUT_BITMAP_8_BY_13)
{
	iSetColor(glowR, glowG, glowB);
	iText(x - 1, y - 1, text, font);
	iText(x + 1, y - 1, text, font);
	iText(x - 1, y + 1, text, font);
	iText(x + 1, y + 1, text, font);

	iSetColor(mainR, mainG, mainB);
	iText(x, y, text, font);
}

#endif