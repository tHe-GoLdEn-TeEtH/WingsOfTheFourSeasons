#ifndef GAMEVARIABLES_H
#define GAMEVARIABLES_H

bool gameOver = false;
int lives = 3;
bool paused = false;
bool pKeyWasDown = false;
bool leaveToMenuRequested = false;
bool escKeyWasDown = false;

int gameState = 0;   // 0 = Menu, 1 = Winter, 2 = Monsoon, 3 = Summer, 4 = Spring, 10 = Story intro
int natureMeter = 0;
int cameraX = 0;
int aeroX = 250;
int aeroY = 150;

const int WORLD_WIDTH = 3600;

// AERO MOVEMENT 
const int AERO_FRAME_COUNT = 8;

// Forward: facing right
unsigned int aeroFrames[AERO_FRAME_COUNT];

// Backward: facing left
unsigned int aeroBackwardFrames[AERO_FRAME_COUNT];

bool aeroFacingRight = true;

int currentAeroFrame = 0;
int aeroAnimCounter = 0;

/// PAUSE RESET EXIT /////
unsigned int pauseIconTex;
unsigned int restartIconTex;
unsigned int closeIconTex;

void loadHudIcons()
{
	pauseIconTex = iLoadImage("Assets/PauseResetExit/pause_button.png");
	restartIconTex = iLoadImage("Assets/PauseResetExit/restart_button.png");
	closeIconTex = iLoadImage("Assets/PauseResetExit/close_button.png");
}

void drawHudIcons()
{
	iShowImage(1080, 655, 52, 48, pauseIconTex);
	iShowImage(1140, 655, 52, 48, restartIconTex);
	iShowImage(1200, 655, 52, 48, closeIconTex);
}

// seeds of hope
unsigned int seedTex;

void loadSeedSprite()
{
	seedTex = iLoadImage("Assets/SeedsOfHope.png");
}

//// MONSOON RIVER /////
unsigned int waveLargeTex;
unsigned int waveMediumTex;
unsigned int waveSmallTex;

float waveLargeOffset = 0.0f;
float waveMediumOffset = 0.0f;
float waveSmallOffset = 0.0f;

const int WAVE_TILE_WIDTH = 640;
const int WAVE_TILE_HEIGHT = 60;

void loadWaveTextures()
{
	waveLargeTex = iLoadImage("Assets/Wave/LargeWave.png");
	waveMediumTex = iLoadImage("Assets/Wave/MediumWave.png");
	waveSmallTex = iLoadImage("Assets/Wave/SmallWave.png");
}

//////////////////////////////////////////

bool levelComplete = false;
int timeLeft = 60;
int frameCounter = 0;
int invulnerableFrames = 0;

char currentPlayerName[20] = "";
int totalGameSeconds = 0;
int totalGameFrameCounter = 0;

//ENERGY LEVEL

int energy = 100;
const int ENERGY_MAX = 100;

unsigned int energyBarFrameTex;

void loadEnergyBarFrame()
{
	energyBarFrameTex = iLoadImage("Assets/EnergyBar.png");
}

void drainEnergy()
{
	frameCounter++;
	if (frameCounter >= 40)
	{
		frameCounter = 0;
		energy--;

		if (energy <= 0)
		{
			energy = 0;
			gameOver = true;
		}
	}
}

