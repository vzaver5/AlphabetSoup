// AlphabetSoup.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <ctime>

using namespace std;

//Function prototypes
vector<string> populate(int numChars, sf::RenderWindow &window);

int main()
{
	int numChars = 5;			//Number of characters in the soup. Initially 5.
	vector<string> allMight;	//Vecor that holds all contents on the screen
	random_device rd;
	int round = 1;				//Round number to decide high score
	int seconds = 30;			//Base time you get is 60 seconds
	time_t start;				//Start time 
	time_t end;					//End time. Needed to find time elapsed.
	int score = 0;				//Score
	char bonus;					//Char that will be worth 200 points

	cout << "Chose a character to count as 2x the points. (A-Z or a-z)" << endl;
	cin >> bonus;
	bonus = toupper(bonus);
	string bonusString(1, bonus);					//User input as an Upper Case String

	sf::RenderWindow window(sf::VideoMode(400, 400), "Alphabet Soup");

	//Create the initial soup
	//5 character and will grow when the soup is finished
	allMight = populate(numChars, window);
	cout << "ROUND " << round << " !" << endl;
	//Debugging stuff
	//cout << "Original Screen: ";
	//for (string i : allMight) {
	//	cout << i << ", ";
	//}

	

	time(&start);			//Beginning time

	//Debugging stuff
	cout << "Start time is: " << start << endl;

	while (window.isOpen()){
		//Code to make the window close
		sf::Event event;


		//Debugging stuff
		//cout << "Checking the time" << endl;
		time(&end);				//Constantly check the end time
		//Debugging stuff
		//cout << "End time is: " << end << endl;

		//If the difference from start to finish is equal to or greater than amount of time given then end game
		if ((int)difftime(end, start) >= seconds) {
			cout << "GAME OVER" << endl;
			cout << "Final Score: " << score << endl;
			system("pause");
			break;
		}
		
		while (window.pollEvent(event))
		{
			//Debugging stuff
			//cout << "Time diff: " << difftime(end, start) << endl;
			cout << "Time remaining: " << seconds - difftime(end, start) << endl;
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode > 96 && event.text.unicode < 123) {
					char keyPress = event.text.unicode;
					keyPress = toupper(keyPress);				//Convert to uppercase
					string input(1, keyPress);					//User input as an Upper Case String
					
					//Debugging stuff
					//cout << "You pressed:" << input << endl;	
					//for (string p : allMight) {
					//	cout << p << endl;
					//}

					//Delete the sprite that they chose
					int position = -1;
					for (string i : allMight) {				//Traverse through the vector
						position++;
						if (i == input) {					//Check if vector contains the input user chose on keyboard
							allMight.erase(allMight.begin() + position);	//Delete the letter from the vector
							
							//Update the score for hitting the correct char
							if (bonusString == input) {
								score += 200;
							}
							else {
								score += 100;
							}
							

							window.clear();									//Clear screen

							//Redraw the screen to have all but deleted char
							for (string n : allMight) {
								sf::Texture texture;
								texture.loadFromFile("Textures/" + n + ".png");		//Load up the textuer
								
								//Set the Positions
								int spriteX;	//Sprite's X coord
								int spriteY;	//Sprite's Y coord
								spriteX = rd() % 390;
								spriteY = rd() % 390;

								//Create the sprite taking position and texture
								sf::Sprite sprite;
								sprite.setPosition(spriteX, spriteY);		//Set position of the sprite
								sprite.setTexture(texture);			//Apply texture to sprite
								//Draw sprite
								window.draw(sprite);
							}
							//Show the screen
							window.display();
							break;
						}
						//If they input a character that's not on the screen deduct their time
						if (position == (allMight.size()-1)) {
							if (input != i) {
								//Lose time
								seconds -= 3;		//Lose 3 seconds from total time
							}
						}
					}
					//Once the soup is empty we want to restart
					if (allMight.size() == 0) {
						round++;
						cout << "ROUND " << round << " !"<< endl;
						numChars += 5;
						seconds += 5;
						cout << "Current score: " << score << endl;
						allMight = populate(numChars, window);
						
					}
				}
			}

		}
	}
	return 0;
}

//Purpose: Create new sprites and display them on the screen
//Return: Returns a vector<string> that is all of the sprites currently on the screen
vector<string> populate(int numChars, sf::RenderWindow &window) {
	random_device rd;		//RNG 
	string sprites[26] = { "A" ,"B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
	sf::Texture spriteTexture;		//Load picture into here
	sf::Sprite target;				//Load texture into here
	vector<string> allMight;					//Vector that will contain all chars on the screen

	for (int i = 0; i < numChars; i++) {
		//Choose sprite randomly
		int spriteNum = rd() % 26;					//Number that will retrieve coresponding value from sprites[]
		string filename = sprites[spriteNum];		//File that we are accessing

		//Load picture to sprite
		spriteTexture.loadFromFile("Textures/" + filename + ".png");

		//Debuggstuff
		//cout << spriteNum<< endl;

		//Load in at random positions
		int spriteX;	//Sprite's X coord
		int spriteY;	//Sprite's Y coord
		spriteX = rd() % 390;
		spriteY = rd() % 390;
		target.setPosition(spriteX, spriteY);		//Set position of the sprite
		target.setTexture(spriteTexture);			//Apply texture to sprite

		
		allMight.push_back(filename);				//Add to a almighty vector

		//Draw target
		window.draw(target);
	}
	//Display the drawn
	window.display();
	return allMight;
}