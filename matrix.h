#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include "point.h"

class Matrix{
	protected:
		/** \brief matrix */
  	std::vector<std::vector<int> > mat;
		/** Matrix's width */
		int width;
    /** Matrix's height */
		int height;

		/** \brief check if the point is in the Matrix's bound*/
		bool isInBound(const Point &p) const;
		/** \brief check if the coordinates are in the Matrix's bound*/
		bool isInBound(const int x, const int y) const;
		/** \brief return the coordinate of the firs occurrency of a given value*/
		Point find(const int& val) const;
		/** \brief check if a point is in bound and is not wall */
		int suitable(const Point& p) const;

  public:
		/** constructor (size 0,0)*/
		Matrix();
		/** constructor of given size*/
		Matrix(const int w_, const int h_);
  	/** copy constructor */
		Matrix(const Matrix& obj);
  	/** destructor */
		~Matrix();

		/** \brief find start point */
		Point findStart() const;
		/** \brief find end point */
		Point findEnd() const;
		/** \brief create a new matrix of a given size */
		void create(const int w_, const int h_);

  	/** \brief get the value of a Matrix's cell*/
		int get(const Point& p) const;
  	/** \brief get the value of a Matrix's cell*/
		int get(const int& x, const int& y) const;

		/** \brief return Matrix's width*/
		int getWidth() const;
		/** \brief return Matrix's height*/
		int getHeight() const;

		/** \brief set the value of a Matrix's cell*/
		void set(const Point& p, const int& val);
		/** \brief set the value of a Matrix's cell*/
		void set(const int& x, const int& y, const int& val);

		/** \brief get the value of the cell on the Left */
		int getLeft(Point p) const;
  	/** \brief get the value of the cell on the Right */
		int getRight(Point p) const;
  	/** \brief get the value of the cell on the Top */
		int getTop(Point p) const;
  	/** \brief get the value of the cell on the Bottom */
		int getBottom(Point p) const;

		/** \brief get the coordinate's of the cell on the Left, set the cell with a given value*/
		Point onLeft(const Point& p, const int& val);
  	/** \brief get the coordinate's of the cell on the Right, set the cell with a given value*/
		Point onRight(const Point& p, const int& val);
  	/** \brief get the coordinate's of the cell on the Top, set the cell with a given value*/
		Point onTop(const Point& p, const int& val);
  	/** \brief get the coordinate's of the cell on the Bottom, set the cell with a given value*/
		Point onBottom(const Point& p, const int& val);

};

/** \brief stream the matrix */
std::ostream& operator<<(std::ostream& out, const Matrix& mat);

#endif
