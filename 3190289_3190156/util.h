#pragma once
#include <iostream>
#include "graphics.h"
#include <fstream>

#define WINDOW_WIDTH 1500 //width of the browsers window
#define WINDOW_HEIGHT 900 //height of the browsers window

#define CANVAS_WIDTH 1400 //width of canvas(what we see in browser, smaller than the window)
#define CANVAS_HEIGHT 800 //height of canvas(what we see in browser, smaller than the window)

#define ASSET_PATH ".\\assets\\" //shortcut for the file path of assets in project

#define SET_COLOR(brush_color, red, green, blue){brush_color[0] = red; brush_color[1] = green, brush_color[2] = blue;}
//function for utilizing RGB color model. For each colors intensity, we use float values from 0(0%) to 1(100%)

#define DEBUG_MODE 1 //variable for debugging purposes

inline float distance(float x1, float y1, float x2, float y2) //calculates the distance between two points(x,y)
{
	float dx = x1 - x2;

	float dy = y1 - y2;

	return sqrtf(dx*dx + dy*dy);
}

inline void printDebugMessage(const char* message, bool& once) //display message to .exe file for debugging purposes
{
	if (once) //we must use a boolean variable to make sure the message is printed only once
	{
		std::cout << message << graphics::getGlobalTime() / (float) 1000 << " sec" << std::endl;
		once = false;
	}
}
//Note: Since we have MessageLoop, without the boolean once a simple std::cout command with no if case will be executed non-stop.

inline void playSong(float volume, bool& once) //plays specific mp3 file only once(used when status = STATUS_BROWSER)
{
	if (!once) //we must use a boolean variable to make sure the music file is played only once, since looping = true
			   //there is no problem considering the number of times the song is played
	{
		graphics::playMusic(ASSET_PATH + std::string("background_browser_music.mp3"), volume, true, 60000);
		once = true;
	}
}
//Note: Since we have MessageLoop, without the boolean once, the command playMusic() will start playing the 1st msec of the song indefinetely.

inline bool fileExists(std::string current_path) //used to check if one file exists in project(used to check the existence of specific png,mp3,ttf)
{												 //used to check the existence of specific png, mp3, ttf files
	std::ifstream file;							 //to make sure there is no mistake in the construction of movie database

	std::string pathOfFile = current_path;

	file.open(pathOfFile);

	if(file)
	{
		std::cout << current_path << " file exists" << std::endl;
		return true;
	}
	else
	{
		std::cout << current_path << " file doesn't exist" << std::endl;
		return false;
	}
}

inline void toLowerCase(std::string& current) //turns all characters of one string to lower case
{
	for (int x = 0; x < current.length(); x++)
	{
		current[x] = (tolower(current[x]));
	}
 
}
//Note: Used to turn all possible movie names or textfields' content to lower case so that the search of movies can be less strict  