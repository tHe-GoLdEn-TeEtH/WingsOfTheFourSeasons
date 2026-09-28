#ifndef LEVEL4_H
#define LEVEL4_H

#include <cstdlib>
#include <cmath>
#include "GameVariables.h"
#include "LifeHUD.h"
#include "Utilities.h"
#include "Settings.h"

// ----------------------------------------------------------------------------
// CONSTANTS & GAMEPLAY SETTINGS
// ----------------------------------------------------------------------------
const int NATURE_MAX_4 = 100;
const int SPRING_GROUND_Y = 150;

// ----------------------------------------------------------------------------
// ASSET IDENTIFIERS & TEXTURES
// ----------------------------------------------------------------------------
unsigned int springBgTex4 = 0;
unsigned int hunterAimTex4 = 0;
unsigned int hunterShootTex4 = 0;
unsigned int hunterTowerTex4 = 0;
unsigned int bulletTex4 = 0;
unsigned int aimWarningTex4 = 0;
unsigned int springTree1Tex4 = 0;
unsigned int springTree2Tex4 = 0;
unsigned int netTrapTex4 = 0;
unsigned int springBlossomTex4 = 0;
unsigned int springDewTex4 = 0;
unsigned int aegisShieldTex4 = 0;
unsigned int sakuraPetalTex4 = 0;

// ----------------------------------------------------------------------------
// ATMOSPHERE & TIMERS
// ----------------------------------------------------------------------------
float aeroPitch4 = 0.0f;
int   springGlideTimer4 = 0;
bool  aegisShieldActive4 = false;
float shieldRot4 = 0.0f;
float globalSpringTimer4 = 0.0f;
bool gameOverSoundPlayed4 = false;

// ----------------------------------------------------------------------------
// SAKURA DRIFTING PETALS (Atmospheric breeze particles)
// ----------------------------------------------------------------------------
const int SAKURA_PETAL_COUNT_4 = 32;
float petalX4[SAKURA_PETAL_COUNT_4];
float petalY4[SAKURA_PETAL_COUNT_4];
float petalSpeedX4[SAKURA_PETAL_COUNT_4];
float petalSpeedY4[SAKURA_PETAL_COUNT_4];
float petalRot4[SAKURA_PETAL_COUNT_4];
float petalRotSpeed4[SAKURA_PETAL_COUNT_4];
float petalPhase4[SAKURA_PETAL_COUNT_4];

// ----------------------------------------------------------------------------
// HUNTERS (ENEMIES)
// ----------------------------------------------------------------------------
const int HUNTER_COUNT_4 = 6;
enum HunterState4 { HUNTER_IDLE_4, HUNTER_AIMING_4, HUNTER_SHOOTING_4, HUNTER_COOLDOWN_4 };

int   hunterX4[HUNTER_COUNT_4] = { 550, 1150, 1750, 2350, 2950, 3450 };
int   hunterY4[HUNTER_COUNT_4] = { 150, 310, 150, 310, 150, 310 }; // 3 on ground, 3 perched on watchtower platforms
bool  hunterOnTower4[HUNTER_COUNT_4] = { false, true, false, true, false, true };
HunterState4 hunterState4[HUNTER_COUNT_4];
int   hunterTimer4[HUNTER_COUNT_4];
bool  hunterFacingLeft4[HUNTER_COUNT_4];
float hunterAimTargetX4[HUNTER_COUNT_4];
float hunterAimTargetY4[HUNTER_COUNT_4];

// ----------------------------------------------------------------------------
// BULLETS (PROJECTILES)
// ----------------------------------------------------------------------------
const int MAX_BULLETS_4 = 14;
struct Bullet4
{
	float x, y;
	float vx, vy;
	float angle;
	bool  active;
	int   lifetime;
};
Bullet4 bullets4[MAX_BULLETS_4];

// ----------------------------------------------------------------------------
// OBSTACLES: WATCHTOWERS, SPRING TREES & NET TRAPS
// ----------------------------------------------------------------------------
// Hunter Watchtowers
const int TOWER_COUNT_4 = 3;
int towerX4[TOWER_COUNT_4] = { 1150, 2350, 3450 };
const int TOWER_DRAW_WIDTH_4 = 140;
const int TOWER_DRAW_HEIGHT_4 = 276;

// Spring Trees (Blooming Cherry & Fresh Oak)
const int TREE_COUNT_4 = 6;
int treeX4[TREE_COUNT_4] = { 380, 850, 1500, 2050, 2680, 3200 };
int treeVariant4[TREE_COUNT_4] = { 0, 1, 0, 1, 0, 1 }; // 0 = Cherry (SpringTree_1), 1 = Oak (SpringTree_2)
const int TREE_DRAW_WIDTH_4 = 180;
const int TREE_DRAW_HEIGHT_4 = 270;

// Aerial Hunter Snare Net Traps
const int NET_COUNT_4 = 4;
int netX4[NET_COUNT_4] = { 720, 1420, 2180, 2850 };
int netY4[NET_COUNT_4] = { 470, 500, 460, 510 };
const int NET_DRAW_WIDTH_4 = 95;
const int NET_DRAW_HEIGHT_4 = 110;

