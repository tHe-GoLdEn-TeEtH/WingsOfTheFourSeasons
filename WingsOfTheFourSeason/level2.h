#ifndef LEVEL2_H 
#define LEVEL2_H 
#include <cstdlib>
#include <cmath>
#include "GameVariables.h"
#include "LifeHUD.h"
#include "Utilities.h"


unsigned int monsoonBackground2;

void loadMonsoonBackground()
{
	monsoonBackground2 = iLoadImage("Assets/MonsoonBG.png");
}

const int BOAT_TYPES_COUNT = 3;
unsigned int boatTextures[BOAT_TYPES_COUNT];

unsigned int fishTextures[2];
unsigned int toucanFrames[4];
unsigned int cloudTextures[2];
unsigned int branchTex;
float aeroPitch = 0.0f;

void loadLevel2CustomSprites()
{
	boatTextures[0] = iLoadImage("Assets/Boats/Boat1.png");
	boatTextures[1] = iLoadImage("Assets/Boats/Boat2.png");
	boatTextures[2] = iLoadImage("Assets/Boats/Boat3.png");
	fishTextures[0] = iLoadImage("Assets/Fish/Fish1.png");
	fishTextures[1] = iLoadImage("Assets/Fish/Fish2.png");
	toucanFrames[0] = iLoadImage("Assets/ObstacleBird/Toucan_0.png");
	toucanFrames[1] = iLoadImage("Assets/ObstacleBird/Toucan_1.png");
	toucanFrames[2] = iLoadImage("Assets/ObstacleBird/Toucan_2.png");
	toucanFrames[3] = iLoadImage("Assets/ObstacleBird/Toucan_3.png");
	cloudTextures[0] = iLoadImage("Assets/Clouds/StormCloud1.png");
	cloudTextures[1] = iLoadImage("Assets/Clouds/StormCloud2.png");
	branchTex = iLoadImage("Assets/Branch.png");
}

void loadBoatSprites()
{
	loadLevel2CustomSprites();
}

void loadSandbarSprites()
{
	loadLevel2CustomSprites();
}

const int SNOW_COUNT_2 = 70;
int snowX2[SNOW_COUNT_2];
int snowY2[SNOW_COUNT_2];

int lightningState2 = 0;
int lightningTimer2 = 120;
int lightningCloudIndex2 = 0;

float windVisualOffsetX = 0.0f;

//PREDATOR HAWKS
const int HAWK_COUNT_2 = 2;
bool hawkActive2[HAWK_COUNT_2] = { false, false };
int hawkX2[HAWK_COUNT_2];
int hawkY2[HAWK_COUNT_2];
int hawkAttackTimer2[HAWK_COUNT_2] = { 0, 0 };   // >0 while actively draining Aero
int hawkCooldown2[HAWK_COUNT_2] = { 0, 0 };      // >0 while resting after an attack

int hawkAttackEffectTimer2 = 0;
const int HAWK_ATTACK_DURATION_2 = 120;   // 2 seconds at 60 updates/sec

bool gameOverSoundPlayed2 = false;

// seeds 
const int MAX_SEEDS_2 = 7;
int seedX2[MAX_SEEDS_2];
int seedY2[MAX_SEEDS_2];
bool seedCollected2[MAX_SEEDS_2];
int seedCount2 = 6;
int seedsGathered2 = 0;

// Floating boats along the river - spaced out with wide open gaps
const int BOAT_COUNT_2 = 5;
int boatX2[BOAT_COUNT_2] = { 350, 1070, 1790, 2510, 3230 };
int boatType2[BOAT_COUNT_2] = { 0, 1, 2, 0, 1 };
float boatBobTimer2 = 0.0f;

// Storm clouds
const int CLOUD_COUNT_2 = 10;
int cloudX2[CLOUD_COUNT_2] = { 1400, 2000, 2600, 3000, 3400, 400, 1000, 1600, 2200, 2800 };
int cloudWidth2[CLOUD_COUNT_2] = { 80, 110, 110, 140, 110, 110, 140, 110, 140, 140 };
int cloudPhase2[CLOUD_COUNT_2] = { 0, 0, 0, 1, 1, 1, 2, 2, 2, 2 };

// Obstacle birds (Toucans) - fly right-to-left across the screen
const int TOUCAN_COUNT_2 = 3;
int toucanX2[TOUCAN_COUNT_2];
int toucanY2[TOUCAN_COUNT_2];
float toucanFlapTimer2 = 0.0f;

// Flying Branches - drift right-to-left across the mid-screen band, similar timing to seeds
const int BRANCH_COUNT_2 = 3;
float branchX2[BRANCH_COUNT_2];
float branchY2[BRANCH_COUNT_2];
float branchSpeed2[BRANCH_COUNT_2];
float branchRot2[BRANCH_COUNT_2];
float branchRotSpeed2[BRANCH_COUNT_2];


