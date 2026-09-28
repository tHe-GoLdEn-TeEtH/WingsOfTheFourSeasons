#ifndef STORY_H
#define STORY_H
#include "Utilities.h"

const int SLIDE_COUNT = 8;
unsigned int slideTextures[SLIDE_COUNT];
char slideText[SLIDE_COUNT][300];

int currentSlideIndex = 0;
int previousSlideIndex = 0;
int slideState = 1;   // 0 = crossfade transitioning in, 1 = display (static)
float slideAlpha = 1.0f;
int slideDisplayTimer = 0;

const int SLIDE_TRANSITION_FRAMES = 60;   // 1 second crossfade
const int SLIDE_DISPLAY_FRAMES = 240;     // 4 seconds fully visible

void loadStorySlides()
{
	slideTextures[0] = iLoadImage("Assets/Slides/1.png");
	slideTextures[1] = iLoadImage("Assets/Slides/2.png");
	slideTextures[2] = iLoadImage("Assets/Slides/3.png");
	slideTextures[3] = iLoadImage("Assets/Slides/4.png");
	slideTextures[4] = iLoadImage("Assets/Slides/5.png");
	slideTextures[5] = iLoadImage("Assets/Slides/6.png");
	slideTextures[6] = iLoadImage("Assets/Slides/7.png");
	slideTextures[7] = iLoadImage("Assets/Slides/8.png");

	strcpy_s(slideText[0], "In a world where the seasons once turned in harmony, balance has been lost.");
	strcpy_s(slideText[1], "Aero, a blue macaw, is one of the last of his kind, watching his home grow cold and still.");
	strcpy_s(slideText[2], "Winter has taken hold, its ice spreading further than it ever should.");
	strcpy_s(slideText[3], "Aero sets out carrying Seeds of Hope, the only thing that can restore what has been frozen.");
	strcpy_s(slideText[4], "As Winter thaws, the rains of Monsoon arrive, swelling the rivers and awakening old dangers.");
	strcpy_s(slideText[5], "Through storms and struggle, life begins to return, season by season.");
	strcpy_s(slideText[6], "Summer's heat tests Aero's endurance, but the promise of Spring keeps him flying forward.");
	strcpy_s(slideText[7], "Now, the journey begins. Aero must restore all four seasons before it's too late.");
}

void resetStory()
{
	currentSlideIndex = 0;
	previousSlideIndex = 0;
	slideState = 1;
	slideAlpha = 1.0f;
	slideDisplayTimer = 0;
}

void updateStory()
{
	bool isLastSlide = (currentSlideIndex == SLIDE_COUNT - 1);

	if (slideState == 0)
	{
		// Crossfading from previousSlideIndex into currentSlideIndex
		slideAlpha += 1.0f / SLIDE_TRANSITION_FRAMES;
		if (slideAlpha >= 1.0f)
		{
			slideAlpha = 1.0f;
			slideState = 1;
			slideDisplayTimer = 0;
		}
	}
	else if (slideState == 1)
	{
		if (isLastSlide)
		{
			// Final slide waits for Enter instead of auto-advancing
			if (isKeyPressed(13))
			{
				gameState = 1;
				resetLevel1();
			}
		}
		else
		{
			slideDisplayTimer++;
			if (slideDisplayTimer >= SLIDE_DISPLAY_FRAMES)
			{
				previousSlideIndex = currentSlideIndex;
				currentSlideIndex++;
				slideState = 0;
				slideAlpha = 0.0f;
			}
		}
	}
}

void drawFadingText(int x, int y, char text[], float alpha, void* font)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(20 / 255.0f, 15 / 255.0f, 10 / 255.0f, alpha);
	iText(x - 1, y - 1, text, font);
	iText(x + 1, y - 1, text, font);
	iText(x - 1, y + 1, text, font);
	iText(x + 1, y + 1, text, font);

	glColor4f(1.0f, 1.0f, 1.0f, alpha);
	iText(x, y, text, font);

	glDisable(GL_BLEND);
}

