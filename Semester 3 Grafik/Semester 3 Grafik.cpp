// Semester 3 Grafik.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <windows.h>
#include <vector>
#include <time.h>
#include <string.h>
#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
using namespace std;


const int windowHeight = 1600;
const int windowWidth = 700;
int score = 0;

class platform {

	double xPlat;
	double yPlat;
	double height = 10;
	double width = 100;

public:

	void setX(double x) {
		xPlat = x;
	}

	double getX() {
		return xPlat;
	}

	void setY(double y) {
		yPlat = y;
	}

	double getY() {
		return yPlat;
	}

	double getHeight() {
		return height;
	}

	double getWidth() {
		return width;
	}

};

vector<platform> createPlatforms(vector<platform> v_plat, int windowHeight) {
	platform p;

	if (v_plat.size() == 0) {		// Erzeugen der ersten Platform

		p.setX(windowWidth / 2 - 50);
		p.setY(windowHeight - 10);
		v_plat.push_back(p);
	}

	if (v_plat.size() < windowHeight / 50) {		// Platform Vector auffüllen

		p.setX(rand() % (windowWidth - 99));
		p.setY((v_plat.back().getY() - (rand() % 200 + 50)));

		v_plat.push_back(p);


	}

	if (v_plat.front().getY() > windowHeight) {		// löschen der Platformen außerhalb des Bildschirms

		for (int i = 0; i < v_plat.size() - 2; i++)
		{
			v_plat.at(i) = v_plat.at(i + 1);
		}

		v_plat.pop_back();
		v_plat.pop_back();
	}

	return v_plat;
}

bool collision(vector<platform> v_plat, double xPos, double yPos) {

	double figLinks = xPos - 25;		// Hitbox Ende links
	double figRechts = xPos + 25;		// Hitbox Ende rechts

	for (int i = 0; i < v_plat.size() - 1; i++) {

		double mem = v_plat.at(i).getY();

		if (yPos + 90 == mem || yPos + 90 > mem && yPos + 90 < mem + 10) {		// Kollisionsabfrage auf der yAchse

			double platLinks = v_plat.at(i).getX();

			if ((platLinks < figRechts && figRechts <= platLinks + 100) || (figLinks < platLinks + 100 && figLinks >= platLinks)) {		// Kollisionsabfrage auf der xAchse

				return 1;
			}
		}
	}

	return 0;
}

vector<platform>moveScreen(vector<platform> v_plat, int speed) {

	for (int i = 0; i < v_plat.size() - 1; i++)
	{
		v_plat.at(i).setY((v_plat.at(i).getY() + speed));
	}

	score += 5;
	return v_plat;

}

class GameWindow : public Gosu::Window {

public:

	bool left;
	bool right;
	bool jump = 0;
	bool gameOver = 0;
	bool dir = 0;
	bool lippe  = 0;

	int speed = 8;				//Geschwindigkeit 
	int gravity = speed;
	int distance = 0;		// Zählvariable für die Sprunghöhe
	int jumpHeight = 300;	// Festgelegte Sprunghöhe
	
	double xPos = windowWidth / 2;
	double yPos = 1200;
	double xLippe = windowWidth;
	double count = 1;
	

	vector<platform> v_plat;


	Gosu::Image bild1;
	Gosu::Image bild2;
	Gosu::Image gameover;
	Gosu::Image easteregg;
	Gosu::Image bild_platform;
	Gosu::Sample Beep;
	Gosu::Font text = 50;

	GameWindow()
		: Window(windowWidth, windowHeight)
		, bild1("R_player.png")
		, bild2("L_player.png")
		, easteregg("lippe.png")
		, gameover("Gameover.png")
		, bild_platform("platform.png")
		, Beep("Beep.wav")
	{
		set_caption("Gosu Tutorial Game mit Git");
	}

	void update() override {

		left = input().down(Gosu::ButtonName::KB_LEFT);
		right = input().down(Gosu::ButtonName::KB_RIGHT);

		v_plat = createPlatforms(v_plat, windowHeight);

		if (yPos < (windowHeight / 2)) {

			v_plat = moveScreen(v_plat, speed);
			yPos += speed;

		}

		if (left == 1 && gameOver == 0) {		// Bewegt die Spielfigur nach links
			xPos -= 7;
			dir = 1;
		}

		if (right == 1 && gameOver == 0) {		// Bewegt die Spielfigur nach rechts
			xPos += 7;
			dir = 0;
		}

		if (yPos + bild1.height() <= windowHeight && jump == 0) { // Schwerkraft, wirkt erst nach erreichen der maximalen Sprunghöhe
			yPos += gravity;
		}

		if ((collision(v_plat, xPos, yPos) == 1 && jump == 0) && gameOver == 0) { // Sprungvariable setzen
			jump = true;
			Beep.play(1, 0.5, 0);
		}

		if (jump == 1 && jumpHeight > distance && gameOver == 0) {	// Funktion für den Sprung der Spielfigur
			yPos -= speed;
			distance += speed;
		}
		else
		{
			jump = false;
			distance = 0;
			
		}

		if (xPos < 0 && gameOver == 0) {			// Verlassen des Bildschirms nach links und dann wechsel nach rechts
			xPos = windowWidth + xPos;
		}

		if (xPos > windowWidth && gameOver == 0) {		// Verlassen des Bildschirms nach rechts und dann wechsel nach links
			xPos = xPos - windowWidth;
		}

		if ((yPos + bild1.height()) > (v_plat.at(0).getY() + 10)) {
			gameOver = 1;
		}

		if ((score / 1000) == count) {
			count++;
			lippe = 1;
		}

		if (lippe == 1 && xLippe >=  0)
		{
			xLippe -= 10;

		}

		if (xLippe == 0) {
			lippe = 0;
			xLippe = windowWidth;
		}			

	}

	void draw() override {

		text.draw("score:", windowWidth - 200, 0, 1.0, 1.0, 1.0, Gosu::Color::WHITE);
		text.draw(to_string(score), windowWidth - 200, 50, 1.0, 1.0, 1.0, Gosu::Color::WHITE);
		
		platform p;

		if (dir == 1) {

			bild2.draw_rot(xPos, yPos, 1.0, 0.0, 0.5, 0.0);
		}
		if (dir == 0) {

			bild1.draw_rot(xPos, yPos, 1.0, 0.0, 0.5, 0.0);
		}

		for (int i = 0; i < v_plat.size() - 1; i++) {

				p = v_plat.at(i);

				bild_platform.draw_rot(p.getX(), p.getY(), 0.0, 0.0, 0.0, 0.0, 1.0, 1.0);

		}

		if(gameOver == 1) {

			gameover.draw_rot(windowWidth / 2, windowHeight / 2, 2.0, 0.0, 0.5, 0.5, 1.0, 1.0);
		}

		if (lippe == 1) {
			easteregg.draw_rot(xLippe, windowHeight, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0);
		}

	}

};


int main()
{
	srand(time(NULL));
	GameWindow window;
	window.show();
}
