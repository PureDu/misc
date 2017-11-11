#include <SFML/Window.hpp>
#include <iostream>



int main() {
    sf::Window window(sf::VideoMode(800, 600), "My Window");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
            {
                switch (event.key.code) {
                case sf::Keyboard::A:
                    window.setPosition(sf::Vector2i(10, 50));
                    break;
                case sf::Keyboard::S:
                    window.setSize(sf::Vector2u(640, 480));
                    break;
                case sf::Keyboard::D:
                    window.setTitle("SFML window");
                    break;
                case sf::Keyboard::F:
                {
                    auto size = window.getSize();
                    std::cout << "windth " << size.x
                        << "height " << size.y
                        << std::endl;
                }
                default:
                    break;
                }
            }
            case sf::Event::MouseButtonPressed:
            {
                switch (event.mouseButton.button) {
                case sf::Mouse::Right:
                    std::cout << "Right" << std::endl;
                    break;
                case sf::Mouse::Middle:
                    std::cout << "Middle" << std::endl;
                    break;
                case sf::Mouse::Left:
                    std::cout << "Left" << std::endl;
                    break;
                default:
                    break;
                }
            }
            break;
            case sf::Event::JoystickConnected:
                std::cout << "joystick connected: " 
                          << event.joystickConnect.joystickId 
                          << std::endl;
                break;
            case  sf::Event::JoystickDisconnected:
                std::cout << "joystick disconnected: " 
                          << event.joystickConnect.joystickId 
                          << std::endl;
            default:
                break;
            }
        }
    }
    return 0;
}