void drawStory()
{
	// Black letterbox background, so the slightly zoomed-out image has a clean border
	iSetColor(0, 0, 0);
	iFilledRectangle(0, 0, 1280, 720);

	int imgW = 1280;
	int imgH = 720;
	int imgX = 0;
	int imgY = 0;

	if (slideState == 0)
	{
		iShowImage(imgX, imgY, imgW, imgH, slideTextures[previousSlideIndex]);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0f, 1.0f, 1.0f, slideAlpha);
		iShowImage(imgX, imgY, imgW, imgH, slideTextures[currentSlideIndex]);
		glDisable(GL_BLEND);
	}
	else
	{
		iShowImage(imgX, imgY, imgW, imgH, slideTextures[currentSlideIndex]);
	}

	// Text box - translucent rounded panel, fades in together with the slide
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float boxPulse = 0.55f + (sinf(currentSlideIndex + (float)slideDisplayTimer * 0.03f) * 0.05f);
	glColor4f(0.08f, 0.08f, 0.12f, boxPulse * slideAlpha);
	drawRoundedRect(90, 40, 1100, 180, 20);

	glDisable(GL_BLEND);

	// Story text, centered both horizontally and vertically, fading in with slideAlpha
	char* text = slideText[currentSlideIndex];
	int len = (int)strlen(text);
	int lineLen = 45;
	int lineSpacing = 38;

	int lineCount = 1;
	int charIdx = 0;
	for (int i = 0; i <= len; i++)
	{
		if (charIdx >= lineLen && (text[i] == ' ' || text[i] == '\0'))
		{
			lineCount++;
			charIdx = 0;
		}
		else
		{
			charIdx++;
		}
	}

	int boxCenterY = 130;
	int yPos = boxCenterY + (((lineCount - 1) * lineSpacing) / 2);

	char buffer[100];
	int lineStart = 0;
	charIdx = 0;

	for (int i = 0; i <= len; i++)
	{
		if (charIdx >= lineLen && (text[i] == ' ' || text[i] == '\0'))
		{
			strncpy_s(buffer, sizeof(buffer), text + lineStart, charIdx);
			buffer[charIdx] = '\0';
			int lineCenterX = 640 - ((charIdx * 12) / 2);
			drawFadingText(lineCenterX, yPos, buffer, slideAlpha, GLUT_BITMAP_TIMES_ROMAN_24);
			yPos -= lineSpacing;
			lineStart = i + 1;
			charIdx = 0;
		}
		else
		{
			charIdx++;
		}
	}
	if (charIdx > 0)
	{
		strncpy_s(buffer, sizeof(buffer), text + lineStart, charIdx);
		buffer[charIdx] = '\0';
		int lineCenterX = 640 - ((charIdx * 12) / 2);
		drawFadingText(lineCenterX, yPos, buffer, slideAlpha, GLUT_BITMAP_TIMES_ROMAN_24);
	}

	// Hint on the final slide
	if (currentSlideIndex == SLIDE_COUNT - 1 && slideState == 1)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
		char pressEnter[] = "Press ENTER to begin";
		iText(510, 40, pressEnter, GLUT_BITMAP_HELVETICA_18);
		glDisable(GL_BLEND);
	}
}

// ============================================================================
// SEASON TRANSITION SLIDES (2 slides shown between levels)
// ============================================================================
const int TRANSITION_COUNT = 4;        // one set per season completed (Winter, Monsoon, Summer, Spring)
const int TRANSITION_SLIDE_COUNT = 2;  // 2 slides per transition

unsigned int transitionSlideTextures[TRANSITION_COUNT][TRANSITION_SLIDE_COUNT];
char transitionSlideText[TRANSITION_COUNT][TRANSITION_SLIDE_COUNT][300];

int transitionSetIndex = 0;
int transitionSlideIndex = 0;
int transitionPrevSlideIndex = 0;
int transitionSlideState = 1;
float transitionAlpha = 1.0f;
int transitionDisplayTimer = 0;
int transitionNextGameState = 0;   // which gameState to load once the transition finishes

void loadTransitionSlides()
{
	// After Level 1 (Winter) -> before Level 2 (Monsoon)
	transitionSlideTextures[0][0] = iLoadImage("Assets/Slides/W1.png");
	transitionSlideTextures[0][1] = iLoadImage("Assets/Slides/W2.png");
	strcpy_s(transitionSlideText[0][0], "The frost is broken. Nature takes its first breath again.");
	strcpy_s(transitionSlideText[0][1], "But the storm is coming. Aero must follow the waters into a new season.");

	// After Level 2 (Monsoon) -> before Level 3 (Summer)
	transitionSlideTextures[1][0] = iLoadImage("Assets/Slides/R1.png");
	transitionSlideTextures[1][1] = iLoadImage("Assets/Slides/R2.png");
	strcpy_s(transitionSlideText[1][0], "The waters flow freely again. Life returns with every drop.");
	strcpy_s(transitionSlideText[1][1], "The rain has passed. Now Aero must cross a land thirsty for life.");

	// After Level 3 (Summer) -> before Level 4 (Spring)
	transitionSlideTextures[2][0] = iLoadImage("Assets/Slides/S1.png");
	transitionSlideTextures[2][1] = iLoadImage("Assets/Slides/S2.png");
	strcpy_s(transitionSlideText[2][0], "The dry land drinks once more. Hope begins to bloom.");
	strcpy_s(transitionSlideText[2][1], "One season remains. Spring's hunters wait in the meadow, guarding the last piece of balance.");

	// After Level 4 (Spring) -> Game Complete screen
	transitionSlideTextures[3][0] = iLoadImage("Assets/Slides/Sp1.png");
	transitionSlideTextures[3][1] = iLoadImage("Assets/Slides/Sp2.png");
	strcpy_s(transitionSlideText[3][0], "Nature has awakened. The world is alive again..");
	strcpy_s(transitionSlideText[3][1], "Aero's journey is complete... but hope will always have wings.");
}