// Monsoon restoration stages
enum MonsoonStage { MONSOON_BEGINS, RAIN_INTENSIFIES, WATERS_RISE, MONSOON_RESTORED };

MonsoonStage getMonsoonStage()
{
	if (natureMeter < 33) return MONSOON_BEGINS;
	if (natureMeter < 66) return RAIN_INTENSIFIES;
	if (natureMeter < 100) return WATERS_RISE;
	return MONSOON_RESTORED;
}

const int SEED2_MIN_SPACING = 260;

void spawnSeed2(int i)
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

		seedX2[i] = spawnMin + (rand() % (spawnMax - spawnMin));
		seedY2[i] = 200 + (rand() % 400);

		tooClose = false;

		for (int o = 0; o < seedCount2; o++)
		{
			if (o == i) { continue; }
			int dx = seedX2[i] - seedX2[o];
			if (abs(dx) < SEED2_MIN_SPACING)
			{
				tooClose = true;
			}
		}
	}

	seedCollected2[i] = false;
}


void resetLevel2()
{
	startRainSound();

	aeroX = 710;
	aeroY = 320;
	aeroFacingRight = true;
	currentAeroFrame = 0;
	aeroAnimCounter = 0;
	cameraX = 0;
	windVisualOffsetX = 0.0f;
	aeroPitch = 0.0f;
	lives = 5;
	natureMeter = 0;
	gameOver = false;
	gameOverSoundPlayed2 = false;
	levelComplete = false;
	timeLeft = 60;
	frameCounter = 0;
	seedsGathered2 = 0;
	boatBobTimer2 = 0.0f;
	toucanFlapTimer2 = 0.0f;

	invulnerableFrames = 0;
	hawkAttackEffectTimer2 = 0;  //ATTACK INITIALIZATION

	energy = 100;
	// RESET HAWAK
	for (int h = 0; h < HAWK_COUNT_2; h++)
	{
		hawkActive2[h] = false;
		hawkAttackTimer2[h] = 0;
		hawkCooldown2[h] = 0;
	}


	lightningState2 = 0;
	lightningTimer2 = 60 + (rand() % 90);

	for (int i = 0; i < SNOW_COUNT_2; i++)
	{
		snowX2[i] = rand() % 1280;
		snowY2[i] = rand() % 720;
	}

	seedCount2 = 6 + (rand() % 2);

	for (int i = 0; i < seedCount2; i++)
	{
		spawnSeed2(i);
	}

	// Toucan obstacle birds spaced out across the sky, with one immediately approaching
	for (int i = 0; i < TOUCAN_COUNT_2; i++)
	{
		toucanX2[i] = 1100 + (i * 450) + (rand() % 100);
		toucanY2[i] = 260 + (i * 140) + (rand() % 60);
	}

	// Flying branches - spaced out along the top of the screen, positioned in the mid-screen band
	for (int i = 0; i < BRANCH_COUNT_2; i++)
	{
		branchX2[i] = 1280.0f + (i * 500.0f) + (rand() % 200);
		branchY2[i] = 280.0f + (rand() % 220);
		branchSpeed2[i] = 4.0f + ((rand() % 100) / 100.0f) * 3.0f;
		branchRot2[i] = (float)(rand() % 360);
		branchRotSpeed2[i] = 1.5f + ((rand() % 100) / 100.0f) * 2.5f;
	}

	for (int f = 0; f < FISH_COUNT_2; f++)
	{
		fishX2[f] = 710 + (f * 720);
		fishStartX2[f] = fishX2[f];
		fishBaseY2[f] = 75;      // river water surface resting level
		fishY2[f] = fishBaseY2[f];
		fishState2[f] = 0;
		fishJumpTimer2[f] = 15 + (f * 20) + (rand() % 20);
		fishJumpProgress2[f] = 0;
		fishVisible2[f] = true;
	}
}




int getSpikePhase2()
{
	if (natureMeter < 33) { return 0; }
	if (natureMeter < 66) { return 1; }
	return 2;
}

