#include <SFML/Graphics.hpp>
#include <windows.h>

// Inform the Nvidia/AMD driver that this SFML application could
// benefit from using the more powerful discrete GPU
extern "C"
{
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
int main(int argc, char* argv[]);
////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {
    return main(__argc, __argv);
}


int main(int argc, char* argv[]) {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            window.clear();
            window.draw(shape);
            window.display();
        }
    }
    return 0;
}