// Call this to begin a transition: setIndex 0-3 selects which season's slides to show,
// nextState is the gameState to load once the player presses Enter on the final slide
void startTransitionSlides(int setIndex, int nextState)
{
	transitionSetIndex = setIndex;
	transitionSlideIndex = 0;
	transitionPrevSlideIndex = 0;
	transitionSlideState = 1;
	transitionAlpha = 1.0f;
	transitionDisplayTimer = 0;
	transitionNextGameState = nextState;
	gameState = 11;
}

void resetGameCompleteScreen();

void updateTransitionSlides()
{
	bool isLastSlide = (transitionSlideIndex == TRANSITION_SLIDE_COUNT - 1);

	if (transitionSlideState == 0)
	{
		transitionAlpha += 1.0f / SLIDE_TRANSITION_FRAMES;
		if (transitionAlpha >= 1.0f)
		{
			transitionAlpha = 1.0f;
			transitionSlideState = 1;
			transitionDisplayTimer = 0;
		}
	}
	else if (transitionSlideState == 1)
	{
		if (isLastSlide)
		{
			if (isKeyPressed(13))
			{
				gameState = transitionNextGameState;

				if (transitionNextGameState == 2) { resetLevel2(); }
				else if (transitionNextGameState == 3) { resetLevel3(); }
				else if (transitionNextGameState == 4) { resetLevel4(); }
				else if (transitionNextGameState == 12)
				{
					resetGameCompleteScreen();
				}
			}
		}
		else
		{
			transitionDisplayTimer++;
			if (transitionDisplayTimer >= SLIDE_DISPLAY_FRAMES)
			{
				transitionPrevSlideIndex = transitionSlideIndex;
				transitionSlideIndex++;
				transitionSlideState = 0;
				transitionAlpha = 0.0f;
			}
		}
	}
}

