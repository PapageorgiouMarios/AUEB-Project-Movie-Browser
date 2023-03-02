#include "thumbnail.h"
#include "util.h"

void Thumbnail::draw()
{
//------------------------------Draw thumbnail's recntangle--------------------------
	graphics::Brush brush_for_window;
	brush_for_window.outline_opacity = 1.0f;
	brush_for_window.fill_opacity = 0.4f;
	SET_COLOR(brush_for_window.fill_color, 0.01f, 0.01f, 0.01f);
	SET_COLOR(brush_for_window.outline_color, 0.0f, 0.0f, 0.0f);
	brush_for_window.gradient = true;
	graphics::drawRect(pos_x, pos_y, width, height, brush_for_window);
//-----------------------------------------------------------------------------------

//------------------------------------Draw Movie's Poster Picture-------------------------------------------------
	graphics::Brush brush_for_movie_picture;

	if(selected_movie)
	{
		brush_for_movie_picture.texture = ASSET_PATH + std::string(selected_movie->getMainPicture());
	}

	brush_for_movie_picture.fill_opacity = 1.0f;
	graphics::drawRect(pos_x - pos_x / 2, pos_y - pos_y / 2.5, width / 3.5, height / 2.5, brush_for_movie_picture);
//-----------------------------------------------------------------------------------------------------------------

//------------------------------------Draw Movie's Extra Picture 1----------------------------------------------------
	graphics::Brush brush_for_extra_picture_1;
	brush_for_extra_picture_1.outline_opacity = 1.0f;

	if (selected_movie && !selected_movie->getExtraPicture1().empty())
	{
		brush_for_extra_picture_1.texture = ASSET_PATH + std::string(selected_movie->getExtraPicture1());
		graphics::drawRect(pos_x - 350, pos_y + 250, width / 4, height / 4, brush_for_extra_picture_1);

	}
//--------------------------------------------------------------------------------------------------------------------

//------------------------------------Draw Movie's Extra Picture 2----------------------------------------------------
	graphics::Brush brush_for_extra_picture_2;

	if (selected_movie && !selected_movie->getExtraPicture2().empty())
	{
		brush_for_extra_picture_2.texture = ASSET_PATH + std::string(selected_movie->getExtraPicture2());
		graphics::drawRect(pos_x, pos_y + 250, width / 4, height / 4, brush_for_extra_picture_2);

	}
//--------------------------------------------------------------------------------------------------------------------

//------------------------------------Draw Movie's Extra Picture 3----------------------------------------------------
	graphics::Brush brush_for_extra_picture_3;

	if (selected_movie && !selected_movie->getExtraPicture3().empty())
	{
		brush_for_extra_picture_3.texture = ASSET_PATH + std::string(selected_movie->getExtraPicture3());
		graphics::drawRect(pos_x + 350, pos_y + 250, width / 4, height / 4, brush_for_extra_picture_3);

	}
//--------------------------------------------------------------------------------------------------------------------

//------------------------Draw Previous and Next buttons------------------
	if(previous && next)
	{
		previous->draw();
		next->draw();
	}
//------------------------------------------------------------------------

//----------------------------------Draw Movie's Title---------------------------------------
	if(title)
	{
		title->draw();

		if(selected_movie)
		{
			graphics::Brush brush_title;
			graphics::setFont(std::string(ASSET_PATH) + "REGULAR.TTF");
			char space_for_title[50];
			const char* sentence_title = selected_movie->getTitle();
			sprintf_s(space_for_title, sentence_title);
			brush_title.outline_opacity = 0.0f;
			graphics::drawText(pos_x - 110, pos_y - 275, 25, space_for_title, brush_title);
		}

	}
//-------------------------------------------------------------------------------------------

//----------------------------------Draw Movie's Directors' names---------------------------------------
	if(directors)
	{
		directors->draw();

		graphics::Brush brush_genre;
		graphics::setFont(std::string(ASSET_PATH) + "REGULAR.TTF");
		char space_for_director[100];

		std::string sentence_director = "";

		for (auto dir : selected_movie->getDirectors())
		{
			sentence_director.append(dir);

			if (dir != selected_movie->getDirectors().back())
			{
				sentence_director.append(", ");
			}
			else if (dir == selected_movie->getDirectors().back())
			{
				sentence_director.append(" ");
			}
		}

		sprintf_s(space_for_director, sentence_director.data());
		brush_genre.outline_opacity = 0.0f;
		graphics::drawText(pos_x - 115, pos_y - 200, 27, space_for_director, brush_genre);
	}
//-----------------------------------------------------------------------------------------------------

//----------------------------------Draw Movie's Release Year---------------------------------------
	if(release_year)
	{
		release_year->draw();

		if (selected_movie)
		{
			graphics::Brush brush_year;
			graphics::setFont(std::string(ASSET_PATH) + "REGULAR.TTF");
			char space_for_year[20];
			std::string y = std::to_string(selected_movie->getYear());
			const char* sentence_year = y.data();
			sprintf_s(space_for_year, sentence_year);
			brush_year.outline_opacity = 0.0f;
			graphics::drawText(pos_x - 115, pos_y - 140, 27, space_for_year, brush_year);
		}
	}
//---------------------------------------------------------------------------------------------------

//----------------------------------Draw Movie's Cast's Names-----------------------------------------
	if(main_cast)
	{
		main_cast->draw();

		if (selected_movie)
		{
			graphics::Brush brush_cast;
			graphics::setFont(std::string(ASSET_PATH) + "REGULAR.TTF");
			char space_for_cast[150];

			std::string sentence_cast = "";

			for (auto actor : selected_movie->getCast())
			{
				sentence_cast.append(actor);

				if (actor != selected_movie->getCast().back())
				{
					sentence_cast.append(", ");
				}
				else if (actor == selected_movie->getCast().back())
				{
					sentence_cast.append(" ");
				}
			}

			sprintf_s(space_for_cast, sentence_cast.data());
			brush_cast.outline_opacity = 0.0f;
			graphics::drawText(pos_x - 115, pos_y - 75, 27 - (sentence_cast.size() * 0.1), space_for_cast, brush_cast);
		}
	}
//-----------------------------------------------------------------------------------------------------

//----------------------------------Draw Movie's Genres------------------------------------------------
	if(genres)
	{
		genres->draw();

		if (selected_movie)
		{
			graphics::Brush brush_genre;
			graphics::setFont(std::string(ASSET_PATH) + "REGULAR.TTF");
			char space_for_genre[100];

			std::string sentence_genre = "";

			for(auto g: selected_movie->getGenre())
			{
				sentence_genre.append(g);
				
				if(g != selected_movie->getGenre().back())
				{
					sentence_genre.append(", ");
				}
				else if(g == selected_movie->getGenre().back())
				{
					sentence_genre.append(" ");
				}
			}

			sprintf_s(space_for_genre, sentence_genre.data());
			brush_genre.outline_opacity = 0.0f;
			graphics::drawText(pos_x - 110, pos_y - 20, 27, space_for_genre, brush_genre);
		}
	}
//-----------------------------------------------------------------------------------------------------

//----------------------------------Draw Movie's Summary in tokens--------------------------------------
	if(summary)
	{
		summary->draw();

		if (selected_movie)
		{
			graphics::Brush brush_summary;
			graphics::setFont(std::string(ASSET_PATH) + "REGULAR.TTF");
			char space_for_summary[200];
			std::string sentence_summary = selected_movie->getSummary();

			const char* sentence_original = sentence_summary.data();
			char* sentence_for_tokens = (char *) sentence_original;

			char* token = strtok(sentence_for_tokens, "@");

			float sentence_y = pos_y + 30;

			while (token)
			{
				sprintf_s(space_for_summary, token);
				brush_summary.outline_opacity = 0.0f;
				graphics::drawText(pos_x - 445, sentence_y, 25, space_for_summary, brush_summary);

				sentence_y += 40;
				token = strtok(NULL, "@");
			}
		}
	}
//-----------------------------------------------------------------------------------------------------
}

