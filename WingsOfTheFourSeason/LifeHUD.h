#ifndef LIFEHUD_H
#define LIFEHUD_H

// Call only after iInitialize(), while the graphics context is active.
// The local static loads the shared feather texture once, on first draw.
inline void drawFeatherLives(int lifeCount)
{
	static char lifeIconPath[] = "Assets/Life.png";
	static unsigned int lifeIcon = iLoadImage(lifeIconPath);

	iSetColor(255, 255, 255);
	for (int i = 0; i < lifeCount; i++)
	{
		iShowImage(34 + i * 50, 600, 60, 40, lifeIcon);
	}
}

#endif
