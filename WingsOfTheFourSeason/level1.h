#ifndef LEVEL1_H 
#define LEVEL1_H 
#include <cstdlib>
#include <cmath>
#include "GameVariables.h"
#include "LifeHUD.h"
#include "Utilities.h"
#include "Settings.h"

const int SNOW_COUNT = 40;
int snowX[SNOW_COUNT];
int snowY[SNOW_COUNT];
// seeds / winter powerups
const int MAX_SEEDS = 7;
int seedX[MAX_SEEDS];
int seedY[MAX_SEEDS];
bool seedCollected[MAX_SEEDS];
int seedPowerupType[MAX_SEEDS];
int seedCount = 6;
int seedsGathered = 0;

const int WINTER_POWERUP_COUNT = 4;
unsigned int winterPowerupSprites[WINTER_POWERUP_COUNT];
const int powerupWidthByType[WINTER_POWERUP_COUNT] = { 42, 38, 54, 44 };
const int powerupHeightByType[WINTER_POWERUP_COUNT] = { 47, 45, 35, 44 };

// Tree obstacles
const int TREE_COUNT = 6;
int treeX[TREE_COUNT] = { 1100, 1550, 2000, 2450, 2900, 3350 };
const int TREE_SPRITE_COUNT = 4;
unsigned int treeSprites[TREE_SPRITE_COUNT];
int treeVariant[TREE_COUNT] = { 0, 1, 2, 3, 1, 2 };

const int treeWidthByVariant[TREE_SPRITE_COUNT] = { 140, 200, 190, 130 };
const int treeHeightByVariant[TREE_SPRITE_COUNT] = { 280, 270, 180, 370 };
const int TREE_BASE_Y = 150;


const int FAR_TREE_COUNT = 8;
int farTreeX[FAR_TREE_COUNT] = { 360, 760, 1160, 1900, 2400, 2900, 3200, 3560 };
int farTreeHeight[FAR_TREE_COUNT] = { 120, 150, 110, 160, 130, 140, 116, 144 };

const int FAR_TREE_SPRITE_COUNT = 5;
unsigned int farTreeSprites[FAR_TREE_SPRITE_COUNT];
int farTreeVariant[FAR_TREE_COUNT];

unsigned int level1Background;
unsigned int level1SnowRoad;
unsigned int strawTex;
float level1BgScrollX = 0.0f;
float level1RoadScrollX = 0.0f;

const int GROUND_SPIKE_CLUSTERS = 14;
int groundSpikeX[GROUND_SPIKE_CLUSTERS] = { 560, 960, 1360, 1760, 2160, 2560, 2960, 3360, 400, 1060, 1660, 2260, 2860, 3000 };
int groundSpikeCount[GROUND_SPIKE_CLUSTERS] = { 2, 2, 2, 3, 3, 3, 4, 4, 3, 4, 3, 4, 3, 4 };
int groundSpikePhase[GROUND_SPIKE_CLUSTERS] = { 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2 };

const int CEILING_SPIKE_CLUSTERS = 10;
int ceilingSpikeX[CEILING_SPIKE_CLUSTERS] = { 1400, 2000, 2600, 3000, 3400, 400, 1000, 1600, 2200, 2800 };
int ceilingSpikeCount[CEILING_SPIKE_CLUSTERS] = { 2, 3, 3, 4, 3, 3, 4, 3, 4, 4 };
int ceilingSpikePhase[CEILING_SPIKE_CLUSTERS] = { 1, 1, 1, 1, 1, 2, 2, 2, 2, 2 };

const int SPIKE_WIDTH = 24;
const int SPIKE_HEIGHT = 110;

const int ICICLE_COUNT = CEILING_SPIKE_CLUSTERS;
int icicleX[ICICLE_COUNT];
int icicleY[ICICLE_COUNT];

//STRAW
const int MAX_STRAW = 5;
int strawX[MAX_STRAW];
int strawY[MAX_STRAW];
bool strawCollected[MAX_STRAW];
bool gameOverSoundPlayed1 = false;


// Winter restoration stages (matches design doc section 9)
enum WinterStage { FROZEN_DESPAIR, FIRST_SIGNS, NATURE_AWAKENS, WINTER_RESTORED };

