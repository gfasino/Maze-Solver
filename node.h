#ifndef NODE_H
#define NODE_H

#include "point.h"
#include "matrix.h"
#include <vector>

class Node{
	protected:
		/** \brief this node's coordinate */
		Point coord;
		/** \brief root pointer, used for pathfinding and deallocation */
		Node* root;
		/** \brief end's coordinate, used by getDistance() */
		Point end;
		/** \brief sons counter, used for deallocation (smart pointer style) */
		int sons = 0;
		/** \brief distructor protected, you have to call remove()*/
		~Node();

	public:
		/** \brief constructor empty node */
		Node();
		/** \brief copy constructor */
		Node(const Node& obj);
		/** \brief constructor with params */
		Node(const Point& coord_, Node* root_, const Point& end_);
		/** \brief delete this node and the root, if possible*/
		void remove();
		/** \brief return node's point coordinate  */
		Point getCoord();
		/** \brief return node's root pointer*/
		Node* getRoot() const;
		/** \brief return Maze's end coordinate*/
		Point getEnd();

		/** \brief set node's point coordinate  */
		void setCoord(const Point &coord_);
		/** \brief set node's root pointer  */
		void setRoot(Node* root_);
		/** \brief set node's end point coordinate  */
		void setEnd(const Point &end_);
		/** \brief return nodes created with the coordinates aviable around him
				\param maze's Matrix
				\return vector of pointer to that node */
		std::vector<Node*> genSons(Matrix &maze);
		/** \brief */
		float getDistance() const;
		/** \brief return true if the nodes have same coordinates and same root*/
		bool operator==(Node& right);
		/** \brief return true if the nodes have not same coordinates or same root*/
		bool operator!=(Node& right);
};

/** \brief streams node's coordinate*/
std::ostream& operator<<(std::ostream& out, Node n);
//TODO
bool operator< (const Node& left, const Node& right);
bool operator> (const Node& left, const Node& right);

#endif
