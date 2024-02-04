#include<iostream>
#include<cmath>

namespace pointUtils {
    struct Point {
        int x {};
        int y {};

        Point();
        Point(const int, const int);
        Point(const Point&);

        ~Point();

        void setPoint(const int, const int);
        void setPoint(const Point&);

        double getDistanceBetween(const Point&);
        double getDistanceBetween(const int, const int); 

        void swapPoints(Point&);

        void printFormatedPoint() const;

        bool arePointsEqual(const Point&) const;
    };

    Point::Point() : x(), y() {};
    Point::Point(const int x, const int y) : x(x), y(y) {};
    Point::Point(const Point& p) : x(p.x), y(p.y) {};

    Point::~Point() {};

    void Point::setPoint(const int x, const int y) {
        this->x = x;
        this->y = y;
    }

    void Point::setPoint(const Point& p) {
        this->x = p.x;
        this->y = p.y;
    }

    double Point::getDistanceBetween(const Point& p) {
        return std::sqrt(std::pow(this->x - p.x, 2) + std::pow(this->y - p.y, 2));
    }
    
    double Point::getDistanceBetween(const int x, const int y) {
        return std::sqrt(std::pow(this->x - x, 2) + std::pow(this->y - y, 2));
    }

    void Point::swapPoints(Point& p) {
        std::swap(this->x, p.x);
        std::swap(this->y, p.y);
    }

    void Point::printFormatedPoint() const {
        std::cout<<"["<<this->x<<", "<<this->y<<"]";
    }

    bool Point::arePointsEqual(const Point& p) const {
        return this->x == p.x && this->y == p.y;
    }

    void inputPoints(Point *p, const std::size_t size) {
        for (std::size_t i = 0; i < size; i++) {
            std::cout<<"Input point "<<i + 1<<": ";
            std::cin>>p[i].x>>p[i].y;
        }
    }

    void sortPointsByX(Point *p, std::size_t size, const bool sortDesc=false) {
        bool didSortHappen {};

        do {
            didSortHappen = false;
            size--;

            for (std::size_t i = 0; i < size; i++) {
                if (sortDesc && p[i].x < p[i+1].x) {
                    p[i].swapPoints(p[i+1]);
                    didSortHappen = true;
                } else if (!sortDesc && p[i].x > p[i+1].x) {
                    p[i].swapPoints(p[i+1]);
                    didSortHappen = true;
                }
            }
        } while(didSortHappen);
    }

    void sortPointsByY(Point *p, std::size_t size, const bool sortDesc=false) {
        bool didSortHappen {};

        do {
            didSortHappen = false;
            size--;

            for (std::size_t i = 0; i < size; i++) {
                if (sortDesc && p[i].y < p[i+1].y) {
                    p[i].swapPoints(p[i+1]);
                    didSortHappen = true;
                } else if (!sortDesc && p[i].y > p[i+1].y) {
                    p[i].swapPoints(p[i+1]);
                    didSortHappen = true;
                }
            }
        } while(didSortHappen);
    }

    void sortPointsByPoint(Point *p, std::size_t size, const Point &middlePoint, const bool sortDesc=false) {
        bool didSortHappen {};

        do {
            didSortHappen = false;
            size--;

            for (std::size_t i = 0; i < size; i++) {
                const double distanceBetween1 {p[i].getDistanceBetween(middlePoint)};
                const double distanceBetween2 {p[i+1].getDistanceBetween(middlePoint)};

                if (sortDesc && distanceBetween1 < distanceBetween2) {
                    p[i].swapPoints(p[i+1]);
                    didSortHappen = true;
                } else if (!sortDesc && distanceBetween1 > distanceBetween2) {
                    p[i].swapPoints(p[i+1]);
                    didSortHappen = true;
                }
            }
        } while(didSortHappen);
    }

    Point* findPoint(Point *p, const std::size_t size, const Point &pointToFind) {
        Point *point {nullptr};

        for (std::size_t i = 0; i < size; i++) {
            if (pointToFind.arePointsEqual(p[i])) {
                point = p + i;
            }
        }

        return point;
    }

    void printPoints(const Point *p, const std::size_t size, const char *tekstZaIspis) {
        std::cout<<tekstZaIspis;

        for (std::size_t i = 0; i < size; i++) {
            p[i].printFormatedPoint();
            std::cout<<'\n';
        }

        std::cout<<std::endl;
    }
}

int main() {
    pointUtils::Point points[10] {
        {5, 4},
        {1, 10},
        {-5, -6},
        {7, -8},
        {1, 1},
        {0, 0},
        {12, -16},
        {18, 24},
        {-69, 1},
        {16, 7}
    };

    pointUtils::Point pointToSortBy(-5, 0);

    auto foundPoint {pointUtils::findPoint(points, std::size(points), pointToSortBy)};

    if (foundPoint) {
        foundPoint->printFormatedPoint();
    } else {
        std::cout<<"Point not found";
    }
    std::cout<<'\n';

    return 0;
}