WinterStage getWinterStage()
{
	if (natureMeter < 33) return FROZEN_DESPAIR;
	if (natureMeter < 66) return FIRST_SIGNS;
	if (natureMeter < 100) return NATURE_AWAKENS;
	return WINTER_RESTORED;
}

const int SEED_MIN_SPACING = 260;


void spawnSeed(int i)
{
	bool tooClose = true;
	int attempts = 0;

	while (tooClose && attempts < 100)
	{
		attempts++;
		int spawnMin = aeroX + 200;
		int spawnMax = 3400;

		if (spawnMin >= spawnMax)
		{
			spawnMin = 400;
			spawnMax = 3400;
		}

		seedX[i] = spawnMin + (rand() % (spawnMax - spawnMin));
		seedY[i] = 200 + (rand() % 400);

		tooClose = false;

		for (int t = 0; t < TREE_COUNT; t++)
		{
			bool overlapX = (seedX[i] + 20 > treeX[t] - 60) && (seedX[i] - 20 < treeX[t] + 90);
			bool overlapY = (seedY[i] - 20 < TREE_BASE_Y + treeHeightByVariant[treeVariant[t]] + 40);

			if (overlapX && overlapY)
			{
				tooClose = true;
			}
		}

		// Keep a minimum gap from every other seed already placed this round
		for (int o = 0; o < seedCount; o++)
		{
			if (o == i) { continue; }
			int dx = seedX[i] - seedX[o];
			if (abs(dx) < SEED_MIN_SPACING)
			{
				tooClose = true;
			}
		}
	}

	seedPowerupType[i] = rand() % WINTER_POWERUP_COUNT;
	seedCollected[i] = false;
}

void spawnStraw(int i)
{
	bool tooCloseToTree = true;
	int attempts = 0;

	while (tooCloseToTree && attempts < 100)
	{
		attempts++;
		int spawnMin = aeroX + 200;
		int spawnMax = 3400;

		if (spawnMin >= spawnMax)
		{
			spawnMin = 400;
			spawnMax = 3400;
		}

		strawX[i] = spawnMin + (rand() % (spawnMax - spawnMin));
		strawY[i] = 200 + (rand() % 400);

		tooCloseToTree = false;

		for (int t = 0; t < TREE_COUNT; t++)
		{
			bool overlapX = (strawX[i] + 20 > treeX[t] - 60) && (strawX[i] - 20 < treeX[t] + 90);
			bool overlapY = (strawY[i] - 20 < TREE_BASE_Y + treeHeightByVariant[treeVariant[t]] + 40);

			if (overlapX && overlapY)
			{
				tooCloseToTree = true;
			}
		}
	}

	strawCollected[i] = false;
}


void resetLevel1()
{
	aeroX = 450;
	aeroY = 320;
	aeroFacingRight = true;
	currentAeroFrame = 0;
	aeroAnimCounter = 0;
	cameraX = 0;
	level1BgScrollX = 0.0f;
	level1RoadScrollX = 0.0f;
	lives = 3;
	natureMeter = 0;

	gameOver = false;
	gameOverSoundPlayed1 = false;

	levelComplete = false;
	timeLeft = 60;
	frameCounter = 0;
	seedsGathered = 0;

	invulnerableFrames = 0;
	energy = ENERGY_MAX;

	for (int i = 0; i < SNOW_COUNT; i++)
	{
		snowX[i] = rand() % 1280;
		snowY[i] = rand() % 720;
	}

	seedCount = 6 + (rand() % 2);

	for (int i = 0; i < seedCount; i++)
	{
		spawnSeed(i);
	}

	for (int i = 0; i < MAX_STRAW; i++)
	{
		spawnStraw(i);
	}

	// Icicles fall from the middle of each ceiling spike cluster
	for (int i = 0; i < ICICLE_COUNT; i++)
	{
		icicleX[i] = ceilingSpikeX[i] + ((ceilingSpikeCount[i] * SPIKE_WIDTH) / 2);
		icicleY[i] = 700;
	}

	for (int i = 0; i < TREE_COUNT; i++)
	{
		treeVariant[i] = rand() % TREE_SPRITE_COUNT;
	}

	for (int i = 0; i < FAR_TREE_COUNT; i++)
	{
		farTreeVariant[i] = rand() % FAR_TREE_SPRITE_COUNT;
	}
}

