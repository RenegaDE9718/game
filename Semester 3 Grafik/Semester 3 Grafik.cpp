// Semester 3 Grafik.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
//

#include "stdafx.h"
#include <windows.h>
#include <vector>
#include <time.h>
#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
using namespace std;


const int windowHeight = GetSystemMetrics(SM_CYSCREEN);
const int windowWidth = 800;

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

	if (v_plat.size() == 0) {

		p.setX(windowWidth / 2 - 50);
		p.setY(windowHeight - 10);
		v_plat.push_back(p);
	}

	if (v_plat.size() < 10) {

		p.setX(rand() % 701);
		p.setY(v_plat.back().getY() - (rand() % 200 + 50));

		v_plat.push_back(p);

	}

	return v_plat;
}

bool collision(vector<platform> v_plat, double xPos, double yPos) {

	double figLinks = xPos - 50;		// Hitbox Ende links
	double figRechts = xPos + 50;		// Hitbox Ende rechts

	for (int i = 0; i < v_plat.size() - 1; i++) {

		double mem = v_plat.at(i).getY();

		if (yPos == mem || yPos > mem && yPos < mem + 10) {		// Kollisionsabfrage auf der yAchse

			double platLinks = v_plat.at(i).getX();

				if ((platLinks < figRechts && figRechts <= platLinks + 100) || (figLinks < platLinks + 100 && figLinks >= platLinks)) {		// Kollisionsabfrage auf der xAchse

					return 1;
				}

		}

	}

	return 0;
	
}



class GameWindow : public Gosu::Window {

public:

bool left;
bool right;
bool jump = 0;

int gravity = 10;
int distance = 0;		// Z�hlvariable f�r die Sprungh�he
int jumpHeight = 300;	// Festgelegte Sprungh�he

double xPos = windowWidth / 2;
double yPos = windowHeight / 2;

vector<platform> v_plat;


	Gosu::Image bild;
	Gosu::Sample beep;
	GameWindow()
		: Window(windowWidth, windowHeight)
		, bild("placeholder.png")
		, beep("Beep.wav")
	{
		set_caption("Gosu Tutorial Game mit Git");
	}

	void update() override {


		left = input().down(Gosu::ButtonName::KB_LEFT);
		right = input().down(Gosu::ButtonName::KB_RIGHT);

		v_plat = createPlatforms(v_plat, windowHeight);

		if (left == 1) {		// Bewegt die Spielfigur nach links
			xPos -= 5;
		}

		if (right == 1) {		// Bewegt die Spielfigur nach rechts
			xPos += 5;
		}

		if (yPos + bild.height() <= windowHeight && jump == 0) { // Schwerkraft, wirkt erst nach erreichen der maximalen Sprungh�he
			yPos += gravity;
		}

		if (collision(v_plat, xPos, yPos) == 1 && jump == 0) { // Sprungvariable setzen
			jump = true;
			beep.play(1, 0.5, 0);
		}

		if (jump == 1 && jumpHeight > distance) {	// Funktion f�r den Sprung der Spielfigur
			yPos -= 10;
			distance += 10;
		}
		else
		{
			jump = false;
			distance = 0;
		}

		if (xPos < 0) {			// Verlassen des Bildschirms nach links und dann wechsel nach rechts
			xPos = windowWidth + xPos;
		}

		if (xPos > windowWidth) {		// Verlassen des Bildschirms nach rechts und dann wechsel nach links
			xPos = xPos - windowWidth;
		}
		
	}

	void draw() override {

		platform p;
		bild.draw_rot(xPos, yPos, 0.0, 0.0, 0.5, 0.0);
		for (int i = 0; i < v_plat.size() - 1; i++) {

			p = v_plat.at(i);

		graphics().draw_quad(p.getX(),p.getY(),Gosu::Color::GREEN,
							p.getX() + p.getWidth(), p.getY(), Gosu::Color::GREEN,
							p.getX(), p.getY() + p.getHeight(), Gosu::Color::GREEN,
							p.getX() + p.getWidth(), p.getY() + p.getHeight(), Gosu::Color::GREEN, 0.0);

		}
		

	}
};


int main()
{
	srand(time(NULL));
	GameWindow window;
	window.show();

}
