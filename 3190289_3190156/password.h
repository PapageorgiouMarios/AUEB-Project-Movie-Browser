#pragma once
#include "textfield.h"

class PasswordTextfield : public TextField //subclass of base class Textfield
{
public:

	//----Override Textfields functions(which are overrided from base class Widget)----
	void draw() override;
	void update() override;
	void init() override;
	//---------------------------------------------------------------------------------

	PasswordTextfield(std::string new_name, float x, float y, float w, float h, std::string text); //custom constructor 
	~PasswordTextfield(); //destructor
};