void loadTreeSprites()
{
	treeSprites[0] = iLoadImage("Assets/WinterforeTrees/FTree1.png");
	treeSprites[1] = iLoadImage("Assets/WinterforeTrees/FTree2.png");
	treeSprites[2] = iLoadImage("Assets/WinterforeTrees/FTree3.png");
	treeSprites[3] = iLoadImage("Assets/WinterforeTrees/FTree4.png");
}

void loadFarTreeSprites()
{
	farTreeSprites[0] = iLoadImage("Assets/WinterDistantTrees/DistantT_1.png");
	farTreeSprites[1] = iLoadImage("Assets/WinterDistantTrees/DistantT_2.png");
	farTreeSprites[2] = iLoadImage("Assets/WinterDistantTrees/DistantT_3.png");
	farTreeSprites[3] = iLoadImage("Assets/WinterDistantTrees/DistantT_4.png");
	farTreeSprites[4] = iLoadImage("Assets/WinterDistantTrees/DistantT_5.png");
}

void loadLevel1Background()
{
	level1Background = iLoadImage("Assets/winter_bg.png");
	level1SnowRoad = iLoadImage("Assets/snow_road.png");
	winterPowerupSprites[0] = iLoadImage("Assets/WinterPowerups/powerup_berries.png");
	winterPowerupSprites[1] = iLoadImage("Assets/WinterPowerups/powerup_lantern.png");
	winterPowerupSprites[2] = iLoadImage("Assets/WinterPowerups/powerup_pinecones.png");
	winterPowerupSprites[3] = iLoadImage("Assets/WinterPowerups/powerup_snowflakes.png");
	strawTex = iLoadImage("Assets/winter_straw.png");
}

int getSpikePhase()
{
	if (natureMeter < 33) { return 0; }
	if (natureMeter < 66) { return 1; }
	return 2;
}

