#include "text_bubble.h"
#include "graphics.h"
#include "util.h"

void TextBubble::draw()
{
//-----------------------------------Draw Bubble's rectangle------------------------------
	graphics::Brush br;
	br.outline_opacity = 1.0f;
	SET_COLOR(br.outline_color, 0.0f, 1.0f, 1.0f);
	br.gradient = true;
	br.texture = ASSET_PATH + std::string("textfield.png");
	SET_COLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
	SET_COLOR(br.fill_secondary_color, 0.0f, 0.1f, 0.2f);
	graphics::drawRect(pos_x, pos_y, width, height, br);
//-----------------------------------------------------------------------------------------

//-----------------------------------Draw Bubble's text------------------------------------------------------
	graphics::Brush brush_for_text;
	SET_COLOR(brush_for_text.fill_color, 1.0F, 1.0f, 1.0f);
	graphics::setFont(std::string(ASSET_PATH) + "TEXT.TTF");
	char space_for_text[60];
	const char* string_to_char = content.data();
	sprintf_s(space_for_text, string_to_char);
	brush_for_text.outline_opacity = 0.0f;
	graphics::drawText(getX() - (2 * width / 5), getY() + 10, width / 4.5, space_for_text, brush_for_text);
//------------------------------------------------------------------------------------------------------------
}

void TextBubble::update()
{
}

void TextBubble::init()
{
}

TextBubble::TextBubble(std::string content, float x, float y, float width, float height)
{
	setContent(content);
	setX(x);
	setY(y);
	setW(width);
	setH(height);
}

TextBubble::~TextBubble()
{
	bool button_deleted;
	std::string delete_message = content;
	delete_message += " Text Bubble destructor called ";
	printDebugMessage(delete_message.c_str(), button_deleted);
}