// ----------------------------------------------------------------------------
// PICKUPS & POWERUPS
// ----------------------------------------------------------------------------
// Seeds of Hope (+6 Nature Points)
// Seeds of Hope (+6 Nature Points)
const int MAX_SEEDS_4 = 9;
int  seedX4[MAX_SEEDS_4];
int  seedY4[MAX_SEEDS_4];
bool seedCollected4[MAX_SEEDS_4];
int  seedCount4 = 9;

// Spring Blossoms (+10 Nature Points, +1 Life)
const int MAX_BLOSSOMS_4 = 4;
int  blossomX4[MAX_BLOSSOMS_4];
int  blossomY4[MAX_BLOSSOMS_4];
bool blossomCollected4[MAX_BLOSSOMS_4];

// Spring Dewdrops (+35 Energy, Speed Glide Boost)
const int MAX_DEW_4 = 4;
int  dewX4[MAX_DEW_4];
int  dewY4[MAX_DEW_4];
bool dewCollected4[MAX_DEW_4];

// Floral Aegis Shield (Bullet Deflection Powerup)
const int MAX_SHIELDS_4 = 3;
int  shieldX4[MAX_SHIELDS_4];
int  shieldY4[MAX_SHIELDS_4];
bool shieldCollected4[MAX_SHIELDS_4];

// ----------------------------------------------------------------------------
// ASSET LOADING
// ----------------------------------------------------------------------------
void loadLevel4Assets()
{
	static bool loaded = false;
	if (loaded) return;
	loaded = true;

	springBgTex4 = iLoadImage("Assets/Spring/SpringBG.png");
	hunterAimTex4 = iLoadImage("Assets/Spring/Hunter_Aim.png");
	hunterShootTex4 = iLoadImage("Assets/Spring/Hunter_Shoot.png");
	hunterTowerTex4 = iLoadImage("Assets/Spring/Hunter_Tower.png");
	bulletTex4 = iLoadImage("Assets/Spring/Bullet.png");
	aimWarningTex4 = iLoadImage("Assets/Spring/AimWarning.png");
	springTree1Tex4 = iLoadImage("Assets/Spring/SpringTree_1.png");
	springTree2Tex4 = iLoadImage("Assets/Spring/SpringTree_2.png");
	netTrapTex4 = iLoadImage("Assets/Spring/NetTrap.png");
	springBlossomTex4 = iLoadImage("Assets/Spring/SpringBlossom.png");
	springDewTex4 = iLoadImage("Assets/Spring/SpringDew.png");
	aegisShieldTex4 = iLoadImage("Assets/Spring/AegisShield.png");
	sakuraPetalTex4 = iLoadImage("Assets/Spring/SakuraPetal.png");
}

// ----------------------------------------------------------------------------
// SPAWN HELPERS
// ----------------------------------------------------------------------------
const int SEED4_MIN_SPACING = 260;

void spawnSeed4(int i)
{
	bool tooClose = true;
	int attempts = 0;

	while (tooClose && attempts < 100)
	{
		attempts++;
		int spawnMin = 400;
		int spawnMax = WORLD_WIDTH - 250;
		seedX4[i] = spawnMin + (rand() % (spawnMax - spawnMin));
		seedY4[i] = 230 + (rand() % 350);

		tooClose = false;
		for (int o = 0; o < MAX_SEEDS_4; o++)
		{
			if (o == i) { continue; }
			int dx = seedX4[i] - seedX4[o];
			if (abs(dx) < SEED4_MIN_SPACING)
			{
				tooClose = true;
				break;
			}
		}
	}

	seedCollected4[i] = false;
}

void spawnBlossom4(int i)
{
	int spawnMin = 450;
	int spawnMax = WORLD_WIDTH - 300;
	blossomX4[i] = spawnMin + (rand() % (spawnMax - spawnMin));
	blossomY4[i] = 250 + (rand() % 330);
	blossomCollected4[i] = false;
}

void spawnDew4(int i)
{
	int spawnMin = 500;
	int spawnMax = WORLD_WIDTH - 250;
	dewX4[i] = spawnMin + (rand() % (spawnMax - spawnMin));
	dewY4[i] = 220 + (rand() % 360);
	dewCollected4[i] = false;
}

void spawnShield4(int i)
{
	int spawnMin = 600;
	int spawnMax = WORLD_WIDTH - 400;
	shieldX4[i] = spawnMin + (rand() % (spawnMax - spawnMin));
	shieldY4[i] = 280 + (rand() % 270);
	shieldCollected4[i] = false;
}

// ----------------------------------------------------------------------------
// BULLET SPAWNING
// ----------------------------------------------------------------------------
void fireBullet4(float startX, float startY, float targetX, float targetY)
{
	for (int i = 0; i < MAX_BULLETS_4; i++)
	{
		if (!bullets4[i].active)
		{
			bullets4[i].active = true;
			bullets4[i].x = startX;
			bullets4[i].y = startY;
			bullets4[i].lifetime = 140;

			float dx = targetX - startX;
			float dy = targetY - startY;
			float dist = sqrtf(dx * dx + dy * dy);
			if (dist < 1.0f) dist = 1.0f;

			float speed = 10.5f;
			bullets4[i].vx = (dx / dist) * speed;
			bullets4[i].vy = (dy / dist) * speed;
			bullets4[i].angle = atan2f(dy, dx) * (180.0f / 3.14159265f);
			break;
		}
	}
}

