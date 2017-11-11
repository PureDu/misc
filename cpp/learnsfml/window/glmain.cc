#include <sfml/OpenGL.hpp>
#include <SFML/Window.hpp>



int main() {
    sf::Window Window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default,
                      sf::ContextSettings(32));
    Window.setVerticalSyncEnabled(true);

    Window.setActive(true);

    bool running = true;
    while (running) {
        sf::Event event;
        while (Window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
            } else if (event.type == sf::Event::Resized) {
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Window.display()
    }

    return 0;
}