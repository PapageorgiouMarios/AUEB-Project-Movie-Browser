#pragma once
#define _CRT_SECURE_NO_WARNINGS //used to not pop up error while string is split to tokens
#include "button.h"
#include "textfield.h"
#include "thumbnail.h"
#include "text_bubble.h"
#include "selection.h"
#include "music_button.h"
#include "refresh_button.h"
#include "number_only_textfield.h"
#include "password.h"
#include <string>
#include <vector>

class Movie_Browser
{
	static Movie_Browser * m_instance; //instance of our movie browser(for our main function)

//--------------------------All buttons that we can press in general(minus the thumbnail's)----------------------
	Button * procceed_button = nullptr;
	Button * search_button = nullptr;
	Button * clear_filters_button = nullptr;
//---------------------------------------------------------------------------------------------------------------

//----------------------All textfields where we can write any kind of content using keyboard---------------------
	TextField * username_textfield = nullptr;
	TextField * director_textfield = nullptr;
	TextField* actor_textfield = nullptr;
	TextField * title_textfield = nullptr;
//----------------------------------------------------------------------------------------------------------------

//------------------------------------All textfields where we can write 4-digits inputs---------------------------
	NumberOnlyTextfield* from_textfield = nullptr;
	NumberOnlyTextfield * to_textfield = nullptr;
//----------------------------------------------------------------------------------------------------------------

//-------------------------Rectangles with text only to be seen(draw purposes only)---------------------------------
	TextBubble* login_username_bubble = nullptr;
	TextBubble * login_password_bubble = nullptr;
	TextBubble * genre_bubble = nullptr;
	TextBubble * director_bubble = nullptr;
	TextBubble * to_bubble = nullptr;
	TextBubble * from_bubble = nullptr;
	TextBubble* actor_bubble = nullptr;
	TextBubble * release_year_bubble = nullptr;
	TextBubble * title_bubble = nullptr;
//------------------------------------------------------------------------------------------------------------------

	PasswordTextfield * password_textfield = nullptr; //textfield for password. Filled only with * characters

	MusicButton * music_button = nullptr; //button for browser_screen. Turns on/off the background music

	RefreshButton* refresh_button = nullptr; //button for browser screen. Resets the movies displayed in thumbnail

	Thumbnail * display_window = nullptr; //window inside the browser_screen. Used to display all movies

	Selection* genre_choices[14]; //static array for all kinds of movie genres. Why static? We already know all possible genres

	std::string genre_names[14] = { "Action", "Adventure", "Comedy", "Drama",
									"Fantasy", "Horror", "Crime", "Mystery",
									"Romance", "Sci-fi", "Sports", "Thriller",
									"Western", "Historical" }; //all specific genres for any possible movie

	vector<Movie *> view_results; //all movies displayed after searching/refreshing. Changed from Next/Previous button
	vector<Movie *> all_movies; //all movies inside our movie database(used for setting the database and searching inside of it)

//-----------------------------------------------Default values for release year--------------------------------------------------
	int min_year = 1890; //Fact: The oldest movie ever made was 'Roundhay Garden Scene''produced in 1888
	int max_year = 2023; //Current year
//--------------------------------------------------------------------------------------------------------------------------------

	bool database_set = false; //boolean to make sure our movie database is set up only once during the running of our program

public:
	typedef enum {STATUS_INTRO, STATUS_LOGIN, STATUS_BROWSER} status_t; //all possible status for our window 
	//1. Animated intro Screen
	//2. Login Screen 
	//3. Browser Screen

	bool playing = false; // boolean to make sure our music mp3 file is not stuck inside MessageLoop()/ playing only once

	//int movie_index = 0; //index of current movie visible inside vector

	void draw(); //general draw function for window
	void update(); //general update function for window
	void init(); //general initialize function for window

	status_t status = STATUS_INTRO; //status to check which screen is drawn/updated during MessageLoop
	//When program starts running, the intro is playing first(1). Then the login(2), and afterwards the browser(3)

//---------------------------------------------Update functions for each state-------------------------------------
	void updateIntroScreen();
	void updateLoginScreen();
	void updateBrowserScreen();
//-----------------------------------------------------------------------------------------------------------------

//---------------------------------------------Draw functions for each state---------------------------------------
	void drawIntroScreen();
	void drawLoginScreen();
	void drawBrowserScreen();
//-----------------------------------------------------------------------------------------------------------------

	void clearAll(); //method to clear all filters inside movie browser

	bool genre_selected(); //boolean to check if at least one genre was selected for filter

	void setMovieDatabase(); //method to create all Movie class objects(With images, names, release year etc.)

	void setMovieForThumbnail(Thumbnail& thumbnail, Movie& movie); //function to change the movie displayed in the browser's thumbnail

	void FindMoviesFromFilters(vector<Movie*>& results); //searching session when Search button is pressed(if filters are set of course)

	status_t getStatus() { return status; } //getter function for running status

	static void deleteInstance() { if (m_instance) delete m_instance; m_instance = nullptr; } //method to call the destructor of existing browser instance
	static Movie_Browser * getInstance(); //getter for browser's instance

	Movie_Browser(); //default constructor
	~Movie_Browser(); //destructor
};
