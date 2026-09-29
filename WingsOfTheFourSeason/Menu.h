#ifndef MENU_H
#define MENU_H
#include <math.h>
#include <string.h>
#include "Utilities.h"
#include "Leaderboard.h"

int selectedOption = 0;
const int MENU_OPTION_COUNT = 8;
char menuLabels[MENU_OPTION_COUNT][20] = { "NEW GAME", "CONTINUE", "SELECT LEVEL", "LEADER BOARD", "INSTRUCTIONS", "SETTINGS", "CREDITS", "EXIT" };


int menuFrameCounter = 0;
float buttonFloatOffset[MENU_OPTION_COUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };

bool showingSettings = false;
bool showingInstructions = false;
bool showingLeaderboard = false;
bool showingNameEntry = false;
bool showingNoSaveConfirm = false;
bool showingCredits = false;
bool showingLevelMenu = false;

char nameEntryBuffer[20] = "";
int nameEntryLength = 0;

int selectedConfirmOption = 0;

bool startGameClicked = false;
bool continueGameClicked = false;
bool levelSelectClicked = false;
int selectedLevelTarget = 1;

int selectedLevelOption = 0;
const int LEVEL_MENU_COUNT = 5;
char levelLabels[LEVEL_MENU_COUNT][25] = { "Level 01", "Level 02", "Level 03", "Level 04", "Back" };
int levelButtonY[LEVEL_MENU_COUNT] = { 430, 365, 300, 235, 170 };
float levelButtonFloat[LEVEL_MENU_COUNT] = { 0, 0, 0, 0, 0 };

int cursorBlinkCounter = 0;
bool cursorVisible = true;

unsigned int mainMenuBackground;
unsigned int instructionBackground;
unsigned int nameEntryFrameTex;

// Main menu button size/position (matches reference: 250x50)
const int MENU_BTN_X = 515;
const int MENU_BTN_WIDTH = 250;
const int MENU_BTN_HEIGHT = 50;
int menuButtonY[MENU_OPTION_COUNT] = { 449, 392, 335, 278, 221, 164, 107, 50 };

// Measured on-screen mouse Y bounds per button (confirmed via debug overlay,
// interpolated between New Game and Exit), used instead of menuButtonY math
// because the drawing coordinate system and mouse coordinate system don't
// line up 1:1 on the Y axis in this engine
int menuButtonMouseYMin[MENU_OPTION_COUNT] = { 478, 426, 374, 322, 271, 219, 167, 115 };
int menuButtonMouseYMax[MENU_OPTION_COUNT] = { 521, 469, 418, 366, 315, 263, 212, 160 };

// Level-select submenu buttons now match the main menu buttons exactly
const int LEVEL_BTN_X = MENU_BTN_X;
const int LEVEL_BTN_WIDTH = MENU_BTN_WIDTH;
const int LEVEL_BTN_HEIGHT = MENU_BTN_HEIGHT;
const int LEVEL_BTN_CORNER_RADIUS = 6;

void loadMainMenuBackground()
{
	mainMenuBackground = iLoadImage("Assets/menu.png");
	instructionBackground = iLoadImage("Assets/instructions.png");
	nameEntryFrameTex = iLoadImage("Assets/EnterName.png");
}