void drawLevel1()
{
	// 1. Scrolling Winter background image (0.6x parallax)
	int bgOffset = (int)level1BgScrollX % 1280;
	if (bgOffset < 0) { bgOffset += 1280; }

	iShowImage(-bgOffset - 1280, 0, 1280, 720, level1Background);
	iShowImage(-bgOffset, 0, 1280, 720, level1Background);
	iShowImage(-bgOffset + 1280, 0, 1280, 720, level1Background);

	// 2. Snow Road along the ground with roots under the road/trees (1.0x foreground scroll matching trees)
	int roadOffset = (int)level1RoadScrollX % 1280;
	if (roadOffset < 0) { roadOffset += 1280; }

	iShowImage(-roadOffset - 1280, 0, 1280, 160, level1SnowRoad);
	iShowImage(-roadOffset, 0, 1280, 160, level1SnowRoad);
	iShowImage(-roadOffset + 1280, 0, 1280, 160, level1SnowRoad);

	float progress = natureMeter / 100.0f;

	// Falling snow
	iSetColor(255, 255, 255);
	for (int i = 0; i < SNOW_COUNT; i++)
	{
		iFilledCircle(snowX[i], snowY[i], 4);
	}

	// 3. Tree obstacles (located firmly on the snow road)
	for (int i = 0; i < TREE_COUNT; i++)
	{
		int v = treeVariant[i];
		int w = treeWidthByVariant[v];
		int h = treeHeightByVariant[v];
		int drawX = wrapScreenX(treeX[i], cameraX) - (w / 2);
		int drawY = TREE_BASE_Y;

		iShowImage(drawX, drawY, w, h, treeSprites[v]);
	}

	// Winter Powerups (replaces yellow circles)
	for (int i = 0; i < seedCount; i++)
	{
		if (!seedCollected[i])
		{
			int type = seedPowerupType[i];
			int pw = powerupWidthByType[type];
			int ph = powerupHeightByType[type];
			int px = wrapScreenX(seedX[i], cameraX) - (pw / 2);
			int py = seedY[i] - (ph / 2);

			iShowImage(px, py, pw, ph, winterPowerupSprites[type]);
		}
	}

	// Aero - animated sprite (flashes when invulnerable/hit)
	if (invulnerableFrames == 0 || (invulnerableFrames % 6 < 3))
	{
		unsigned int aeroSprite = aeroFacingRight
			? aeroFrames[currentAeroFrame]
			: aeroBackwardFrames[currentAeroFrame];
		iShowImage(wrapScreenX(aeroX, cameraX), aeroY, 100, 80, aeroSprite);
	}

	// Falling icicles
	int currentPhase = getSpikePhase();
	iSetColor(150, 210, 240);
	for (int i = 0; i < ICICLE_COUNT; i++)
	{
		if (ceilingSpikePhase[i] != currentPhase) { continue; }

		int ix = wrapScreenX(icicleX[i], cameraX);
		int iy = icicleY[i];

		double icicleShapeX[3] = { ix, ix + 16, ix + 8 };
		double icicleShapeY[3] = { iy + 50, iy + 50, iy };

		iFilledPolygon(icicleShapeX, icicleShapeY, 3);
	}

	// ---------- HUD ----------

	// Nature Meter - top-left
	drawNatureMeterBar(natureMeter, 100);

	// Lives - feather icons
	drawFeatherLives(lives);

	// Energy Bar - top center, replaces the old countdown timer
	drawEnergyBar();

	// Straw bundles - Energy booster pickups
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int i = 0; i < MAX_STRAW; i++)
	{
		if (!strawCollected[i])
		{
			int sx = wrapScreenX(strawX[i], cameraX);
			int sw = 40;
			int sh = 52;
			iShowImage(sx - (sw / 2), strawY[i] - (sh / 2), sw, sh, strawTex);
		}
	}

	glDisable(GL_BLEND);

	// Pause / Reset / Leave - icon images
	drawHudIcons();

	// Fog overlay removed so background image is displayed with exact colors

	// Game Over / Level Complete / Paused - centered dialogs
	if (gameOver)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.08f, 0.08f, 0.10f, 0.75f);
		iFilledRectangle(0, 0, 1280, 720);
		glDisable(GL_BLEND);

		iSetColor(255, 70, 70);
		iText(540, 390, (char*)"GAME OVER", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255, 255, 255);
		iText(490, 340, (char*)"Press R or Reset Icon to Restart", GLUT_BITMAP_HELVETICA_18);
		iText(500, 305, (char*)"Press ESC to Return to Menu", GLUT_BITMAP_HELVETICA_18);
	}

	if (levelComplete)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.10f, 0.22f, 0.15f, 0.82f);
		iFilledRectangle(0, 0, 1280, 720);
		glDisable(GL_BLEND);

		int msgW = 700, msgH = 336;
		int msgX = (1280 - msgW) / 2;
		int msgY = (720 - msgH) / 2;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		iShowImage(msgX, msgY, msgW, msgH, winterMsgTex);
		glDisable(GL_BLEND);

		char pressEnterMsg[] = "Press ENTER to Continue";
		int peLen = (int)strlen(pressEnterMsg);
		int peCenterX = 640 - ((peLen * 9) / 2);
		drawGlowingText(peCenterX, msgY - 40, pressEnterMsg, 30, 18, 8, 255, 255, 255, GLUT_BITMAP_HELVETICA_18);
	}

	if (paused)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.05f, 0.08f, 0.06f, 0.65f);
		iFilledRectangle(0, 0, 1280, 720);
		glDisable(GL_BLEND);

		iSetColor(255, 240, 120);
		iText(580, 380, (char*)"PAUSED", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255, 255, 255);
		iText(525, 335, (char*)"Press P to Resume Game", GLUT_BITMAP_HELVETICA_18);
	}
}

