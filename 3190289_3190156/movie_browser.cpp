#include "movie_browser.h"
#include "util.h"
#include "graphics.h"
#include "scancodes.h"
#include <iostream>
#include <algorithm>

void Movie_Browser::draw() //draw the project's window in general
{
    if (status == STATUS_INTRO) //if we the intro is playing
    {
        drawIntroScreen(); //draw the intro animation

        static bool intro_draw = true;

        printDebugMessage("Intro Screen drawed: ", intro_draw);
        
    }
    else if (status == STATUS_LOGIN) //if we opened the login screen
    {
        drawLoginScreen(); //draw the login screen

        static bool login_draw = true;

        printDebugMessage("Login Screen drawed: ", login_draw);
 
    }
    else if (status == STATUS_BROWSER) //if we opened the browser screen
    {
        drawBrowserScreen(); //draw the browser screen

        static bool browser_draw = true;

        printDebugMessage("Browser Screen drawed: ", browser_draw);
    }
}

void Movie_Browser::update()
{
    if (status == STATUS_INTRO) //if we the intro is playing
    {
        updateIntroScreen(); //update the intro animation

        static bool intro_update = true;

        printDebugMessage("Intro Screen updated: ", intro_update);
 
    }

    else if (status == STATUS_LOGIN) //if we opened the login screen
    {
        updateLoginScreen(); //update the login screen

        static bool login_update = true;

        printDebugMessage("Login Screen updated: ", login_update);
 
    }
    
    else if (status == STATUS_BROWSER) //if we opened the browser screen
    {
        updateBrowserScreen(); //update the browser screen

        static bool browser_update = true;

        printDebugMessage("Browser Screen updated: ", browser_update);

    }

}

void Movie_Browser::init()
{

}

void Movie_Browser::updateIntroScreen()
{
    graphics::playSound(ASSET_PATH + std::string("intro_music.mp3"), 0.01f, false); //plays the intro sound
    //Note: If we keep dragging the window of the browser, after 17 sec, the sound will play again

    static bool intro_playing = true;

    printDebugMessage("Intro Sound played: ", intro_playing);

    if(graphics::getGlobalTime() > 17000) //if 17 sec are passed
    {
        status = STATUS_LOGIN; //we change to login screen

        static bool to_login = true;

        printDebugMessage("Status changed to STATUS_LOGIN ", to_login);

    }
}

void Movie_Browser::updateLoginScreen()
{
    if(!procceed_button && graphics::getGlobalTime() > 19000) //after 19 sec and the procceed button wasn't created yet
    {
        static bool procceed_button_created = true;

        procceed_button = new Button("Procceed Button ", CANVAS_WIDTH / 2 + 600, CANVAS_HEIGHT / 2 + 350, 160.0f, 50.0f, "Procceed");

        printDebugMessage("Procceed Button created: ", procceed_button_created);

    }

    if(!username_textfield && graphics::getGlobalTime() > 19000) //after 19 sec and the username textfield wasn't created yet
    {
        static bool username_textfield_created = true;

        username_textfield = new TextField("Username Textfield", CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 - 50, 300.0f, 55.0f, "");

        printDebugMessage("Username Textfield created: ", username_textfield_created);
    }

    if (!password_textfield && graphics::getGlobalTime() > 19000) //after 19 sec and the password textfield wasn't created yet
    {
        static bool password_textfield_created = true;

        password_textfield = new PasswordTextfield("Password Textfield", CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 50 , 300.0f, 55.0f, "");

        printDebugMessage("Password Textfield created: ", password_textfield_created);
    }

    if(!login_username_bubble && graphics::getGlobalTime() > 19000) //after 19 sec and the password bubble wasn't created yet
    {
        static bool username_bubble_created = true;

        login_username_bubble = new TextBubble("Username:", CANVAS_WIDTH / 2 - 240, CANVAS_HEIGHT / 2 - 50, 170.0f, 50.0f);

        printDebugMessage("Username Bubble created: ", username_bubble_created);
    }

    if (!login_password_bubble && graphics::getGlobalTime() > 19000) //after 19 sec and the password bubble wasn't created yet
    {
        static bool password_bubble_created = true;

        login_password_bubble = new TextBubble("Password:", CANVAS_WIDTH / 2 - 240, CANVAS_HEIGHT / 2 + 50, 170.0f, 50.0f);

        printDebugMessage("Username Bubble created: ", password_bubble_created);
    }

    if(procceed_button) //if the procceed button was already created
    {
        procceed_button->update(); //the button keeps updating inside MessageLoop
    }

    if(username_textfield) //if the username textfield was already created
    {
        username_textfield->update(); //the textfield keeps updating inside MessageLoop
    }

    if(password_textfield) //if the password textfield was already created
    {
        password_textfield->update(); //the textfield keeps updating inside MessageLoop
    }

    if(login_username_bubble) //if the Username TextBubble was already created
    {
        login_username_bubble->update(); //Redundant. The update() function of TextBubble is empty
    }

    if(login_password_bubble) //if the Password TextBubble was already created
    {
        login_password_bubble->update(); //Redundant. The update() function of TextBubble is empty
    }

    if(procceed_button && 
        username_textfield && 
        password_textfield && 
        login_username_bubble &&
        login_password_bubble &&
        procceed_button->getClicked()) //if the login screen widgets are already made
    {
        static bool to_browser = true;

        if(username_textfield->hasCharacters() && password_textfield->hasCharacters()) //we check if we have written something inside the username textfield
        {
            status = STATUS_BROWSER; //we change to browser screen

            printDebugMessage("Status changed to STATUS_BROWSER ", to_browser);

        }
        else
        {
            static bool not_to_browser = true;

            if(!username_textfield->hasCharacters())
            {
                printDebugMessage("Invalid username, please fill the field correctly ", not_to_browser);
            }

            if(!password_textfield->hasCharacters())
            {
                printDebugMessage("Invalid password, please fill the field correctly ", not_to_browser);
            }

            not_to_browser = true;
        }
    }

    if(status == STATUS_BROWSER) //if we have changed to browser screen, we delete the login screen objects
    {
        procceed_button->~Button();
        login_username_bubble->~TextBubble();
        login_password_bubble->~TextBubble();
        username_textfield->~TextField();
        password_textfield->~PasswordTextfield();
    }
}

