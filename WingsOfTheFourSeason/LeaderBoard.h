#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include <fstream>
#include <cstring>
#include <cmath>

#include "Utilities.h"

const int MAX_LEADERBOARD_ENTRIES = 10;
char leaderboardNames[MAX_LEADERBOARD_ENTRIES][20];
int leaderboardTimes[MAX_LEADERBOARD_ENTRIES];
int leaderboardCount = 0;

bool showingClearConfirm = false;
float leaderboardGlowTimer = 0.0f;

int menuMouseX = 0;
int menuMouseY = 0;

void loadLeaderboard()
{
	leaderboardCount = 0;

	std::ifstream file("leaderboard.txt");
	if (!file.is_open())
	{
		return;
	}

	while (leaderboardCount < MAX_LEADERBOARD_ENTRIES)
	{
		char name[20];
		int timeVal;

		file.getline(name, 20, ',');
		file >> timeVal;
		file.ignore();

		if (file.fail())
		{
			break;
		}

		strcpy_s(leaderboardNames[leaderboardCount], name);
		leaderboardTimes[leaderboardCount] = timeVal;
		leaderboardCount++;
	}

	file.close();
}

void saveLeaderboard()
{
	std::ofstream file("leaderboard.txt");

	for (int i = 0; i < leaderboardCount; i++)
	{
		file << leaderboardNames[i] << "," << leaderboardTimes[i] << "\n";
	}

	file.close();
}

void addLeaderboardEntry(char playerName[], int finishTimeSeconds)
{
	int insertPos = leaderboardCount;
	for (int i = 0; i < leaderboardCount; i++)
	{
		if (finishTimeSeconds < leaderboardTimes[i])
		{
			insertPos = i;
			break;
		}
	}

	int lastSlot = leaderboardCount;
	if (lastSlot >= MAX_LEADERBOARD_ENTRIES) { lastSlot = MAX_LEADERBOARD_ENTRIES - 1; }

	for (int i = lastSlot; i > insertPos; i--)
	{
		strcpy_s(leaderboardNames[i], leaderboardNames[i - 1]);
		leaderboardTimes[i] = leaderboardTimes[i - 1];
	}

	strcpy_s(leaderboardNames[insertPos], playerName);
	leaderboardTimes[insertPos] = finishTimeSeconds;

	if (leaderboardCount < MAX_LEADERBOARD_ENTRIES)
	{
		leaderboardCount++;
	}

	saveLeaderboard();
}

// ===================== DRAWING HELPERS =====================

void drawLeaderboardOrnamentLine(int x1, int y, int x2)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int cx = (x1 + x2) / 2;

	glColor4f(0.40f, 0.80f, 1.0f, 0.45f);
	glLineWidth(1.5f);
	glBegin(GL_LINES);
	glVertex2f((float)x1, (float)y);
	glVertex2f((float)cx - 8, (float)y);
	glVertex2f((float)cx + 8, (float)y);
	glVertex2f((float)x2, (float)y);
	glEnd();
	glLineWidth(1.0f);

	glColor4f(0.40f, 0.80f, 1.0f, 0.75f);
	iFilledCircle(cx, y, 4);
	glColor4f(1.0f, 1.0f, 1.0f, 0.85f);
	iFilledCircle(cx, y, 2);

	glDisable(GL_BLEND);
}

void drawLeaderboardMedal(int cx, int cy, int rank)
{
	int r1, g1, b1, r2, g2, b2, r3, g3, b3;

	if (rank == 1)      { r1 = 255; g1 = 200; b1 = 0;   r2 = 255; g2 = 215; b2 = 50;  r3 = 80; g3 = 50; b3 = 0; }
	else if (rank == 2) { r1 = 160; g1 = 160; b1 = 170; r2 = 200; g2 = 200; b2 = 210; r3 = 60; g3 = 60; b3 = 70; }
	else                { r1 = 180; g1 = 110; b1 = 40;  r2 = 205; g2 = 140; b2 = 60;  r3 = 80; g3 = 40; b3 = 10; }

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float pulse = (float)(sin(leaderboardGlowTimer * 3.0f + rank) + 1.0f) / 2.0f;
	glColor4f(r1 / 255.0f, g1 / 255.0f, b1 / 255.0f, 0.15f + pulse * 0.15f);
	iFilledCircle(cx, cy, 18);

	glDisable(GL_BLEND);

	iSetColor(r1, g1, b1);
	iFilledCircle(cx, cy, 14);
	iSetColor(r2, g2, b2);
	iFilledCircle(cx, cy, 10);

	char rk[4];
	sprintf_s(rk, "%d", rank);
	iSetColor(r3, g3, b3);
	iText(cx - 4, cy - 5, rk, GLUT_BITMAP_HELVETICA_12);
}

// ===================== LEADERBOARD SCREEN =====================

