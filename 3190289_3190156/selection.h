#pragma once
#include "util.h"
#include "widget.h"
#include "button.h"

class Selection : public Button //subclass of base class Button
{
	bool selected = false; //boolean to check if the button was selected(clicked)

public:

//----------------------Override Buttons methods(which are also overrided from Widget base class)----------------
	void draw() override;
	void update() override;
	void init() override;
//----------------------------------------------------------------------------------------------------------------
 
//-------------Setter and getter for selection--------------
	void setSelection(bool s) { selected = s; }
	bool getSelection() { return selected; }
//----------------------------------------------------------

	Selection(std::string new_name, float x, float y, float w, float h, std::string content); //custom constructor
	~Selection()
	{
		bool button_deleted;
		std::string delete_message = name;
		delete_message += " Selection destructor called ";
		printDebugMessage(delete_message.c_str(), button_deleted);
	} //destructor
};