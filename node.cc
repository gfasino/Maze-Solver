#include "node.h"

Node::Node() {
	root = nullptr;
}

Node::Node(const Node& obj) {
	coord = Point(obj.coord);
	root = obj.root;
	end = obj.end;
}

Node::Node(const Point &coord_, Node* root_, const Point& end_) {
	coord = Point(coord_);
	root = root_;
	end = Point(end_);
}

Node::~Node() {
}

void Node::remove() {
	sons--;
	if(sons < 1){
		if (root) this->root->remove();
		delete this;
	}
}

Point Node::getCoord() {
	return coord;
}

Node* Node::getRoot() const{
	return root;
}

Point Node::getEnd() {
	return end;
}

void Node::setCoord(const Point &coord_) {
	coord = coord_;
}

void Node::setRoot(Node* root_) {
	root = root_;
}

void Node::setEnd(const Point &end_) {
	end = end_;
}

std::vector<Node*> Node::genSons(Matrix &maze) {
	std::vector<Node*> vnode;

	if(maze.getLeft(this->coord)){
		vnode.push_back(new Node(maze.onLeft(this->coord, 4), this, end));
		this->sons++;
	}
	if(maze.getRight(this->coord)){
		vnode.push_back(new Node(maze.onRight(this->coord, 4), this, end));
		this->sons++;
	}
	if(maze.getTop(this->coord)){
		vnode.push_back(new Node(maze.onTop(this->coord, 4), this, end));
		this->sons++;
	}
	if(maze.getBottom(this->coord)){
		vnode.push_back(new Node(maze.onBottom(this->coord, 4), this, end));
		this->sons++;
	}
	return vnode;
}

float Node::getDistance() const{
	return coord.getQDistance(end);
}

bool Node::operator==(Node& right) {
	return (this->getCoord() == right.getCoord() &&	this->getRoot() == right.getRoot());
}

bool Node::operator!=(Node& right) {
	return (this->getCoord() != right.getCoord() ||	this->getRoot() != right.getRoot());
}

std::ostream& operator<<(std::ostream& out, Node n){
	out<<n.getCoord();
	return out;
}

bool operator> (const Node& left, const Node& right) {
	return left.getDistance() > right.getDistance();
}

bool operator< (const Node& left, const Node& right) {
 return left.getDistance() < right.getDistance();
}
