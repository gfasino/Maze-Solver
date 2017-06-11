#include "point.h"
#include <iostream>

Point::Point(const int &x_, const int &y_) {
	x = x_;
	y = y_;
}
Point::Point() {
	x = 0;
	y = 0;
}

Point::Point(const Point* obj) {
	x = obj->x;
	y = obj->y;
}

Point::Point(const Point& obj) {
	x = obj.x;
	y = obj.y;
}

int Point::getX() const{
	return x;
}
int Point::getY() const{
	return y;
}

void Point::setX(const int &x_) {
	x = x_;
}
void Point::setY(const int &y_) {
	y = y_;
}

//return quadratic distance for efficency
float Point::getQDistance(const Point& p) const{
	float d1 = (float)(p.getX()-this->x);
	float d2 = (float)(p.getY()-this->y);
	float d = d1*d1+d2*d2;
	return ((d<0) ? -d : d);
}

bool Point::operator==(const Point& right){
	return (this->x == right.getX() &&	this->y == right.getY());
}

bool Point::operator!=(const Point& right){
	return (this->x != right.getX() ||	this->y != right.getY());
}

std::ostream& operator<<(std::ostream& out, const Point& p){
	out<<"X:"<<p.getX()<<" Y:"<<p.getY();
	return out;
}
