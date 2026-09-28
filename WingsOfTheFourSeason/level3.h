#ifndef LEVEL3_H 
#define LEVEL3_H 

#include <cstdlib>
#include <cmath>
#include "GameVariables.h"
#include "LifeHUD.h"
#include "Utilities.h"
#include "Settings.h"

// ----------------------------------------------------------------------------
// GAMEPLAY CONSTANTS
// ----------------------------------------------------------------------------
const int NATURE_MAX_3 = 100;

// ----------------------------------------------------------------------------
// ASSET IDENTIFIERS & TEXTURES
// ----------------------------------------------------------------------------
unsigned int desertBgTex3 = 0;
unsigned int sunFlareTex3 = 0;
unsigned int sunRaysTex3 = 0;

// Cacti Obstacles
const int CACTUS_VARIANT_COUNT_3 = 4;
unsigned int cactusSprites3[CACTUS_VARIANT_COUNT_3];
const int cactusWidthByVariant3[CACTUS_VARIANT_COUNT_3] = { 110, 120, 135, 125 };
const int cactusHeightByVariant3[CACTUS_VARIANT_COUNT_3] = { 260, 240, 175, 230 };

// Distant Cacti
const int FAR_CACTUS_VARIANT_COUNT_3 = 3;
unsigned int farCactusSprites3[FAR_CACTUS_VARIANT_COUNT_3];

// Smooth Animated Walking Camels
const int CAMEL_FRAME_COUNT_3 = 4;
unsigned int camelFrames3[CAMEL_FRAME_COUNT_3];

// Desert Falcon Obstacle Birds
const int FALCON_FRAME_COUNT_3 = 4;
unsigned int falconFrames3[FALCON_FRAME_COUNT_3];

// Pickups & Hazards
unsigned int waterDropTex3 = 0;
unsigned int desertRoseTex3 = 0;
unsigned int tumbleweedTex3 = 0;

float aeroPitch3 = 0.0f;
int hydrationBoostTimer3 = 0;

// ----------------------------------------------------------------------------
// ATMOSPHERE & TIMERS
// ----------------------------------------------------------------------------
float sunHeatTimer3 = 0.0f;

// Moving Sand Wind Streaks
const int SAND_STREAK_COUNT_3 = 30;
float sandStreakX3[SAND_STREAK_COUNT_3];
float sandStreakY3[SAND_STREAK_COUNT_3];
float sandStreakSpeed3[SAND_STREAK_COUNT_3];
int sandStreakLen3[SAND_STREAK_COUNT_3];

// Heat Dust Particles
const int DUST_COUNT_3 = 40;
int dustX3[DUST_COUNT_3];
int dustY3[DUST_COUNT_3];
float dustSpeed3[DUST_COUNT_3];

// ----------------------------------------------------------------------------
// GAMEPLAY OBJECTS & ARRAYS
// ----------------------------------------------------------------------------

// Seeds of Hope (+8 Nature Points)
const int MAX_SEEDS_3 = 7;
int seedX3[MAX_SEEDS_3];
int seedY3[MAX_SEEDS_3];
bool seedCollected3[MAX_SEEDS_3];
int seedCount3 = 6;
int seedsGathered3 = 0;

bool gameOverSoundPlayed3 = false;

// Water Droplets (+35 Energy, +5 Nature Points, Speed Glide)
const int MAX_WATER_3 = 5;
int waterX3[MAX_WATER_3];
int waterY3[MAX_WATER_3];
bool waterCollected3[MAX_WATER_3];
float waterBobTimer3 = 0.0f;

// Desert Rose (+1 Life/HP, +10 Nature Points, Floral Shield)
const int MAX_ROSE_3 = 4;
int roseX3[MAX_ROSE_3];
int roseY3[MAX_ROSE_3];
bool roseCollected3[MAX_ROSE_3];
float roseBobTimer3 = 0.0f;

// Foreground Cactus Obstacles
const int CACTUS_COUNT_3 = 7;
int cactusX3[CACTUS_COUNT_3] = { 400, 920, 1450, 1980, 2520, 3050, 3450 };
int cactusVariant3[CACTUS_COUNT_3] = { 0, 1, 2, 3, 0, 1, 3 };
const int CACTUS_BASE_Y_3 = 135; // Planted securely on top of sand dunes

// Distant Parallax Cacti
const int FAR_CACTUS_COUNT_3 = 8;
int farCactusX3[FAR_CACTUS_COUNT_3] = { 250, 720, 1200, 1680, 2150, 2620, 3100, 3500 };
int farCactusVariant3[FAR_CACTUS_COUNT_3] = { 0, 1, 2, 0, 1, 2, 0, 1 };

