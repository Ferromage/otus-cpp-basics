#pragma once
#include "Point.hpp"
#include "Painter.hpp"
#include "Velocity.hpp"

class Dust {
public:
    Dust();
    void draw(Painter& painter) const;
    
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;

    void setCenter(const Point& center);
    Point getCenter() const;

    bool isStarted() const;
    void engine();
    void start();

private:
    Point m_center;
    Velocity m_velocity;
    bool m_isEnabled;
    size_t m_lifeCnt;
};