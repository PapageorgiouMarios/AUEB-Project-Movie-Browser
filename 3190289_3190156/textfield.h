#pragma once
#include "widget.h"
#include <iostream>
#include <string>
#include "util.h"

class TextField : public Widget //subclass of base class Widget
{
protected:

	std::string name; //Name for debugging

	float pos_x, pos_y; //Coordinates for Canvas

	float width, height; //Dimensions of image rectangle

	std::string text_inside; //Text written by us and drawn inside the rectangle

	bool highlighted = false; //boolean variable to check if our mouse is in position to click the button

	bool clicked = false; //boolean to check if button was clicked

	bool writing = false; //boolean to check if we are currently writing inside the textfield

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
	void setText(std::string fill) { text_inside = fill; }
	void setHighlight(bool h) { highlighted = h; }
	void setClick(bool c) { clicked = c; }
	void setWriting(bool wr) { writing = wr; }
//----------------------------------------------------------------------------------

	bool contains(float x, float y); //method to check if the textfield has the given coordinates

//----------------------------------Getters-------------------------------------------------------
	std::string getName() { return name; }
	float getX() { return pos_x; }
	float getY() { return pos_y; }
	float getWidth() { return width; }
	float getHeight() { return height; }
	bool getHighlight() { return highlighted; }
	std::string getText() { return text_inside; }
	bool getWriting() { return writing; }
//-------------------------------------------------------------------------------------------------

	bool hasCharacters(); //method to check if the text inside the textfield is empty or has only character " "(pressed only space)

	TextField(){} //default constructor

	~TextField()
	{
		bool button_deleted;
		std::string delete_message = name;
		delete_message += " Textfield destructor called ";
		printDebugMessage(delete_message.c_str(), button_deleted);
	} //destructor

	TextField(std::string new_name, float x, float y, float w, float h, std::string text); //custom constructor
	 
};