void  updateLevel1()
{
	if (gameOver && !gameOverSoundPlayed1)
	{
		playGameOverSound();
		gameOverSoundPlayed1 = true;
	}

	if (gameOver || levelComplete)
	{
		if (isKeyPressed('r') || isKeyPressed('R'))
		{
			resetLevel1();
		}
		return;
	}
	bool pKeyDown = isKeyPressed('p') || isKeyPressed('P');
	if (pKeyDown && !pKeyWasDown)
	{
		paused = !paused;
	}
	pKeyWasDown = pKeyDown;
	bool escKeyDown = isKeyPressed(27);
	if (escKeyDown && !escKeyWasDown)
	{
		leaveToMenuRequested = true;
	}
	escKeyWasDown = escKeyDown;
	if (paused)
	{
		return;
	}

	// Snow falls and drifts gently backwards as Aero flies forward
	for (int i = 0; i < SNOW_COUNT; i++)
	{
		snowY[i] -= 2;
		snowX[i] -= 1;
		if (snowY[i] < 0)
		{
			snowY[i] = 720;
			snowX[i] = rand() % 1280;
		}
		if (snowX[i] < 0)
		{
			snowX[i] += 1280;
		}
	}

	int previousAeroX = aeroX;
	int previousAeroY = aeroY;

	bool upPressed = isKeyPressed('w') || isKeyPressed('W') || isKeyPressed(' ') || isSpecialKeyPressed(GLUT_KEY_UP);
	bool downPressed = isKeyPressed('s') || isKeyPressed('S') || isSpecialKeyPressed(GLUT_KEY_DOWN);
	bool leftPressed = isKeyPressed('a') || isKeyPressed('A') || isSpecialKeyPressed(GLUT_KEY_LEFT);
	bool rightPressed = isKeyPressed('d') || isKeyPressed('D') || isSpecialKeyPressed(GLUT_KEY_RIGHT);

	if (upPressed)
	{
		aeroY += 6;
	}
	if (downPressed)
	{
		aeroY -= 6;
	}
	if (leftPressed)
	{
		aeroX -= 6;
		aeroFacingRight = false;
	}
	if (rightPressed)
	{
		aeroX += 7;
		aeroFacingRight = true;
	}

	// Automatic forward flight (Aero glides forward through the air)
	if (!leftPressed && !rightPressed)
	{
		aeroX += 3;
		aeroFacingRight = true;
	}

	// Aero wraps around the world 
	if (aeroX < 0)
	{
		aeroX += WORLD_WIDTH;
	}
	if (aeroX >= WORLD_WIDTH)
	{
		aeroX -= WORLD_WIDTH;
	}
	if (aeroY < 160)
	{
		aeroY = 160;
	}
	if (aeroY > 640)
	{
		aeroY = 640;
	}

	// Collision with tree obstacles
	for (int i = 0; i < TREE_COUNT; i++)
	{
		int v = treeVariant[i];
		int w = treeWidthByVariant[v];
		int h = treeHeightByVariant[v];
		int treeLeft = treeX[i] - (w / 2) + 25;
		int treeRight = treeX[i] + (w / 2) - 25;

		int wrappedAeroX = aeroX;
		int diff = wrappedAeroX - treeX[i];
		if (diff >  WORLD_WIDTH / 2) { wrappedAeroX -= WORLD_WIDTH; }
		if (diff < -WORLD_WIDTH / 2) { wrappedAeroX += WORLD_WIDTH; }

		bool overlapX = (wrappedAeroX + 75 > treeLeft) && (wrappedAeroX + 15 < treeRight);
		bool overlapY = (aeroY < TREE_BASE_Y + h - 15) && (aeroY + 65 > TREE_BASE_Y);

		if (overlapX && overlapY)
		{
			if (invulnerableFrames <= 0)
			{
				playHurtSound();
				lives--;
				invulnerableFrames = 60;
				aeroX = previousAeroX - 20;
				if (lives <= 0)
				{
					gameOver = true;
				}
			}
		}
	}

	// Update continuous background scroll (0.6x parallax) and snow road scroll (1.0x foreground)
	int deltaX = aeroX - previousAeroX;
	if (deltaX < -WORLD_WIDTH / 2) { deltaX += WORLD_WIDTH; }
	if (deltaX >  WORLD_WIDTH / 2) { deltaX -= WORLD_WIDTH; }
	level1BgScrollX += (float)deltaX * 0.6f;
	while (level1BgScrollX >= 1280.0f) { level1BgScrollX -= 1280.0f; }
	while (level1BgScrollX < 0.0f)     { level1BgScrollX += 1280.0f; }

	level1RoadScrollX += (float)deltaX;
	while (level1RoadScrollX >= 1280.0f) { level1RoadScrollX -= 1280.0f; }
	while (level1RoadScrollX < 0.0f)     { level1RoadScrollX += 1280.0f; }

	// Camera follows Aero, wrapping smoothly with the world
	cameraX = aeroX - 590;
	if (cameraX < 0) { cameraX += WORLD_WIDTH; }
	if (cameraX >= WORLD_WIDTH) { cameraX -= WORLD_WIDTH; }

	// Aero touches any winter powerup
	for (int i = 0; i < seedCount; i++)
	{
		if (!seedCollected[i])
		{
			int dx = (aeroX + 50) - seedX[i];
			if (dx >  WORLD_WIDTH / 2) { dx -= WORLD_WIDTH; }
			if (dx < -WORLD_WIDTH / 2) { dx += WORLD_WIDTH; }
			int dy = (aeroY + 40) - seedY[i];
			int distance = sqrt((double)((dx * dx) + (dy * dy)));

			if (distance < 60)
			{
				playSeedCollectSound();
				natureMeter = natureMeter + 3;
				if (natureMeter > 100)
				{
					natureMeter = 100;
				}

				// Powerup bonus: gives +5 Energy!
				energy = energy + 5;
				if (energy > ENERGY_MAX) { energy = ENERGY_MAX; }

				if (natureMeter >= 100)
				{
					levelComplete = true;
					seedCollected[i] = true;
				}
				else
				{
					spawnSeed(i);
				}
			}
		}
	}

	int currentPhase = getSpikePhase();
	int icicleSpeed = 6 + ((natureMeter / 25) * 2);

	// Icicles fall downward, then reset to the top once they hit the ground
	for (int i = 0; i < ICICLE_COUNT; i++)
	{
		if (ceilingSpikePhase[i] != currentPhase) { continue; }

		icicleY[i] = icicleY[i] - icicleSpeed;
		if (icicleY[i] < 160)
		{
			icicleY[i] = 700;
		}
	}

	// Check if Aero is hit by a falling icicle
	for (int i = 0; i < ICICLE_COUNT; i++)
	{
		if (ceilingSpikePhase[i] != currentPhase) { continue; }

		int dx = (aeroX + 50) - (icicleX[i] + 8);
		// Wrap-correct the X delta so hits register anywhere in the world
		if (dx >  WORLD_WIDTH / 2) { dx -= WORLD_WIDTH; }
		if (dx < -WORLD_WIDTH / 2) { dx += WORLD_WIDTH; }
		int dy = (aeroY + 40) - (icicleY[i] + 25);
		int distance = (int)sqrt((double)((dx * dx) + (dy * dy)));

		if (distance < 50 && invulnerableFrames <= 0)
		{
			playHurtSound();
			lives = lives - 1;
			invulnerableFrames = 45;
			if (lives <= 0) { gameOver = true; }
			icicleY[i] = 700;
		}
	}

	// Ground and ceiling spike collisions removed since spikes are not rendered

	if (invulnerableFrames > 0)
	{
		invulnerableFrames--;
	}

	// Energy drains over time, refilled by collecting straw
	drainEnergy();

	// Aero collects straw, refilling Energy
	for (int i = 0; i < MAX_STRAW; i++)
	{
		if (!strawCollected[i])
		{
			int dx = (aeroX + 50) - strawX[i];
			int dy = (aeroY + 40) - strawY[i];
			int distance = sqrt((double)((dx * dx) + (dy * dy)));

			if (distance < 60)
			{
				energy = energy + 20;
				if (energy > ENERGY_MAX) { energy = ENERGY_MAX; }
				spawnStraw(i);
			}
		}
	}

	// Cycle through flap frames
	aeroAnimCounter++;
	if (aeroAnimCounter >= 6)
	{
		aeroAnimCounter = 0;
		currentAeroFrame = (currentAeroFrame + 1) % AERO_FRAME_COUNT;
	}
}
#endif