#pragma once
#include "button.h"
#include "movie.h"

class RefreshButton :Button //subclass of base class Button
{
	bool ready_to_refresh = false;

public:

	//----------------------Override Button methods(which are also overrided from Widget base class)----------------
	void draw() override;
	void update() override;
	void init() override;
	//--------------------------------------------------------------------------------------------------------------

	void setRefresh(bool r) { ready_to_refresh = r; }
	bool getRefresh() { return ready_to_refresh; }

	void resetVectors(vector<Movie*>& results, vector<Movie*> all_movies);

	RefreshButton(std::string new_name, float x, float y, float w, float h); //custom constructor for refresh button
	~RefreshButton(); //destructor for refresh button
};