void Movie_Browser::updateBrowserScreen()
{
    static int movie_index = 0; //index of current movie visible inside vector

    if(view_results.empty() && !database_set) //if thumbnail's movie list has no movies and the database was not created at the start
    {
        setMovieDatabase(); //we create the database of the movies
        database_set = true; //we make sure the database was created only once(to avoid copies)
    }

    if(!display_window) //if the thumbnail which displays movies wasn't created yet
    {
        display_window = new Thumbnail(CANVAS_WIDTH/2 + 110, CANVAS_HEIGHT/2, (int) CANVAS_WIDTH - 250, CANVAS_HEIGHT - 50);
        //we create the Thumbnail to display our movies

        if(!view_results.empty()) //if the number of movies available for display are more than 0
        {
            if(display_window->getSelectedMovie() == nullptr) //we check if a beginning movie was not set yet for the thumbnail
            {
                setMovieForThumbnail(*display_window, *view_results.at(0)); 
                //Basically, we are saying that the first movie from the database will be displayed first on Thumbnail
            }

            else
            {
                setMovieForThumbnail(*display_window, *view_results.at(movie_index));
            }
        }
    }

    if(!music_button) //if music button wasn't created yet
    {
        music_button = new MusicButton("Music Button ", 120, 51, 44, 44, true);
        //we create the music button which plays music by default
    }

    if(!refresh_button) //if refresh button wasn't created yet
    {
        refresh_button = new RefreshButton("Refresh Button ", 170, 49, 34, 34);
        //we create the refresh button which resets the view_results to all_movies
    }

    if(!search_button) //if search button wasn't created yet
    {
        search_button = new Button("Search Button ", 50, CANVAS_HEIGHT - 20, 90, 35, "Search");
        //we create the search button which call the movie searching function 
    }

    if(!clear_filters_button) //if clear filters button wasn't created yet
    {
        clear_filters_button = new Button("Clear Filters Button ", 150, CANVAS_HEIGHT - 20, 90, 35, "Clear Filters");
        //we create the clear filters button that clears any filter we have filled 
    }

    if(!genre_bubble) //if the Pick Genre TextBubble wasn't created yet
    {
        std::string s = "Pick Genre:";
        genre_bubble = new TextBubble(s, 65, CANVAS_HEIGHT - 270, s.size() * 10, 31);
    }

    if (!director_bubble) //if the Director TextBubble wasn't created yet
    {
        std::string db = "Director:";
        director_bubble = new TextBubble(db, 65, CANVAS_HEIGHT - 350, db.size() * 12, 31);
    }

    if(!director_textfield) //if the Textfield for directors wasn't created yet
    {
        director_textfield = new TextField("Director Textfield", 110, CANVAS_HEIGHT - 310, 235.0f, 55.0f, "");
    }

    if(!to_bubble) //if the To TextBubble wasn't created yet
    {
        std::string tb = "To:  ";
        to_bubble = new TextBubble(tb, 45, CANVAS_HEIGHT - 390, tb.size() * 15, 28);
    }

    if(!to_textfield) //if the NumberOnlyTextfield for to release year wasn't created yet
    {
        to_textfield = new NumberOnlyTextfield("Release year TO NumberOnlyTextfield", 150, CANVAS_HEIGHT - 390, 140.0f, 55.0f, "");
    }

    if(!from_textfield) //if the NumberOnlyTextfield for from release year wasn't created yet
    {
        from_textfield = new NumberOnlyTextfield("Release year FROM NumberOnlyTextfield", 150, CANVAS_HEIGHT - 460, 140.0f, 55.0f, "");
    }

    if(!from_bubble) //if the From TextBubble wasn't created yet
    {
        std::string tb = "From:";
        from_bubble = new TextBubble(tb, 45, CANVAS_HEIGHT - 460, tb.size() * 15, 28);
    }

    if(!release_year_bubble) //if the Released TextBubble wasn't created yet
    {
        std::string rb = "Released:";
        release_year_bubble = new TextBubble(rb, 65, CANVAS_HEIGHT - 505, rb.size() * 12, 31);
    }

    if(!title_textfield) //if the Textfield for title wasn't created yet
    {
        title_textfield = new TextField("Title Textfield", 115, CANVAS_HEIGHT - 635, 235.0f, 55.0f, "");
    }

    if(!title_bubble) //if the Title TextBubble wasn't created yet
    {
        std::string tb = "Title:";
        title_bubble = new TextBubble(tb, 70, CANVAS_HEIGHT - 675, tb.size() * 19, 30);
    }

    if(!actor_textfield) //if the Textfield for one actor wasn't created yet
    {
        actor_textfield = new TextField("Actor Textfield", 115, CANVAS_HEIGHT - 545, 235.0f, 55.0f, "");
    }

    if(!actor_bubble) //if the Actor TextBubble wasn't created yet
    {
        std::string tb = "Actor:";
        actor_bubble = new TextBubble(tb, 70, CANVAS_HEIGHT - 585, tb.size() * 19, 30);
    }

    //For all possible genres
    for(int i = 0; i < 14; i++) //if each genre Selection wasn't created yet
    {
        if(!genre_choices[i])
        {
            if(i  >= 0 && i < 3)
            {
                genre_choices[i] = new Selection(genre_names[i] + " Genre ", 35 + 80 * (i - 0), CANVAS_HEIGHT - 220, 61, 28, genre_names[i]);
            }
            else if( i >= 3 && i < 6)
            {
                genre_choices[i] = new Selection(genre_names[i] + " Genre ", 35 + 80 * (i - 3), CANVAS_HEIGHT - 180, 61, 28, genre_names[i]);
            }
            else if(i >= 6 && i < 9)
            {
                genre_choices[i] = new Selection(genre_names[i] + " Genre ", 35 + 80 * (i - 6), CANVAS_HEIGHT - 140, 61, 28, genre_names[i]);
            }

            else if (i >= 9 && i < 12)
            {
                genre_choices[i] = new Selection(genre_names[i] + " Genre ", 35 + 80 * (i - 9), CANVAS_HEIGHT - 100, 61, 28, genre_names[i]);
            }

            else if (i >= 12 && i < 14)
            {
                genre_choices[i] = new Selection(genre_names[i] + " Genre ", 35 + 80 * (i - 12), CANVAS_HEIGHT - 60, 61, 28, genre_names[i]);
            }
        }
    }

    if(music_button) //if the music button was already created
    {
        music_button->update(); //the music button keeps updating inside MessageLoop
    }

    if(music_button && music_button->getState()) //if music button is already created and the music is turned on
    {
        playSong(0.9, playing);
    }

    if(music_button && !music_button->getState()) // if music button is already createdand the music is turned off
    {
        graphics::stopMusic(); //stop the music until the button is pressed again
        playing = false; //we reset our playing boolean to avoid infinite playing if the button is pressed again
    }

    if(refresh_button) //if the refresh button was already created
    {
        refresh_button->update(); //the refresh button keeps updating inside MessageLoop
    }

    if(refresh_button && refresh_button->getRefresh())
    {
        refresh_button->resetVectors(view_results, all_movies);
        setMovieForThumbnail(*display_window, *view_results.at(0));
    }

    if(display_window) //if the movie display thumbnail was already created
    {
        display_window->update(); //the thumbnail keeps updating inside MessageLoop
    }

    if(search_button) //if the search button was already created
    {
        search_button->update(); //the search button keeps updating inside MessageLoop
    }

    if(clear_filters_button) //if the clear filters button was already created
    {
        clear_filters_button->update(); //the clear filters button keeps updating inside MessageLoop
    }

    for (int i = 0; i < 14; i++) //for each genre
    {
        if (genre_choices[i]) //if each genre's selection button was already created
        {
            genre_choices[i]->update(); //the genre's selection button keeps updating inside MessageLoop
        }
    }

    if(genre_bubble) //if the textbubble of genres is already created
    {
        genre_bubble->update(); //Redundant. The update() function of TextBubble is empty
    }

    if(director_textfield) //if the Textfield for one director wasn't created yet
    {
        director_textfield->update(); //the director textfield keeps updating inside MessageLoop
    }

    if(actor_textfield) //if the Textfield for one actor wasn't created yet
    {
        actor_textfield->update(); //the actor textfield keeps updating inside MessageLoop
    }

    if(actor_bubble) //if the textbubble of actor is already created
    {
        actor_bubble->update(); //Redundant. The update() function of TextBubble is empty
    }

    if(director_bubble) //if the textbubble of actor is already created
    {
        director_bubble->update(); //Redundant. The update() function of TextBubble is empty
    }

    if(to_bubble) //if the textbubble of to is already created
    {
        to_bubble->update(); //Redundant. The update() function of TextBubble is empty
    }

    if(from_bubble) //if the textbubble of from is already created
    {
        from_bubble->update(); //Redundant. The update() function of TextBubble is empty
    }

    if(to_textfield) //if the Textfield for to release year wasn't created yet
    {
        to_textfield->update(); //the to release year textfield keeps updating inside MessageLoop
    }

    if(from_textfield) //if the Textfield for from release year wasn't created yet
    {
        from_textfield->update(); //the from release year textfield keeps updating inside MessageLoop
    }

    if(release_year_bubble) //if the textbubble of release year is already created
    {
        release_year_bubble->update(); //Redundant. The update() function of TextBubble is empty
    }

    if(title_textfield) //if the Textfield for title wasn't created yet
    {
        title_textfield->update(); //the from title textfield keeps updating inside MessageLoop
    }

    if(clear_filters_button && clear_filters_button->getClicked()) //if the clear filters button exists and is pressed
    {
        clearAll(); //call method to empty all filled filters
    }

    if(display_window && display_window->getPrevious()->getClicked()) //if previous button of existant thumbnail was clicked
    {
        if(movie_index == 0 && view_results.size() > 0) //if we press previous button and the current movie is the first of the results vector
        {
            movie_index = view_results.size() - 1; //we go to the last movie of the vector
        }
        else if(view_results.size() > 0 && movie_index > 0) //if we press previous button and there are multiple movies and the current movie is not the first nor the last 
        {
            movie_index = movie_index - 1; //we go to the previous movie
        }
        if(view_results.size() == 1) //if there is only one movie for thumbnail
        {
            movie_index = 0; //we keep the index of the only movie inside vector
        }
        std::cout << "Selected movie  at index " << movie_index << ": " << view_results.at(movie_index)->getTitle() << endl;
        setMovieForThumbnail(*display_window, *view_results.at(movie_index)); //in all cases we set the previous movie of the vector
    }

    if (display_window && display_window->getNext()->getClicked()) //if next button of existant thumbnail was clicked
    {
        if (movie_index == view_results.size() - 1 && view_results.size() > 0) //if we press previous button and the current movie is the last of the results vector
        {
            movie_index = 0; ////we go to the first movie of the vector
        }
        else if(view_results.size() > 0 && movie_index < view_results.size() - 1) //if we next previous button and there are multiple movies and the current movie is not the first nor the last 
        {
            movie_index = movie_index + 1; //we go to the next movie
        }
        if (view_results.size() == 1) //if there is only one movie for thumbnail
        {
            movie_index = 0; //we keep the index of the only movie inside vector
        }
        std::cout << "Selected movie  at index " << movie_index << ": " << view_results.at(movie_index)->getTitle() << endl;
        setMovieForThumbnail(*display_window, *view_results.at(movie_index)); //in all cases we set the next movie of the vector
    }

    if(search_button && search_button->getClicked()) //if the search button exists and is pressed
    {
        movie_index = 0;
        FindMoviesFromFilters(view_results);
        //searchFilters(view_results); //we search all movies to find results
        setMovieForThumbnail(*display_window, *view_results.at(0)); //we set the first movie of the result vector(must be one)
    }
}