// Smooth Walking Camels
const int CAMEL_COUNT_3 = 3;
float camelX3[CAMEL_COUNT_3];
int camelBaseY3[CAMEL_COUNT_3] = { 110, 130, 100 };
float camelSpeed3[CAMEL_COUNT_3] = { 1.2f, 1.0f, 1.3f };
float camelTimer3 = 0.0f;

// Desert Falcon Obstacle Birds (Gentle and predictable flight)
const int FALCON_COUNT_3 = 3;
float falconX3[FALCON_COUNT_3];
float falconY3[FALCON_COUNT_3];
float falconBaseY3[FALCON_COUNT_3];
float falconSpeed3[FALCON_COUNT_3];
float falconFlapTimer3 = 0.0f;

// Rolling Tumbleweeds
const int TUMBLE_COUNT_3 = 3;
float tumbleX3[TUMBLE_COUNT_3];
float tumbleY3[TUMBLE_COUNT_3];
float tumbleBaseY3[TUMBLE_COUNT_3];
float tumbleSpeed3[TUMBLE_COUNT_3];
float tumbleRot3[TUMBLE_COUNT_3];
float tumbleTimer3 = 0.0f;

// ----------------------------------------------------------------------------
// ASSET LOADING
// ----------------------------------------------------------------------------
void loadLevel3Assets()
{
	static bool loaded = false;
	if (loaded) return;
	loaded = true;

	desertBgTex3 = iLoadImage("Assets/Desert/DesertBG.png");
	sunFlareTex3 = iLoadImage("Assets/Desert/SunFlare.png");
	sunRaysTex3 = iLoadImage("Assets/Desert/SunRays.png");

	cactusSprites3[0] = iLoadImage("Assets/Desert/Cactus1.png");
	cactusSprites3[1] = iLoadImage("Assets/Desert/Cactus2.png");
	cactusSprites3[2] = iLoadImage("Assets/Desert/Cactus3.png");
	cactusSprites3[3] = iLoadImage("Assets/Desert/Cactus4.png");

	farCactusSprites3[0] = iLoadImage("Assets/Desert/FarCactus_1.png");
	farCactusSprites3[1] = iLoadImage("Assets/Desert/FarCactus_2.png");
	farCactusSprites3[2] = iLoadImage("Assets/Desert/FarCactus_3.png");

	camelFrames3[0] = iLoadImage("Assets/Desert/Camel_0.png");
	camelFrames3[1] = iLoadImage("Assets/Desert/Camel_1.png");
	camelFrames3[2] = iLoadImage("Assets/Desert/Camel_2.png");
	camelFrames3[3] = iLoadImage("Assets/Desert/Camel_3.png");

	falconFrames3[0] = iLoadImage("Assets/Desert/Falcon_0.png");
	falconFrames3[1] = iLoadImage("Assets/Desert/Falcon_1.png");
	falconFrames3[2] = iLoadImage("Assets/Desert/Falcon_2.png");
	falconFrames3[3] = iLoadImage("Assets/Desert/Falcon_3.png");

	waterDropTex3 = iLoadImage("Assets/Desert/WaterDrop.png");
	desertRoseTex3 = iLoadImage("Assets/Desert/DesertRose.png");
	tumbleweedTex3 = iLoadImage("Assets/Desert/Tumbleweed.png");
}

void loadtreeSprites3()
{
	loadLevel3Assets();
}

void loadFartreeSprites3()
{
	loadLevel3Assets();
}

// ----------------------------------------------------------------------------
// SPAWN HELPERS
// ----------------------------------------------------------------------------
const int SEED3_MIN_SPACING = 260;

void spawnSeed3(int i)
{
	bool tooClose = true;
	int attempts = 0;

	while (tooClose && attempts < 100)
	{
		attempts++;
		int spawnMin = aeroX + 220;
		int spawnMax = WORLD_WIDTH - 200;

		if (spawnMin >= spawnMax)
		{
			spawnMin = 350;
			spawnMax = WORLD_WIDTH - 200;
		}

		seedX3[i] = spawnMin + (rand() % (spawnMax - spawnMin));
		seedY3[i] = 230 + (rand() % 360);

		tooClose = false;
		for (int c = 0; c < CACTUS_COUNT_3; c++)
		{
			bool overlapX = (seedX3[i] + 40 > cactusX3[c] - 40) && (seedX3[i] - 40 < cactusX3[c] + 40);
			bool overlapY = (seedY3[i] - 40 < CACTUS_BASE_Y_3 + 260);

			if (overlapX && overlapY)
			{
				tooClose = true;
				break;
			}
		}

		if (!tooClose)
		{
			for (int o = 0; o < seedCount3; o++)
			{
				if (o == i) { continue; }
				int dx = seedX3[i] - seedX3[o];
				if (abs(dx) < SEED3_MIN_SPACING)
				{
					tooClose = true;
					break;
				}
			}
		}
	}

	seedCollected3[i] = false;
}

