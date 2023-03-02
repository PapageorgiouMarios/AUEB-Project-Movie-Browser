#pragma once
#include "widget.h"
#include <string>

class TextBubble : public Widget //subclass of base class Widget
{
	float pos_x, pos_y; //coordinates of the widget

	float width, height; //dimension of the bubble rectangle

	std::string content; //content drawed at the middle of the rectangle

public:
//---------------------Override methods from base class Widget--------------------
	void draw() override;
	void update() override;
	void init() override;
//--------------------------------------------------------------------------------

//----------------------------------Setters---------------------------------------
	void setX(float x) { pos_x = x; }
	void setY(float y) { pos_y = y; }
	void setW(float w) { width = w; }
	void setH(float h) { height = h; }
	void setContent(std::string c) { content = c; }
//--------------------------------------------------------------------------------

//----------------------------------Getters---------------------------------------
	float getX() { return pos_x; }
	float getY() { return pos_y; }
	float getW() { return width; }
	float getH() { return height; }
	std::string getContent() { return content; }
//--------------------------------------------------------------------------------

	TextBubble(std::string content, float x, float y, float width, float height); //custom consrtuctor
	~TextBubble(); //destructor
};