void Movie_Browser::drawIntroScreen()
{
    graphics::Brush brush_for_background;

    brush_for_background.outline_opacity = 0.0f;

    brush_for_background.texture = ASSET_PATH + std::string("intro_background.png");

    //---------------------------------------ANIMATION-------------------------------------
    brush_for_background.fill_opacity = -0.2f;

    brush_for_background.fill_opacity += (graphics::getGlobalTime() / 10000.0f);
    //-------------------------------------------------------------------------------------

    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, brush_for_background); //covers the whole canvas

    graphics::Brush brush_for_logo;

    brush_for_logo.outline_opacity = 0.0f;

    brush_for_logo.texture = ASSET_PATH + std::string("intro_dragon.png");

    //---------------------------------------ANIMATION-------------------------------------
    brush_for_logo.fill_opacity = -0.4f;

    brush_for_logo.fill_opacity += (graphics::getGlobalTime() / 10000.0f);
    //-------------------------------------------------------------------------------------

    graphics::drawRect(CANVAS_WIDTH / 2 + 25, CANVAS_HEIGHT / 2 - 25, 350, 350, brush_for_logo); //draws the Hermes logo

//--------------------------------------------Draw Blue Eyes' Title---------------------------------------------------
    graphics::Brush brush_for_title;
    SET_COLOR(brush_for_title.fill_color, 0.0F, 0.3F, 0.9f); //gives color to the character array's letters
    graphics::setFont(std::string(ASSET_PATH) + "TEXT.TTF");
    char info1[40];
    sprintf_s(info1, "Blue-Eyes Tube ");

    brush_for_title.outline_opacity = 0.0f;
