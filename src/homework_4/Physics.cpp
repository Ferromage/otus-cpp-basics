#include "Physics.hpp"
#include <algorithm>

double dot(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Physics::Physics(double timePerTick) : timePerTick{timePerTick} {}

void Physics::setWorldBox(const Point& topLeft, const Point& bottomRight) {
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
}

void Physics::update(std::vector<Ball>& balls, std::vector<Dust>& dust, const size_t ticks) const {
    for (size_t i = 0; i < ticks; ++i) {
        move(balls, dust);
        collideWithBox(balls);
        collideBalls(balls, dust);
    }
}

void Physics::collideBalls(std::vector<Ball>& balls, std::vector<Dust>& dust) const {
    for (auto a = balls.begin(); a != balls.end(); ++a) {
        for (auto b = std::next(a); b != balls.end(); ++b) {
            if (!a->isCollidable() || !b->isCollidable()) {
                continue;
            }
            
            const double distanceBetweenCenters2 =
                distance2(a->getCenter(), b->getCenter());
            const double collisionDistance = a->getRadius() + b->getRadius();
            const double collisionDistance2 =
                collisionDistance * collisionDistance;

            if (distanceBetweenCenters2 < collisionDistance2) {
                processCollision(*a, *b, distanceBetweenCenters2, dust);
            }
        }
    }
}

void Physics::collideWithBox(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        if (!ball.isCollidable()) {
            continue;
        }

        const Point p = ball.getCenter();
        const double r = ball.getRadius();
        // определяет, находится ли v в диапазоне (lo, hi) (не включая границы)
        auto isOutOfRange = [](double v, double lo, double hi) {
            return v < lo || v > hi;
        };

        if (isOutOfRange(p.x, topLeft.x + r, bottomRight.x - r)) {
            Point vector = ball.getVelocity().vector();
            vector.x = -vector.x;
            ball.setVelocity(vector);
        } else if (isOutOfRange(p.y, topLeft.y + r, bottomRight.y - r)) {
            Point vector = ball.getVelocity().vector();
            vector.y = -vector.y;
            ball.setVelocity(vector);
        }
    }
}

void Physics::move(std::vector<Ball>& balls, std::vector<Dust>& dust) const {
    for (Ball& ball : balls) {
        Point newPos =
            ball.getCenter() + ball.getVelocity().vector() * timePerTick;
        ball.setCenter(newPos);
    }
    for (Dust& item : dust) {
        Point newPos =
            item.getCenter() + item.getVelocity().vector() * timePerTick;
        item.setCenter(newPos);
        item.engine();
    }
}

void Physics::processCollision(Ball& a, Ball& b,
                               double distanceBetweenCenters2, 
                               std::vector<Dust>& dust) const {
    // нормированный вектор столкновения
    const Point normal =
        (b.getCenter() - a.getCenter()) / std::sqrt(distanceBetweenCenters2);

    // получаем скорость в векторном виде
    const Point aV = a.getVelocity().vector();
    const Point bV = b.getVelocity().vector();

    // коэффициент p учитывает скорость обоих мячей
    const double p =
        2 * (dot(aV, normal) - dot(bV, normal)) / (a.getMass() + b.getMass());

    // задаем новые скорости мячей после столкновения
    a.setVelocity(Velocity(aV - normal * p * a.getMass()));
    b.setVelocity(Velocity(bV + normal * p * b.getMass()));
    
    generateDust(dust, a, b);
}

void Physics::generateDust(std::vector<Dust>& dust, const Ball& ball1, const Ball& ball2) const {
    static constexpr double cos45 = std::cos(45);
    static constexpr double sin45 = std::sin(45);
    static const Point directions[] = { {1, 0}, 
                                        {cos45, sin45}, 
                                        {0, 1}, 
                                        {-cos45, sin45}, 
                                        {-1, 0}, 
                                        {-cos45, -sin45}, 
                                        {0, -1}, 
                                        {cos45, -sin45} };

    const auto max1 = std::max(std::abs(ball1.getVelocity().vector().x), std::abs(ball1.getVelocity().vector().y));
    const auto max2 = std::max(std::abs(ball2.getVelocity().vector().x), std::abs(ball2.getVelocity().vector().y));
    const double speed = std::max(max1, max2) * 3;

    const auto& r1 = ball1.getRadius();
    const auto& r2 = ball2.getRadius();    
    const double x = (r2 * ball1.getCenter().x + r1 * ball2.getCenter().x) / (r1 + r2);
    const double y = (r2 * ball1.getCenter().y + r1 * ball2.getCenter().y) / (r1 + r2);

    auto it = dust.begin();
    for (size_t i = 0; i < sizeof(directions) / sizeof(directions[0]); i++) {
        it = std::find_if(it, dust.end(), [](const auto& item) {return !item.isStarted();});
        if (it != dust.end()) {
            it->setCenter(Point(x, y));
            it->setVelocity(Velocity(directions[i] * speed));
            it->start();
        }
    }
}