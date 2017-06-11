#ifndef POINT_H
#define POINT_H


#include <iostream>

class Point{
	protected:
  	int x;
  	int y;

	public:
		/** \brief constructor with params*/
		Point(const int &x_, const int &y_);
		/** \brief constructor set at (-1,-1)*/
		Point();
		/** \brief copy constructor by pointer */
		Point(const Point* obj);
		/** \brief copy constructor */
		Point(const Point& obj);

		/** \brief x getter*/
		int getX() const;
		/** \brief y getter*/
		int getY() const;

		/** \brief x setter */
		void setX(const int &x_);
		/** \brief y setter */
		void setY(const int &y_);
		/** \brief return quadratic distance from a given Point*/
  	float getQDistance(const Point& p) const;
		/** \brief return true if two point have the same coordinate*/
		bool operator==(const Point& right);
		/** \brief return true if two point have not the same coordinate*/
		bool operator!=(const Point& right);
};

/** \brief stream coordinate x & y */
std::ostream& operator<<(std::ostream& out, const Point& p);

#endif // POINT_H
