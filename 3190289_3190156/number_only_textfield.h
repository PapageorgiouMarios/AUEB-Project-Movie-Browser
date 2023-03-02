#pragma once
#include "textfield.h"

class NumberOnlyTextfield : public TextField //subclass of base class Textfield
{
	int digits; //the four digits 

public:

//----Override Textfields functions(which are overrided from base class Widget)----
	void draw() override;
	void update() override;
	void init() override;
//---------------------------------------------------------------------------------

	int getYearDigits() { return std::stoi(getText());} //getter for the release year of a movie string after turning it to int
	//Note: Normally we have to check if stoi method can work properly for all scenarios(not number, NULL, negative numbers etc.)
	//BUT since we always make sure what is written inside the NumberOnlyTextfield(check update function for keyboard)
	//we cover all possible positive number combinations(for example 0100, 01, 2065, 001, etc.)

	NumberOnlyTextfield(std::string new_name, float x, float y, float w, float h, std::string text); //custom constructor 
	~NumberOnlyTextfield(); //destructor
};