void Thumbnail::update()
{
//-------------------------Update Previous and Next button-------------------------------
	if(previous && next)
	{
		previous->update();

		next->update();
	}
//----------------------------------------------------------------------------------------
}

void Thumbnail::init()
{
}

Thumbnail::Thumbnail(float x, float y, float width, float height)
{
	setX(x);
	setY(y);
	setW(width);
	setH(height);

	previous = new Button("Previous Button ", pos_x - 520, pos_y - 350, 100, 35, "Previous");
	next = new Button("Next Button ", pos_x + 520, pos_y - 350, 100, 35, "Next");

	std::string bubble1 = "Title:";
	title = new TextBubble(bubble1, pos_x - 175, pos_y - 280, bubble1.size() * 18, 38);

	std::string bubble2 = "Directors:";
	directors = new TextBubble(bubble2, pos_x - 180, pos_y - 210, bubble2.size() * 10, 38);

	std::string bubble3 = "Released:";
	release_year = new TextBubble(bubble3, pos_x - 180, pos_y - 150, bubble3.size() * 11, 38);

	std::string bubble_for_actors = "Main Cast:";
	main_cast = new TextBubble(bubble_for_actors, pos_x - 180, pos_y - 80, bubble_for_actors.size() * 10, 38);

	std::string bubble4 = "Genre:";
	genres = new TextBubble(bubble4, pos_x - 175, pos_y - 30, bubble4.size() * 18, 38);

	std::string bubble5 = "Summary:";
	summary = new TextBubble(bubble5, pos_x - 510, pos_y + 20, bubble5.size() * 13, 38);
}

Thumbnail::~Thumbnail()
{
	bool thumbnail_deleted;
	std::string delete_message = "Thumbnail destructor called ";
	printDebugMessage(delete_message.c_str(), thumbnail_deleted);
}