void drawLeaderboardScreen()
{
	leaderboardGlowTimer += 0.03f;

	int px = 90, py = 40, pw = 1100, ph = 640;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int g = 3; g > 0; g--)
	{
		glColor4f(0.20f, 0.65f, 0.70f, 0.06f + g * 0.04f);
		drawRoundedRect(px - g * 3, py - g * 3, pw + g * 6, ph + g * 6, 22);
	}

	glColor4f(0.12f, 0.25f, 0.27f, 0.55f);
	drawRoundedRect(px, py, pw, ph, 18);
	glDisable(GL_BLEND);

	int corners[4][2] = { { px + 15, py + ph - 15 }, { px + pw - 15, py + ph - 15 }, { px + 15, py + 15 }, { px + pw - 15, py + 15 } };
	for (int i = 0; i < 4; i++)
	{
		iSetColor(80, 190, 220);
		iFilledCircle(corners[i][0], corners[i][1], 4);
		iSetColor(200, 230, 255);
		iFilledCircle(corners[i][0], corners[i][1], 2);
	}

	// Title - centered in the panel
	char lbTitle[] = "LEADERBOARD";
	int titleLen = (int)strlen(lbTitle);
	int titleCenterX = px + (pw / 2) - ((titleLen * 12) / 2);
	drawGlowingText(titleCenterX, py + ph - 55, lbTitle, 20, 60, 70, 220, 240, 255, GLUT_BITMAP_TIMES_ROMAN_24);

	drawLeaderboardOrnamentLine(px + 60, py + ph - 80, px + pw - 60);

	// Column headers
	int headerY = py + ph - 120;
	iSetColor(30, 60, 55);
	iFilledRectangle(px + 20, headerY - 10, pw - 40, 32);

	iSetColor(200, 235, 255);
	iText(px + 70, headerY, "RANK");
	iText(px + 260, headerY, "PLAYER");
	iText(px + 820, headerY, "TIME");

	int rowY = headerY - 46;
	int rowGap = 40;

	if (leaderboardCount == 0)
	{
		iSetColor(120, 160, 200);
		char noneMsg[] = "No entries yet - start a game to see scores here!";
		iText(px + (pw / 2) - 220, py + (ph / 2), noneMsg);
	}
	else
	{
		for (int i = 0; i < leaderboardCount; i++)
		{
			int rowBgY = rowY - 8;
			int rowBgH = 34;

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			if (i % 2 == 0) { glColor4f(1.0f, 1.0f, 1.0f, 0.04f); }
			else            { glColor4f(0.0f, 0.0f, 0.0f, 0.12f); }
			drawRoundedRect(px + 25, rowBgY, pw - 50, rowBgH, 6);

			if (i < 3)
			{
				int acR, acG, acB;
				if (i == 0)      { acR = 255; acG = 215; acB = 0; }
				else if (i == 1) { acR = 192; acG = 192; acB = 210; }
				else             { acR = 205; acG = 140; acB = 55; }

				glColor4f(acR / 255.0f, acG / 255.0f, acB / 255.0f, 0.7f);
				iFilledRectangle(px + 25, rowBgY, 4, rowBgH);
			}
			glDisable(GL_BLEND);

			if (i < 3)
			{
				drawLeaderboardMedal(px + 90, rowY + 7, i + 1);
			}
			else
			{
				char rankStr[6];
				sprintf_s(rankStr, "#%d", i + 1);
				iSetColor(180, 210, 240);
				iText(px + 78, rowY, rankStr);
			}

			iSetColor(245, 255, 255);
			iText(px + 260, rowY, leaderboardNames[i]);

			char timeStr[16];
			sprintf_s(timeStr, "%ds", leaderboardTimes[i]);
			iSetColor(245, 255, 255);
			iText(px + 820, rowY, timeStr);

			rowY -= rowGap;
		}
	}

	// Buttons pinned to a fixed spot at the bottom of the panel - using measured
	// on-screen bounds directly, confirmed via debug overlay testing
	bool backHovered = (menuMouseX >= 125 && menuMouseX <= 317 &&
		menuMouseY >= 138 && menuMouseY <= 176);
	bool clearHovered = (menuMouseX >= 913 && menuMouseX <= 1158 &&
		menuMouseY >= 138 && menuMouseY <= 176);

	int buttonY = py + 30;
	int buttonH = 45;
	int backW = 200;
	int clearW = 250;

	// Back button - boxy with soft rounded corners, hover glow
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (backHovered)
	{
		glColor4f(0.35f, 0.55f, 0.80f, 0.35f);
		drawRoundedRect(px + 30 - 4, buttonY - 4, backW + 8, buttonH + 8, 10);
		glColor4f(0.33f, 0.49f, 0.65f, 1.0f);
	}
	else
	{
		glColor4f(0.24f, 0.35f, 0.47f, 1.0f);
	}
	drawRoundedRect(px + 30, buttonY, backW, buttonH, 8);
	glDisable(GL_BLEND);

	iSetColor(255, 255, 255);
	char backBtn[] = "Back";
	iText(px + 105, buttonY + 15, backBtn);

	// Clear Leaderboard button - boxy with soft rounded corners, hover glow
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (clearHovered)
	{
		glColor4f(0.85f, 0.35f, 0.35f, 0.35f);
		drawRoundedRect(px + pw - 280 - 4, buttonY - 4, clearW + 8, buttonH + 8, 10);
		glColor4f(0.61f, 0.29f, 0.29f, 1.0f);
	}
	else
	{
		glColor4f(0.47f, 0.24f, 0.24f, 1.0f);
	}
	drawRoundedRect(px + pw - 280, buttonY, clearW, buttonH, 8);
	glDisable(GL_BLEND);

	iSetColor(255, 255, 255);
	char clearBtn[] = "Clear Leaderboard";
	iText(px + pw - 265, buttonY + 15, clearBtn);

	if (showingClearConfirm)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.0f, 0.0f, 0.0f, 0.75f);
		iFilledRectangle(0, 0, 1280, 720);
		glDisable(GL_BLEND);

		int dw = 520, dh = 230;
		int dx = (1280 - dw) / 2;
		int dy = (720 - dh) / 2;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		for (int g = 3; g > 0; g--)
		{
			glColor4f(1.0f, 0.24f, 0.24f, 0.06f + g * 0.05f);
			drawRoundedRect(dx - g * 3, dy - g * 3, dw + g * 6, dh + g * 6, 18);
		}
		glColor4f(0.07f, 0.09f, 0.14f, 0.95f);
		drawRoundedRect(dx, dy, dw, dh, 15);
		glDisable(GL_BLEND);

		iSetColor(200, 50, 50);
		iFilledCircle(dx + (dw / 2), dy + dh - 40, 16);
		iSetColor(255, 255, 255);
		char warnIcon[] = "!";
		iText(dx + (dw / 2) - 4, dy + dh - 46, warnIcon);

		iSetColor(255, 120, 120);
		char warn1[] = "Are you sure you want to clear";
		char warn2[] = "ALL leaderboard data?";
		iText(dx + 70, dy + 150, warn1);
		iText(dx + 100, dy + 125, warn2);

		iSetColor(180, 140, 140);
		char warn3[] = "This action cannot be undone.";
		iText(dx + 120, dy + 100, warn3);

		bool yesHovered = (menuMouseX >= dx + 60 && menuMouseX <= dx + 240 &&
			menuMouseY >= dy + 30 && menuMouseY <= dy + 75);
		bool cancelHovered = (menuMouseX >= dx + 280 && menuMouseX <= dx + 460 &&
			menuMouseY >= dy + 30 && menuMouseY <= dy + 75);

		// Yes, Clear All - boxy with soft rounded corners, hover glow
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (yesHovered)
		{
			glColor4f(0.95f, 0.35f, 0.35f, 0.35f);
			drawRoundedRect(dx + 60 - 4, dy + 30 - 4, 188, 53, 10);
			glColor4f(0.75f, 0.24f, 0.24f, 1.0f);
		}
		else
		{
			glColor4f(0.59f, 0.16f, 0.16f, 1.0f);
		}
		drawRoundedRect(dx + 60, dy + 30, 180, 45, 8);
		glDisable(GL_BLEND);

		iSetColor(255, 255, 255);
		char yesBtn[] = "Yes, Clear All";
		iText(dx + 80, dy + 45, yesBtn);

		// Cancel - boxy with soft rounded corners, hover glow
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (cancelHovered)
		{
			glColor4f(0.55f, 0.60f, 0.70f, 0.35f);
			drawRoundedRect(dx + 280 - 4, dy + 30 - 4, 188, 53, 10);
			glColor4f(0.37f, 0.41f, 0.47f, 1.0f);
		}
		else
		{
			glColor4f(0.27f, 0.31f, 0.37f, 1.0f);
		}
		drawRoundedRect(dx + 280, dy + 30, 180, 45, 8);
		glDisable(GL_BLEND);

		iSetColor(255, 255, 255);
		char cancelBtn[] = "Cancel";
		iText(dx + 345, dy + 45, cancelBtn);
	}
}

// ===================== CLICK HANDLING =====================
// Returns true if "Back" was clicked (caller should close the leaderboard screen)
bool handleLeaderboardClick(int mx, int my)
{
	if (showingClearConfirm)
	{
		int dw = 520, dh = 230;
		int dx = (1280 - dw) / 2;
		int dy = (720 - dh) / 2;

		bool onYes = (mx >= dx + 60 && mx <= dx + 240 && my >= dy + 30 && my <= dy + 75);
		bool onCancel = (mx >= dx + 280 && mx <= dx + 460 && my >= dy + 30 && my <= dy + 75);

		if (onYes)
		{
			leaderboardCount = 0;
			saveLeaderboard();
			showingClearConfirm = false;
		}
		else if (onCancel)
		{
			showingClearConfirm = false;
		}
		return false;
	}

	// Using measured on-screen button bounds directly (confirmed via debug overlay)
	bool onBack = (mx >= 125 && mx <= 317 && my >= 138 && my <= 176);
	bool onClear = (mx >= 913 && mx <= 1158 && my >= 138 && my <= 176);

	if (onBack)
	{
		return true;
	}
	else if (onClear)
	{
		showingClearConfirm = true;
	}

	return false;
}

#endif