//--------------------------------------------------------------------------------------------------------------------

    //---------------------------------------ANIMATION-------------------------------------
    brush_for_title.fill_opacity = -0.5f;

    brush_for_title.fill_opacity += (graphics::getGlobalTime() / 11000.0f);
    //-------------------------------------------------------------------------------------

    graphics::drawText(CANVAS_WIDTH / 2 - 250, CANVAS_HEIGHT / 2 - 280, 100, info1, brush_for_title);

    graphics::Brush brush_for_student_names;

    SET_COLOR(brush_for_student_names.fill_color, 0.0f, 0.3f, 0.9f);

    graphics::setFont(std::string(ASSET_PATH) + "REGULAR.TTF");

    char info2[60]; //we set 60 because if we set 40 like the previous text, it'll pop up error because of the non-efficient space of the array

    sprintf_s(info2, "Created by: Marios Papageorge and Jason Kaminas");

    brush_for_student_names.outline_opacity = 0.0f;

    //---------------------------------------ANIMATION-------------------------------------
    brush_for_student_names.fill_opacity = -0.8f;

    brush_for_student_names.fill_opacity += (graphics::getGlobalTime() / 11000.0f);
    //-------------------------------------------------------------------------------------

    graphics::drawText(CANVAS_WIDTH / 2 - 680, CANVAS_HEIGHT / 2 + 380, 20, info2, brush_for_student_names);
}

void Movie_Browser::drawLoginScreen()
{
    graphics::Brush brush_for_login;

    brush_for_login.outline_opacity = 0;

    brush_for_login.texture = ASSET_PATH + std::string("login_background.png");

    SET_COLOR(brush_for_login.fill_color, 0.0f, 0.4f, 0.8f);

    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, brush_for_login);

    if(procceed_button) //if procceed button is already created
    {
        procceed_button->draw(); //the procceed button remains drawed inside MessageLoop
    }

    if(username_textfield) //if username textfield is already created
    {
        username_textfield->draw(); //the username textfield remains drawed inside MessageLoop
    }

    if(login_username_bubble) //if the username bubble is already created
    {
        login_username_bubble->draw(); //the username bubble remains drawed inside MessageLoop
    }

    if(password_textfield) //if password textfield is already created
    {
        password_textfield->draw(); // the password textfield remains drawed inside MessageLoop
    }

    if(login_password_bubble) //if the password bubble is already created
    {
        login_password_bubble->draw(); //the password bubble remains drawed inside MessageLoop
    }
    //----------------------------------Draw Dragon Lady Logo-------------------------------------
    
    if(graphics::getGlobalTime() > 18000) //after the first 18 sec
    {
        graphics::Brush brush_for_logo;

        brush_for_logo.outline_opacity = 0.0f;

        brush_for_logo.texture = ASSET_PATH + std::string("dragon_lady.png");

        graphics::drawRect(CANVAS_WIDTH / 2 - 570, CANVAS_HEIGHT / 2 - 250, 240, 350, brush_for_logo);
    }

    //--------------------------------------------------------------------------------------------

    //-------------------------------------Draw welcome message-----------------------------------

    if(graphics::getGlobalTime() > 18500)
    {
        graphics::Brush brush_summary;
        graphics::setFont(std::string(ASSET_PATH) + "REGULAR.TTF");
        char space_for_summary[300];
        std::string sentence_summary = "";
        sentence_summary += "Welcome to Blue-Eyes Tube!@";
        sentence_summary += "Here you can find all your favourite movies.@";
        sentence_summary += "To procceed to the browser,@";
        sentence_summary += "please fill your username and password.@";
        sentence_summary += "In order to search movies fitting to any specific tastes,@";
        sentence_summary += "You can fill any of the browser's filters(Title, Director, Actor, Release Year, genre)@";
        sentence_summary += "and begin searching. Happy hunting!@";

        const char* sentence_original = sentence_summary.data();
        char* sentence_for_tokens = (char*)sentence_original;

        char* token = strtok(sentence_for_tokens, "@");

        float sentence_y = 100;

        while (token)
        {
            sprintf_s(space_for_summary, token);
            brush_summary.outline_opacity = 0.0f;
            graphics::drawText(250, sentence_y, 20, space_for_summary, brush_summary);

            sentence_y += 25;
            token = strtok(NULL, "@");
        }
    }
    //--------------------------------------------------------------------------------------------
}