// ----------------------------------------------------------------------------
// RESET LEVEL 4
// ----------------------------------------------------------------------------
void resetLevel4()
{
	loadLevel4Assets();

	aeroX = 150;
	aeroY = 320;
	aeroFacingRight = true;
	currentAeroFrame = 0;
	aeroAnimCounter = 0;
	cameraX = 0;
	aeroPitch4 = 0.0f;
	springGlideTimer4 = 0;
	aegisShieldActive4 = false;
	shieldRot4 = 0.0f;
	globalSpringTimer4 = 0.0f;

	lives = 3;
	natureMeter = 0;
	energy = ENERGY_MAX;
	gameOver = false;
	gameOverSoundPlayed4 = false;
	levelComplete = false;
	paused = false;
	leaveToMenuRequested = false;
	escKeyWasDown = false;
	pKeyWasDown = false;
	timeLeft = 60;
	frameCounter = 0;
	invulnerableFrames = 0;

	// Reset Petals
	for (int i = 0; i < SAKURA_PETAL_COUNT_4; i++)
	{
		petalX4[i] = (float)(rand() % 1280);
		petalY4[i] = (float)(rand() % 720);
		petalSpeedX4[i] = 1.8f + ((rand() % 100) / 100.0f) * 2.0f;
		petalSpeedY4[i] = 0.6f + ((rand() % 100) / 100.0f) * 1.2f;
		petalRot4[i] = (float)(rand() % 360);
		petalRotSpeed4[i] = 1.2f + ((rand() % 100) / 100.0f) * 2.2f;
		petalPhase4[i] = ((rand() % 100) / 100.0f) * 6.28f;
	}

	// Reset Hunters
	for (int i = 0; i < HUNTER_COUNT_4; i++)
	{
		hunterState4[i] = HUNTER_IDLE_4;
		hunterTimer4[i] = 40 + (rand() % 70);
		hunterFacingLeft4[i] = true;
		hunterAimTargetX4[i] = 0;
		hunterAimTargetY4[i] = 0;
	}

	// Reset Bullets
	for (int i = 0; i < MAX_BULLETS_4; i++)
	{
		bullets4[i].active = false;
	}

	// Reset Pickups
	for (int i = 0; i < MAX_SEEDS_4; i++)    spawnSeed4(i);
	for (int i = 0; i < MAX_BLOSSOMS_4; i++) spawnBlossom4(i);
	for (int i = 0; i < MAX_DEW_4; i++)      spawnDew4(i);
	for (int i = 0; i < MAX_SHIELDS_4; i++)  spawnShield4(i);
}

