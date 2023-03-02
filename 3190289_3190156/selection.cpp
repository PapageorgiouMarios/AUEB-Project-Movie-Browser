#include "selection.h"
#include "button.h"

void Selection::draw()
{
//------------------------------Draw Button's rectangle-----------------------------
	float h = 1.0f * highlighted;
	graphics::Brush br;
	br.outline_opacity = 1.0f;
	SET_COLOR(br.outline_color, 0.0f, h, 0.0f);
	br.gradient = true;
	br.texture = ASSET_PATH + std::string("button.png");
	SET_COLOR(br.fill_color, 0.0f, selected * 0.3f, 0.0f); //we make sure the button remains selected
	SET_COLOR(br.fill_secondary_color, 0.0f, selected * 0.9f, selected * 0.9f); //used for seeing selected movie genres
	graphics::drawRect(pos_x, pos_y, width, height, br);
//----------------------------------------------------------------------------------

//-------------------------------------------Draw Button's text--------------------------------------------------------
	graphics::Brush brush_for_button_text;
	SET_COLOR(brush_for_button_text.fill_color, 1.0F, 1.0F, 1.0f);
	graphics::setFont(std::string(ASSET_PATH) + "TEXT.TTF");
	char space_for_text[30];
	const char* string_to_char = text_fill.data();
	sprintf_s(space_for_text, string_to_char);
	brush_for_button_text.outline_opacity = 0.0f;
	graphics::drawText(getX() - (2 * width / 5), getY() + width / 14, width / 4.7, space_for_text, brush_for_button_text);
//----------------------------------------------------------------------------------------------------------------------
}

void Selection::update()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	setHighlight(contains(mx, my));

	if (ms.button_left_pressed && getHighlight() && !selected)
	{
		std::cout << getName() << "selected: " << graphics::getGlobalTime() / (float)1000 << " sec" << std::endl;

		setSelection(true);

		graphics::playSound(ASSET_PATH + std::string("click.wav"), 0.1f, false);

	}
	else if(ms.button_left_pressed && getHighlight() && selected)
	{
		std::cout << getName() << "unselected: " << graphics::getGlobalTime() / (float)1000 << " sec" << std::endl;

		setSelection(false);

		graphics::playSound(ASSET_PATH + std::string("click.wav"), 0.1f, false);
	}

}

void Selection::init()
{
}

Selection::Selection(std::string new_name, float x, float y, float w, float h, std::string content)
{
	setName(new_name);
	setX(x);
	setY(y);
	setWidth(w);
	setHeight(h);
	setContent(content);
}
