#pragma once

#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:
    Ball(const Point& center, const Velocity& velocity, const Color& color, double radius, bool isCollidable);
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool isCollidable() const;

private:
    Point m_center;
    Velocity m_velocity;
    Color m_color;
    const double m_radius;
    const double m_mass;
    const double m_isCollidable;
};
