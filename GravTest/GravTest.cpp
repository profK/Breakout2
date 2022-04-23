// GravTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFPhysics.h>
#include <chrono>
using namespace std;
using namespace std::chrono;
using namespace sfp;
using namespace sf;
int main()
{
	World world(Vector2f(0, 10));
	PhysicsCircle circle;
	circle.setRadius(50);
	circle.setCenter(Vector2f(100, 100));
	world.AddPhysicsBody(circle);
	PhysicsRectangle fallingRect(Vector2f(20, 60), Vector2f(40, 120));
	world.AddPhysicsBody(fallingRect);
	//world.AddPhysicsObject(
	//	DynamicPhysicsObject(AABB(Vector2f(20, 20), Vector2f(40, 40))));
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 50));
	floor.setCenter(Vector2f(400, 575));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);
	RenderWindow window(VideoMode(800, 600), "Test Window");
	system_clock::time_point last = system_clock::now();
	while (!Keyboard::isKeyPressed(Keyboard::Space)) {
		window.clear(Color::Black);
		system_clock::time_point current = system_clock::now();
		unsigned int deltaMs =
			std::chrono::duration_cast<std::chrono::milliseconds>(current - last).count();
		if (deltaMs == 0) {
			continue;
		}
		world.UpdatePhysics(deltaMs);
		last = current;
		world.VisualizeAllBounds(window);
		//window.draw(circle);
		//window.draw(fallingRect);
		//window.draw(floor);
		window.display();
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