void drawMenu()
{
	iShowImage(0, 0, 1280, 720, mainMenuBackground);

	if (showingLevelMenu)
	{
		char levelMenuTitle[] = "SELECT LEVEL";
		int titleLen = (int)strlen(levelMenuTitle);
		int titleCenterX = 640 - ((titleLen * 9) / 2);
		drawGlowingText(titleCenterX, 500, levelMenuTitle, 40, 25, 10, 255, 230, 100);

		for (int i = 0; i < LEVEL_MENU_COUNT; i++)
		{
			int by = levelButtonY[i] + (int)levelButtonFloat[i];

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			if (i == selectedLevelOption)
			{
				glColor4f(1.0f, 0.9f, 0.4f, 0.30f);
				drawRoundedRect(LEVEL_BTN_X - 8, by - 6, LEVEL_BTN_WIDTH + 16, LEVEL_BTN_HEIGHT + 12, LEVEL_BTN_CORNER_RADIUS + 2);

				glColor4f(0.35f, 0.22f, 0.10f, 0.55f);
				drawRoundedRect(LEVEL_BTN_X, by, LEVEL_BTN_WIDTH, LEVEL_BTN_HEIGHT, LEVEL_BTN_CORNER_RADIUS);
			}
			else
			{
				glColor4f(0.20f, 0.13f, 0.08f, 0.45f);
				drawRoundedRect(LEVEL_BTN_X, by, LEVEL_BTN_WIDTH, LEVEL_BTN_HEIGHT, LEVEL_BTN_CORNER_RADIUS);
			}

			glDisable(GL_BLEND);

			int textLen = (int)strlen(levelLabels[i]);
			int textCenterX = LEVEL_BTN_X + (LEVEL_BTN_WIDTH / 2) - ((textLen * 9) / 2);

			drawGlowingText(textCenterX, by + 18, levelLabels[i], 30, 18, 8, 255, 255, 255);
		}

		return;
	}

	if (showingInstructions)
	{
		iShowImage(0, 0, 1280, 720, instructionBackground);
		return;
	}

	if (showingLeaderboard)
	{
		drawLeaderboardScreen();
		return;
	}

	if (showingSettings)
	{
		int spw = 680, sph = 240;
		int spx = (1280 - spw) / 2;
		int spy = 190;
		int panelTop = spy + sph;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		for (int g = 3; g > 0; g--)
		{
			glColor4f(0.20f, 0.65f, 0.70f, 0.06f + g * 0.04f);
			drawRoundedRect(spx - g * 3, spy - g * 3, spw + g * 6, sph + g * 6, 20);
		}
		glColor4f(0.12f, 0.25f, 0.27f, 0.75f);
		drawRoundedRect(spx, spy, spw, sph, 16);
		glDisable(GL_BLEND);

		char settingsTitle[] = "SETTINGS";
		int settingsTitleLen = (int)strlen(settingsTitle);
		int settingsTitleCenterX = spx + (spw / 2) - ((settingsTitleLen * 9) / 2);
		iSetColor(255, 255, 255);
		iText(settingsTitleCenterX, panelTop - 30, settingsTitle);

		int musicToggleX = spx + 220;
		int musicToggleY = panelTop - 115;

		char musicLabel[] = "Music:";
		iText(spx + 60, musicToggleY + 12, musicLabel);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		if (musicEnabled) { glColor4f(0.24f, 0.55f, 0.30f, 1.0f); }
		else              { glColor4f(0.47f, 0.24f, 0.24f, 1.0f); }
		drawRoundedRect(musicToggleX, musicToggleY, 120, 40, 8);
		glDisable(GL_BLEND);

		iSetColor(255, 255, 255);
		if (musicEnabled) { char onLabel[] = "ON"; iText(musicToggleX + 40, musicToggleY + 12, onLabel); }
		else { char offLabel[] = "OFF"; iText(musicToggleX + 35, musicToggleY + 12, offLabel); }

		int sfxToggleX = musicToggleX;
		int sfxToggleY = panelTop - 195;

		char sfxLabel[] = "SFX:";
		iText(spx + 60, sfxToggleY + 12, sfxLabel);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		if (sfxEnabled) { glColor4f(0.24f, 0.55f, 0.30f, 1.0f); }
		else            { glColor4f(0.47f, 0.24f, 0.24f, 1.0f); }
		drawRoundedRect(sfxToggleX, sfxToggleY, 120, 40, 8);
		glDisable(GL_BLEND);

		iSetColor(255, 255, 255);
		if (sfxEnabled) { char onLabel2[] = "ON"; iText(sfxToggleX + 40, sfxToggleY + 12, onLabel2); }
		else { char offLabel2[] = "OFF"; iText(sfxToggleX + 35, sfxToggleY + 12, offLabel2); }

		iSetColor(160, 175, 175);
		char backMsg2[] = "ESC to go back";
		int backMsgLen = (int)strlen(backMsg2);
		int backMsgCenterX = spx + (spw / 2) - ((backMsgLen * 6) / 2);
		iText(backMsgCenterX, spy + 30, backMsg2);

		return;
	}

	if (showingCredits)
	{
		iShowImage(0, 0, 1280, 720, creditsScreenTex);

		iSetColor(220, 220, 220);
		char backMsg3[] = "ESC to go back";
		iText(560, 30, backMsg3);

		return;
	}

	if (showingNoSaveConfirm)
	{
		iSetColor(30, 30, 30);
		iFilledRectangle(300, 280, 680, 160);

		iSetColor(255, 255, 255);
		char msg1[] = "No saved game found.";
		char msg2[] = "Want to start a new game?";
		iText(420, 400, msg1);
		iText(420, 370, msg2);

		char yesLabel[] = "Yes";
		char noLabel[] = "No";

		if (selectedConfirmOption == 0) { iSetColor(60, 110, 200); }
		else { iSetColor(90, 100, 115); }
		iFilledRectangle(400, 300, 180, 50);
		iSetColor(255, 255, 255);
		iText(465, 316, yesLabel);

		if (selectedConfirmOption == 1) { iSetColor(60, 110, 200); }
		else { iSetColor(90, 100, 115); }
		iFilledRectangle(700, 300, 180, 50);
		iSetColor(255, 255, 255);
		iText(765, 316, noLabel);

		return;
	}

	if (showingNameEntry)
	{
		// Ornate decorative frame - shrunk down significantly and shifted lower on screen
		const int NAME_FRAME_W = 560;
		const int NAME_FRAME_H = 283; // keeps the original artwork's aspect ratio
		const int NAME_FRAME_X = (1280 - NAME_FRAME_W) / 2;
		const int NAME_FRAME_Y = ((720 - NAME_FRAME_H) / 2) - 80;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		iShowImage(NAME_FRAME_X, NAME_FRAME_Y, NAME_FRAME_W, NAME_FRAME_H, nameEntryFrameTex);
		glDisable(GL_BLEND);

		// Empty input slot inside the frame image (measured proportionally from the artwork)
		int inputBoxX = NAME_FRAME_X + (int)(NAME_FRAME_W * 0.135f);
		int inputBoxW = (int)(NAME_FRAME_W * 0.735f);
		int inputBoxY = NAME_FRAME_Y + (int)(NAME_FRAME_H * 0.438f);
		int inputBoxH = (int)(NAME_FRAME_H * 0.195f);

		// Subtle dark backing behind the typed text - widened to fully span the
		// input slot's rounded ends, and nudged slightly lower
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.05f, 0.10f, 0.09f, 0.28f);
		drawRoundedRect(inputBoxX - 22, inputBoxY - 4 - 6, inputBoxW + 44, inputBoxH + 8, 10);
		glDisable(GL_BLEND);

		// Typed name, bigger glowing text, vertically centered in the input slot
		char displayText[18];
		if (cursorVisible)
		{
			sprintf_s(displayText, sizeof(displayText), "%s|", nameEntryBuffer);
		}
		else
		{
			sprintf_s(displayText, sizeof(displayText), "%s", nameEntryBuffer);
		}
		drawGlowingText(inputBoxX + 28, inputBoxY + (inputBoxH / 2) - 10, displayText, 20, 35, 25, 255, 255, 255, GLUT_BITMAP_TIMES_ROMAN_24);

		// Character counter, right-aligned inside the slot, slightly larger
		char counter[10];
		sprintf_s(counter, sizeof(counter), "%d/15", nameEntryLength);
		drawGlowingText(inputBoxX + inputBoxW - 70, inputBoxY + (inputBoxH / 2) - 10, counter, 20, 35, 25, 210, 225, 210, GLUT_BITMAP_HELVETICA_18);

		return;
	}

	// Draw all 8 buttons - simple boxy rectangles with soft rounded corners, centered dark-outlined text
	const int MENU_BTN_CORNER_RADIUS = 6;

	for (int i = 0; i < MENU_OPTION_COUNT; i++)
	{
		int by = menuButtonY[i] + (int)buttonFloatOffset[i];

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (i == selectedOption)
		{
			glColor4f(1.0f, 0.9f, 0.4f, 0.30f);
			drawRoundedRect(MENU_BTN_X - 8, by - 6, MENU_BTN_WIDTH + 16, MENU_BTN_HEIGHT + 12, MENU_BTN_CORNER_RADIUS + 2);

			glColor4f(0.35f, 0.22f, 0.10f, 0.55f);
			drawRoundedRect(MENU_BTN_X, by, MENU_BTN_WIDTH, MENU_BTN_HEIGHT, MENU_BTN_CORNER_RADIUS);
		}
		else
		{
			glColor4f(0.20f, 0.13f, 0.08f, 0.45f);
			drawRoundedRect(MENU_BTN_X, by, MENU_BTN_WIDTH, MENU_BTN_HEIGHT, MENU_BTN_CORNER_RADIUS);
		}

		glDisable(GL_BLEND);

		int textLen = (int)strlen(menuLabels[i]);
		int textCenterX = MENU_BTN_X + (MENU_BTN_WIDTH / 2) - ((textLen * 9) / 2);

		drawGlowingText(textCenterX, by + 18, menuLabels[i], 30, 18, 8, 255, 255, 255);
	}
}


