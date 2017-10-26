// Semester 3 Grafik.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

const int Fensterbreite = 800;
const int Fensterhoehe = 600;
bool left;
bool right;
bool up;
bool jump;
double rotation = 0.0;
double turnspeed = 2.5;
double xPos = Fensterbreite/2;
double yPos = Fensterhoehe/2;


class GameWindow : public Gosu::Window {
public:
	Gosu::Image bild;
	GameWindow()
		: Window(640, 480)
		, bild("trekt.png")
	{
		set_caption("Gosu Tutorial Game mit Git");
	}

	void update() override {
		left = input().down(Gosu::ButtonName::KB_LEFT);
		right = input().down(Gosu::ButtonName::KB_RIGHT);
		up = input().down(Gosu::ButtonName::KB_UP);
		jump = input().down(Gosu::ButtonName::KB_SPACE);

		if (left == 1) {
			xPos -= 5;
		}
		if (right == 1) {
			xPos += 5;
		}
		if (up == 1) {
			yPos -= 5;
		}

		if (jump == 1) {
			yPos -= 20;
		}

		if (yPos + 280 <= Fensterhoehe) {
			yPos += 10;
		}
	}

	void draw() override {
		bild.draw_rot(xPos, yPos, 0.0,
			0.0, // Rotationswinkel in Grad
			0.5, 0.5, // Position der "Mitte" relativ zu x, y
			0.5, 0.5

		);

	}
};

int main()
{
GameWindow window;
window.show();

}
