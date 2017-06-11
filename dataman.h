#ifndef DATAMAN_H
#define DATAMAN_H

#include <list>
#include <queue>
#include "node.h"

class GenericManager{
protected:
	/** \brief sorting function */
	static bool NodeSort(const Node* lhs, const Node* rhs);
	/** \brief sorting class */
	struct CompareClass : public std::binary_function<Node*, Node*, bool> {
		bool operator()(const Node* lhs, const Node* rhs) const;
	};

	public:
		/** \brief get a node and remove it from datacontainer*/
		virtual Node* get() = 0;
		/** \brief add a collection of Node to datacontainer*/
		virtual void add(std::vector<Node*>& q) = 0;
		/** \brief add a node to datacontainer*/
		virtual void add(Node* q) = 0;
		/** \brief check if datacontainer is empty*/
		virtual bool isNotEmpty() = 0;
		/** \brief destructor*/
		virtual ~GenericManager();
		/** \brief remove all node left in datacontainer*/
		virtual void clearAll();
};

class ListManager : public GenericManager{
	protected:
		std::list<Node*> first_q;
		std::list<Node*> second_q;
		/** \brief method to move all data from another data structure*/
		void changeFrom(GenericManager* obj);

	public:
		/** \brief constructor */
		ListManager();
    /** \brief copy constructor */
		ListManager(ListManager& obj);
		/** \brief copy constructor from other object */
		ListManager(GenericManager* obj);
		/** \brief destructor*/
		virtual ~ListManager();

		/** \brief check if list is empty*/
    virtual bool isNotEmpty();
		/** \brief add a node to list*/
		virtual void add(Node* n);
		/** \brief get node for list */
		virtual Node* get();

		/** \brief add a collection of Node to list */
		virtual void add(std::vector<Node*>& q);
};

class ListManagerHe1 : public ListManager{
	public:
		/** \brief add a collection of Node to list */
		virtual void add(std::vector<Node*>& q);
		/** \brief constructor*/
		ListManagerHe1();
		/** \brief constructor from other object*/
		ListManagerHe1(GenericManager* obj);
		/** \brief destructor*/
		virtual ~ListManagerHe1();
};

class ListManagerHe2 : public ListManager{
	public:
		/** \brief add a collection of Node to list */
		virtual void add(std::vector<Node*>& q);
		/** \brief constructor*/
		ListManagerHe2();
		/** \brief constructor from other object*/
		ListManagerHe2(GenericManager* obj);
		/** \brief destructor*/
		virtual ~ListManagerHe2();
};

class QueueManager : public GenericManager{
	private:
  		std::priority_queue<Node*, std::vector<Node*>, GenericManager::CompareClass> first_q;

	public:
		/** \brief constructor*/
		QueueManager();
		/** \brief copy constructor*/
		QueueManager(QueueManager& obj);
		/** \brief constructor from other object*/
		QueueManager(GenericManager* mn);
		/** \brief destructor*/
    virtual ~QueueManager();

		/** \brief add a collection of Node to queue */
		virtual void add(std::vector<Node*>& q);
		/** \brief add a Node to queue */
		virtual void add(Node* n);
		/** \brief check if queue is not empty */
		virtual bool isNotEmpty();
		/** \brief get node for queue */
		virtual Node* get();
};

#endif
