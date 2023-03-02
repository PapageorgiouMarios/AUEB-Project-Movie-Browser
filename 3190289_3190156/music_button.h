#pragma once
#include "button.h"

class MusicButton :Button //subclass of base class Button
{
	bool on; //boolean 

public:

//----------------------Override Button methods(which are also overrided from Widget base class)----------------
	void draw() override;
	void update() override;
	void init() override;
//--------------------------------------------------------------------------------------------------------------

//------------Simple methods to change the value of on boolean(for better viewing purposes)----------------------
	void turnMusicOn() { on = true; }
	void turnMusicOff() { on = false; }
//---------------------------------------------------------------------------------------------------------------

//-------------Setter and getter for the on boolean----------
	void setState(bool state) { on = state; }
	bool getState() { return on; }
//-----------------------------------------------------------

	MusicButton(std::string new_name, float x, float y, float w, float h, bool music_state); //custom constructor for music button
	~MusicButton(); //destructor for music button
};