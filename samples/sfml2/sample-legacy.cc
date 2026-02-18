#define GLLD_IMPLEMENTATION
#include "./../../glld.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/VideoMode.hpp>


int main(void) {
    sf::Window  window(sf::VideoMode( { 800, 600 } ), "glld.h - SFML sample", sf::Style::Titlebar | sf::Style::Close);
    if (!window.setActive()) { return (1); }
    if (!glldLoadGL()) { return (1); }

    while (window.isOpen()) {
        window.display();

        sf::Event event = { };
        while (window.pollEvent(event)) {
            switch (event.type) {
                case (sf::Event::Closed): {
                    window.close();
                } break;

                default: { } break;
            }
        }
        
        
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);


        glBegin(GL_QUADS);
            glVertex2f(-0.5,-0.5);
            glVertex2f(-0.5, 0.5);
            glVertex2f( 0.5, 0.5);
            glVertex2f( 0.5,-0.5);
        glEnd();
    }
    
    if (!glldUnloadGL()) { return (1); }
    
    return (0);
}
