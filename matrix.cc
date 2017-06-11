#include "matrix.h"

Matrix::Matrix() {
	create(0,0);
}

Matrix::Matrix(const int w_, const int h_) {
	create(w_, h_);
}

Matrix::Matrix(const Matrix& obj) {
	mat = obj.mat;
	width = obj.width;
	height = obj.height;
}

Matrix::~Matrix() {
}

bool Matrix::isInBound(const Point &p) const{
	return (p.getX()>0 && p.getY()>0 && p.getX()<this->height && p.getY()<this->width);
}

bool Matrix::isInBound(const int x, const int y) const{
	return (x>0 && y>0 && x<this->height && y<this->width);
}

Point Matrix::find(const int& val) const{
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
			if(mat[i][j] == val)
				return Point(i,j);
	return Point(-1,-1);
}

int Matrix::suitable(const Point& p) const{
	if(isInBound(p)){
		if(mat[p.getX()][p.getY()] == 0 ||
			mat[p.getX()][p.getY()] == 2 ||
			mat[p.getX()][p.getY()] == 3)
			return 1;
	}
	return 0;
}

Point Matrix::findStart() const{
	return find(2);
}

Point Matrix::findEnd() const{
	return find(3);
}

//TODO doesn not clear stuff in the previous row expanded
void Matrix::create(const int w_, const int h_) {
	width = w_;
	height = h_;
	mat.resize(height, std::vector<int>( width , 0));
}

int Matrix::get(const Point& p) const {
	return mat[p.getX()][p.getY()];
}

int Matrix::get(const int& x, const int& y) const {
	return mat[x][y];
}

int Matrix::getWidth() const{
	return width;
}

int Matrix::getHeight() const{
	return height;
}

void Matrix::set(const Point& p, const int& val) {
	if(isInBound(p))
		mat[p.getX()][p.getY()] = val;
}

void Matrix::set(const int& x, const int& y, const int& val) {
	if(isInBound(x,y))
		mat[x][y] = val;
}


int Matrix::getLeft(Point p) const{
	p.setY(p.getY()-1);
	return suitable(p);
}

int Matrix::getRight(Point p) const{
	p.setY(p.getY()+1);
	return suitable(p);
}

int Matrix::getTop(Point p) const{
	p.setX(p.getX()-1);
	return suitable(p);
}
int Matrix::getBottom(Point p) const{
	p.setX(p.getX()+1);
	return suitable(p);
}

Point Matrix::onLeft(const Point& p, const int& val) {
	Point np(p);
	np.setY(np.getY()-1);
	if(isInBound(np)){
		set(np, val);
		return np;
	}
	return Point(0,0);
}

Point Matrix::onRight(const Point& p, const int& val) {
	Point np(p);
	np.setY(np.getY()+1);
	if(isInBound(np)){
		set(np, val);
		return np;
	}
	return Point(0,0);
}

Point Matrix::onTop(const Point& p, const int& val) {
	Point np(p);
	np.setX(np.getX()-1);
	if(isInBound(np)){
		set(np, val);
		return np;
	}
	return Point(0,0);
}

Point Matrix::onBottom(const Point& p, const int& val) {
	Point np(p);
	np.setX(np.getX()+1);
	if(isInBound(np)){
		set(np, val);
		return np;
	}
	return Point(0,0);
}

std::ostream& operator<<(std::ostream& out, const Matrix& mat){
	for(int i=0; i<mat.getHeight(); i++){
		for(int j=0; j<mat.getWidth() ;j++)
			out<<mat.get(i,j);
		out<<std::endl;
		}
	return out;
}