void spawnWater3(int i)
{
	bool tooClose = true;
	int attempts = 0;

	while (tooClose && attempts < 100)
	{
		attempts++;
		int spawnMin = aeroX + 200;
		int spawnMax = WORLD_WIDTH - 200;

		if (spawnMin >= spawnMax)
		{
			spawnMin = 350;
			spawnMax = WORLD_WIDTH - 200;
		}

		waterX3[i] = spawnMin + (rand() % (spawnMax - spawnMin));
		waterY3[i] = 210 + (rand() % 380);

		tooClose = false;
		for (int c = 0; c < CACTUS_COUNT_3; c++)
		{
			bool overlapX = (waterX3[i] + 40 > cactusX3[c] - 40) && (waterX3[i] - 40 < cactusX3[c] + 40);
			bool overlapY = (waterY3[i] - 40 < CACTUS_BASE_Y_3 + 260);

			if (overlapX && overlapY)
			{
				tooClose = true;
				break;
			}
		}
	}

	waterCollected3[i] = false;
}

void spawnDesertRose3(int i)
{
	bool tooClose = true;
	int attempts = 0;

	while (tooClose && attempts < 100)
	{
		attempts++;
		int spawnMin = aeroX + 250;
		int spawnMax = WORLD_WIDTH - 200;

		if (spawnMin >= spawnMax)
		{
			spawnMin = 350;
			spawnMax = WORLD_WIDTH - 200;
		}

		roseX3[i] = spawnMin + (rand() % (spawnMax - spawnMin));
		roseY3[i] = 230 + (rand() % 350);

		tooClose = false;
		for (int c = 0; c < CACTUS_COUNT_3; c++)
		{
			bool overlapX = (roseX3[i] + 40 > cactusX3[c] - 40) && (roseX3[i] - 40 < cactusX3[c] + 40);
			bool overlapY = (roseY3[i] - 40 < CACTUS_BASE_Y_3 + 260);

			if (overlapX && overlapY)
			{
				tooClose = true;
				break;
			}
		}
	}

	roseCollected3[i] = false;
}

// ----------------------------------------------------------------------------
// RESET LEVEL 3
// ----------------------------------------------------------------------------
void resetLevel3()
{
	loadLevel3Assets();

	aeroX = 400;
	aeroY = 320;
	aeroPitch3 = 0.0f;
	aeroFacingRight = true;
	hydrationBoostTimer3 = 0;
	cameraX = 0;
	lives = 5;            // Generous starting lives for easy completion
	natureMeter = 0;

	gameOver = false;
	gameOverSoundPlayed3 = false;

	levelComplete = false;
	timeLeft = 60;
	frameCounter = 0;
	seedsGathered3 = 0;

	invulnerableFrames = 0;
	energy = 100;         // Full starting energy

	sunHeatTimer3 = 0.0f;
	waterBobTimer3 = 0.0f;
	roseBobTimer3 = 0.0f;
	camelTimer3 = 0.0f;
	falconFlapTimer3 = 0.0f;
	tumbleTimer3 = 0.0f;

	// Sand Wind Streaks
	for (int i = 0; i < SAND_STREAK_COUNT_3; i++)
	{
		sandStreakX3[i] = (float)(rand() % 1280);
		sandStreakY3[i] = 100.0f + (float)(rand() % 400);
		sandStreakSpeed3[i] = 5.0f + ((rand() % 100) / 100.0f) * 6.0f;
		sandStreakLen3[i] = 25 + (rand() % 50);
	}

	// Dust motes
	for (int i = 0; i < DUST_COUNT_3; i++)
	{
		dustX3[i] = rand() % 1280;
		dustY3[i] = rand() % 720;
		dustSpeed3[i] = 0.6f + ((rand() % 100) / 100.0f) * 0.8f;
	}

	// Camels walking peacefully across the world
	camelX3[0] = 500.0f;
	camelX3[1] = 1700.0f;
	camelX3[2] = 2900.0f;

	// Forward-soaring desert falcons (flying forward to the right)
	falconX3[0] = 200.0f;  falconBaseY3[0] = 370.0f; falconSpeed3[0] = 4.8f;
	falconX3[1] = -350.0f; falconBaseY3[1] = 480.0f; falconSpeed3[1] = 5.6f;
	falconX3[2] = -850.0f; falconBaseY3[2] = 310.0f; falconSpeed3[2] = 4.2f;

	// Relaxed tumbleweeds
	for (int i = 0; i < TUMBLE_COUNT_3; i++)
	{
		tumbleX3[i] = 1280.0f + (i * 450.0f) + (rand() % 150);
		tumbleBaseY3[i] = 140.0f + (rand() % 30);
		tumbleSpeed3[i] = 3.2f + ((rand() % 100) / 100.0f) * 1.5f;
		tumbleRot3[i] = 0.0f;
	}

	// Seeds of Hope
	seedCount3 = 6;
	for (int i = 0; i < seedCount3; i++)
	{
		spawnSeed3(i);
	}

	// Water Droplets
	for (int i = 0; i < MAX_WATER_3; i++)
	{
		spawnWater3(i);
	}

	// Desert Roses
	for (int i = 0; i < MAX_ROSE_3; i++)
	{
		spawnDesertRose3(i);
	}
}