void drawTransitionSlides()
{
	iSetColor(0, 0, 0);
	iFilledRectangle(0, 0, 1280, 720);

	int imgW = 1280;
	int imgH = 720;

	if (transitionSlideState == 0)
	{
		iShowImage(0, 0, imgW, imgH, transitionSlideTextures[transitionSetIndex][transitionPrevSlideIndex]);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0f, 1.0f, 1.0f, transitionAlpha);
		iShowImage(0, 0, imgW, imgH, transitionSlideTextures[transitionSetIndex][transitionSlideIndex]);
		glDisable(GL_BLEND);
	}
	else
	{
		iShowImage(0, 0, imgW, imgH, transitionSlideTextures[transitionSetIndex][transitionSlideIndex]);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float boxPulse = 0.55f + (sinf(transitionSlideIndex + (float)transitionDisplayTimer * 0.03f) * 0.05f);
	glColor4f(0.08f, 0.08f, 0.12f, boxPulse * transitionAlpha);
	drawRoundedRect(90, 40, 1100, 180, 20);

	glDisable(GL_BLEND);

	char* text = transitionSlideText[transitionSetIndex][transitionSlideIndex];
	int len = (int)strlen(text);
	int lineLen = 45;
	int lineSpacing = 38;

	int lineCount = 1;
	int charIdx = 0;
	for (int i = 0; i <= len; i++)
	{
		if (charIdx >= lineLen && (text[i] == ' ' || text[i] == '\0'))
		{
			lineCount++;
			charIdx = 0;
		}
		else
		{
			charIdx++;
		}
	}

	int boxCenterY = 130;
	int yPos = boxCenterY + (((lineCount - 1) * lineSpacing) / 2);

	char buffer[100];
	int lineStart = 0;
	charIdx = 0;

	for (int i = 0; i <= len; i++)
	{
		if (charIdx >= lineLen && (text[i] == ' ' || text[i] == '\0'))
		{
			strncpy_s(buffer, sizeof(buffer), text + lineStart, charIdx);
			buffer[charIdx] = '\0';
			int lineCenterX = 640 - ((charIdx * 12) / 2);
			drawFadingText(lineCenterX, yPos, buffer, transitionAlpha, GLUT_BITMAP_TIMES_ROMAN_24);
			yPos -= lineSpacing;
			lineStart = i + 1;
			charIdx = 0;
		}
		else
		{
			charIdx++;
		}
	}
	if (charIdx > 0)
	{
		strncpy_s(buffer, sizeof(buffer), text + lineStart, charIdx);
		buffer[charIdx] = '\0';
		int lineCenterX = 640 - ((charIdx * 12) / 2);
		drawFadingText(lineCenterX, yPos, buffer, transitionAlpha, GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if (transitionSlideIndex == TRANSITION_SLIDE_COUNT - 1 && transitionSlideState == 1)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
		char pressEnter[] = "Press ENTER to continue";
		iText(500, 40, pressEnter, GLUT_BITMAP_HELVETICA_18);
		glDisable(GL_BLEND);
	}
}

// ============================================================================
// GAME COMPLETE SUMMARY SCREEN (shown after the final transition slides)
// ============================================================================
float gameCompleteGlowTimer = 0.0f;

void resetGameCompleteScreen()
{
	gameCompleteGlowTimer = 0.0f;
}

void updateGameCompleteScreen()
{
	gameCompleteGlowTimer += 0.03f;

	if (isKeyPressed(13))
	{
		addLeaderboardEntry(currentPlayerName, totalGameSeconds);
		showingLeaderboard = true;
		gameState = 0;
		applyMusicSetting();
	}
}

void drawGameCompleteScreen()
{
	iSetColor(0, 0, 0);
	iFilledRectangle(0, 0, 1280, 720);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int px = 240, py = 220, pw = 800, ph = 340;

	for (int g = 3; g > 0; g--)
	{
		float pulse = 0.10f + (sinf(gameCompleteGlowTimer * 2.0f) * 0.04f);
		glColor4f(1.0f, 0.85f, 0.35f, pulse + g * 0.03f);
		drawRoundedRect(px - g * 3, py - g * 3, pw + g * 6, ph + g * 6, 22);
	}
	glColor4f(0.10f, 0.09f, 0.06f, 0.90f);
	drawRoundedRect(px, py, pw, ph, 18);

	glDisable(GL_BLEND);

	char title[] = "GAME COMPLETE!";
	int titleLen = (int)strlen(title);
	int titleCenterX = 640 - ((titleLen * 12) / 2);
	drawGlowingText(titleCenterX, py + ph - 70, title, 60, 40, 10, 255, 220, 90, GLUT_BITMAP_TIMES_ROMAN_24);

	char subtitle[] = "All Four Seasons Restored";
	int subLen = (int)strlen(subtitle);
	int subCenterX = 640 - ((subLen * 9) / 2);
	drawGlowingText(subCenterX, py + ph - 115, subtitle, 30, 25, 15, 255, 255, 255, GLUT_BITMAP_HELVETICA_18);

	char playerLine[60];
	sprintf_s(playerLine, "Player: %s", currentPlayerName);
	int playerLen = (int)strlen(playerLine);
	int playerCenterX = 640 - ((playerLen * 9) / 2);
	drawGlowingText(playerCenterX, py + ph - 175, playerLine, 20, 15, 10, 220, 235, 255, GLUT_BITMAP_HELVETICA_18);

	char timeLine[60];
	int minutes = totalGameSeconds / 60;
	int seconds = totalGameSeconds % 60;
	if (minutes > 0)
	{
		sprintf_s(timeLine, "Total Time: %dm %ds", minutes, seconds);
	}
	else
	{
		sprintf_s(timeLine, "Total Time: %ds", seconds);
	}
	int timeLen = (int)strlen(timeLine);
	int timeCenterX = 640 - ((timeLen * 9) / 2);
	drawGlowingText(timeCenterX, py + ph - 215, timeLine, 20, 15, 10, 220, 235, 255, GLUT_BITMAP_HELVETICA_18);

	char pressEnter[] = "Press ENTER to View Leaderboard";
	int peLen = (int)strlen(pressEnter);
	int peCenterX = 640 - ((peLen * 9) / 2);
	drawGlowingText(peCenterX, py + 40, pressEnter, 30, 18, 8, 255, 255, 255, GLUT_BITMAP_HELVETICA_18);
}

#endif