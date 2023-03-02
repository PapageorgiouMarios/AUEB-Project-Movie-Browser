#include "refresh_button.h"

void RefreshButton::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.gradient = true;
	br.texture = ASSET_PATH + std::string("refresh.png");
	graphics::drawRect(pos_x, pos_y, width, height, br);

}

void RefreshButton::update()
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
		setRefresh(true);

	}
	else
	{
		setClick(false);
		setRefresh(false);
	}
}

void RefreshButton::init()
{
}

void RefreshButton::resetVectors(vector<Movie*>& results, vector<Movie*> all_movies)
{
	if(results == all_movies)
	{
		std::cout << "Already refreshed" << std::endl;
	}
	else
	{
		results = all_movies;
		std::cout << "Refresh thumbnail's movies to all movies in database" << std::endl;
	}
}

RefreshButton::RefreshButton(std::string new_name, float x, float y, float w, float h)
{
	setName(new_name);
	setX(x);
	setY(y);
	setWidth(w);
	setHeight(h);

}

RefreshButton::~RefreshButton()
{
	bool button_deleted;
	std::string delete_message = name;
	delete_message += "Refresh Button destructor called ";
	printDebugMessage(delete_message.c_str(), button_deleted);
}