// ----------------------------------------------------------------------------
// UPDATE LEVEL 4
// ----------------------------------------------------------------------------
void updateLevel4()
{
	if (gameOver && !gameOverSoundPlayed4)
	{
		playGameOverSound();
		gameOverSoundPlayed4 = true;
	}

	// Check ESC key immediately - allows returning to menu at ANY time (playing, paused, game over, or victory!)
	if (isKeyPressed(27) != 0)
	{
		leaveToMenuRequested = true;
		paused = false;
		return;
	}

	// Check Pause key
	bool pKeyDown = (isKeyPressed('p') != 0) || (isKeyPressed('P') != 0);
	if (pKeyDown && !pKeyWasDown)
	{
		paused = !paused;
	}
	pKeyWasDown = pKeyDown;

	// If paused, don't update gameplay
	if (paused) return;

	// If game over, allow quick restart with R key
	if (gameOver)
	{
		if ((isKeyPressed('r') != 0) || (isKeyPressed('R') != 0))
		{
			resetLevel4();
		}
		return;
	}

	// If level complete, wait for Enter (leaderboard) or ESC (menu)
	if (levelComplete)
	{
		return;
	}

	drainEnergy();

	globalSpringTimer4 += 0.035f;
	shieldRot4 += 3.5f;
	if (springGlideTimer4 > 0) springGlideTimer4--;

	if (invulnerableFrames > 0) invulnerableFrames--;

	int previousAeroX = aeroX;
	int previousAeroY = aeroY;

	// Input controls
	bool upPressed = (isKeyPressed('w') != 0) || (isKeyPressed('W') != 0) || (isKeyPressed(' ') != 0) || (isSpecialKeyPressed(GLUT_KEY_UP) != 0);
	bool downPressed = (isKeyPressed('s') != 0) || (isKeyPressed('S') != 0) || (isSpecialKeyPressed(GLUT_KEY_DOWN) != 0);
	bool leftPressed = (isKeyPressed('a') != 0) || (isKeyPressed('A') != 0) || (isSpecialKeyPressed(GLUT_KEY_LEFT) != 0);
	bool rightPressed = (isKeyPressed('d') != 0) || (isKeyPressed('D') != 0) || (isSpecialKeyPressed(GLUT_KEY_RIGHT) != 0);

	int vertSpeed = 6;
	int horizSpeed = (springGlideTimer4 > 0) ? 9 : 7;

	if (upPressed)
	{
		aeroY += vertSpeed;
		aeroPitch4 = (aeroPitch4 < 18.0f) ? aeroPitch4 + 2.5f : 18.0f;
	}
	else if (downPressed)
	{
		aeroY -= vertSpeed;
		aeroPitch4 = (aeroPitch4 > -18.0f) ? aeroPitch4 - 2.5f : -18.0f;
	}
	else
	{
		aeroPitch4 *= 0.88f;
	}

	if (leftPressed)
	{
		aeroX -= horizSpeed;
		aeroFacingRight = false;
	}
	if (rightPressed)
	{
		aeroX += horizSpeed;
		aeroFacingRight = true;
	}

	// Automatic forward flight (smooth flappy bird glide)
	if (!leftPressed && !rightPressed)
	{
		aeroX += (springGlideTimer4 > 0) ? 5 : 3;
		aeroFacingRight = true;
	}

	// Wrap world horizontally
	if (aeroX < 0) aeroX += WORLD_WIDTH;
	if (aeroX >= WORLD_WIDTH) aeroX -= WORLD_WIDTH;

	// Keep within screen vertical bounds
	if (aeroY < SPRING_GROUND_Y) aeroY = SPRING_GROUND_Y;
	if (aeroY > 640) aeroY = 640;

	// Wing Flap Animation
	aeroAnimCounter++;
	if (aeroAnimCounter >= 4)
	{
		aeroAnimCounter = 0;
		currentAeroFrame = (currentAeroFrame + 1) % AERO_FRAME_COUNT;
	}

	// ------------------------------------------------------------------------
	// CAMERA POSITIONING
	// ------------------------------------------------------------------------
	cameraX = aeroX - 350;
	if (cameraX < 0) cameraX += WORLD_WIDTH;
	if (cameraX >= WORLD_WIDTH) cameraX -= WORLD_WIDTH;

	// ------------------------------------------------------------------------
	// SAKURA PETALS BREEZE PARTICLES
	// ------------------------------------------------------------------------
	int deltaX = aeroX - previousAeroX;
	if (deltaX < -WORLD_WIDTH / 2) deltaX += WORLD_WIDTH;
	if (deltaX >  WORLD_WIDTH / 2) deltaX -= WORLD_WIDTH;

	for (int i = 0; i < SAKURA_PETAL_COUNT_4; i++)
	{
		petalX4[i] -= petalSpeedX4[i] + (deltaX * 0.2f);
		petalY4[i] -= petalSpeedY4[i] + sinf(globalSpringTimer4 * 2.0f + petalPhase4[i]) * 0.7f;
		petalRot4[i] += petalRotSpeed4[i];

		if (petalX4[i] < -20)
		{
			petalX4[i] = 1300;
			petalY4[i] = (float)(rand() % 720);
		}
		if (petalY4[i] < -20)
		{
			petalY4[i] = 730;
			petalX4[i] = (float)(rand() % 1280);
		}
	}

	// ------------------------------------------------------------------------
	// HUNTER AI (AIMING, TELEGRAPHING & SHOOTING)
	// ------------------------------------------------------------------------
	for (int i = 0; i < HUNTER_COUNT_4; i++)
	{
		int hWorldX = hunterX4[i];
		int hWorldY = hunterY4[i];

		// Calculate relative horizontal distance across wrapped world
		int relX = aeroX - hWorldX;
		if (relX >  WORLD_WIDTH / 2) relX -= WORLD_WIDTH;
		if (relX < -WORLD_WIDTH / 2) relX += WORLD_WIDTH;

		// Direction hunter faces
		hunterFacingLeft4[i] = (relX < 0);

		float dist = sqrtf((float)(relX * relX + (aeroY - hWorldY) * (aeroY - hWorldY)));

		switch (hunterState4[i])
		{
		case HUNTER_IDLE_4:
			// Detect Aero within range (~700px)
			if (dist < 720.0f)
			{
				hunterTimer4[i]--;
				if (hunterTimer4[i] <= 0)
				{
					// Enter Aiming state (0.55s telegraph)
					hunterState4[i] = HUNTER_AIMING_4;
					hunterTimer4[i] = 34; // 34 frames of warning reticle telegraph
					hunterAimTargetX4[i] = (float)aeroX;
					hunterAimTargetY4[i] = (float)aeroY;
				}
			}
			break;

		case HUNTER_AIMING_4:
			// Track Aero smoothly while aiming
			hunterAimTargetX4[i] += (aeroX - hunterAimTargetX4[i]) * 0.28f;
			hunterAimTargetY4[i] += (aeroY - hunterAimTargetY4[i]) * 0.28f;

			hunterTimer4[i]--;
			if (hunterTimer4[i] <= 0)
			{
				// Shoot!
				hunterState4[i] = HUNTER_SHOOTING_4;
				hunterTimer4[i] = 14; // Muzzle flash display duration

				// Spawn bullet towards target
				float muzzleOffsetX = hunterFacingLeft4[i] ? -42.0f : 42.0f;
				fireBullet4((float)hWorldX + muzzleOffsetX, (float)hWorldY + 54.0f,
					hunterAimTargetX4[i] + 44.0f, hunterAimTargetY4[i] + 45.0f);
			}
			break;

		case HUNTER_SHOOTING_4:
			hunterTimer4[i]--;
			if (hunterTimer4[i] <= 0)
			{
				// Enter reload cooldown
				hunterState4[i] = HUNTER_COOLDOWN_4;
				hunterTimer4[i] = 130 + (rand() % 65); // 2.2 - 3.2 seconds reload
			}
			break;

		case HUNTER_COOLDOWN_4:
			hunterTimer4[i]--;
			if (hunterTimer4[i] <= 0)
			{
				hunterState4[i] = HUNTER_IDLE_4;
				hunterTimer4[i] = 30 + (rand() % 40);
			}
			break;
		}
	}

	// ------------------------------------------------------------------------
	// BULLET PHYSICS & COLLISION
	// ------------------------------------------------------------------------
	for (int i = 0; i < MAX_BULLETS_4; i++)
	{
		if (bullets4[i].active)
		{
			bullets4[i].x += bullets4[i].vx;
			bullets4[i].y += bullets4[i].vy;
			bullets4[i].lifetime--;

			// Wrap bullet in world horizontally
			if (bullets4[i].x < 0) bullets4[i].x += WORLD_WIDTH;
			if (bullets4[i].x >= WORLD_WIDTH) bullets4[i].x -= WORLD_WIDTH;

			if (bullets4[i].lifetime <= 0 || bullets4[i].y < 80 || bullets4[i].y > 750)
			{
				bullets4[i].active = false;
				continue;
			}

			// Collision check with Aero
			int bRelX = (int)bullets4[i].x - (aeroX + 44);
			if (bRelX >  WORLD_WIDTH / 2) bRelX -= WORLD_WIDTH;
			if (bRelX < -WORLD_WIDTH / 2) bRelX += WORLD_WIDTH;
			float bRelY = bullets4[i].y - (aeroY + 48);

			float bulletDist = sqrtf((float)(bRelX * bRelX + bRelY * bRelY));
			if (bulletDist < 36.0f)
			{
				bullets4[i].active = false;

				if (aegisShieldActive4)
				{
					// Aegis shield absorbs the bullet safely!
					aegisShieldActive4 = false;
					invulnerableFrames = 40;
				}
				else if (invulnerableFrames <= 0)
				{
					// Aero hit by hunter bullet!
					playHurtSound();
					lives--;
					invulnerableFrames = 65;
					aeroX = previousAeroX - 25;
					if (lives <= 0)
					{
						gameOver = true;
					}
				}
			}
		}
	}

	// ------------------------------------------------------------------------
	// OBSTACLE COLLISIONS (TREES, TOWER LOGS & AERIAL NETS)
	// ------------------------------------------------------------------------
	// 1. Spring Trees (Trunk & Lower Canopy Collision)
	for (int i = 0; i < TREE_COUNT_4; i++)
	{
		int tw = TREE_DRAW_WIDTH_4;
		int th = TREE_DRAW_HEIGHT_4;
		int trunkLeft = treeX4[i] - 28;
		int trunkRight = treeX4[i] + 28;

		int wrappedAeroX = aeroX + 44;
		int diff = wrappedAeroX - treeX4[i];
		if (diff >  WORLD_WIDTH / 2) wrappedAeroX -= WORLD_WIDTH;
		if (diff < -WORLD_WIDTH / 2) wrappedAeroX += WORLD_WIDTH;

		bool hitX = (wrappedAeroX + 30 > trunkLeft) && (wrappedAeroX - 30 < trunkRight);
		bool hitY = (aeroY < SPRING_GROUND_Y + th - 30) && (aeroY + 50 > SPRING_GROUND_Y);

		if (hitX && hitY)
		{
			if (invulnerableFrames <= 0)
			{
				playHurtSound();
				lives--;
				invulnerableFrames = 60;
				aeroX = previousAeroX - 25;
				if (lives <= 0) gameOver = true;
			}
		}
	}

	// 2. Hunter Watchtowers (Solid timber collision)
	for (int i = 0; i < TOWER_COUNT_4; i++)
	{
		int tw = TOWER_DRAW_WIDTH_4;
		int th = TOWER_DRAW_HEIGHT_4;
		int tLeft = towerX4[i] - (tw / 2) + 18;
		int tRight = towerX4[i] + (tw / 2) - 18;

		int wrappedAeroX = aeroX + 44;
		int diff = wrappedAeroX - towerX4[i];
		if (diff >  WORLD_WIDTH / 2) wrappedAeroX -= WORLD_WIDTH;
		if (diff < -WORLD_WIDTH / 2) wrappedAeroX += WORLD_WIDTH;

		bool hitX = (wrappedAeroX + 30 > tLeft) && (wrappedAeroX - 30 < tRight);
		bool hitY = (aeroY < SPRING_GROUND_Y + th - 20) && (aeroY + 50 > SPRING_GROUND_Y);

		if (hitX && hitY)
		{
			if (invulnerableFrames <= 0)
			{
				playHurtSound();
				lives--;
				invulnerableFrames = 60;
				aeroX = previousAeroX - 25;
				if (lives <= 0) gameOver = true;
			}
		}
	}

	// 3. Hanging Aerial Net Traps
	for (int i = 0; i < NET_COUNT_4; i++)
	{
		int nw = NET_DRAW_WIDTH_4;
		int nh = NET_DRAW_HEIGHT_4;
		int nLeft = netX4[i] - (nw / 2) + 12;
		int nRight = netX4[i] + (nw / 2) - 12;

		int wrappedAeroX = aeroX + 44;
		int diff = wrappedAeroX - netX4[i];
		if (diff >  WORLD_WIDTH / 2) wrappedAeroX -= WORLD_WIDTH;
		if (diff < -WORLD_WIDTH / 2) wrappedAeroX += WORLD_WIDTH;

		bool hitX = (wrappedAeroX + 30 > nLeft) && (wrappedAeroX - 30 < nRight);
		bool hitY = (aeroY < netY4[i] + nh - 10) && (aeroY + 50 > netY4[i]);

		if (hitX && hitY)
		{
			if (invulnerableFrames <= 0)
			{
				playHurtSound();
				lives--;
				invulnerableFrames = 60;
				aeroX = previousAeroX - 25;
				if (lives <= 0) gameOver = true;
			}
		}
	}

	// ------------------------------------------------------------------------
	// PICKUP COLLECTION
	// ------------------------------------------------------------------------
	// Seeds of Hope (+6 Nature Points)
	for (int i = 0; i < seedCount4; i++)
	{
		if (!seedCollected4[i])
		{
			int diff = (aeroX + 44) - seedX4[i];
			if (diff >  WORLD_WIDTH / 2) diff -= WORLD_WIDTH;
			if (diff < -WORLD_WIDTH / 2) diff += WORLD_WIDTH;

			bool collX = (abs(diff) < 45);
			bool collY = (abs((aeroY + 48) - seedY4[i]) < 45);

			if (collX && collY)
			{
				playSeedCollectSound();
				seedCollected4[i] = true;
				natureMeter += 6;
				if (natureMeter >= NATURE_MAX_4)
				{
					natureMeter = NATURE_MAX_4;
					levelComplete = true;
				}
			}
		}
	}

	// Spring Blossoms (+10 Nature Points, +1 Life)
	for (int i = 0; i < MAX_BLOSSOMS_4; i++)
	{
		if (!blossomCollected4[i])
		{
			int diff = (aeroX + 44) - blossomX4[i];
			if (diff >  WORLD_WIDTH / 2) diff -= WORLD_WIDTH;
			if (diff < -WORLD_WIDTH / 2) diff += WORLD_WIDTH;

			bool collX = (abs(diff) < 45);
			bool collY = (abs((aeroY + 48) - blossomY4[i]) < 45);

			if (collX && collY)
			{
				blossomCollected4[i] = true;
				if (lives < 3) lives++;
				natureMeter += 10;
				if (natureMeter >= NATURE_MAX_4)
				{
					natureMeter = NATURE_MAX_4;
					levelComplete = true;
				}
			}
		}
	}

	// Spring Dewdrops (+35 Energy, Speed Glide)
	for (int i = 0; i < MAX_DEW_4; i++)
	{
		if (!dewCollected4[i])
		{
			int diff = (aeroX + 44) - dewX4[i];
			if (diff >  WORLD_WIDTH / 2) diff -= WORLD_WIDTH;
			if (diff < -WORLD_WIDTH / 2) diff += WORLD_WIDTH;

			bool collX = (abs(diff) < 45);
			bool collY = (abs((aeroY + 48) - dewY4[i]) < 45);

			if (collX && collY)
			{
				dewCollected4[i] = true;
				energy += 35;
				if (energy > ENERGY_MAX) energy = ENERGY_MAX;
				natureMeter += 5;
				springGlideTimer4 = 160; // Smooth speed glide boost!
				if (natureMeter >= NATURE_MAX_4)
				{
					natureMeter = NATURE_MAX_4;
					levelComplete = true;
				}
			}
		}
	}

	// Floral Aegis Shield (Bullet Deflection Powerup)
	for (int i = 0; i < MAX_SHIELDS_4; i++)
	{
		if (!shieldCollected4[i])
		{
			int diff = (aeroX + 44) - shieldX4[i];
			if (diff >  WORLD_WIDTH / 2) diff -= WORLD_WIDTH;
			if (diff < -WORLD_WIDTH / 2) diff += WORLD_WIDTH;

			bool collX = (abs(diff) < 45);
			bool collY = (abs((aeroY + 48) - shieldY4[i]) < 45);

			if (collX && collY)
			{
				shieldCollected4[i] = true;
				aegisShieldActive4 = true;
				natureMeter += 5;
				if (natureMeter >= NATURE_MAX_4)
				{
					natureMeter = NATURE_MAX_4;
					levelComplete = true;
				}
			}
		}
	}
}

