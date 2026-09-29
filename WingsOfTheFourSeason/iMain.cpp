#include "iGraphics.h"
#include "GameVariables.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "level4.h"
#include "Leaderboard.h"
#include "SaveLoad.h"
#include "Settings.h"
#include "Menu.h"
#include "Story.h"



#include <cstdio>
#include <cmath>
#include <cstring>



void iDraw()
{
	if (gameState == 0)
	{
		drawMenu();
	}
	else if (gameState == 1)
	{
		drawLevel1();
	}
	else if (gameState == 2)
	{
		drawLevel2();
	}
	else if (gameState == 3)
	{
		drawLevel3();
	}
	else if (gameState == 4)
	{
		drawLevel4();
	}
	else if (gameState == 10)
	{
		drawStory();
	}
	else if (gameState == 11)
	{
		drawTransitionSlides();
	}
	else if (gameState == 12)
	{
		drawGameCompleteScreen();
	}
}


void fixedUpdate()
{
	if (gameState == 0)
	{
		updateMenu();

		if (levelSelectClicked)
		{
			levelSelectClicked = false;
			showingLevelMenu = false;

			if (strlen(currentPlayerName) == 0)
			{
				strcpy_s(currentPlayerName, "Player");
			}
			totalGameSeconds = 0;
			totalGameFrameCounter = 0;

			gameState = selectedLevelTarget;

			if (selectedLevelTarget == 1) { resetLevel1(); }
			else if (selectedLevelTarget == 2) { resetLevel2(); }
			else if (selectedLevelTarget == 3) { resetLevel3(); }
			else if (selectedLevelTarget == 4) { resetLevel4(); }

			writeSaveData(currentPlayerName, selectedLevelTarget, totalGameSeconds);

			mciSendString("pause bgsong", NULL, 0, NULL);
		}

		if (startGameClicked)
		{
			startGameClicked = false;
			showingNameEntry = false;

			strcpy_s(currentPlayerName, nameEntryBuffer);
			totalGameSeconds = 0;
			totalGameFrameCounter = 0;

			gameState = 10;
			resetStory();
		}

		if (continueGameClicked)
		{
			continueGameClicked = false;

			strcpy_s(currentPlayerName, savedPlayerName);
			totalGameSeconds = savedElapsedTime;
			totalGameFrameCounter = 0;

			gameState = savedLevel;

			if (savedLevel == 1) { resetLevel1(); }
			else if (savedLevel == 2) { resetLevel2(); }
			else if (savedLevel == 3) { resetLevel3(); }
			else if (savedLevel == 4) { resetLevel4(); }

			mciSendString("pause bgsong", NULL, 0, NULL);
		}
	}
	else if (gameState == 1)
	{
		updateLevel1();

		totalGameFrameCounter++;
		if (totalGameFrameCounter >= 60)
		{
			totalGameFrameCounter = 0;
			totalGameSeconds++;
		}

		if (leaveToMenuRequested)
		{
			leaveToMenuRequested = false;
			gameState = 0;
			applyMusicSetting();
		}

		if (levelComplete && (isKeyPressed(13)))
		{
			writeSaveData(currentPlayerName, 2, totalGameSeconds);
			startTransitionSlides(0, 2);
		}
	}
	else if (gameState == 2)
	{
		updateLevel2();
		totalGameFrameCounter++;
		if (totalGameFrameCounter >= 60)
		{
			totalGameFrameCounter = 0;
			totalGameSeconds++;
		}
		if (leaveToMenuRequested)
		{
			leaveToMenuRequested = false;
			gameState = 0;
			applyMusicSetting();
			stopRainSound();
		}

		if (gameOver)
		{
			stopRainSound();
		}

		if (levelComplete && (isKeyPressed(13)))
		{
			writeSaveData(currentPlayerName, 3, totalGameSeconds);
			startTransitionSlides(1, 3);
			stopRainSound();
		}
	}
	else if (gameState == 3)
	{
		updateLevel3();
		totalGameFrameCounter++;
		if (totalGameFrameCounter >= 60)
		{
			totalGameFrameCounter = 0;
			totalGameSeconds++;
		}
		if (leaveToMenuRequested)
		{
			leaveToMenuRequested = false;
			gameState = 0;
			applyMusicSetting();
		}

		if (levelComplete && (isKeyPressed(13)))
		{
			writeSaveData(currentPlayerName, 4, totalGameSeconds);
			startTransitionSlides(2, 4);
		}
	}
	else if (gameState == 4)
	{
		updateLevel4();
		totalGameFrameCounter++;
		if (totalGameFrameCounter >= 60)
		{
			totalGameFrameCounter = 0;
			totalGameSeconds++;
		}
		if (leaveToMenuRequested)
		{
			leaveToMenuRequested = false;
			gameState = 0;
			paused = false;
			escKeyWasDown = false;
			pKeyWasDown = false;
			applyMusicSetting();
		}

		// Spring completed: All Four Seasons restored! Grand game completion!
		if (levelComplete && (isKeyPressed(13)))
		{
			startTransitionSlides(3, 12);
		}
	}
	else if (gameState == 10)
	{
		updateStory();
	}
	else if (gameState == 11)
	{
		updateTransitionSlides();
	}
	else if (gameState == 12)
	{
		updateGameCompleteScreen();
	}
}

