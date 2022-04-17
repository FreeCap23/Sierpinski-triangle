#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include "point.cpp"

#define AA_LEVEL 8U
#define MAX_POINTS 10000

sf::Vector2f getRandomPoint(Point triangle[3]) {
    using namespace std;
    // Reference points
    sf::Vector2f refPointRight;
    refPointRight.y = 300;
    refPointRight.x = 500;
    sf::Vector2f refPointLeft;
    refPointLeft.y = 300;
    refPointLeft.x = 300;

    int ya = triangle[0].getPosition().y;
    int yb = triangle[1].getPosition().y;

    // Setup random number generator
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> getRandomY(ya, yb);
    
    // Generate a random Y coordinate
    int yp = getRandomY(rng);

    // Using the generated Y coordinate, calculate a range for the X coordinate
    // So that the random point generated is inside the triangle.
    float xRange[2];
    if (yp < refPointLeft.y) {
        xRange[0] = refPointLeft.x + (refPointLeft.y - yp) / 2;
        xRange[1] = refPointRight.x - (refPointLeft.y - yp) / 2;
    }
    else {
        xRange[0] = refPointLeft.x - (yp - refPointLeft.y) / 2;
        xRange[1] = refPointRight.x + (yp - refPointLeft.y) / 2;
    }

    uniform_int_distribution<mt19937::result_type> getRandomX(xRange[0], xRange[1]);
    int xp = getRandomX(rng);

    return sf::Vector2f(xp, yp);
}

int main(int argc, char const** argv) {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sierpinski triangle", 7U, sf::ContextSettings(0U, 0U, AA_LEVEL));

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile("src/icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Set the font
    sf::Font font;
    if (!font.loadFromFile("src/sansation.ttf")) {
        return EXIT_FAILURE;
    }
    // And add the placeholder text for the framerate
    sf::Text fpsCounter("Placeholder text. If this doesn't change, the app is frozen", font, 16U);
    fpsCounter.setPosition(0,0);
    sf::Clock clock;

    // Point counter
    sf::Text pointCounter("placeholder", font, 16U);
    pointCounter.setPosition(0, 16);

    // TODO: Test other triangle sizes
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dice(0, 2);
    Point lastPoint;
    Point midPoints[MAX_POINTS];
    Point origPoints[3];
    origPoints[0].setPosition(400, 100); // Top
    origPoints[1].setPosition(200, 500); // Bottom left
    origPoints[2].setPosition(600, 500); // Bottom right

    midPoints[0].setPosition(getRandomPoint(origPoints));
    lastPoint =  midPoints[0];
    Point selectedPoint = origPoints[dice(rng)];

    int i = 1;

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Create a point at the midpoint of selectedPoint and lastPoint
        midPoints[i].setPosition(sf::Vector2f((selectedPoint.getPosition().x + lastPoint.getPosition().x) / 2, (selectedPoint.getPosition().y + lastPoint.getPosition().y) / 2));
        lastPoint = midPoints[i];
        selectedPoint = origPoints[dice(rng)];


        // Clear screen
        window.clear();

        // Calculate and show framerate
        float framerate = 1.f / clock.getElapsedTime().asSeconds();
        fpsCounter.setString(sf::String(std::to_string(framerate)));
        clock.restart();
        window.draw(fpsCounter);

        pointCounter.setString(sf::String(std::to_string(i)));
        window.draw(pointCounter);

        window.draw(origPoints[0]);
        window.draw(origPoints[1]);
        window.draw(origPoints[2]);
        
        for (int j = 0; j < i; j++)
            window.draw(midPoints[j]);
        window.draw(lastPoint);

        // Update the window
        window.display();
        if (i != MAX_POINTS - 1)
            i++;
    }

    return EXIT_SUCCESS;
}