// ----------------------------------------------------------------------------
// DRAW LEVEL 4
// ----------------------------------------------------------------------------
void drawLevel4()
{
	// 1. STABLE PANORAMIC SPRING BACKGROUND (Pure landscape painting, no seam tears)
	iShowImage(0, 0, 1280, 720, springBgTex4);

	// Enable Clean OpenGL Alpha Testing & Alpha Blending for all sprites
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.05f);

	// 2. HUNTER WATCHTOWERS (Firmly grounded on the meadow)
	for (int i = 0; i < TOWER_COUNT_4; i++)
	{
		int tx = wrapScreenX(towerX4[i], cameraX);
		int tw = TOWER_DRAW_WIDTH_4;
		int th = TOWER_DRAW_HEIGHT_4;
		if (tx < -180 || tx > 1460) continue;

		// Ground contact shadow
		glColor4f(0.18f, 0.28f, 0.12f, 0.40f);
		iFilledEllipse(tx, SPRING_GROUND_Y + 4, (int)(tw * 0.44f), 12);

		iShowImage(tx - (tw / 2), SPRING_GROUND_Y, tw, th, hunterTowerTex4);
	}

	// 3. SPRING TREES (Cherry Blossom & Spring Oak Obstacles)
	for (int i = 0; i < TREE_COUNT_4; i++)
	{
		int v = treeVariant4[i];
		int tw = TREE_DRAW_WIDTH_4;
		int th = TREE_DRAW_HEIGHT_4;
		int tx = wrapScreenX(treeX4[i], cameraX);
		if (tx < -200 || tx > 1480) continue;

		// Soft tree base ground shadow
		glColor4f(0.18f, 0.28f, 0.12f, 0.42f);
		iFilledEllipse(tx, SPRING_GROUND_Y + 5, (int)(tw * 0.42f), 14);

		// Subtle gentle breeze sway
		float sway = sinf(globalSpringTimer4 * 1.6f + i * 1.4f) * 1.2f;

		glPushMatrix();
		glTranslatef((float)tx, (float)SPRING_GROUND_Y, 0.0f);
		glRotatef(sway, 0.0f, 0.0f, 1.0f);
		iShowImage(-tw / 2, 0, tw, th, (v == 0) ? springTree1Tex4 : springTree2Tex4);
		glPopMatrix();
	}

	// 4. AERIAL HANGING NET TRAPS
	for (int i = 0; i < NET_COUNT_4; i++)
	{
		int nx = wrapScreenX(netX4[i], cameraX);
		int ny = netY4[i];
		int nw = NET_DRAW_WIDTH_4;
		int nh = NET_DRAW_HEIGHT_4;
		if (nx < -140 || nx > 1420) continue;

		// Gentle pendulum sway in the spring breeze
		float netSway = sinf(globalSpringTimer4 * 2.0f + i * 2.0f) * 2.5f;

		glPushMatrix();
		glTranslatef((float)nx, (float)(ny + nh), 0.0f);
		glRotatef(netSway, 0.0f, 0.0f, 1.0f);
		iShowImage(-nw / 2, -nh, nw, nh, netTrapTex4);
		glPopMatrix();
	}

	// 5. HUNTERS & WARNING TELEGRAPHS
	for (int i = 0; i < HUNTER_COUNT_4; i++)
	{
		int hx = wrapScreenX(hunterX4[i], cameraX);
		int hy = hunterY4[i];

		if (hx < -140 || hx > 1420) continue;

		// Ground shadow for ground hunters
		if (!hunterOnTower4[i])
		{
			glColor4f(0.18f, 0.28f, 0.12f, 0.40f);
			iFilledEllipse(hx, hy + 4, 32, 10);
		}

		// Warning Telegraph: Red Laser Line & Reticle during AIMING phase
		if (hunterState4[i] == HUNTER_AIMING_4)
		{
			int targetScrX = wrapScreenX((int)hunterAimTargetX4[i], cameraX) + 44;
			int targetScrY = (int)hunterAimTargetY4[i] + 48;

			// Pulsing alpha laser line
			float pulse = 0.45f + 0.35f * sinf(globalSpringTimer4 * 14.0f);
			glColor4f(1.0f, 0.15f, 0.15f, pulse);
			glLineWidth(2.2f);
			glBegin(GL_LINES);
			glVertex2f((float)hx, (float)(hy + 52));
			glVertex2f((float)targetScrX, (float)targetScrY);
			glEnd();
			glLineWidth(1.0f);

			// Warning lock-on reticle over Aero
			int rw = 54;
			int rh = 54;
			iShowImage(targetScrX - (rw / 2), targetScrY - (rh / 2), rw, rh, aimWarningTex4);
		}

		// Choose hunter sprite (Aim pose vs Muzzle flash Shoot pose)
		bool isShooting = (hunterState4[i] == HUNTER_SHOOTING_4);
		unsigned int hunterTex = isShooting ? hunterShootTex4 : hunterAimTex4;
		int drawH = 114;
		int drawW = isShooting ? 122 : 76;

		// Render Hunter with proper facing direction
		glPushMatrix();
		glTranslatef((float)hx, (float)hy, 0.0f);
		if (!hunterFacingLeft4[i])
		{
			// Facing right: flip horizontally
			glScalef(-1.0f, 1.0f, 1.0f);
		}
		iShowImage(-drawW / 2, 0, drawW, drawH, hunterTex);
		glPopMatrix();
	}

	// 6. BULLET PROJECTILES (With glowing flare trail)
	for (int i = 0; i < MAX_BULLETS_4; i++)
	{
		if (bullets4[i].active)
		{
			int bx = wrapScreenX((int)bullets4[i].x, cameraX);
			int by = (int)bullets4[i].y;
			int bw = 50;
			int bh = 16;

			if (bx < -70 || bx > 1350) continue;

			glPushMatrix();
			glTranslatef((float)bx, (float)by, 0.0f);
			glRotatef(bullets4[i].angle, 0.0f, 0.0f, 1.0f);
			iShowImage(-bw / 2, -bh / 2, bw, bh, bulletTex4);
			glPopMatrix();
		}
	}

	// 7. PICKUPS: SEEDS, BLOSSOMS, DEWDROPS & AEGIS SHIELDS
	// Seeds of Hope
	for (int i = 0; i < seedCount4; i++)
	{
		if (!seedCollected4[i])
		{
			int sx = wrapScreenX(seedX4[i], cameraX);
			float bob = sinf(globalSpringTimer4 * 2.2f + i) * 6.0f;
			iShowImage(sx - 20, (int)(seedY4[i] + bob) - 20, 40, 40, seedTex);
		}
	}

	// Spring Blossoms
	for (int i = 0; i < MAX_BLOSSOMS_4; i++)
	{
		if (!blossomCollected4[i])
		{
			int bx = wrapScreenX(blossomX4[i], cameraX);
			float bob = cosf(globalSpringTimer4 * 2.4f + i * 1.5f) * 6.0f;
			int bw = 46;
			int bh = 46;
			iShowImage(bx - (bw / 2), (int)(blossomY4[i] + bob) - (bh / 2), bw, bh, springBlossomTex4);
		}
	}

	// Spring Dewdrops
	for (int i = 0; i < MAX_DEW_4; i++)
	{
		if (!dewCollected4[i])
		{
			int dx = wrapScreenX(dewX4[i], cameraX);
			float bob = sinf(globalSpringTimer4 * 2.8f + i * 1.8f) * 5.0f;
			int dw = 38;
			int dh = 46;
			iShowImage(dx - (dw / 2), (int)(dewY4[i] + bob) - (dh / 2), dw, dh, springDewTex4);
		}
	}

	// Floral Aegis Shields
	for (int i = 0; i < MAX_SHIELDS_4; i++)
	{
		if (!shieldCollected4[i])
		{
			int sx = wrapScreenX(shieldX4[i], cameraX);
			float bob = sinf(globalSpringTimer4 * 2.0f + i * 2.2f) * 6.0f;
			int sw = 48;
			int sh = 48;

			glPushMatrix();
			glTranslatef((float)sx, (float)((int)(shieldY4[i] + bob)), 0.0f);
			glRotatef(shieldRot4, 0.0f, 0.0f, 1.0f);
			iShowImage(-sw / 2, -sh / 2, sw, sh, aegisShieldTex4);
			glPopMatrix();
		}
	}

	// 8. AERO (PLAYER FLAPPY BIRD)
	if (invulnerableFrames == 0 || (invulnerableFrames % 6 < 3))
	{
		unsigned int aeroSprite = aeroFacingRight
			? aeroFrames[currentAeroFrame]
			: aeroBackwardFrames[currentAeroFrame];

		int aeroScrX = wrapScreenX(aeroX, cameraX);
		int aw = 88;
		int ah = 116;

		// Spring Glide Wind Aura
		if (springGlideTimer4 > 0)
		{
			glColor4f(0.35f, 0.95f, 0.65f, 0.35f);
			iFilledCircle(aeroScrX + (aw / 2), aeroY + (ah / 2), 52);
		}

		// Floral Aegis Protective Shield Aura
		if (aegisShieldActive4)
		{
			glPushMatrix();
			glTranslatef((float)(aeroScrX + aw / 2), (float)(aeroY + ah / 2), 0.0f);
			glRotatef(shieldRot4, 0.0f, 0.0f, 1.0f);
			iShowImage(-38, -38, 76, 76, aegisShieldTex4);
			glPopMatrix();
		}

		// Aero Sprite with Pitch Rotation
		glPushMatrix();
		glTranslatef((float)aeroScrX + (aw / 2.0f), (float)aeroY + (ah / 2.0f), 0.0f);
		glRotatef(aeroFacingRight ? aeroPitch4 : -aeroPitch4, 0.0f, 0.0f, 1.0f);
		iShowImage(-aw / 2, -ah / 2, aw, ah, aeroSprite);
		glPopMatrix();
	}

	// 9. SAKURA PETALS DRIFTING IN THE BREEZE
	for (int i = 0; i < SAKURA_PETAL_COUNT_4; i++)
	{
		int px = (int)petalX4[i];
		int py = (int)petalY4[i];
		int pw = 22;
		int ph = 22;

		glPushMatrix();
		glTranslatef((float)px, (float)py, 0.0f);
		glRotatef(petalRot4[i], 0.0f, 0.0f, 1.0f);
		iShowImage(-pw / 2, -ph / 2, pw, ph, sakuraPetalTex4);
		glPopMatrix();
	}

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);

	// ------------------------------------------------------------------------
	// ACCESSIBLE HUD
	// ------------------------------------------------------------------------
	// Nature Restoration Meter (Spring Green/Pink theme)
	drawNatureMeterBar(natureMeter, NATURE_MAX_4);

	iSetColor(255, 255, 255);
	char natureLabel[45];
	sprintf_s(natureLabel, "SPRING RESTORATION: %d%%", natureMeter);
	iText(48, 745, natureLabel);

	// Re-enable alpha blending so transparent PNGs (feathers, HUD icons) render correctly
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.05f);

	// Life HUD (Feathers)
	drawFeatherLives(lives);

	// Energy Bar
	drawEnergyBar();

	// HUD Controls (Pause, Reset, Close)
	drawHudIcons();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);

	// ------------------------------------------------------------------------
	// OVERLAYS: GAME OVER & GRAND VICTORY COMPLETION
	// ------------------------------------------------------------------------
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
		int msgY = (720 - msgH) / 2 + 40;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		iShowImage(msgX, msgY, msgW, msgH, springMsgTex);
		glDisable(GL_BLEND);

		iSetColor(255, 255, 255);
		iText(490, msgY - 40, (char*)"Press ENTER to Proceed", GLUT_BITMAP_HELVETICA_18);
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

#endif // LEVEL4_H