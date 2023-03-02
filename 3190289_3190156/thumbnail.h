#pragma once
#define _CRT_SECURE_NO_WARNINGS //used to not pop up error while string is split to tokens
#include "widget.h"
#include "button.h"
#include "textfield.h"
#include "movie.h"
#include "text_bubble.h"

class Thumbnail : public Widget //subclass of base class Widget
{
	float pos_x, pos_y; //Coordinates for Canvas

	float width, height; //Dimensions of image rectangle

	Button * previous = nullptr; //pointer for Previous Button(used to change to previous movie)
	Button * next = nullptr; //pointer for Next Button(used to change to next movie)

	Movie * selected_movie = nullptr; //pointer for Movie displayed currently

//---------------------------------Textbubbles(for viewing purposes)--------------------------
	TextBubble * title = nullptr;
	TextBubble * directors = nullptr;
	TextBubble * main_cast = nullptr;
	TextBubble * release_year = nullptr;
	TextBubble * genres = nullptr;
	TextBubble * summary = nullptr;
//--------------------------------------------------------------------------------------------

//-------------------------------Names of all pictures from asset file---------------------------
	std::string picture_of_movie = ""; //name of poster picture. Every movie has one of those. Mandatory
	std::string extra_picture_of_movie1 = ""; //name of extra picture(from scenes trailers etc.). Not necessary to exist in file
	std::string extra_picture_of_movie2 = ""; //name of extra picture(from scenes trailers etc.). Not necessary to exist in file
	std::string extra_picture_of_movie3 = ""; //name of extra picture(from scenes trailers etc.). Not necessary to exist in file
//-----------------------------------------------------------------------------------------------

public:

//-----------------------------Override Widget's methods--------------------------
	void draw() override;
	void update() override;
	void init() override;
//---------------------------------------------------------------------------------

//------------------------------------Setters--------------------------------------
	void setX(float x) { pos_x = x; }
	void setY(float y) { pos_y = y; }
	void setW(float w) { width = w; }
	void setH(float h) { height = h; }
	void setSelectedMovie(Movie* my_movie) { selected_movie = my_movie; }
	void setPicture(std::string path) { picture_of_movie = path; }
	void setExtraPicture1(std::string path1) { extra_picture_of_movie1 = path1; }
	void setExtraPicture2(std::string path2) { extra_picture_of_movie2 = path2; }
	void setExtraPicture3(std::string path3) { extra_picture_of_movie3 = path3; }
//----------------------------------------------------------------------------------

//------------------------------------Getters--------------------------------------
	float getX() { return pos_x; }
	float getY() { return pos_y; }
	float getW() { return width; }
	float getH() { return height; }
	Button* getPrevious(){ return previous; }
	Button* getNext() { return next; }
	Movie* getSelectedMovie() { return selected_movie; }
//----------------------------------------------------------------------------------

	Thumbnail(float x, float y, float width, float height); //custom constructor
	~Thumbnail();//destructor

};