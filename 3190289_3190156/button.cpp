#include "button.h"
#include "graphics.h"
#include "util.h"

void Button::draw()
{
	float h = 1.0f * highlighted; //value that depends on the location of our mouse for button
	graphics::Brush br;
	br.outline_opacity = 1.0f;
	SET_COLOR(br.outline_color, 0, h, h); //it gives color to the outline to check if we can click the button

//-------------------------------Draw Button's rectangle--------------------------------
	br.gradient = true;
	br.texture = ASSET_PATH + std::string("button.png");
	SET_COLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
	SET_COLOR(br.fill_secondary_color, 0.0f, 0.1f, 0.2f);

	graphics::drawRect(pos_x, pos_y, width, height, br);
//--------------------------------------------------------------------------------------

//-------------------------------Draw Button's text---------------------------------------------------------------------
	graphics::Brush brush_for_button_text;
	SET_COLOR(brush_for_button_text.fill_color, 1.0F, 1.0F, 1.0f); 
	graphics::setFont(std::string(ASSET_PATH) + "TEXT.TTF");
	char space_for_text[50];
	const char * string_to_char = text_fill.data();
	sprintf_s(space_for_text, string_to_char);
	brush_for_button_text.outline_opacity = 0.0f;

	graphics::drawText(getX() - (2* width / 5), getY() + width / 15, width/5, space_for_text, brush_for_button_text);
//------------------------------------------------------------------------------------------------------------------
}

void Button::update()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	setHighlight(contains(mx, my)); //the button always checks if our mouse is inside the button's rectangle

	if (ms.button_left_pressed && getHighlight()) //if we click mouse's left button
	{
		std::cout << getName() << "pressed: " << graphics::getGlobalTime() / (float)1000 << " sec" << std::endl;

		setClick(true);

		graphics::playSound(ASSET_PATH + std::string("click.wav"), 0.1f, false);

	}
	else
	{
		setClick(false);
	}

}

void Button::init()
{

}

bool Button::contains(float x, float y)
{
	return distance(x, y, pos_x, pos_y) < (width / 2);
}

Button::Button(std::string new_name, float x, float y, float w, float h, std::string content)
{
	setName(new_name);
	setX(x);
	setY(y);
	setWidth(w);
	setHeight(h);
	setContent(content);
}