void drawLevel2()
{
	// Full Monsoon background image (replaces procedural sky)
	float progress = natureMeter / 100.0f;
	iShowImage(0, 0, 1280, 720, monsoonBackground2);

	// Layered scrolling waves - large, medium, small, each at a different speed
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int tilesNeeded = (1280 / WAVE_TILE_WIDTH) + 2;

	for (int t = -1; t < tilesNeeded; t++)
	{
		int tx = (t * WAVE_TILE_WIDTH) - (int)waveLargeOffset;
		iShowImage(tx, 90, WAVE_TILE_WIDTH, WAVE_TILE_HEIGHT, waveLargeTex);
	}

	for (int t = -1; t < tilesNeeded; t++)
	{
		int tx = (t * WAVE_TILE_WIDTH) - (int)waveMediumOffset;
		iShowImage(tx, 60, WAVE_TILE_WIDTH, WAVE_TILE_HEIGHT, waveMediumTex);
	}

	for (int t = -1; t < tilesNeeded; t++)
	{
		int tx = (t * WAVE_TILE_WIDTH) - (int)waveSmallOffset;
		iShowImage(tx, 30, WAVE_TILE_WIDTH, WAVE_TILE_HEIGHT, waveSmallTex);
	}

	glDisable(GL_BLEND);




	int currentPhase = getSpikePhase2();

	// Realistic translucent volumetric storm clouds
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (int c = 0; c < CLOUD_COUNT_2; c++)
	{
		if (cloudPhase2[c] != currentPhase) { continue; }

		int cx = wrapScreenX(cloudX2[c], cameraX);
		int cType = c % 2;
		int cw = (cType == 0) ? 360 : 420;
		int ch = (cType == 0) ? 210 : 190;
		int cy = 520 + (c % 3) * 20;

		iShowImage(cx - (cw / 2), cy, cw, ch, cloudTextures[cType]);
	}
	glDisable(GL_BLEND);

	// Lightning warning flicker with internal electric cloud illumination
	if (lightningState2 == 1 && (lightningTimer2 / 4) % 2 == 0)
	{
		int wx = wrapScreenX(cloudX2[lightningCloudIndex2], cameraX);
		int cType = lightningCloudIndex2 % 2;
		int cw = (cType == 0) ? 390 : 450;
		int ch = (cType == 0) ? 230 : 210;
		int cy = 515 + (lightningCloudIndex2 % 3) * 20;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.85f, 0.95f, 1.0f, 0.45f);
		iShowImage(wx - (cw / 2), cy, cw, ch, cloudTextures[cType]);
		glDisable(GL_BLEND);
	}

	if (lightningState2 == 2)
	{
		int bx = wrapScreenX(cloudX2[lightningCloudIndex2], cameraX);

		// Dynamic thunderstorm screen flash (illuminates sky and landscape)
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		float flashAlpha = (float)lightningTimer2 / 10.0f * 0.40f;
		glColor4f(0.90f, 0.95f, 1.0f, flashAlpha);
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(1280, 0);
		glVertex2f(1280, 720);
		glVertex2f(0, 720);
		glEnd();
		glDisable(GL_BLEND);

		// Outer electric cyan glow for the main bolt
		iSetColor(130, 220, 255);
		iLine(bx - 1, 600, bx - 21, 480);
		iLine(bx + 1, 600, bx - 19, 480);
		iLine(bx - 20, 480, bx + 16, 360);
		iLine(bx + 15, 360, bx - 12, 250);
		iLine(bx - 12, 250, bx + 18, 170);
		iLine(bx + 18, 170, bx, 130);

		// Branch 1: splits off toward left
		iLine(bx - 20, 480, bx - 60, 410);
		iLine(bx - 60, 410, bx - 45, 330);

		// Branch 2: splits off toward right
		iLine(bx + 15, 360, bx + 55, 290);
		iLine(bx + 55, 290, bx + 40, 220);

		// Core hot-white main bolt
		iSetColor(255, 255, 255);
		iLine(bx, 600, bx - 20, 480);
		iLine(bx - 20, 480, bx + 15, 360);
		iLine(bx + 15, 360, bx - 12, 250);
		iLine(bx - 12, 250, bx + 18, 170);
		iLine(bx + 18, 170, bx, 130);

		// Water impact flash at the strike point
		iSetColor(255, 255, 255);
		iFilledEllipse(bx, 130, 24, 8);
		iSetColor(160, 230, 255);
		iFilledEllipse(bx, 130, 36, 12);
	}

	// Angled monsoon rain streaks
	iSetColor(200, 220, 240);
	for (int i = 0; i < SNOW_COUNT_2; i++)
	{
		iLine(snowX2[i], snowY2[i], snowX2[i] - 5, snowY2[i] - 18);
	}

	// Floating boats along the river - natural balanced proportions
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int i = 0; i < BOAT_COUNT_2; i++)
	{
		int type = boatType2[i];
		int bw = (type == 0) ? 210 : (type == 1 ? 220 : 210);
		int bh = (type == 0) ? 152 : (type == 1 ? 74 : 137);
		int baseY = (type == 0) ? 95 : (type == 1 ? 105 : 95);

		int bobY = baseY + (int)(sin(boatBobTimer2 + i * 1.4f) * 3.0f);
		int sx = wrapScreenX(boatX2[i], cameraX);

		iShowImage(sx - (bw / 2), bobY, bw, bh, boatTextures[type]);
	}

	glDisable(GL_BLEND);

	// Seeds of Hope (fixed: now correctly reads seedX2/seedY2/seedCollected2/seedCount2)
	for (int i = 0; i < seedCount2; i++)
	{
		if (!seedCollected2[i])
		{
			int sx = wrapScreenX(seedX2[i], cameraX);
			iShowImage(sx - 20, seedY2[i] - 20, 40, 40, seedTex);
		}
	}

	// Fish - natural parabolic jumping animation out of the river with rotation
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int f = 0; f < FISH_COUNT_2; f++)
	{
		if (!fishVisible2[f]) { continue; }

		// Only drawn when leaping out of the water in parabolic motion (not floating horizontally)
		if (fishState2[f] == 1)
		{
			int fx = wrapScreenX(fishX2[f], cameraX);
			int type = fishType2[f];
			int fw = (type == 0) ? 80 : 54;
			int fh = (type == 0) ? 34 : 60;
			int jumpHeight = 220 + (type * 40);

			// Tangent angle along the parabolic arc: vx = 180, vy = 4 * H * (1 - 2t)
			float t = (float)fishJumpProgress2[f] / 80.0f;
			float vx = 180.0f;
			float vy = 4.0f * (float)jumpHeight * (1.0f - 2.0f * t);
			float fishAngle = atan2(vy, vx) * (180.0f / 3.14159265f);

			glPushMatrix();
			glTranslatef((float)fx, (float)fishY2[f], 0.0f);
			glRotatef(fishAngle, 0.0f, 0.0f, 1.0f);
			iShowImage(-fw / 2, -fh / 2, fw, fh, fishTextures[type]);
			glPopMatrix();

			// Sparkling water droplets around airborne fish
			iSetColor(240, 255, 255);
			iFilledCircle(fx - 12, fishY2[f] - 10, 3);
			iFilledCircle(fx + 16, fishY2[f] - 6, 2);
			iFilledCircle(fx - 22, fishY2[f] + 8, 2);

			// Water splash effect when breaking the surface
			if (fishY2[f] < 170)
			{
				iSetColor(220, 240, 255);
				iFilledEllipse(fx - 14, 148, 10, 4);
				iFilledEllipse(fx + 14, 148, 10, 4);
				iFilledEllipse(fx, 150, 16, 6);
			}
		}
	}

	glDisable(GL_BLEND);

	// Hawks - dark silhouette, simple triangular wings
	iSetColor(50, 45, 40);
	for (int h = 0; h < HAWK_COUNT_2; h++)
	{
		if (!hawkActive2[h]) { continue; }
		if (hawkAttackTimer2[h] > 0)
		{
			iSetColor(180, 40, 40);   // flashes red while actively draining Energy
		}
		else
		{
			iSetColor(50, 45, 40);
		}
		int hx = wrapScreenX(hawkX2[h], cameraX);
		int hy = hawkY2[h];
		iFilledEllipse(hx, hy, 14, 8);
		double wingLX[3] = { hx - 6, hx - 36, hx - 6 };
		double wingLY[3] = { hy + 4, hy, hy - 4 };
		iFilledPolygon(wingLX, wingLY, 3);
		double wingRX[3] = { hx + 6, hx + 36, hx + 6 };
		double wingRY[3] = { hy + 4, hy, hy - 4 };
		iFilledPolygon(wingRX, wingRY, 3);
	}
	// Aero - pure natural proportions and graceful flight banking
	if (invulnerableFrames % 4 < 2)
	{
		unsigned int aeroSprite = aeroFacingRight
			? aeroFrames[currentAeroFrame]
			: aeroBackwardFrames[currentAeroFrame];

		int aeroScrX = wrapScreenX(aeroX, cameraX);
		int aw = 88;
		int ah = 116;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPushMatrix();
		glTranslatef((float)aeroScrX + (aw / 2.0f), (float)aeroY + (ah / 2.0f), 0.0f);
		glRotatef(aeroFacingRight ? aeroPitch : -aeroPitch, 0.0f, 0.0f, 1.0f);
		iShowImage(-aw / 2, -ah / 2, aw, ah, aeroSprite);
		glPopMatrix();

		glDisable(GL_BLEND);
	}

	// Obstacle Toucan birds - 4-frame smooth flapping animation, natural undulation, and flight tilt
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int i = 0; i < TOUCAN_COUNT_2; i++)
	{
		int tx = toucanX2[i];
		// Natural undulating swoop: rises during downstroke, glides during upstroke
		float flapCycle = toucanFlapTimer2 * 2.0f + i * 2.1f;
		float ty = (float)toucanY2[i] + sin(flapCycle) * 12.0f;
		float pitch = cos(flapCycle) * 8.0f;
		int frame = ((int)(toucanFlapTimer2 * 4.0f + i * 1.5f)) % 4;

		glPushMatrix();
		glTranslatef((float)tx + 48.0f, ty + 32.0f, 0.0f);
		glRotatef(pitch, 0.0f, 0.0f, 1.0f);
		iShowImage(-48, -32, 96, 64, toucanFrames[frame]);
		glPopMatrix();
	}

	glDisable(GL_BLEND);

	// Flying branches - tumbling debris drifting across the mid-screen band
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int i = 0; i < BRANCH_COUNT_2; i++)
	{
		int bx = wrapScreenX((int)branchX2[i], cameraX);
		int by = (int)branchY2[i];
		int bw = 50;
		int bh = 40;

		if (bx < -70 || bx > 1350) continue;

		glPushMatrix();
		glTranslatef((float)bx, (float)by, 0.0f);
		glRotatef(branchRot2[i], 0.0f, 0.0f, 1.0f);
		iShowImage(-bw / 2, -bh / 2, bw, bh, branchTex);
		glPopMatrix();
	}

	glDisable(GL_BLEND);

	// ---------- HUD ----------

	drawNatureMeterBar(natureMeter, 100);

	drawFeatherLives(lives);

	// Energy Bar - top center, replaces the countdown timer

	drawEnergyBar();


	// PAUSE RESET EXIT
	drawHudIcons();


	// Fog overlay removed for crystal clear background clarity

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

		int msgW = 700, msgH = 300;
		int msgX = (1280 - msgW) / 2;
		int msgY = (720 - msgH) / 2;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		iShowImage(msgX, msgY, msgW, msgH, monsoonMsgTex);
		glDisable(GL_BLEND);

		iSetColor(255, 255, 255);
		iText(490, msgY - 40, (char*)"Press ENTER to Continue", GLUT_BITMAP_HELVETICA_18);
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