void drawEnergyBar()
{
	// Ornate leaf-vine capsule frame, squeezed narrower and taller than its native
	// aspect ratio so it reads as a compact rectangular bar instead of a thin pill
	const int ENERGY_FRAME_X = 490;
	const int ENERGY_FRAME_Y = 645;
	const int ENERGY_FRAME_W = 230;
	const int ENERGY_FRAME_H = 100;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Inner glass track inside the frame artwork (measured proportionally, pulled in
	// from the rounded leaf-cap ends, widened slightly for a fuller-looking fill)
	int insetX = (int)(ENERGY_FRAME_W * 0.1f);
	int insetY = (int)(ENERGY_FRAME_H * 0.42f);

	int trackX = ENERGY_FRAME_X + insetX;
	int trackY = ENERGY_FRAME_Y + insetY;
	int trackMaxW = ENERGY_FRAME_W - (insetX * 2);
	int trackH = ENERGY_FRAME_H - (insetY * 2);

	// Energy fill, drawn first so the frame artwork sits on top and hides any overshoot
	int fillW = (int)((energy / (float)ENERGY_MAX) * trackMaxW);
	if (fillW > trackMaxW) fillW = trackMaxW;
	if (fillW < 0) fillW = 0;

	iSetColor(70, 220, 140);
	iFilledRectangle(trackX, trackY, fillW, trackH);

	// Ornate frame drawn on top, its transparent inner track lets the fill show through
	iShowImage(ENERGY_FRAME_X, ENERGY_FRAME_Y, ENERGY_FRAME_W, ENERGY_FRAME_H, energyBarFrameTex);

	glDisable(GL_BLEND);
}

// NATURE METER

unsigned int natureMeterFrameTex;

void loadNatureMeterFrame()
{
	natureMeterFrameTex = iLoadImage("Assets/NatureMeter.png");
}

void drawNatureMeterBar(int value, int maxValue)
{
	// Ornate wood-and-gem frame, sized slightly wider and longer than its native
	// aspect ratio for a more prominent HUD presence
	const int NM_FRAME_X = 30;
	const int NM_FRAME_Y = 640;
	const int NM_FRAME_W = 380;
	const int NM_FRAME_H = 100;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Inner track inside the frame artwork, pulled in well clear of the wooden
	// borders and rounded gem end-caps on all sides
	int insetX = (int)(NM_FRAME_W * 0.1123f);
	int insetY = (int)(NM_FRAME_H * 0.40f);

	int trackX = NM_FRAME_X + insetX;
	int trackY = NM_FRAME_Y + insetY;
	int trackMaxW = NM_FRAME_W - (insetX * 2);
	int trackH = NM_FRAME_H - (insetY * 2);

	// Fill, drawn first so the frame artwork sits on top and hides any overshoot
	int fillW = (int)((value / (float)maxValue) * trackMaxW);
	if (fillW > trackMaxW) fillW = trackMaxW;
	if (fillW < 0) fillW = 0;

	iSetColor(85, 210, 120);
	iFilledRectangle(trackX, trackY, fillW, trackH);

	// Ornate frame drawn on top, its transparent inner track lets the fill show through
	iShowImage(NM_FRAME_X, NM_FRAME_Y, NM_FRAME_W, NM_FRAME_H, natureMeterFrameTex);

	glDisable(GL_BLEND);
}

//   LEVEL 2 VARIABLES START HERE //

// DISTANT MOUNTAINS AND DISTANT TREES
const int MOUNTAIN_COUNT_2 = 6;
int mountainX2[MOUNTAIN_COUNT_2] = { 300, 1200, 2000, 2600, 3100, 3500 };
int mountainWidth2[MOUNTAIN_COUNT_2] = { 300, 400, 350, 450, 300, 380 };
int mountainHeight2[MOUNTAIN_COUNT_2] = { 180, 220, 200, 240, 190, 210 };

// FISH VARIABLE
const int FISH_COUNT_2 = 5;
int fishX2[FISH_COUNT_2] = { 710, 1430, 2150, 2870, 3590 };
int fishY2[FISH_COUNT_2] = { 75, 75, 75, 75, 75 };
int fishSize2[FISH_COUNT_2] = { 0, 1, 0, 1, 0 };
bool fishVisible2[FISH_COUNT_2] = { true, true, true, true, true };
// FISH JUMPING STATE
int fishState2[FISH_COUNT_2] = { 0, 0, 0, 0, 0 };      // 0 = waiting, 1 = jumping
int fishJumpTimer2[FISH_COUNT_2] = { 40, 85, 130, 60, 110 };  // frames until next jump
int fishJumpProgress2[FISH_COUNT_2] = { 0, 0, 0, 0, 0 };       // 0 to jumpDuration, tracks where in the arc
int fishBaseY2[FISH_COUNT_2] = { 75, 75, 75, 75, 75 };   // remembers each fish's resting water-level Y
int fishStartX2[FISH_COUNT_2] = { 710, 1430, 2150, 2870, 3590 }; // takeoff X position for parabolic leap
int fishType2[FISH_COUNT_2] = { 0, 1, 0, 1, 0 };

unsigned int winterMsgTex;
unsigned int monsoonMsgTex;
unsigned int summerMsgTex;
unsigned int springMsgTex;

void loadLevelCompleteMessages()
{
	winterMsgTex = iLoadImage("Assets/WMsg.png");
	monsoonMsgTex = iLoadImage("Assets/MMsg.png");
	summerMsgTex = iLoadImage("Assets/SMsg.png");
	springMsgTex = iLoadImage("Assets/SpMsg.png");
}

void loadAeroSprites()
{
	char forwardPaths[AERO_FRAME_COUNT][128] = {
		"Assets/Aero'sMovement/left_to_right/frame_01.png",
		"Assets/Aero'sMovement/left_to_right/frame_02.png",
		"Assets/Aero'sMovement/left_to_right/frame_03.png",
		"Assets/Aero'sMovement/left_to_right/frame_04.png",
		"Assets/Aero'sMovement/left_to_right/frame_05.png",
		"Assets/Aero'sMovement/left_to_right/frame_06.png",
		"Assets/Aero'sMovement/left_to_right/frame_07.png",
		"Assets/Aero'sMovement/left_to_right/frame_08.png"
	};

	char backwardPaths[AERO_FRAME_COUNT][128] = {
		"Assets/Aero'sMovement/right_to_left/frame_01.png",
		"Assets/Aero'sMovement/right_to_left/frame_02.png",
		"Assets/Aero'sMovement/right_to_left/frame_03.png",
		"Assets/Aero'sMovement/right_to_left/frame_04.png",
		"Assets/Aero'sMovement/right_to_left/frame_05.png",
		"Assets/Aero'sMovement/right_to_left/frame_06.png",
		"Assets/Aero'sMovement/right_to_left/frame_07.png",
		"Assets/Aero'sMovement/right_to_left/frame_08.png"
	};

	for (int i = 0; i < AERO_FRAME_COUNT; i++)
	{
		aeroFrames[i] = iLoadImage(forwardPaths[i]);
		aeroBackwardFrames[i] = iLoadImage(backwardPaths[i]);
	}
}

unsigned int getCurrentAeroSprite()
{
	if (aeroFacingRight)
	{
		return aeroFrames[currentAeroFrame];
	}

	return aeroBackwardFrames[currentAeroFrame];
}



int wrapScreenX(int worldX, int camera)
{
	int rel = worldX - camera;
	if (rel < -WORLD_WIDTH / 2) { rel += WORLD_WIDTH; }
	if (rel > WORLD_WIDTH / 2) { rel -= WORLD_WIDTH; }
	return rel;
}

#endif