void Movie_Browser::drawBrowserScreen()
{
//--------------------------------------Draw Background---------------------------------------------------------
    graphics::Brush brush_for_browser;

    brush_for_browser.outline_opacity = 0;

    brush_for_browser.texture = ASSET_PATH + std::string("browser.png");

    SET_COLOR(brush_for_browser.fill_color, 0.0f, 0.2f, 0.7f);

    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, brush_for_browser);
//--------------------------------------------------------------------------------------------------------------

//-------------------------------------Draw Dragon Logo--------------------------------------
    graphics::Brush brush_for_logo;

    brush_for_logo.outline_opacity = 0.0f;

    brush_for_logo.texture = ASSET_PATH + std::string("intro_dragon.png");

    graphics::drawRect(60, 60, 110, 110, brush_for_logo);
//--------------------------------------------------------------------------------------------

    if(display_window) //if thumbnail is already created
    {
        display_window->draw(); //the thumbnail remains drawed inside MessageLoop

//------------------------------------------------Draw how many movies can be displayed--------------------------------------------------
        graphics::Brush brush_for_results;
        graphics::setFont(std::string(ASSET_PATH) + "TEXT.TTF");
        char space_for_results[50];
        std::string sentence_results = "Movies Found: ";
        int number_of_found = view_results.size();
        sentence_results += std::to_string(number_of_found);
        sprintf_s(space_for_results, sentence_results.data());
        brush_for_results.outline_opacity = 0.0f;
        graphics::drawText(display_window->getX() / 2 + 300, display_window->getY() / 2 - 140, 25, space_for_results, brush_for_results);
//---------------------------------------------------------------------------------------------------------------------------------------   
    }

    if (music_button) //if music button is already created
    {
        music_button->draw(); //the music button remains drawed inside MessageLoop
    }

    if(refresh_button) //if refresh button is already created
    {
        refresh_button->draw(); //the refresh button remains drawed inside MessageLoop
    }

    if(search_button) //if search button is already created
    {
        search_button->draw(); //the search button remains drawed inside MessageLoop
    }

    if(clear_filters_button) //if clear filters button is already created
    {
        clear_filters_button->draw(); //the clear filters button remains drawed inside MessageLoop
    }

    for (int i = 0; i < 14; i++) //for each genre selection  
    {
        if (genre_choices[i]) //if each selection is already created
        {
            genre_choices[i]->draw(); //each selection remains drawed inside MessageLoop
        }
    }

    if(genre_bubble) //if the genre bubble is already created
    {
        genre_bubble->draw(); //the genre bubble remains drawed inside MessageLoop
    }

    if(director_textfield) //if the director textfield is already created
    {
        director_textfield->draw(); //the director textfield remains drawed inside MessageLoop
    }

    if (actor_textfield) //if the actor textfield is already created
    {
        actor_textfield->draw(); //the actor textfield remains drawed inside MessageLoop
    }

    if(director_bubble) //if the director bubble is already created
    {
        director_bubble->draw(); //the director bubble remains drawed inside MessageLoop
    }

    if (actor_bubble) //if the actor bubble is already created
    {
        actor_bubble->draw(); //the actor bubble remains drawed inside MessageLoop
    }

    if(to_bubble) //if the to bubble is already created
    {
        to_bubble->draw(); //the to bubble remains drawed inside MessageLoop
    }

    if(from_bubble) //if the from bubble is already created
    {
        from_bubble->draw(); //the from bubble remains drawed inside MessageLoop
    }

    if(to_textfield) //if the to textfield is already created
    {
        to_textfield->draw(); //the to textfield remains drawed inside MessageLoop
    }

    if(from_textfield) //if the from textfield is already created
    {
        from_textfield->draw(); //the from textfield remains drawed inside MessageLoop
    }

    if(release_year_bubble) //if the release year bubble is already created
    {
        release_year_bubble->draw(); //the release year bubble remains drawed inside MessageLoop
    }

    if(title_textfield) //if the title textfield is already created
    {
        title_textfield->draw(); //the title textfield remains drawed inside MessageLoop
    }

    if(title_bubble) //if the title bubble is already created
    {
        title_bubble->draw(); //the title bubble remains drawed inside MessageLoop
    }
}

void Movie_Browser::clearAll()
{
    if(title_textfield->hasCharacters()) //we check if we have written something inside the title textfield
    {
        title_textfield->setText(""); //we empty the text inside the title textfield 

        std::cout << title_textfield->getName() << " cleared!" << endl;
    }

    if(from_textfield->hasCharacters()) //we check if we have written something inside the from textfield
    {
        from_textfield->setText(""); //we empty the text inside the from textfield 

        std::cout << from_textfield->getName() << " cleared!" << endl;
    }

    if(to_textfield->hasCharacters()) //we check if we have written something inside the to textfield
    {
        to_textfield->setText(""); //we empty the text inside the to textfield 

        std::cout << to_textfield->getName() << " cleared!" << endl;
    }

    if(director_textfield->hasCharacters()) //we check if we have written something inside the director textfield
    {
        director_textfield->setText(""); //we empty the text inside the director textfield 

        std::cout << director_textfield->getName() << " cleared!" << endl;
    }

    for(int i = 0; i < 14; i++) ///for each genre selection
    {
        if(genre_choices[i]->getSelection()) //if one genre was selected
        {
            genre_choices[i]->setSelection(false); //we unselect it

            std::cout << genre_choices[i]->getName() << " cleared!" << endl;
        }
    }

}

bool Movie_Browser::genre_selected()
{
    bool flag = false; //boolean to be returned

    for(int i = 0; i < 14; i++) //for each genre selection
    {
        if(genre_choices[i]->getSelection()) //if we have chosen a genre
        {
            flag = true; //we'll return true
            break; //we want at least one
        }
    }

    return flag;
}

