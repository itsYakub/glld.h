#define GLLD_IMPLEMENTATION
#include "./../../glld.h"

#include <optional>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <SFML/Window/ContextSettings.hpp>


int main(void) {
    sf::Window window(sf::VideoMode( { 800, 600 } ), "glld.h - SFML sample", sf::Style::Default, sf::State::Windowed);
    if (!window.setActive()) { return (1); }
    if (!glld_load()) { return (1); }

    while (window.isOpen()) {
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);


        glBegin(GL_QUADS);
            glVertex2f(-0.5,-0.5);
            glVertex2f(-0.5, 0.5);
            glVertex2f( 0.5, 0.5);
            glVertex2f( 0.5,-0.5);
        glEnd();
        
        
        window.display();
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) { window.close(); }
        }
    }
    
    if (!glldUnloadGL()) { return (1); }
    
    return (0);
}
