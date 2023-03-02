#include "graphics.h"
#include "util.h"
#include <string>
#include "movie_browser.h"
#include <iostream>

void update(float ms)
{
    Movie_Browser* my_movie_browser = Movie_Browser::getInstance();

    my_movie_browser->update();
}

void draw()
{
    Movie_Browser * my_movie_browser = Movie_Browser::getInstance();

    my_movie_browser->draw();
}

int main(int argc, char ** argv)
{
    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Blue Eyes"); //creates the window of the project. Up to the left the name of the window will be Blue Eyes
    
    std::cout << "Window created successfully" << std::endl;

    Movie_Browser * movie_browser = Movie_Browser::getInstance();
 
    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::startMessageLoop(); //begins the loop of the browser_project. It's like a big while for our movie browser

    Movie_Browser::deleteInstance();

    return 0;
}