void Movie_Browser::setMovieDatabase()
{
    Movie * movie_1 = new Movie();

    movie_1->setTitle("Scarface");

    movie_1->setYear(1983);

    movie_1->addActor("Al Pacino");
    movie_1->addActor("Michelle Pfeiffer");
    movie_1->addActor("Steven Bauer");
    movie_1->addActor("Robert Loggia");
    movie_1->addActor("Miriam Colon");
    movie_1->addActor("Paul Shenar");
 

    movie_1->addDirector("Brian De Palma");

    movie_1->addGenre("Crime");
    movie_1->addGenre("Drama");

    movie_1->setSummary("In 1980 Miami, a determined Cuban immigrant takes over a drug cartel and succumbs to greed.");

    movie_1->setMainPicture("Scarface_main_picture.png");
    movie_1->setExtraPicture1("Scarface_extra_picture_1.png");
    movie_1->setExtraPicture2("Scarface_extra_picture_2.png");

    Movie* movie_2 = new Movie();

    movie_2->setTitle("Split");

    movie_2->setYear(2016);

    movie_2->addActor("James McAvoy");
    movie_2->addActor("Anya Taylor-Joy");
    movie_2->addActor("Haley Lu Richardson");

    movie_2->addDirector("M. Night Shyamalan");

    movie_2->addGenre("Horror");
    movie_2->addGenre("Thriller");

    movie_2->setSummary("Three girls are kidnapped by a man with a diagnosed 23 distinct personalities.@They must try to escape before the apparent emergence of a frightful new 24th.");

    movie_2->setMainPicture("Split_main_picture.png");
    movie_2->setExtraPicture1("Split_extra_picture_1.png");
    movie_2->setExtraPicture2("Split_extra_picture_2.png");
    movie_2->setExtraPicture3("Split_extra_picture_3.png");

    Movie* movie_3 = new Movie();

    movie_3->setTitle("Avatar");

    movie_3->setYear(2009);

    movie_3->addActor("Sam Worthington");
    movie_3->addActor("Zoe Saldana");
    movie_3->addActor("Sigourney Weaver");
    movie_3->addActor("Michelle Rodriguez");

    movie_3->addDirector("James Cameron");

    movie_3->addGenre("Action");
    movie_3->addGenre("Adventure");
    movie_3->addGenre("Fantasy");

    movie_3->setSummary("A paraplegic Marine dispatched to the moon Pandora on a unique mission becomes@torn between following his orders and protecting the world he feels is his home.");

    movie_3->setMainPicture("Avatar_main_picture.png");
    movie_3->setExtraPicture1("Avatar_extra_picture_1.png");
    movie_3->setExtraPicture2("Avatar_extra_picture_2.png");
    movie_3->setExtraPicture3("Avatar_extra_picture_3.png");

    Movie* movie_4 = new Movie();

    movie_4->setTitle("The Godfather");

    movie_4->setYear(1972);

    movie_4->addActor("Marlon Brando");
    movie_4->addActor("Al Pacino");
    movie_4->addActor("James Caan");
    movie_4->addActor("Diane Keaton");
    movie_4->addActor("Robert Duvall");

    movie_4->addDirector("Francis Ford Coppola");

    movie_4->addGenre("Crime");
    movie_4->addGenre("Drama");

    movie_4->setSummary("The aging patriarch of an organized crime dynasty in postwar New York City@transfers control of his clandestine empire to his reluctant youngest son.");

    movie_4->setMainPicture("Godfather_main_picture.png");
    movie_4->setExtraPicture1("Godfather_extra_picture_1.png");
    movie_4->setExtraPicture2("Godfather_extra_picture_2.png");

    Movie* movie_5 = new Movie();

    movie_5->setTitle("The Godfather Part II");

    movie_5->setYear(1974);

    movie_5->addActor("Al Pacino");
    movie_5->addActor("Robert De Niro");
    movie_5->addActor("Robert Duvall");

    movie_5->addDirector("Francis Ford Coppola");

    movie_5->addGenre("Crime");
    movie_5->addGenre("Drama");

    movie_5->setSummary("The early life and career of Vito Corleone in 1920s New York City is @portrayed, while his son, Michael, expands and tightens his grip on the family crime syndicate.");

    movie_5->setMainPicture("Godfather2_main_picture.png");
    movie_5->setExtraPicture1("Godfather2_extra_picture_1.png");
    movie_5->setExtraPicture2("Godfather2_extra_picture_2.png");

    Movie* movie_6 = new Movie();

    movie_6->setTitle("The Godfather Part III");

    movie_6->setYear(1990);

    movie_6->addActor("Al Pacino");
    movie_6->addActor("Diane Keaton");
    movie_6->addActor("Andy Garcia");

    movie_6->addDirector("Francis Ford Coppola");

    movie_6->addGenre("Crime");
    movie_6->addGenre("Drama");

    movie_6->setSummary("Follows Michael Corleone, now in his 60s, as he seeks to free his family@from crime and find a suitable successor to his empire.");

    movie_6->setMainPicture("Godfather3_main_picture.png");
    movie_6->setExtraPicture1("Godfather3_extra_picture_1.png");
    movie_6->setExtraPicture2("Godfather3_extra_picture_2.png");

    Movie* movie_7 = new Movie();

    movie_7->setTitle("Hercules");

    movie_7->setYear(1997);

    movie_7->addActor("Tate Donovan");
    movie_7->addActor("Susan Egan");
    movie_7->addActor("James Woods");

    movie_7->addDirector("Baran bo Odar");
    movie_7->addDirector("Jantje Friese");

    movie_7->addGenre("Adventure");
    movie_7->addGenre("Fantasy");
    movie_7->addGenre("Comedy");

    movie_7->setSummary("The son of Zeus and Hera is stripped of his immortality as an infant and must become@a true hero in order to reclaim it.");

    movie_7->setMainPicture("Hercules_main_picture.png");
    movie_7->setExtraPicture1("Hercules_extra_picture_1.png");
    movie_7->setExtraPicture2("Hercules_extra_picture_2.png");
    movie_7->setExtraPicture3("Hercules_extra_picture_3.png");

    Movie* movie_8 = new Movie();

    movie_8->setTitle("Man Of Steel");

    movie_8->setYear(2013);

    movie_8->addActor("Henry Cavil");
    movie_8->addActor("Amy Adams");
    movie_8->addActor("Michael Shannon");

    movie_8->addDirector("Zack Snyder");

    movie_8->addGenre("Action");
    movie_8->addGenre("Adventure");
    movie_8->addGenre("Sci-fi");

    movie_8->setSummary("An alien child is evacuated from his dying world and sent to Earth to live among humans.@His peace is threatened when other survivors of his home planet invade Earth.");

    movie_8->setMainPicture("Man_Of_Steel_main_picture.png");
    movie_8->setExtraPicture1("Man_Of_Steel_extra_picture_1.png");
    movie_8->setExtraPicture2("Man_Of_Steel_extra_picture_2.png");
    movie_8->setExtraPicture3("Man_Of_Steel_extra_picture_3.png");

    Movie* movie_9 = new Movie();

    movie_9->setTitle("Run Fatboy Run");

    movie_9->setYear(2007);

    movie_9->addActor("Simon Pegg");
    movie_9->addActor("Thawndiwe Newton");
    movie_9->addActor("Hank Azaria");

    movie_9->addDirector("David Schwimmer");

    movie_9->addGenre("Comedy");
    movie_9->addGenre("Romance");
    movie_9->addGenre("Sports");

    movie_9->setSummary("Five years after jilting his pregnant fiancee on their wedding day, out-of-shape Dennis decides to@run a marathon to win her back.");

    movie_9->setMainPicture("Fatboy_main_picture.png");
    movie_9->setExtraPicture1("Fatboy_extra_picture_1.png");
    movie_9->setExtraPicture2("Fatboy_extra_picture_2.png");
    movie_9->setExtraPicture3("Fatboy_extra_picture_3.png");

    Movie* movie_10 = new Movie();

    movie_10->setTitle("Oppenheimer");

    movie_10->setYear(2023);

    movie_10->addActor("Christopher Nolan");
    movie_10->addActor("Kai Bird");
    movie_10->addActor("Martin Sherwin");

    movie_10->addDirector("Christopher Nolan");

    movie_10->addGenre("Historical");
    movie_10->addGenre("Drama");

    movie_10->setSummary("The story of American scientist J. Robert Oppenheimer and his role in the development of the@atomic bomb.");

    movie_10->setMainPicture("Oppenheimer_main_picture.png");
    movie_10->setExtraPicture1("Oppenheimer_extra_picture_1.png");
    movie_10->setExtraPicture2("Oppenheimer_extra_picture_2.png");

//----------------------------------Add to vector for thumbnail---------------------------------
    view_results.push_back(movie_1);
    view_results.push_back(movie_2);
    view_results.push_back(movie_3);
    view_results.push_back(movie_4);
    view_results.push_back(movie_5);
    view_results.push_back(movie_6);
    view_results.push_back(movie_7);
    view_results.push_back(movie_8);
    view_results.push_back(movie_9);
    view_results.push_back(movie_10);
//----------------------------------------------------------------------------------------------

//--------------------------------Add to vector for movies in general---------------------------
    all_movies.push_back(movie_1);
    all_movies.push_back(movie_2);
    all_movies.push_back(movie_3);
    all_movies.push_back(movie_4);
    all_movies.push_back(movie_5);
    all_movies.push_back(movie_6);
    all_movies.push_back(movie_7);
    all_movies.push_back(movie_8);
    all_movies.push_back(movie_9);
    all_movies.push_back(movie_10);
//-----------------------------------------------------------------------------------------------

    bool movies_ready;

    for(auto m: all_movies)
    {
        std::cout << "Movie " << m->getTitle() << " added to database!" << endl;
    }

    printDebugMessage("Database set ", movies_ready);

}

