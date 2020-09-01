#include "Application.h"


Application::Application(unsigned int w, unsigned int h,
                         const std::wstring & title )
    : m_window { {w, h}, title}
{
    m_entrer_nomFichier = false;
    s = "Niveau_?";
    m_effacer = false;
}

void Application::stop() {
    m_running = false;
}

void Application::run()
{
    m_window.setFramerateLimit(20);
    m_running = true;

    init();
    while (m_running) {  // voir
        process_events();
        loop();
    }
}

void Application::process_events()
{
    if (! m_window.isOpen()) {
        stop();
        return;
    }

    sf::Event event;

    while (m_window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed :
            stop();
            break;
        case sf::Event::KeyPressed :
            key_pressed(event.key);
            break;
        case sf::Event::MouseButtonPressed :
            // bouton = event.mouseButton.button;
            set_mouse_coord(event.mouseButton.x, event.mouseButton.y);
            mouse_button_pressed();
            break;
        case sf::Event::MouseButtonReleased :
            // bouton = event.mouseButton.button;
            set_mouse_coord(event.mouseButton.x, event.mouseButton.y);
            mouse_button_released();
            break;
        case sf::Event::MouseMoved :
            set_mouse_coord(event.mouseMove.x, event.mouseMove.y);
            mouse_moved();
            break;
        case sf::Event::TextEntered:
            if (m_effacer)
            {
                s.pop_back();
                m_effacer = false;
            }
            else if (m_entrer_nomFichier && s.size() < 21)
            {
                if (event.text.unicode < 128 && event.text.unicode > 31) {
                    s.push_back((char)event.text.unicode);
                }
            }
            break;
        default:
            break;
        }
    }
}

/*
 * mémorisation de la position de la souris,
 * avec conversion de coordonnées  pixel -> fenetre
 */
void Application::set_mouse_coord(int x, int y)
{
    auto pos = m_window.mapPixelToCoords( {x, y});
    m_mouse = { pos.x, pos.y };
}

/*
 * utilitaires (fonctions statiques)
 */

float Application::module(const Position & v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

float Application::distance(const Position & p1, const Position & p2 )
{
    return module( p1 - p2 );
}
