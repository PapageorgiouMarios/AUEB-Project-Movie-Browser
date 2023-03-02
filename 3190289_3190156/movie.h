#pragma once
#include <string>
#include <vector>
#include "util.h"

using namespace std;

class Movie
{
	const char* title = ""; // Movie's Title

	unsigned int release_year; // Year the movie was released (preferably between 1900 and 2023)

	vector<string> directors; //names of multiple directors

	vector<string> cast; //names of multiple actors

	vector<string> genres; //all movie's genres

	string summary = ""; // A synopsis for the plot of the movie

//------------------------------------Paths of picture inside assets file--------------------------------------

	string picture = ""; //Poster(Main) picture of movie. Always included, mandatory

	string extra_picture_1 = ""; //Extra picture(from scenes, trailers etc.). Not necessary to exist

	string extra_picture_2 = ""; //Extra picture(from scenes, trailers etc.). Not necessary to exist

	string extra_picture_3 = ""; //Extra picture(from scenes, trailers etc.). Not necessary to exist
//---------------------------------------------------------------------------------------------------------------

public:

//------------------------------------------------Setters------------------------------------------------
	void setTitle(const char* m_title) { title = m_title; }
	void setYear(unsigned int m_year) { release_year = m_year; }
	void setSummary(string m_summary) { summary = m_summary; }
	void setMainPicture(string m_picture) { picture = m_picture; }
	void setExtraPicture1(string m_extra_picture_1) { extra_picture_1 = m_extra_picture_1; }
	void setExtraPicture2(string m_extra_picture_2) { extra_picture_2 = m_extra_picture_2; }
	void setExtraPicture3(string m_extra_picture_3) { extra_picture_3 = m_extra_picture_3; }
//-------------------------------------------------------------------------------------------------------

//----------------------------------------------Methods for adding---------------------------------------
	void addDirector(string director_name) { directors.push_back(director_name); }
	void addActor(string actor_name) { cast.push_back(actor_name); }
	void addGenre(string m_genre) { genres.push_back(m_genre); }
//-------------------------------------------------------------------------------------------------------

//--------------------------------------------------Getters---------------------------------------
	const char* getTitle() { return title; }
	unsigned int getYear() { return release_year; }
	vector<string> getDirectors() { return directors; }
	vector<string> getCast() { return cast; }
	vector<string> getGenre() { return genres; }
	string getSummary() { return summary; }
	string getMainPicture() { return picture; }
	string getExtraPicture1() { return extra_picture_1; }
	string getExtraPicture2() { return extra_picture_2; }
	string getExtraPicture3() { return extra_picture_3; }
//-------------------------------------------------------------------------------------------------

	Movie(){} //default constructor

	~Movie()
	{
		bool button_deleted;
		std::string delete_message = title;
		delete_message += " Movie destructor called ";
		printDebugMessage(delete_message.c_str(), button_deleted);
	} //destructor
	
};