// ----------------------------------------------------------------------------
// DRAW LEVEL 3
// ----------------------------------------------------------------------------
void drawLevel3()
{
	// 1. STABLE PANORAMIC DESERT BACKGROUND (No seam tears, smooth & clean)
	iShowImage(0, 0, 1280, 720, desertBgTex3);

	// 2. NATURAL STEADY SUNLIGHT (Zero flashing / strobing!)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Soft additive sunlight

	// Volumetric sunbeam light shafts (Gentle, steady illumination)
	glColor4f(1.0f, 0.95f, 0.75f, 0.20f);
	iShowImage(0, 0, 1280, 720, sunRaysTex3);

	// Pure golden optical solar flare over the sun (Steady radiance, no flashing)
	int fx = 640 - 170;
	int fy = 570 - 170;
	glColor4f(1.0f, 0.95f, 0.82f, 0.65f);
	iShowImage(fx, fy, 340, 340, sunFlareTex3);

	glDisable(GL_BLEND);

	// 3. ANIMATED DESERT SAND WIND STREAKS (Natural moving desert breeze)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int i = 0; i < SAND_STREAK_COUNT_3; i++)
	{
		float alpha = 0.22f + ((i % 4) * 0.06f);
		glColor4f(0.95f, 0.82f, 0.52f, alpha);
		glLineWidth((i % 3 == 0) ? 2.0f : 1.2f);
		glBegin(GL_LINES);
		glVertex2f(sandStreakX3[i], sandStreakY3[i]);
		glVertex2f(sandStreakX3[i] + sandStreakLen3[i], sandStreakY3[i]);
		glEnd();
	}
	glLineWidth(1.0f);

	// 4. PARALLAX DISTANT CACTI (Smooth half-speed camera scrolling)
	for (int i = 0; i < FAR_CACTUS_COUNT_3; i++)
	{
		int farW = 75;
		int farH = 110;
		int farX = wrapScreenX(farCactusX3[i], cameraX / 2) - (farW / 2);
		int farY = 160;

		iShowImage(farX, farY, farW, farH, farCactusSprites3[farCactusVariant3[i]]);
	}

	// 5. SMOOTH WALKING CAMELS (Natural leg strides & ground shadows)
	for (int i = 0; i < CAMEL_COUNT_3; i++)
	{
		int cx = wrapScreenX((int)camelX3[i], cameraX);
		int cFrame = ((int)(camelTimer3 * 4.5f + i * 1.5f)) % CAMEL_FRAME_COUNT_3;
		float stepBob = sin(camelTimer3 * 9.0f + i * 2.0f) * 2.2f;
		int cw = 165;
		int ch = 115;
		int cy = camelBaseY3[i] + (int)stepBob;

		// Soft ground contact shadow
		glColor4f(0.48f, 0.32f, 0.16f, 0.40f);
		iFilledEllipse(cx, cy + 8, cw * 0.44, 12);

		iShowImage(cx - (cw / 2), cy, cw, ch, camelFrames3[cFrame]);
	}

	// 6. FOREGROUND CACTI WITH NATURAL GROUNDING (Embedded into sand dunes!)
	for (int i = 0; i < CACTUS_COUNT_3; i++)
	{
		int v = cactusVariant3[i];
		int cw = cactusWidthByVariant3[v];
		int ch = cactusHeightByVariant3[v];
		int drawX = wrapScreenX(cactusX3[i], cameraX) - (cw / 2);
		int drawY = CACTUS_BASE_Y_3;

		// A. Directional contact shadow cast onto the sand dunes
		glColor4f(0.45f, 0.30f, 0.14f, 0.45f);
		iFilledEllipse(drawX + (cw / 2) + 8, drawY + 6, (int)(cw * 0.46f), 12);

		// B. Subtle desert wind micro-sway
		float sway = sin(sunHeatTimer3 * 1.5f + i * 1.2f) * 1.0f;

		glPushMatrix();
		glTranslatef((float)(drawX + cw / 2), (float)drawY, 0.0f);
		glRotatef(sway, 0.0f, 0.0f, 1.0f);
		iShowImage(-cw / 2, 0, cw, ch, cactusSprites3[v]);
		glPopMatrix();

		// C. Sand Dune Bedding: Mounds sand around stem base so roots are naturally buried!
		glColor4f(0.86f, 0.70f, 0.44f, 0.90f);
		iFilledEllipse(drawX + (cw / 2), drawY + 5, (int)(cw * 0.32f), 9);
		glColor4f(0.96f, 0.82f, 0.52f, 0.70f); // Warm sunlit sand crest
		iFilledEllipse(drawX + (cw / 2) - 4, drawY + 7, (int)(cw * 0.20f), 5);
	}

	// 7. SEEDS OF HOPE
	for (int i = 0; i < seedCount3; i++)
	{
		if (!seedCollected3[i])
		{
			int sx = wrapScreenX(seedX3[i], cameraX);
			float seedBob = sin(waterBobTimer3 * 1.5f + i) * 5.0f;
			iShowImage(sx - 20, (int)(seedY3[i] + seedBob) - 20, 40, 40, seedTex);
		}
	}

	// 8. WATER DROPLETS
	for (int i = 0; i < MAX_WATER_3; i++)
	{
		if (!waterCollected3[i])
		{
			int wx = wrapScreenX(waterX3[i], cameraX);
			float dropBob = sin(waterBobTimer3 * 2.0f + i * 1.6f) * 5.0f;
			int ww = 38;
			int wh = 46;
			iShowImage(wx - (ww / 2), (int)(waterY3[i] + dropBob) - (wh / 2), ww, wh, waterDropTex3);
		}
	}

	// 9. DESERT ROSE
	for (int i = 0; i < MAX_ROSE_3; i++)
	{
		if (!roseCollected3[i])
		{
			int rx = wrapScreenX(roseX3[i], cameraX);
			float roseBob = cos(roseBobTimer3 * 1.8f + i * 1.4f) * 5.0f;
			int rw = 48;
			int rh = 48;
			iShowImage(rx - (rw / 2), (int)(roseY3[i] + roseBob) - (rh / 2), rw, rh, desertRoseTex3);
		}
	}

	// 10. ROLLING TUMBLEWEED HAZARDS
	for (int i = 0; i < TUMBLE_COUNT_3; i++)
	{
		int tx = (int)tumbleX3[i];
		int ty = (int)tumbleY3[i];
		int tw = 48;
		int th = 48;

		glColor4f(0.50f, 0.35f, 0.18f, 0.35f);
		iFilledEllipse(tx, (int)tumbleBaseY3[i] + 4, 22, 8);

		glPushMatrix();
		glTranslatef((float)tx, (float)ty, 0.0f);
		glRotatef(tumbleRot3[i], 0.0f, 0.0f, 1.0f);
		iShowImage(-tw / 2, -th / 2, tw, th, tumbleweedTex3);
		glPopMatrix();
	}

	// 11. DESERT FALCON BIRDS (Moving FORWARD to the right with natural undulation & dune shadow)
	for (int i = 0; i < FALCON_COUNT_3; i++)
	{
		int fx = (int)falconX3[i];
		if (fx < -100 || fx > 1380) continue;

		float flapCycle = falconFlapTimer3 * 2.2f + i * 2.1f;
		float fy = falconY3[i];
		float pitch = cos(flapCycle) * 8.0f;
		int frame = ((int)(falconFlapTimer3 * 4.0f + i * 1.5f)) % FALCON_FRAME_COUNT_3;
		int fw = 86;
		int fh = 56;

		// Soft desert bird shadow gliding across the sand dunes far below
		glColor4f(0.48f, 0.32f, 0.16f, 0.22f);
		iFilledEllipse(fx, 138, 36, 9);

		glPushMatrix();
		glTranslatef((float)fx, fy, 0.0f);
		glRotatef(pitch, 0.0f, 0.0f, 1.0f);
		iShowImage(-fw / 2, -fh / 2, fw, fh, falconFrames3[frame]);
		glPopMatrix();
	}

	// 12. AERO (Player Bird with Direction, Pitch & Aura)
	if (invulnerableFrames % 4 < 2)
	{
		unsigned int aeroSprite = aeroFacingRight
			? aeroFrames[currentAeroFrame]
			: aeroBackwardFrames[currentAeroFrame];

		int aeroScrX = wrapScreenX(aeroX, cameraX);
		int aw = 88;
		int ah = 116;

		// Hydration Glide Aura
		if (hydrationBoostTimer3 > 0)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glColor4f(0.4f, 0.85f, 1.0f, 0.35f);
			iFilledCircle(aeroScrX + (aw / 2), aeroY + (ah / 2), 50);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		// Floral Shield Aura
		if (invulnerableFrames > 35)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glColor4f(1.0f, 0.6f, 0.75f, 0.40f);
			iFilledCircle(aeroScrX + (aw / 2), aeroY + (ah / 2), 54);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		glPushMatrix();
		glTranslatef((float)aeroScrX + (aw / 2.0f), (float)aeroY + (ah / 2.0f), 0.0f);
		glRotatef(aeroFacingRight ? aeroPitch3 : -aeroPitch3, 0.0f, 0.0f, 1.0f);
		iShowImage(-aw / 2, -ah / 2, aw, ah, aeroSprite);
		glPopMatrix();
	}

	glDisable(GL_BLEND);

	// 13. HEAT DUST PARTICLES
	iSetColor(255, 242, 190);
	for (int i = 0; i < DUST_COUNT_3; i++)
	{
		iFilledCircle(dustX3[i], dustY3[i], (i % 3 == 0) ? 2 : 1);
	}

	// ------------------------------------------------------------------------
	// ACCESSIBLE HUD
	// ------------------------------------------------------------------------

	// Nature Restoration Meter (Fast & clear feedback)
	drawNatureMeterBar(natureMeter, NATURE_MAX_3);

	iSetColor(255, 255, 255);
	char natureLabel[40];
	sprintf_s(natureLabel, "SUMMER RESTORATION: %d%%", natureMeter);
	iText(48, 745, natureLabel);

	// Life HUD (Feathers)
	drawFeatherLives(lives);

	// Energy Bar
	drawEnergyBar();

	// HUD Controls
	drawHudIcons();

	// Popups / Overlays
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
		iShowImage(msgX, msgY, msgW, msgH, summerMsgTex);
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

// ----------------------------------------------------------------------------
// UPDATE LEVEL 3
// ----------------------------------------------------------------------------
void updateLevel3()
{
	if (gameOver && !gameOverSoundPlayed3)
	{
		playGameOverSound();
		gameOverSoundPlayed3 = true;
	}

	if (gameOver || levelComplete)
	{
		if (isKeyPressed('r') || isKeyPressed('R'))
		{
			resetLevel3();
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

	// 1. Timers
	sunHeatTimer3 += 0.04f;
	waterBobTimer3 += 0.05f;
	roseBobTimer3 += 0.05f;
	camelTimer3 += 0.04f;
	falconFlapTimer3 += 0.05f;
	tumbleTimer3 += 0.04f;

	if (hydrationBoostTimer3 > 0)
	{
		hydrationBoostTimer3--;
	}

	// 2. Animated Sand Wind Streaks
	for (int i = 0; i < SAND_STREAK_COUNT_3; i++)
	{
		sandStreakX3[i] -= sandStreakSpeed3[i];
		if (sandStreakX3[i] < -sandStreakLen3[i])
		{
			sandStreakX3[i] = 1280.0f + (rand() % 200);
			sandStreakY3[i] = 100.0f + (float)(rand() % 400);
		}
	}

	// 3. Heat Dust Particles
	for (int i = 0; i < DUST_COUNT_3; i++)
	{
		dustY3[i] += (int)dustSpeed3[i];
		dustX3[i] += (int)(sin((dustY3[i] * 0.03f) + (sunHeatTimer3 * 2.0f) + i) * 1.5f);
		if (dustY3[i] > 720)
		{
			dustY3[i] = 0;
			dustX3[i] = rand() % 1280;
		}
	}

	// 4. Camels Smoothly Walking Across the World
	for (int i = 0; i < CAMEL_COUNT_3; i++)
	{
		camelX3[i] += camelSpeed3[i];
		if (camelX3[i] >= WORLD_WIDTH)
		{
			camelX3[i] -= WORLD_WIDTH;
		}
	}

	// 5. Rolling Tumbleweeds
	for (int i = 0; i < TUMBLE_COUNT_3; i++)
	{
		tumbleX3[i] -= tumbleSpeed3[i];
		tumbleRot3[i] += tumbleSpeed3[i] * 2.2f;

		float bounce = fabs(sin(tumbleTimer3 * 2.4f + i * 1.7f));
		tumbleY3[i] = tumbleBaseY3[i] + (bounce * 26.0f);

		if (tumbleX3[i] < -80.0f)
		{
			tumbleX3[i] = 1280.0f + 250.0f + (rand() % 300);
			tumbleBaseY3[i] = 140.0f + (rand() % 30);
		}
	}

	// 6. Desert Falcons (Soaring gracefully FORWARD to the right!)
	for (int i = 0; i < FALCON_COUNT_3; i++)
	{
		falconX3[i] += falconSpeed3[i];

		float flapCycle = falconFlapTimer3 * 2.2f + i * 2.1f;
		falconY3[i] = falconBaseY3[i] + sin(flapCycle) * 20.0f;

		if (falconX3[i] > 1280.0f + 160.0f)
		{
			falconX3[i] = -150.0f - (rand() % 350);
			falconBaseY3[i] = 240.0f + (rand() % 280);
			falconSpeed3[i] = 4.2f + ((rand() % 100) / 100.0f) * 2.2f;
		}
	}

	// 7. AUTHENTIC FLAPPY BIRD CONTROLS & FLIGHT
	int previousAeroX = aeroX;
	int previousAeroY = aeroY;

	int moveSpeed = (hydrationBoostTimer3 > 0) ? 9 : 6;

	bool upPressed = isKeyPressed('w') || isKeyPressed('W') || isKeyPressed(' ') || isSpecialKeyPressed(GLUT_KEY_UP);
	bool downPressed = isKeyPressed('s') || isKeyPressed('S') || isSpecialKeyPressed(GLUT_KEY_DOWN);
	bool leftPressed = isKeyPressed('a') || isKeyPressed('A') || isSpecialKeyPressed(GLUT_KEY_LEFT);
	bool rightPressed = isKeyPressed('d') || isKeyPressed('D') || isSpecialKeyPressed(GLUT_KEY_RIGHT);

	if (upPressed)   { aeroY += moveSpeed; }
	if (downPressed) { aeroY -= moveSpeed; }

	if (leftPressed)
	{
		aeroFacingRight = false;
		aeroX -= moveSpeed;
	}
	if (rightPressed)
	{
		aeroFacingRight = true;
		aeroX += moveSpeed + 1;
	}

	// Automatic forward flight (Flappy Bird forward glide, matching Level 1 & Level 2)
	if (!leftPressed && !rightPressed)
	{
		aeroX += 3;
		aeroFacingRight = true;
	}

	// Smooth flight pitch banking
	float targetPitch = 0.0f;
	if (upPressed) { targetPitch = 14.0f; }
	else if (downPressed) { targetPitch = -12.0f; }
	aeroPitch3 += (targetPitch - aeroPitch3) * 0.18f;

	// Standard WORLD_WIDTH = 3600 boundary wrapping
	if (aeroX < 0) { aeroX += WORLD_WIDTH; }
	if (aeroX >= WORLD_WIDTH) { aeroX -= WORLD_WIDTH; }
	if (aeroY < 150) { aeroY = 150; }
	if (aeroY > 640) { aeroY = 640; }

	// 8. Fair Cactus Hitboxes (Trunk collision only)
	for (int i = 0; i < CACTUS_COUNT_3; i++)
	{
		int ch = cactusHeightByVariant3[cactusVariant3[i]];

		int trunkLeft = cactusX3[i] - 18;
		int trunkRight = cactusX3[i] + 18;
		int trunkTop = CACTUS_BASE_Y_3 + ch - 25;

		bool overlapX = (aeroX + 65 > trunkLeft) && (aeroX + 22 < trunkRight);
		bool overlapY = (aeroY < trunkTop) && (aeroY + 50 > CACTUS_BASE_Y_3);

		if (overlapX && overlapY)
		{
			aeroX = previousAeroX;
			aeroY = previousAeroY;
			if (invulnerableFrames <= 0)
			{
				playHurtSound();
				lives--;
				invulnerableFrames = 60;
				if (lives <= 0) { gameOver = true; }
			}
		}
	}

	// Camera follows Aero smoothly
	cameraX = aeroX - 590;
	if (cameraX < 0) { cameraX += WORLD_WIDTH; }
	if (cameraX >= WORLD_WIDTH) { cameraX -= WORLD_WIDTH; }

	int aeroScreenX = wrapScreenX(aeroX, cameraX);

	// 9. Seeds of Hope (+8 Nature Points!)
	for (int i = 0; i < seedCount3; i++)
	{
		if (!seedCollected3[i])
		{
			int dx = (aeroX + 44) - seedX3[i];
			int dy = (aeroY + 58) - seedY3[i];
			int distance = (int)sqrt((double)((dx * dx) + (dy * dy)));

			if (distance < 55)
			{
				natureMeter += 8;
				if (natureMeter >= NATURE_MAX_3)
				{
					natureMeter = NATURE_MAX_3;
					levelComplete = true;
					seedCollected3[i] = true;
				}
				else
				{
					spawnSeed3(i);
				}
			}
		}
	}

	// 10. Water Droplets (+35 Energy, +5 Nature Points, Speed Glide)
	for (int i = 0; i < MAX_WATER_3; i++)
	{
		if (!waterCollected3[i])
		{
			int dx = (aeroX + 44) - waterX3[i];
			int dy = (aeroY + 58) - waterY3[i];
			int distance = (int)sqrt((double)((dx * dx) + (dy * dy)));

			if (distance < 55)
			{
				energy += 35;
				if (energy > ENERGY_MAX) { energy = ENERGY_MAX; }
				natureMeter += 5;
				if (natureMeter >= NATURE_MAX_3)
				{
					natureMeter = NATURE_MAX_3;
					levelComplete = true;
				}
				hydrationBoostTimer3 = 120; // 2 seconds of speed glide
				spawnWater3(i);
			}
		}
	}

	// 11. Desert Rose (+1 Life/HP, +10 Nature Points, Floral Shield)
	for (int i = 0; i < MAX_ROSE_3; i++)
	{
		if (!roseCollected3[i])
		{
			int dx = (aeroX + 44) - roseX3[i];
			int dy = (aeroY + 58) - roseY3[i];
			int distance = (int)sqrt((double)((dx * dx) + (dy * dy)));

			if (distance < 55)
			{
				if (lives < 5)
				{
					lives++;
				}
				playSeedCollectSound();
				natureMeter += 4;
				if (natureMeter >= NATURE_MAX_3)
				{
					natureMeter = NATURE_MAX_3;
					levelComplete = true;
					roseCollected3[i] = true;
				}
				else
				{
					spawnDesertRose3(i);
				}
				invulnerableFrames = 100; // Protective floral shield
			}
		}
	}

	// 12. Falcon Collision (Forgiving)
	for (int i = 0; i < FALCON_COUNT_3; i++)
	{
		int fdx = (aeroScreenX + 44) - (int)falconX3[i];
		int fdy = (aeroY + 58) - (int)falconY3[i];
		int fdist = (int)sqrt((double)((fdx * fdx) + (fdy * fdy)));

		if (fdist < 46 && invulnerableFrames <= 0)
		{
			playHurtSound();
			lives--;
			invulnerableFrames = 60;
			if (lives <= 0) { gameOver = true; }
			falconBaseY3[i] += 70.0f;
			falconX3[i] += 120.0f;
		}
	}

	// 13. Tumbleweed Collision
	for (int i = 0; i < TUMBLE_COUNT_3; i++)
	{
		int tdx = (aeroScreenX + 44) - (int)tumbleX3[i];
		int tdy = (aeroY + 58) - (int)tumbleY3[i];
		int tdist = (int)sqrt((double)((tdx * tdx) + (tdy * tdy)));

		if (tdist < 42 && invulnerableFrames <= 0)
		{
			playHurtSound();
			lives--;
			invulnerableFrames = 60;
			if (lives <= 0) { gameOver = true; }
			tumbleX3[i] = 1280.0f + 250.0f + (rand() % 300);
		}
	}

	// 14. Invulnerability Timer
	if (invulnerableFrames > 0)
	{
		invulnerableFrames--;
	}

	// 15. Slow Energy Drain (Drains every 90 frames = 1.5s)
	frameCounter++;
	if (frameCounter >= 90)
	{
		frameCounter = 0;
		energy--;
		if (energy <= 0)
		{
			energy = 0;
			gameOver = true;
		}
	}

	// 16. Aero Flap Animation
	aeroAnimCounter++;
	if (aeroAnimCounter >= 6)
	{
		aeroAnimCounter = 0;
		currentAeroFrame = (currentAeroFrame + 1) % AERO_FRAME_COUNT;
	}
}

#endif