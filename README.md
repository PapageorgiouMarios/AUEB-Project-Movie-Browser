# AUEB-Project-Movie-Browser
Custom Movie Browser for movie search using C++ and sgg library

In this year's project, for C++ language course, we were meant to create our own movie browser using only the external library named SGG (link for library's description: https://cgaueb.github.io/sgg/index.html).

This specific browser is called "Blue Eyes Tube"

![Screenshot (1579)](https://user-images.githubusercontent.com/102749207/222513121-62404045-0dc9-4b1f-ba7a-abf664b1cbfb.jpg)

?) How to run the program properly:

At first, after the animated intro, a login screen will pop up asking username and password. The user doesn't have to know any specific credentials. All they have to do is to fill the two templates.

![fotor_2023-3-2_18_59_20](https://user-images.githubusercontent.com/102749207/222513196-d2a6aab1-8cd9-4758-aca8-4fd5385a7d15.jpg)

After typing username and password, we procceed to the browser screen. 

Note: Our movie database includes 10 specific movies (movie_browser.cpp: lines 864-1128) which are shown by default in the beginning

![Screenshot (1582)](https://user-images.githubusercontent.com/102749207/222513233-535ee323-2648-4c83-ab1a-e84fbb6be275.jpg)

Of course, if we wish to search a specific movie, there are some filters, more specifically Title, Actor, Director, Release Year and Genres.

The textfields don't require any strict search patterns such as capital letters ,full title, or all filters filled 
![Screenshot (1585)](https://user-images.githubusercontent.com/102749207/222513278-8e5c71c0-d524-4b55-a1a5-870ee05fc6e1.jpg)

Extra features:
 - Music Button that can be turned ON/OFF
 - Refresh Button to set the browser to its default state (view all 10 movies)
 - Clear Filters Button to erase the content of any textfields and 'unselect' all selected genres
 - Debug print messages shown in .exe file while running the program
 - In util.h file: Method fileExists to see if a specific file exists in project such as .png, mp3, etc.
