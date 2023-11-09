#include "Dust.h"
#include "Color.hpp"

namespace {
    constexpr size_t lifeDuration = 200; //int ticks
    constexpr double defaultRadius = 15.0;
    const Color activeColor{1.0, 0.0, 0.0};
}

Dust::Dust() : m_isEnabled(false), m_lifeCnt(0) {

}

void Dust::draw(Painter& painter) const {
    const double radius = m_isEnabled ? defaultRadius : 0.0;
    painter.draw(m_center, radius, activeColor);
}

void Dust::setVelocity(const Velocity& velocity) {
    m_velocity = velocity;
}

Velocity Dust::getVelocity() const {
    return m_velocity;
}

void Dust::setCenter(const Point& center) {    
    m_center = center;    
}

Point Dust::getCenter() const {
    return m_center;
}

void Dust::start() {
    if (!m_isEnabled) {
        m_isEnabled = true;
        m_lifeCnt = lifeDuration;
    }
}

bool Dust::isStarted() const {
    return m_isEnabled;
}

void Dust::engine() {
    if (m_isEnabled) {
        if (--m_lifeCnt == 0) {
            m_isEnabled = false;
        } 
    }
}