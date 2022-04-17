#include <SFML/Graphics.hpp>
#ifndef bullet_cpp
#define bullet_cpp
#endif

class Point : public sf::Shape {
public:
    Point() {
        m_vertices.setPrimitiveType(sf::Points);
        m_vertices.resize(4);
        m_vertices[0].position = sf::Vector2f( -0.1 ,  0.1 );
        m_vertices[1].position = sf::Vector2f( -0.1 , -0.1 );
        m_vertices[2].position = sf::Vector2f(  0.1 , -0.1 );
        m_vertices[3].position = sf::Vector2f(  0.1 ,  0.1 );
    }
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(m_vertices, states);
    }

    virtual std::size_t getPointCount() const {
        return 4;
    }

    virtual sf::Vector2f getPoint(std::size_t index) const {
        return sf::Vector2f(0, 0);
    }

    sf::VertexArray m_vertices;
};