void Movie_Browser::setMovieForThumbnail(Thumbnail& thumbnail, Movie& movie)
{
    thumbnail.setSelectedMovie(&movie);
    //Note: We use a method by reference to set one specific movie from the database to the thumbnail of movies
}

void Movie_Browser::FindMoviesFromFilters(vector<Movie*>& results)
{
    vector<Movie*> valid_movies; //vector to save all valid movies(if they exist)

    if (!(title_textfield->hasCharacters()) &&
        !(director_textfield->hasCharacters()) &&
        !genre_selected() &&
        !(from_textfield->hasCharacters()) &&
        !(to_textfield->hasCharacters()) &&
        !(actor_textfield->hasCharacters())) //if we haven't filled any filters
    {
        std::cout << "No filter input to begin searching!" << std::endl;
        return; //return without changing the view_results
    }
    else //if we have filled at least one filter for searching
    {
        for (auto movie : all_movies) //for each movie einside database
        {
//-------------------------------------Booleans to check reject invalid movies----------------------------
            bool invalid_title = false;
            bool invalid_actor = false;
            bool invalid_director = false;
            bool invalid_release_year = false;
            bool invalid_genres = false;
//--------------------------------------------------------------------------------------------------------

//---------------------------------Inputs to be checked for each movie----------------------
            std::string written_title = "";
            std::string written_one_actor_name = "";
            std::string written_one_director_name = "";
            int written_min_year = 0;
            int written_max_year = 0;
            vector<std::string> selected_genres;
//------------------------------------------------------------------------------------------

//-----------------------------------------------Title--------------------------------------------------------------------
            if (title_textfield->hasCharacters()) //if we have filled the title textfield
            {
                written_title = title_textfield->getText();
                toLowerCase(written_title);
                std::string movie_title = movie->getTitle();
                toLowerCase(movie_title);

                if(movie_title.find(written_title) != std::string::npos)
                {
                    std::cout << "Movie " << movie->getTitle() << " fits title filter " << written_title << std::endl;
                }
                else
                {
                    invalid_title = true;
                }
            }
//-------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------Actors--------------------------------------------------------------------
            if(actor_textfield->hasCharacters())
            {
                written_one_actor_name = actor_textfield->getText();
                toLowerCase(written_one_actor_name);
                vector<std::string> movie_cast = movie->getCast();

                bool at_least_one_actor = false;

                for (auto actor : movie_cast)
                {
                    toLowerCase(actor);

                    if (actor.find(written_one_actor_name) != std::string::npos)
                    {
                        at_least_one_actor = true;
                        std::cout << "Movie " << movie->getTitle() << " has actor " << actor << std::endl;
                    }
                }

                invalid_actor = !(at_least_one_actor);
            }
//-------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------Directors--------------------------------------------------------------------
            if(director_textfield->hasCharacters())
            {
                written_one_director_name = director_textfield->getText();
                toLowerCase(written_one_director_name);
                vector<std::string> movie_directors = movie->getDirectors();
                bool at_least_one_director = false;
                for (auto director : movie_directors)
                {
                    toLowerCase(director);
                    if(director.find(written_one_director_name) != std::string::npos)
                    {
                        at_least_one_director = true;
                        std::cout << "Movie " << movie->getTitle() << " has director " << director << std::endl;
                    }
                }
              
                invalid_director = !(at_least_one_director);
            }
//-------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------Release Year--------------------------------------------------------------------
            if(from_textfield->hasCharacters())
            {
                if (from_textfield->getYearDigits() >= min_year)
                {
                    written_min_year = from_textfield->getYearDigits();
                }
                else
                {
                    written_min_year = min_year;
                }
            }
            else
            {
                written_min_year = min_year;
            }

            if(to_textfield->hasCharacters())
            {
                if (to_textfield->getYearDigits() <= max_year)
                {
                    written_max_year = to_textfield->getYearDigits();
                }
                else
                {
                    written_max_year = max_year;
                }
            }
            else
            {
                written_max_year = max_year;
            }

            if (written_max_year > 0 && written_min_year > 0)
            {
                std::cout << "Movie " << movie->getTitle() << " release year: " << movie->getYear() <<std::endl;

                if(movie->getYear() > written_max_year)
                {
                    invalid_release_year = true;
                }

                if(movie->getYear() < written_min_year)
                {
                    invalid_release_year = true;
                }
            }
//-------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------Genres--------------------------------------------------------------------
            if (genre_selected())
            {
                for (int j = 0; j < 14; j++)
                {
                    if (genre_choices[j]->getSelection())
                    {
                        selected_genres.push_back(genre_choices[j]->getContent());
                    }
                }
                sort(selected_genres.begin(), selected_genres.end());
                vector<std::string> movie_genres = movie->getGenre();
                std::sort(movie_genres.begin(), movie_genres.end());
                bool includes_genres = std::includes(movie_genres.begin(), movie_genres.end(), selected_genres.begin(), selected_genres.end());
                
                if(!(includes_genres))
                {
                    invalid_genres = true;
                }
            }
//-------------------------------------------------------------------------------------------------------------------------
            if (invalid_title == false && 
                invalid_actor == false && 
                invalid_director == false && 
                invalid_release_year == false && 
                invalid_genres == false) //if the current movie inside for is valid
            {
                valid_movies.push_back(movie); //we add it to the valid movies vector
            }
        }
    }
    if(valid_movies.size() > 0) //if we have found at least one movie from search filters
    {
        results = valid_movies; //we replace the movies shown in thumbnail with those fitting the filters

        std::cout << "Movies found from filters: "<< results.size() << std::endl;

        for(int i = 0; i < results.size(); i++)
        {
            std::cout << i + 1 << ". " << results[i]->getTitle() << " valid!" << std::endl;
        }
    }
    else
    {
        std::cout << "No movies found from filters" << std::endl;
    }
}

