#include "textfield.h"
#include "graphics.h"
#include "util.h"

using namespace graphics;

void TextField::draw()
{
	float h = 1.0f * highlighted;

//----------------------------------Draw Textfield's rectangle------------------------------------
	graphics::Brush br;
	br.outline_opacity = h;
	SET_COLOR(br.outline_color, 0, h, h);
	br.gradient = true;
	br.texture = ASSET_PATH + std::string("text_field.png");
	graphics::drawRect(pos_x, pos_y, width, height, br);
//-------------------------------------------------------------------------------------------------

//----------------------------------Draw Textfield's text----------------------------------------------------
	graphics::Brush brush_for_text;
	SET_COLOR(brush_for_text.fill_color, 1.0F, 1.0f, 1.9f);
	graphics::setFont(std::string(ASSET_PATH) + "REGULAR.TTF");
	char space_for_text[60];
	const char* string_to_char = text_inside.data();
	sprintf_s(space_for_text, string_to_char);
	brush_for_text.outline_opacity = 0.0f;

	graphics::drawText(getX() - (2 * width / 5) - 5, getY() + 4, width / 21, space_for_text, brush_for_text);
//------------------------------------------------------------------------------------------------------------
}

void TextField::update()
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

	if(clicked)
	{
		setWriting(true);

		std::string message = "Writing on: " + name + " ";

		printDebugMessage(message.c_str(), check_writing_status);
	}

	if(writing)
	{
		static float delay = 0.0f; //time passed from pressing one key on keyboard(typematic delay)

		static int prev = 0; //int that takes the value of previous scancode pressed

		static bool capital = false; //boolean to check if CAPSLOCK key was pressed to write uppercase characters

		delay += graphics::getDeltaTime(); //we put the time from previous engine update

//-----------------------Write all alphabetical characters(upper and lower case A-Z & a-z)-------------------------------------
		for (int i = graphics::SCANCODE_A; i <= graphics::SCANCODE_Z; i++)
		{
			bool check_character = true;

			if (graphics::getKeyState((graphics::scancode_t)i)) //we check if the proper character was pressed
			{
				if (prev == i && delay < 150.0f) //we check if one character is already on its way to be put on textfield
				{
					continue; //if we already pressed a character we continue the for loop
				}//it's necessary because without it, the one character we press will be put in the textfield multiple times

				else if(delay >= 150.0f) //if we are ready to press another character
				{
					prev = i; //we take the character we pressed

					std::string successful_input = ""; //string to make properly the message string

					if(text_inside.size() < 60) //if we have space to write more characters inside the textfield
					{
						if(capital) //if we have pressed the CAPSLOCK key
						{
							text_inside.push_back(char(prev + 61)); //we add the key's character to textfield
							successful_input += name + ": character "; 
							successful_input += char(prev + 61);
							successful_input += " profitably put.\n";
						}
						else
						{
							text_inside.push_back(char(prev + 61 + 32));
							successful_input += name + ": character ";
							successful_input += char(prev + 61 + 32);
							successful_input += " profitably put.\n";
						}
 
					}
					else //if we don't have enough space to write any more characters
					{
						successful_input += "Can't add any more characters.\n";
					}
					successful_input += name + " current text: " + text_inside + " ";
					printDebugMessage(successful_input.c_str(), check_character);

					delay = 0.0f; //we reset the typematic delay
				} 
			}
		}
//------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------Write all numbers(from 0 to 9)-----------------------------------------------------
		static float delay2 = 0.0f; //time passed from pressing one key on keyboard(typematic delay)

		static int prev2 = 0; //int that takes the value of previous scancode pressed

		delay2 += graphics::getDeltaTime(); //we put the time from previous engine update

		for (int j = graphics::SCANCODE_1; j <= graphics::SCANCODE_0; j++)  
		{
			bool check_character2 = true;

			if (graphics::getKeyState((graphics::scancode_t)j)) //we check if the proper character was pressed
			{
				if (prev2 == j && delay2 < 150.0f) //we check if one character is already on its way to be put on textfield
				{
					continue; //if we already pressed a character we continue the for loop
				}//it's necessary because without it, the one character we press will be put in the textfield multiple times

				else if (delay2 >= 150.0f) //if we are ready to press another character
				{
					prev2 = j; //we take the character we pressed

					char number_input = ' ';

					if((graphics::scancode_t)j != graphics::SCANCODE_0)
					{
						number_input = char(prev2 + 19); //we save the key's character to textfield
					}
					else 
					{
						number_input = char(prev2 + 9); //we save the key's character to textfield
					}

					std::string successful_input2 = "";

					if (text_inside.size() < 60) //if we have space to write more characters inside the textfield
					{
						text_inside.push_back(number_input);
						successful_input2 += name + ": number ";
						successful_input2 += number_input;
						successful_input2 += " opportunely put.\n";
					}
					else
					{
						successful_input2 += "Can't add any more characters.\n";
					}

					successful_input2 += name + " current text: " + text_inside + " ";
					printDebugMessage(successful_input2.c_str(), check_character2);

					delay2 = 0.0f; //we reset the typematic delay
				}
			}
		}
//------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------Special characters-----------------------------------------------------------------
		static float delay3 = 0.0f; //time passed from pressing one key on keyboard(typematic delay)

		static int prev3 = 0; //int that takes the value of previous scancode pressed

		delay3 += graphics::getDeltaTime(); //we put the time from previous engine update

		for (int k = graphics::SCANCODE_BACKSPACE; k <= graphics::SCANCODE_CAPSLOCK; k++)
		{
			bool check_character3 = true;

			if (graphics::getKeyState((graphics::scancode_t)k)) //we check if the proper character was pressed
			{
				if (prev3 == k && delay3 < 150.0f) //we check if one character is already on its way to be put on textfield
				{
					continue; //if we already pressed a character we continue the for loop
				}//it's necessary because without it, the one character we press will be put in the textfield multiple times

				else if (delay3 >= 150.0f) //if we are ready to press another character
				{
					prev3 = k; //we take the character we pressed

					char key_input3 = ' ';
					std::string successful_input3 = "";

					if ((graphics::scancode_t)k == graphics::SCANCODE_BACKSPACE) //we check pressed BACKSPACE
					{
						successful_input3 += name + ": BACKSPACE key pressed.\n";

						if(text_inside.size() > 0) //we check if there are more characters to remove from the textfield
						{
							key_input3 = text_inside.back();
							text_inside.pop_back();
							successful_input3 += "Character ";
							successful_input3 += key_input3 + " removed from textfield.\n";
						}
	
		
					}
					else if ((graphics::scancode_t)k == graphics::SCANCODE_TAB) //we check pressed TAB
					{
						successful_input3 += name + ": TAB key pressed.\n";

						if(text_inside.size() <= 56)
						{
							key_input3 = ' ';
							text_inside.push_back(key_input3);
							text_inside.push_back(key_input3);
							text_inside.push_back(key_input3);
							text_inside.push_back(key_input3);
						}
						else
						{
							successful_input3 += "Can't go futher. \n";
						}
					}
					else if ((graphics::scancode_t)k == graphics::SCANCODE_SPACE) //we check pressed SPACE
					{
						successful_input3 += name + ": SPACE key pressed.\n";

						if(text_inside.size() < 40)
						{
							key_input3 = ' ';
							text_inside.push_back(key_input3);
						}
						else
						{
							successful_input3 += "Can't go futher. \n";
						}
					}
					else if((graphics::scancode_t)k == graphics::SCANCODE_CAPSLOCK) //we check pressed CAPSLOCK
					{
						successful_input3 += name + ": CAPSLOCK key pressed.\n";

						if(capital)
						{
							capital = false;
							successful_input3 += name + ": Characters are lower case.\n";
						}
						else
						{
							capital = true;
							successful_input3 += name + ": Characters are upper case.\n";
						}
					}

					successful_input3 += name + " current text: " + text_inside + " ";
					printDebugMessage(successful_input3.c_str(), check_character3);

					delay3 = 0.0f; //we reset the typematic delay
//------------------------------------------------------------------------------------------------------------------------------
				}
			}
		}
	}

}

void TextField::init()
{
}

bool TextField::contains(float x, float y)
{
	return distance(x, y, pos_x, pos_y) < width * 0.2;
}

bool TextField::hasCharacters()
{
	if(text_inside.empty())
	{
		return false;
	}
	else
	{
		for (int c = 0; c < text_inside.size(); c++)
		{
			if (text_inside[c] != ' ')
			{
				return true;
			}
		}
		return false;
	}
}

TextField::TextField(std::string new_name, float x, float y, float w, float h, std::string text)
{
	setName(new_name);
	setX(x);
	setY(y);
	setWidth(w);
	setHeight(h);
	setText(text);
}