bool enterKeyWasDown = false;
bool upKeyWasDown = false;
bool downKeyWasDown = false;
bool backspaceWasDown = false;
bool menuEscKeyWasDown = false;
bool typedKeyState[256] = { false };

void checkTypedChar(int code)
{
	bool down = isKeyPressed(code);
	if (down && !typedKeyState[code] && nameEntryLength < 15)
	{
		nameEntryBuffer[nameEntryLength] = (char)code;
		nameEntryLength++;
		nameEntryBuffer[nameEntryLength] = '\0';
	}
	typedKeyState[code] = down;
}

void updateMenu()
{
	bool enterDown = isKeyPressed(13);
	bool upDown = isKeyPressed('w') || isSpecialKeyPressed(GLUT_KEY_UP);
	bool downDown = isKeyPressed('s') || isSpecialKeyPressed(GLUT_KEY_DOWN);

	if (showingLevelMenu)
	{
		menuFrameCounter++;
		for (int i = 0; i < LEVEL_MENU_COUNT; i++)
		{
			levelButtonFloat[i] = sinf((menuFrameCounter + (i * 15)) * 0.05f) * 5.0f;

			int animY = levelButtonY[i] + (int)levelButtonFloat[i];

			bool insideX = (menuMouseX >= LEVEL_BTN_X && menuMouseX <= LEVEL_BTN_X + LEVEL_BTN_WIDTH);
			bool insideY = (menuMouseY >= animY && menuMouseY <= animY + LEVEL_BTN_HEIGHT);

			if (insideX && insideY)
			{
				selectedLevelOption = i;
			}
		}

		bool escDown = isKeyPressed(27);
		if (escDown && !menuEscKeyWasDown)
		{
			showingLevelMenu = false;
			playClickSound();
		}
		menuEscKeyWasDown = escDown;

		if (upDown && !upKeyWasDown)
		{
			selectedLevelOption--;
			if (selectedLevelOption < 0) { selectedLevelOption = LEVEL_MENU_COUNT - 1; }
			playClickSound();
		}
		if (downDown && !downKeyWasDown)
		{
			selectedLevelOption++;
			if (selectedLevelOption >= LEVEL_MENU_COUNT) { selectedLevelOption = 0; }
			playClickSound();
		}

		if (enterDown && !enterKeyWasDown)
		{
			playClickSound();

			if (selectedLevelOption == 0)
			{
				selectedLevelTarget = 1;
				levelSelectClicked = true;
			}
			else if (selectedLevelOption == 1)
			{
				selectedLevelTarget = 2;
				levelSelectClicked = true;
			}
			else if (selectedLevelOption == 2)
			{
				selectedLevelTarget = 3;
				levelSelectClicked = true;
			}
			else if (selectedLevelOption == 3)
			{
				selectedLevelTarget = 4;
				levelSelectClicked = true;
			}
			else if (selectedLevelOption == 4)
			{
				showingLevelMenu = false;
			}
		}

		enterKeyWasDown = enterDown;
		upKeyWasDown = upDown;
		downKeyWasDown = downDown;
		return;
	}

	if (showingInstructions || showingSettings || showingCredits)
	{
		bool escDown = isKeyPressed(27);
		if (escDown && !menuEscKeyWasDown)
		{
			showingInstructions = false;
			showingSettings = false;
			showingCredits = false;
		}
		menuEscKeyWasDown = escDown;
		enterKeyWasDown = enterDown;
		return;
	}

	if (showingLeaderboard)
	{
		bool escDown = isKeyPressed(27);
		if (escDown && !menuEscKeyWasDown)
		{
			if (showingClearConfirm)
			{
				showingClearConfirm = false;
			}
			else
			{
				showingLeaderboard = false;
			}
		}
		menuEscKeyWasDown = escDown;
		enterKeyWasDown = enterDown;
		return;
	}

	if (showingNoSaveConfirm)
	{
		if (upDown && !upKeyWasDown) { selectedConfirmOption = 0; }
		if (downDown && !downKeyWasDown) { selectedConfirmOption = 1; }

		if (enterDown && !enterKeyWasDown)
		{
			showingNoSaveConfirm = false;

			if (selectedConfirmOption == 0)
			{
				showingNameEntry = true;
				nameEntryBuffer[0] = '\0';
				nameEntryLength = 0;
			}
		}

		enterKeyWasDown = enterDown;
		upKeyWasDown = upDown;
		downKeyWasDown = downDown;
		return;
	}

	if (showingNameEntry)
	{
		cursorBlinkCounter++;
		if (cursorBlinkCounter >= 30)
		{
			cursorBlinkCounter = 0;
			cursorVisible = !cursorVisible;
		}

		for (int c = 'a'; c <= 'z'; c++) { checkTypedChar(c); }
		for (int c = 'A'; c <= 'Z'; c++) { checkTypedChar(c); }
		checkTypedChar(' ');

		bool backDown = isKeyPressed(8);
		if (backDown && !backspaceWasDown && nameEntryLength > 0)
		{
			nameEntryLength--;
			nameEntryBuffer[nameEntryLength] = '\0';
		}
		backspaceWasDown = backDown;

		if (enterDown && !enterKeyWasDown && nameEntryLength > 0)
		{
			startGameClicked = true;
		}

		bool escDown = isKeyPressed(27);
		if (escDown && !menuEscKeyWasDown)
		{
			showingNameEntry = false;
			nameEntryBuffer[0] = '\0';
			nameEntryLength = 0;
		}
		menuEscKeyWasDown = escDown;

		enterKeyWasDown = enterDown;
		return;
	}

	menuFrameCounter++;

	for (int i = 0; i < MENU_OPTION_COUNT; i++)
	{
		buttonFloatOffset[i] = sinf((menuFrameCounter + (i * 15)) * 0.05f) * 5.0f;

		bool insideX = (menuMouseX >= MENU_BTN_X && menuMouseX <= MENU_BTN_X + MENU_BTN_WIDTH);
		bool insideY = (menuMouseY >= menuButtonMouseYMin[i] && menuMouseY <= menuButtonMouseYMax[i]);

		if (insideX && insideY)
		{
			selectedOption = i;
		}
	}

	if (upDown && !upKeyWasDown)
	{
		selectedOption--;
		if (selectedOption < 0) { selectedOption = MENU_OPTION_COUNT - 1; }
		playClickSound();
	}
	if (downDown && !downKeyWasDown)
	{
		selectedOption++;
		if (selectedOption >= MENU_OPTION_COUNT) { selectedOption = 0; }
		playClickSound();
	}

	if (enterDown && !enterKeyWasDown)
	{
		playClickSound();

		if (selectedOption == 0)
		{
			showingNameEntry = true;
			nameEntryBuffer[0] = '\0';
			nameEntryLength = 0;
		}
		else if (selectedOption == 1)
		{
			if (hasSaveData)
			{
				continueGameClicked = true;
			}
			else
			{
				showingNoSaveConfirm = true;
				selectedConfirmOption = 0;
			}
		}
		else if (selectedOption == 2)
		{
			showingLevelMenu = true;
			selectedLevelOption = 0;
		}
		else if (selectedOption == 3)
		{
			showingLeaderboard = true;
		}
		else if (selectedOption == 4)
		{
			showingInstructions = true;
		}
		else if (selectedOption == 5)
		{
			showingSettings = true;
		}
		else if (selectedOption == 6)
		{
			showingCredits = true;
		}
		else if (selectedOption == 7)
		{
			exit(0);
		}
	}

	enterKeyWasDown = enterDown;
	upKeyWasDown = upDown;
	downKeyWasDown = downDown;
}