void updateLevel2()
{
	if (gameOver && !gameOverSoundPlayed2)
	{
		playGameOverSound();
		gameOverSoundPlayed2 = true;
	}

	// Wave layers scroll continuously, independent of Aero's movement ///
	waveLargeOffset += 0.8f;
	waveMediumOffset += 1.6f;
	waveSmallOffset += 2.8f;

	if (waveLargeOffset > WAVE_TILE_WIDTH) { waveLargeOffset -= WAVE_TILE_WIDTH; }
	if (waveMediumOffset > WAVE_TILE_WIDTH) { waveMediumOffset -= WAVE_TILE_WIDTH; }
	if (waveSmallOffset > WAVE_TILE_WIDTH) { waveSmallOffset -= WAVE_TILE_WIDTH; }

	boatBobTimer2 += 0.04f;


	if (gameOver || levelComplete)
	{
		if (isKeyPressed('r') || isKeyPressed('R'))
		{
			resetLevel2();
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

	// Rain movement only
	for (int i = 0; i < SNOW_COUNT_2; i++)
	{
		snowY2[i] -= 16;
		snowX2[i] -= 5;
		if (snowY2[i] < 0)
		{
			snowY2[i] = 720;
			snowX2[i] = rand() % 1280;
		}
		if (snowX2[i] < 0)
		{
			snowX2[i] += 1280;
		}
	}

	// Fish jump cycle - parabolic motion coming out from the water
	const int JUMP_DURATION = 80;
	const int JUMP_DIST_X = 180;

	for (int f = 0; f < FISH_COUNT_2; f++)
	{
		if (fishState2[f] == 0)
		{
			// Leap trigger assist when Aero approaches ahead
			int aeroScrX = wrapScreenX(aeroX, cameraX);
			int fishScrX = wrapScreenX(fishX2[f], cameraX);
			int distAhead = fishScrX - aeroScrX;
			if (distAhead >= 80 && distAhead <= 320 && fishJumpTimer2[f] > 8)
			{
				fishJumpTimer2[f] = 8;
			}

			fishJumpTimer2[f]--;
			if (fishJumpTimer2[f] <= 0)
			{
				fishState2[f] = 1;
				fishJumpProgress2[f] = 0;
				fishStartX2[f] = fishX2[f];
			}
		}
		else
		{
			fishJumpProgress2[f]++;
			float t = (float)fishJumpProgress2[f] / (float)JUMP_DURATION;
			// Pure parabolic motion: y(t) = y_base + 4 * H * t * (1 - t)
			float arc = 4.0f * t * (1.0f - t);
			if (arc < 0.0f) { arc = 0.0f; }
			int jumpHeight = 220 + (fishType2[f] * 40);
			fishY2[f] = fishBaseY2[f] + (int)(arc * jumpHeight);
			fishX2[f] = fishStartX2[f] + (int)(t * JUMP_DIST_X);
			if (fishX2[f] >= WORLD_WIDTH) { fishX2[f] -= WORLD_WIDTH; }

			if (fishJumpProgress2[f] >= JUMP_DURATION)
			{
				fishState2[f] = 0;
				fishY2[f] = fishBaseY2[f];
				fishJumpTimer2[f] = 30 + (rand() % 40);
			}
		}
	}

	// Aero catches a fish with generous, satisfying hitbox & swoop assist
	{
		int aeroScrX = wrapScreenX(aeroX, cameraX);
		int aeroCenterX = aeroScrX + 44;
		int aeroCenterY = aeroY + 58;

		for (int f = 0; f < FISH_COUNT_2; f++)
		{
			if (!fishVisible2[f]) { continue; }

			int fishScrX = wrapScreenX(fishX2[f], cameraX);
			int fdx = aeroCenterX - fishScrX;
			int fdy = aeroCenterY - fishY2[f];
			int fdist = sqrt((double)((fdx * fdx) + (fdy * fdy)));

			// Aero catches the airborne fish emerging from the water in parabolic arc
			bool airborneCatch = (fishState2[f] == 1) && (fdist < 115 || (abs(fdx) < 85 && abs(fdy) < 85));

			if (airborneCatch)
			{
				energy = energy + 35;
				if (energy > ENERGY_MAX) { energy = ENERGY_MAX; }
				natureMeter = natureMeter + 5;
				if (natureMeter >= 100)
				{
					natureMeter = 100;
					levelComplete = true;
				}
				printf("Fish caught! Energy: %d, Nature: %d\n", energy, natureMeter);

				// Returns to water, quickly ready to leap again
				fishState2[f] = 0;
				fishY2[f] = fishBaseY2[f];
				fishJumpTimer2[f] = 20 + (rand() % 25);
			}
		}
	}

	// Hawks pursue and attack Aero directly - late Monsoon challenge
	int hawkPhase = getSpikePhase2();

	for (int h = 0; h < HAWK_COUNT_2; h++)
	{
		if (hawkCooldown2[h] > 0) { hawkCooldown2[h]--; }

		if (!hawkActive2[h])
		{
			if (hawkCooldown2[h] <= 0 && hawkPhase == 2 && (rand() % 40) == 0)
			{
				hawkActive2[h] = true;
				hawkAttackTimer2[h] = 0;
				hawkX2[h] = cameraX + 1200;
				hawkY2[h] = 650;
			}
		}
		else if (hawkAttackTimer2[h] > 0)
		{
			// Red flash duration only - the hit already happened, no ongoing drain here
			hawkX2[h] = aeroX;
			hawkY2[h] = aeroY;
			hawkAttackTimer2[h]--;
			if (hawkAttackTimer2[h] <= 0)
			{
				hawkActive2[h] = false;
				hawkCooldown2[h] = 300;   // rest before it can attack again
			}
		}
		else
		{
			// Pursuing Aero at a gentle, dodgeable speed
			if (hawkX2[h] < aeroX) { hawkX2[h] += 5; }
			if (hawkX2[h] > aeroX) { hawkX2[h] -= 5; }
			if (hawkY2[h] < aeroY) { hawkY2[h] += 5; }
			if (hawkY2[h] > aeroY) { hawkY2[h] -= 5; }
			int hdx = hawkX2[h] - aeroX;
			int hdy = hawkY2[h] - aeroY;
			int hdist = sqrt((double)((hdx * hdx) + (hdy * hdy)));
			if (hdist < 50)
			{
				hawkAttackTimer2[h] = 60;   // starts the 1-second red flash

				energy -= 3;   // one-time hit on contact, ~3% of the Energy bar
				if (energy < 0) { energy = 0; }
			}
		}
	}

	// Apply the rapid drain while the attack effect is active
	if (hawkAttackEffectTimer2 > 0)
	{
		hawkAttackEffectTimer2--;

		if (hawkAttackEffectTimer2 % 10 == 0)
		{
			energy -= 5;
			if (energy < 0) { energy = 0; }
			if (energy <= 0) { gameOver = true; }
		}
	}


	int previousAeroX = aeroX;
	int previousAeroY = aeroY;

	bool upPressed = isKeyPressed('w') || isKeyPressed('W') || isKeyPressed(' ') || isSpecialKeyPressed(GLUT_KEY_UP);
	bool downPressed = isKeyPressed('s') || isKeyPressed('S') || isSpecialKeyPressed(GLUT_KEY_DOWN);
	bool leftPressed = isKeyPressed('a') || isKeyPressed('A') || isSpecialKeyPressed(GLUT_KEY_LEFT);
	bool rightPressed = isKeyPressed('d') || isKeyPressed('D') || isSpecialKeyPressed(GLUT_KEY_RIGHT);

	if (upPressed) { aeroY += 6; }
	if (downPressed) { aeroY -= 6; }
	if (leftPressed)
	{
		aeroFacingRight = false;
		aeroX -= 6;
	}
	if (rightPressed)
	{
		aeroFacingRight = true;
		aeroX += 7;
	}

	// Automatic forward flight (Aero glides forward through the air, matching Level 1)
	if (!leftPressed && !rightPressed)
	{
		aeroX += 3;
		aeroFacingRight = true;
	}

	windVisualOffsetX = 0.0f;

	float targetPitch = 0.0f;
	if (upPressed) { targetPitch = 15.0f; }
	else if (downPressed) { targetPitch = -12.0f; }
	aeroPitch += (targetPitch - aeroPitch) * 0.18f;

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
	if (aeroY > 648)
	{
		aeroY = 648;
	}


	cameraX = aeroX - 590;
	if (cameraX < 0) { cameraX += WORLD_WIDTH; }
	if (cameraX >= WORLD_WIDTH) { cameraX -= WORLD_WIDTH; }

	// Aero touches any seed
	for (int i = 0; i < seedCount2; i++)
	{
		if (!seedCollected2[i])
		{
			int dx = (aeroX + 50) - seedX2[i];
			int dy = (aeroY + 40) - seedY2[i];
			int distance = sqrt((double)((dx * dx) + (dy * dy)));

			if (distance < 85)
			{
				playSeedCollectSound();
				natureMeter = natureMeter + 6;
				if (natureMeter > 100)
				{
					natureMeter = 100;
				}
				if (natureMeter >= 100)
				{
					levelComplete = true;
					seedCollected2[i] = true;
				}
				else
				{
					spawnSeed2(i);
				}
			}
		}
	}

	// Boats are solid - Aero can't fly through them
	for (int i = 0; i < BOAT_COUNT_2; i++)
	{
		int type = boatType2[i];
		int bw = (type == 0) ? 210 : (type == 1 ? 220 : 210);
		int bh = (type == 0) ? 152 : (type == 1 ? 74 : 137);
		int baseY = (type == 0) ? 95 : (type == 1 ? 105 : 95);
		int bobY = baseY + (int)(sin(boatBobTimer2 + i * 1.4f) * 3.0f);

		int boatLeft = boatX2[i] - (bw / 2);
		int boatRight = boatX2[i] + (bw / 2);
		int boatBottom = bobY;
		int boatTop = bobY + bh;

		// Wrap-aware X overlap, same technique used for other hazards
		int wrappedAeroX = aeroX;
		int midBoat = (boatLeft + boatRight) / 2;
		int diff = wrappedAeroX - midBoat;
		if (diff > WORLD_WIDTH / 2) { wrappedAeroX -= WORLD_WIDTH; }
		if (diff < -WORLD_WIDTH / 2) { wrappedAeroX += WORLD_WIDTH; }

		bool overlapX = (wrappedAeroX + 75 > boatLeft + 15) && (wrappedAeroX + 25 < boatRight - 15);
		bool overlapY = (aeroY < boatTop - 10) && (aeroY + 60 > boatBottom);

		if (overlapX && overlapY)
		{
			aeroX = previousAeroX;
			aeroY = previousAeroY;
		}
	}

	int currentPhase = getSpikePhase2();
	toucanFlapTimer2 += 0.10f;
	int toucanSpeed = 7;

	// Toucan obstacle birds fly right to left across the screen
	for (int i = 0; i < TOUCAN_COUNT_2; i++)
	{
		toucanX2[i] -= toucanSpeed;
		if (toucanX2[i] < -120)
		{
			toucanX2[i] = 1280 + (rand() % 250);
			// Distinct altitude slots so there is always a wide open corridor for Aero
			int altSlot = (i + rand() % 3) % 3;
			if (altSlot == 0) { toucanY2[i] = 260 + (rand() % 60); }
			else if (altSlot == 1) { toucanY2[i] = 390 + (rand() % 70); }
			else { toucanY2[i] = 530 + (rand() % 60); }
		}
	}

	// Flying branches drift right to left across the mid-screen band, tumbling as they go
	for (int i = 0; i < BRANCH_COUNT_2; i++)
	{
		branchX2[i] -= branchSpeed2[i];
		branchRot2[i] += branchRotSpeed2[i];

		if (branchX2[i] < -80.0f)
		{
			branchX2[i] = 1280.0f + 300.0f + (rand() % 300);
			branchY2[i] = 280.0f + (rand() % 220);
			branchSpeed2[i] = 4.0f + ((rand() % 100) / 100.0f) * 3.0f;
			branchRotSpeed2[i] = 1.5f + ((rand() % 100) / 100.0f) * 2.5f;
		}
	}

	// Check if Aero is hit by an obstacle Toucan bird (AABB overlap, more forgiving/reliable than a tiny circle)
	int aeroScreenX = wrapScreenX(aeroX, cameraX);
	int aeroLeft = aeroScreenX + 10;
	int aeroRight = aeroScreenX + 78;
	int aeroTop = aeroY + 100;
	int aeroBottom = aeroY + 16;

	for (int i = 0; i < TOUCAN_COUNT_2; i++)
	{
		if (invulnerableFrames > 0) { break; }

		float flapCycle = toucanFlapTimer2 * 2.0f + i * 2.1f;
		float ty = (float)toucanY2[i] + sin(flapCycle) * 12.0f;

		int toucanLeft = toucanX2[i] + 14;
		int toucanRight = toucanX2[i] + 82;
		int toucanTop = (int)ty + 56;
		int toucanBottom = (int)ty + 8;

		bool overlapX = (aeroRight > toucanLeft) && (aeroLeft < toucanRight);
		bool overlapY = (aeroBottom < toucanTop) && (aeroTop > toucanBottom);

		if (overlapX && overlapY)
		{
			playHurtSound();
			lives = lives - 1;
			invulnerableFrames = 75;
			if (lives <= 0) { gameOver = true; }
			toucanX2[i] = 1280 + (rand() % 300);
			toucanY2[i] = 260 + (rand() % 300);
		}
	}

	// Check if Aero is hit by a flying branch
	for (int i = 0; i < BRANCH_COUNT_2; i++)
	{
		if (invulnerableFrames > 0) { break; }

		int branchScrX = wrapScreenX((int)branchX2[i], cameraX);
		int bdx = (aeroScreenX + 44) - (branchScrX + 25);
		int bdy = (aeroY + 58) - ((int)branchY2[i] + 20);
		int bdist = (int)sqrt((double)((bdx * bdx) + (bdy * bdy)));

		if (bdist < 38)
		{
			playHurtSound();
			lives = lives - 1;
			invulnerableFrames = 75;
			if (lives <= 0) { gameOver = true; }
			branchX2[i] = 1280.0f + 300.0f + (rand() % 300);
			branchY2[i] = 280.0f + (rand() % 220);
		}
	}

	// Lightning state machine
	lightningTimer2--;
	if (lightningTimer2 <= 0)
	{
		if (lightningState2 == 0)
		{
			// a cloud that belongs to the current active phase
			int eligibleClouds[CLOUD_COUNT_2];
			int eligibleCount = 0;
			for (int c = 0; c < CLOUD_COUNT_2; c++)
			{
				if (cloudPhase2[c] == currentPhase)
				{
					eligibleClouds[eligibleCount++] = c;
				}
			}
			if (eligibleCount > 0)
			{
				lightningCloudIndex2 = eligibleClouds[rand() % eligibleCount];
				lightningState2 = 1;
				lightningTimer2 = 45;
			}
			else
			{
				// No active clouds this phase — skip this lightning cycle
				lightningTimer2 = 120 + (rand() % 180);
			}
		}
		else if (lightningState2 == 1)
		{
			lightningState2 = 2;
			lightningTimer2 = 10;

			int strikeScreenX = wrapScreenX(cloudX2[lightningCloudIndex2], cameraX);
			int aeroScreenX2 = wrapScreenX(aeroX, cameraX);
			bool underCloud = (aeroScreenX2 + 100 > strikeScreenX - (cloudWidth2[lightningCloudIndex2] / 2))
				&& (aeroScreenX2 < strikeScreenX + (cloudWidth2[lightningCloudIndex2] / 2));

			if (underCloud && invulnerableFrames <= 0)
			{
				playHurtSound();
				lives = lives - 1;
				invulnerableFrames = 75;
				if (lives <= 0) { gameOver = true; }
			}
		}
		else
		{
			lightningState2 = 0;
			lightningTimer2 = 120 + (rand() % 180);
		}
	}

	if (invulnerableFrames > 0)
	{
		invulnerableFrames--;
	}

	//ENERGY LEVEL

	drainEnergy();

	// Cycle through flap frames dynamically based on flight effort
	if (upPressed)
	{
		aeroAnimCounter += 2; // flap vigorously when climbing
	}
	else
	{
		aeroAnimCounter++; // smooth steady flap when cruising
	}

	if (aeroAnimCounter >= 6)
	{
		aeroAnimCounter = 0;
		currentAeroFrame = (currentAeroFrame + 1) % AERO_FRAME_COUNT;
	}
}
#endif