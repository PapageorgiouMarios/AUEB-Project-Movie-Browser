#include "music_button.h"

void MusicButton::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.gradient = true;

//----------Change the picture of the button depending of the state of boolean on----------
	if(on)
	{
		br.texture = ASSET_PATH + std::string("on.png"); 
	}
	else
	{
		br.texture = ASSET_PATH + std::string("off.png");
	}
	
	graphics::drawRect(pos_x, pos_y, width, height, br);
//-----------------------------------------------------------------------------------------
}

void MusicButton::update()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	setHighlight(contains(mx, my));

	if (ms.button_left_pressed && getHighlight())
	{
		std::cout << name << "pressed: " << graphics::getGlobalTime() / (float)1000 << " sec" << std::endl;

		setClick(true);

	}
	else
	{
		setClick(false);
	}

	if(clicked && on)
	{
		turnMusicOff(); //we could just write on = false but we preffered a single command function for understanding purposes
	}
	else if(clicked && !on)
	{
		turnMusicOn(); //we could just write on = true but we preffered a single command function for understanding purposes
	}
}

void MusicButton::init()
{
}

MusicButton::MusicButton(std::string new_name, float x, float y, float w, float h, bool music_state)
{
	setName(new_name);
	setX(x);
	setY(y);
	setWidth(w);
	setHeight(h);
	setState(music_state);
}

MusicButton::~MusicButton()
{
	bool button_deleted;
	std::string delete_message = name + " Music Button destructor called ";
	printDebugMessage(delete_message.c_str(), button_deleted);
}
 