void handleMenuClick(int mx, int my)
{
	if (showingLevelMenu)
	{
		for (int i = 0; i < LEVEL_MENU_COUNT; i++)
		{
			int boxY = levelButtonY[i] + (int)levelButtonFloat[i];

			bool insideX = (mx >= LEVEL_BTN_X && mx <= LEVEL_BTN_X + LEVEL_BTN_WIDTH);
			bool insideY = (my >= boxY && my <= boxY + LEVEL_BTN_HEIGHT);

			if (insideX && insideY)
			{
				selectedLevelOption = i;
				playClickSound();

				if (i == 0)
				{
					selectedLevelTarget = 1;
					levelSelectClicked = true;
				}
				else if (i == 1)
				{
					selectedLevelTarget = 2;
					levelSelectClicked = true;
				}
				else if (i == 2)
				{
					selectedLevelTarget = 3;
					levelSelectClicked = true;
				}
				else if (i == 3)
				{
					selectedLevelTarget = 4;
					levelSelectClicked = true;
				}
				else if (i == 4)
				{
					showingLevelMenu = false;
				}
			}
		}
		return;
	}

	if (showingLeaderboard)
	{
		if (handleLeaderboardClick(mx, my))
		{
			showingLeaderboard = false;
		}
		return;
	}

	if (showingSettings)
	{
		int spw = 680;
		int spx = (1280 - spw) / 2;
		int spy = 190;
		int sph = 240;
		int panelTop = spy + sph;
		int musicToggleX = spx + 220;
		int musicToggleY = panelTop - 115;
		int sfxToggleX = musicToggleX;
		int sfxToggleY = panelTop - 195;

		bool onMusicToggle = (mx >= musicToggleX && mx <= musicToggleX + 120 && my >= musicToggleY && my <= musicToggleY + 40);
		bool onSfxToggle = (mx >= sfxToggleX && mx <= sfxToggleX + 120 && my >= sfxToggleY && my <= sfxToggleY + 40);

		if (onMusicToggle)
		{
			musicEnabled = !musicEnabled;
			applyMusicSetting();
			saveSettings();
		}
		else if (onSfxToggle)
		{
			sfxEnabled = !sfxEnabled;
			saveSettings();
		}
		return;
	}

	if (showingInstructions || showingCredits)
	{
		showingInstructions = false;
		showingCredits = false;
		return;
	}

	if (showingNoSaveConfirm)
	{
		bool onYes = (mx >= 400 && mx <= 580 && my >= 300 && my <= 350);
		bool onNo = (mx >= 700 && mx <= 880 && my >= 300 && my <= 350);

		if (onYes)
		{
			showingNoSaveConfirm = false;
			showingNameEntry = true;
			nameEntryBuffer[0] = '\0';
			nameEntryLength = 0;
		}
		else if (onNo)
		{
			showingNoSaveConfirm = false;
		}
		return;
	}

	if (showingNameEntry)
	{
		return;
	}

	for (int i = 0; i < MENU_OPTION_COUNT; i++)
	{
		bool insideX = (mx >= MENU_BTN_X && mx <= MENU_BTN_X + MENU_BTN_WIDTH);
		bool insideY = (my >= menuButtonMouseYMin[i] && my <= menuButtonMouseYMax[i]);

		if (insideX && insideY)
		{
			selectedOption = i;
			playClickSound();

			if (i == 0)
			{
				showingNameEntry = true;
				nameEntryBuffer[0] = '\0';
				nameEntryLength = 0;
			}
			else if (i == 1)
			{
				if (hasSaveData)
				{
					continueGameClicked = true;
				}
				else
				{
					showingNoSaveConfirm = true;
					selectedConfirmOption = 0;
				}
			}
			else if (i == 2)
			{
				showingLevelMenu = true;
				selectedLevelOption = 0;
			}
			else if (i == 3)
			{
				showingLeaderboard = true;
			}
			else if (i == 4)
			{
				showingInstructions = true;
			}
			else if (i == 5)
			{
				showingSettings = true;
			}
			else if (i == 6)
			{
				showingCredits = true;
			}
			else if (i == 7)
			{
				exit(0);
			}
		}
	}
}

#endif