Movie_Browser * Movie_Browser::getInstance()
{
    if(!m_instance)
        m_instance = new Movie_Browser();
    return m_instance;
  
}

Movie_Browser::Movie_Browser(){}

Movie_Browser::~Movie_Browser()
{
    if (login_username_bubble)
    {
        login_username_bubble->~TextBubble();
    }

    if (login_password_bubble)
    {
        login_password_bubble->~TextBubble();
    }

    if (username_textfield)
    {
        username_textfield->~TextField();
    }

    if (password_textfield)
    {
        password_textfield->~PasswordTextfield();
    }

    if (procceed_button)
    {
        procceed_button->~Button();
    }

    if (music_button)
    {
        music_button->~MusicButton();
    }

    if (refresh_button)
    {
        refresh_button->~RefreshButton();
    }

    if(search_button)
    {
        search_button->~Button();
    }

    if(clear_filters_button)
    {
        clear_filters_button->~Button();
    }
 

    if(director_textfield)
    {
        director_textfield->~TextField();
    }

    if(actor_textfield)
    {
        actor_textfield->~TextField();
    }

    if(title_textfield)
    {
        title_textfield->~TextField();
    }

    if(from_textfield)
    {
        from_textfield->~NumberOnlyTextfield();
    }

    if(to_textfield)
    {
        to_textfield->~NumberOnlyTextfield();
    }

    if(genre_bubble)
    {
        genre_bubble->~TextBubble();
    }

    if(director_bubble)
    {
        director_bubble->~TextBubble();
    }

    if(to_bubble)
    {
        to_bubble->~TextBubble();
    }

    if(from_bubble)
    {
        from_bubble->~TextBubble();
    }

    if(actor_bubble)
    {
        actor_bubble->~TextBubble();
    }

    if(release_year_bubble)
    {
        release_year_bubble->~TextBubble();
    }

    if(title_bubble)
    {
        title_bubble->~TextBubble();
    }
 
 

    if(display_window)
    {
        display_window->~Thumbnail();
    }
}

Movie_Browser * Movie_Browser::m_instance = nullptr;