void iMouseMove(int mx, int my)
{
	menuMouseX = mx;
	menuMouseY = my;
}

void iPassiveMouseMove(int mx, int my)
{
	menuMouseX = mx;
	menuMouseY = my;
}

void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (gameState == 0)
		{
			handleMenuClick(mx, my);

			if (levelSelectClicked)
			{
				levelSelectClicked = false;
				showingLevelMenu = false;

				if (strlen(currentPlayerName) == 0)
				{
					strcpy_s(currentPlayerName, "Player");
				}
				totalGameSeconds = 0;
				totalGameFrameCounter = 0;

				gameState = selectedLevelTarget;

				if (selectedLevelTarget == 1) { resetLevel1(); }
				else if (selectedLevelTarget == 2) { resetLevel2(); }
				else if (selectedLevelTarget == 3) { resetLevel3(); }
				else if (selectedLevelTarget == 4) { resetLevel4(); }

				writeSaveData(currentPlayerName, selectedLevelTarget, totalGameSeconds);

				mciSendString("pause bgsong", NULL, 0, NULL);
			}

			if (startGameClicked)
			{
				startGameClicked = false;
				showingNameEntry = false;

				strcpy_s(currentPlayerName, nameEntryBuffer);
				totalGameSeconds = 0;
				totalGameFrameCounter = 0;

				gameState = 10;
				resetStory();
			}

			if (continueGameClicked)
			{
				continueGameClicked = false;
				strcpy_s(currentPlayerName, savedPlayerName);
				totalGameSeconds = savedElapsedTime;
				totalGameFrameCounter = 0;
				gameState = savedLevel;

				if (savedLevel == 1) { resetLevel1(); }
				else if (savedLevel == 2) { resetLevel2(); }
				else if (savedLevel == 3) { resetLevel3(); }
				else if (savedLevel == 4) { resetLevel4(); }

				mciSendString("pause bgsong", NULL, 0, NULL);
			}
		}
		else if (gameState == 1 || gameState == 2 || gameState == 3 || gameState == 4)
		{
			// Pause button bounds (drawn at x=1080..1132, y=655..703)
			if (mx >= 1080 && mx <= 1132 && my >= 655 && my <= 703)
			{
				paused = !paused;
			}

			// Reset button bounds (drawn at x=1140..1192, y=655..703)
			if (mx >= 1140 && mx <= 1192 && my >= 655 && my <= 703)
			{
				if (gameState == 1) { resetLevel1(); }
				else if (gameState == 2) { resetLevel2(); }
				else if (gameState == 3) { resetLevel3(); }
				else if (gameState == 4) { resetLevel4(); }
			}

			// Leave button bounds (drawn at x=1200..1252, y=655..703)
			if (mx >= 1200 && mx <= 1252 && my >= 655 && my <= 703)
			{
				leaveToMenuRequested = true;
			}
		}
	}
}

// Special Keys:
// GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
// GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT



int main()
{
	srand(time(NULL));
	// Opening/Loading the audio files
	mciSendString("open \"Audios//background.mp3\" alias bgsong", NULL, 0, NULL);
	mciSendString("open \"Audios//gameover.mp3\" alias ggsong", NULL, 0, NULL);
	mciSendString("open \"Assets//Audios//Menue//Scrolling_Sound.mp3\" alias clicksound", NULL, 0, NULL);
	mciSendString("open \"Audios//SeedCollection.mp3\" alias seedsound", NULL, 0, NULL);
	mciSendString("open \"Audios//HurtSound.mp3\" alias hurtsound", NULL, 0, NULL);
	mciSendString("open \"Audios//RainThunder.mp3\" alias rainsound", NULL, 0, NULL);
	mciSendString("open \"Audios//Thunder.mp3\" alias thundersound", NULL, 0, NULL);
	// Playing the background audio on repeat
	mciSendString("play bgsong repeat", NULL, 0, NULL);

	// If the use of an audio is finished, close it to free memory
	// mciSendString("close bgsong", NULL, 0, NULL);
	// mciSendString("close ggsong", NULL, 0, NULL);

	iInitialize(1280, 720, "Wings of the Four Seasons");
	loadAeroSprites();
	loadTreeSprites();
	loadFarTreeSprites();

	loadtreeSprites3();
	loadFartreeSprites3();
	loadLeaderboard();
	loadSaveData();
	loadSettings();
	applyMusicSetting();
	loadMainMenuBackground();
	loadWaveTextures();
	loadLevel1Background();
	loadMonsoonBackground();
	resetLevel1();
	loadBoatSprites();
	loadSeedSprite();
	loadHudIcons();
	loadEnergyBarFrame();
	loadNatureMeterFrame();
	loadLevelCompleteMessages();
	loadLevel4Assets();
	loadStorySlides();
	loadTransitionSlides();
	iStart();
	return 0;
}