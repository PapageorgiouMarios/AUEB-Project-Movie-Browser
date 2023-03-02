#include "number_only_textfield.h"

void NumberOnlyTextfield::draw()
{
	float h = 1.0f * highlighted;

//----------------------------------Draw textfields rectangle-----------------------------------------------------
	graphics::Brush br;
	br.outline_opacity = h;
	SET_COLOR(br.outline_color, h, 0, 0);
	br.gradient = true;
	br.texture = ASSET_PATH + std::string("text_field.png");
	SET_COLOR(br.fill_color, 0.0f, 0.4f, 1.0f);
	graphics::drawRect(pos_x, pos_y, width, height, br);
//----------------------------------------------------------------------------------------------------------------

//----------------------------------Draw textfields input-----------------------------------------------------
	graphics::Brush brush_for_text;
	SET_COLOR(brush_for_text.fill_color, 1.0F, 1.0f, 1.9f);
	graphics::setFont(std::string(ASSET_PATH) + "REGULAR.TTF");
	char space_for_text[60];
	const char* string_to_char = text_inside.data();
	sprintf_s(space_for_text, string_to_char);
	brush_for_text.outline_opacity = 0.0f;

	graphics::drawText(getX() - 18, getY() + 4, width / 10, space_for_text, brush_for_text);
//-------------------------------------------------------------------------------------------------------------
}

void NumberOnlyTextfield::update()
{

	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	static bool check_writing_status = true;

	setHighlight(contains(mx, my));

	if (ms.button_left_pressed && getHighlight())
	{
		setClick(true);
		std::cout << "Clicked on textfield: " << name << std::endl;
	}
	if (ms.button_left_pressed && !getHighlight())
	{
		setClick(false);
		setWriting(false);
		check_writing_status = true;
	}

	if (clicked)
	{
		setWriting(true);

		std::string message = "Writing on: " + name + " ";

		printDebugMessage(message.c_str(), check_writing_status);
	}

	if (writing)
	{
//------------------------------------Writing numbers from 0 to 9----------------------------------------------------------
		static float delay = 0.0f;

		static int prev = 0;

		delay += graphics::getDeltaTime();

		for (int j = graphics::SCANCODE_1; j <= graphics::SCANCODE_0; j++)
		{
			bool check_character = true;

			if (graphics::getKeyState((graphics::scancode_t)j))
			{
				if (prev == j && delay < 150.0f)
				{
					continue;
				}

				else if (delay >= 150.0f)
				{
					prev = j;

					char number_input = ' ';

					if ((graphics::scancode_t)j != graphics::SCANCODE_0)
					{
						number_input = char(prev + 19);
					}
					else
					{
						number_input = char(prev + 9);
					}

					std::string successful_input = "";

					if (text_inside.size() < 4)
					{
						text_inside.push_back(number_input);
						successful_input += name + ": number ";
						successful_input += number_input;
						successful_input += " put.\n";
					}
					else
					{
						successful_input += "Can't add any more digits.\n";
					}

					successful_input += name + " current text: " + text_inside + " ";
					printDebugMessage(successful_input.c_str(), check_character);

					delay = 0.0f;
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------

//------------------------------------Erase existing input------------------------------------------------------------------
		static float delay2 = 0.0f;

		static int prev2 = 0;

		delay2 += graphics::getDeltaTime();

		for (int k = graphics::SCANCODE_BACKSPACE; k <= graphics::SCANCODE_CAPSLOCK; k++)
		{
			bool check_character2 = true;

			if (graphics::getKeyState((graphics::scancode_t)k))
			{
				if (prev2 == k && delay2 < 150.0f)
				{
					continue;
				}

				else if (delay2 >= 150.0f)
				{
					prev2 = k;

					char key_input2 = ' ';
					std::string successful_input2 = "";

					if ((graphics::scancode_t)k == graphics::SCANCODE_BACKSPACE)
					{
						successful_input2 += name + ": BACKSPACE key pressed.\n";

						if (text_inside.size() > 0)
						{
							key_input2 = text_inside.back();
							text_inside.pop_back();
							successful_input2 += "Digit ";
							successful_input2 += key_input2 + " removed from number textfield.\n";
						}
					}
				}
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------------------
}

void NumberOnlyTextfield::init()
{
}

NumberOnlyTextfield::NumberOnlyTextfield(std::string new_name, float x, float y, float w, float h, std::string text)
{
	setName(new_name);
	setX(x);
	setY(y);
	setWidth(w);
	setHeight(h);
	setText(text);
}

NumberOnlyTextfield::~NumberOnlyTextfield()
{
	bool textfield_deleted;
	std::string delete_message2 = name + " Number Only Textfield destructor called ";
	printDebugMessage(delete_message2.c_str(), textfield_deleted);
}
