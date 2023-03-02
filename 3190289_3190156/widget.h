#pragma once

class Widget //class from which most classes will inherit its methods
{
//------------------Pure virtual methods----------------------
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void init() = 0;
//------------------------------------------------------------
};