// Semester 3 Grafik.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

const int Fensterhoehe = 600;
const int Fensterbreite = 800;
bool left;
bool right;
bool jump;
int gravity = 10;
int distance = 0;
int jumpHeight = 300;	// Festgelegte Sprunghöhe
double xPos = Fensterbreite/2;
double yPos = Fensterhoehe/2;


class GameWindow : public Gosu::Window {
public:
	Gosu::Image bild;
	GameWindow()
		: Window(640, 480)
		, bild("placeholder.png")
	{
		set_caption("Gosu Tutorial Game mit Git");
	}

	void update() override {

		left = input().down(Gosu::ButtonName::KB_LEFT);
		right = input().down(Gosu::ButtonName::KB_RIGHT);

		if (left == 1) {
			xPos -= 5;
		}

		if (right == 1) {
			xPos += 5;
		}

		if (yPos + bild.height() <= Fensterhoehe && jump == 0) { // Schwerkraft, wirkt erst nach erreichen der maximalen Sprunghöhe
			yPos += gravity;
		}

		if (yPos + bild.height() == Fensterhoehe) { // Sprungvariable setzen
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
			xPos = Fensterbreite + xPos - bild.width();
		}

		if (xPos + bild.width() > Fensterbreite) {		// Verlassen des Bildschirms nach rechts und dann wechsel nach links
			xPos = Fensterbreite - xPos - bild.width();
		}
	}

	void draw() override {

		bild.draw_rot(xPos, yPos, 0.0, 0.0, 1.0, 1.0

		);

	}
};

int main()
{
GameWindow window;
window.show();

}
