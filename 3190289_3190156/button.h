#pragma once
#include "widget.h"
#include <iostream>
#include <string>
#include "util.h"

class Button : public Widget //subclass of base class Widget
{
protected:

	std::string name; //Name for debugging

	float pos_x, pos_y; //Coordinates for Canvas

	float width, height; //Dimensions of image rectangle

	std::string text_fill; //Text drawn to the center of the button

	bool highlighted = false; //boolean variable to check if our mouse is in position to click the button

	bool clicked = false; //boolean to check if button was clicked

public:

//-----------------------------Override Widget's methods--------------------------
	virtual void draw() override;
	virtual void update() override;
	virtual void init() override;
//--------------------------------------------------------------------------------

//----------------------------------Setters---------------------------------------
	void setName(std::string new_name) { name = new_name; }
	void setX(float x) { pos_x = x; }
	void setY(float y) { pos_y = y; }
	void setWidth(float w) { width = w; }
	void setHeight(float h) { height = h; }
	void setContent(std::string content) { text_fill = content; }
	void setHighlight(bool h) { highlighted = h; }
	void setClick(bool c) { clicked = c; }
//----------------------------------------------------------------------------------

	bool contains(float x, float y); //method to check if the button has the given coordinates

//----------------------------------Getters-------------------------------------------------------
	std::string getName() { return name; }
	float getX() { return pos_x; }
	float getY() { return pos_y; }
	float getWidth() { return width; }
	float getHeight() { return height; }
	bool getClicked() { return clicked; }
	bool getHighlight() { return highlighted; }
	std::string getContent() { return text_fill; }
//-------------------------------------------------------------------------------------------------

	Button(){} //default constructor

	~Button() //destructor
	{
		bool button_deleted;
		std::string delete_message = name + " destructor called ";
		printDebugMessage(delete_message.c_str(), button_deleted);
	}

	Button(std::string new_name, float x, float y, float w, float h, std::string content); //custom constructor
 
};
