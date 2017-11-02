// Semester 3 Grafik.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <windows.h>
#include <vector>
#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>


const int windowHeight = GetSystemMetrics(SM_CYSCREEN);
const int windowWidth = 800;

bool left;
bool right;
bool jump = 0;

int gravity = 10;
int distance = 0;		// Zählvariable für die Sprunghöhe
int jumpHeight = 300;	// Festgelegte Sprunghöhe
double xPos = windowWidth/2;
double yPos = windowHeight/2;




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



class GameWindow : public Gosu::Window {

public:

	Gosu::Image bild;
	GameWindow()
		: Window(windowWidth, windowHeight)
		, bild("placeholder.png")
	{
		set_caption("Gosu Tutorial Game mit Git");
	}

	void update() override {

		left = input().down(Gosu::ButtonName::KB_LEFT);
		right = input().down(Gosu::ButtonName::KB_RIGHT);

		if (left == 1) {		// Bewegt die Spielfigur nach links
			xPos -= 5;
		}

		if (right == 1) {		// Bewegt die Spielfigur nach rechts
			xPos += 5;
		}

		if (yPos + bild.height() <= windowHeight && jump == 0) { // Schwerkraft, wirkt erst nach erreichen der maximalen Sprunghöhe
			yPos += gravity;
		}

		if (yPos + bild.height() == windowHeight) { // Sprungvariable setzen
			jump = true;
		}

		if (jump == 1 && jumpHeight > distance) {	// Funktion für den Sprung der Spielfigur
			yPos -= 10;
			distance += 10;
		}
		else
		{
			jump = false;
			distance = 0;
		}

		if (xPos < 0) {			// Verlassen des Bildschirms nach links und dann wechsel nach rechts
			xPos = windowWidth - (bild.width() / 2);
		}

		if (xPos + bild.width() > windowWidth) {		// Verlassen des Bildschirms nach rechts und dann wechsel nach links
			xPos = windowWidth - xPos - bild.width();
		}

		
	}

	void draw() override {

		platform p;
		p.setX(100);
		p.setY(100);
		bild.draw_rot(xPos, yPos, 0.0, 0.0, 0.5, 0.0);
		graphics().draw_quad(p.getX(),p.getY(),Gosu::Color::GREEN,
							p.getX() + p.getWidth(), p.getY(), Gosu::Color::GREEN,
							p.getX(), p.getY() + p.getHeight(), Gosu::Color::GREEN,
							p.getX() + p.getWidth(), p.getY() + p.getHeight(), Gosu::Color::GREEN, 0.0);
		

	}
};


int main()
{
	GameWindow window;
	window.show();

}
