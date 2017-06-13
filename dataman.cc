#include "dataman.h"
#include <algorithm>
#include <vector>

//sorting stuff
bool GenericManager::NodeSort(const Node* lhs, const Node* rhs) {
	return (*lhs) > (*rhs);
}

bool GenericManager::CompareClass::operator()(const Node* lhs, const Node* rhs) const {
	return (*lhs) > (*rhs);
}

void GenericManager::clearAll(){
	while(isNotEmpty()){
		Node* n = get();
		if(n) n->remove();
	}
}

//ListManager
void ListManager::changeFrom(GenericManager* obj){
	if(dynamic_cast<QueueManager*>(obj)){
		while(obj->isNotEmpty()){
			this->add(obj->get());
		}
		//delete obj;
	}
	if(dynamic_cast<ListManager*>(obj)){
		this->first_q = ((ListManager*) obj)->first_q;
		this->second_q = ((ListManager*) obj)->second_q;
	}
}

ListManager::ListManager(){
}

ListManager::ListManager(ListManager& obj) {
	first_q = obj.first_q;
	second_q = obj.second_q;
}

ListManager::ListManager(GenericManager* obj) {
	changeFrom(obj);
}

GenericManager::~GenericManager(){
}

ListManager::~ListManager(){
}

ListManagerHe1::~ListManagerHe1(){
}

ListManagerHe2::~ListManagerHe2(){
}

QueueManager::~QueueManager(){
}

bool ListManager::isNotEmpty(){
  return (first_q.size()+second_q.size());
}

bool QueueManager::isNotEmpty(){
  return (first_q.size());
}


 Node* ListManager::get(){
  Node* p = nullptr;

	if(!first_q.empty()){
		p = first_q.front();
		first_q.pop_front();
		return p;
	}

	if(!second_q.empty()){
		p = second_q.front();
		second_q.pop_front();
		return p;
	}
	return p;
}

void ListManager::add(std::vector<Node*>& q){
	std::sort (q.begin(), q.end(), GenericManager::NodeSort);
	for(std::vector<Node*>::iterator it=q.begin(); it!=q.end(); ++it)
		first_q.push_back(*it);
}

 void ListManager::add(Node* n){
  if(n) first_q.push_back(n);
}


ListManagerHe1::ListManagerHe1(){
}

ListManagerHe2::ListManagerHe2(){
}

ListManagerHe1::ListManagerHe1(GenericManager* obj){
	this->changeFrom(obj);
}

ListManagerHe2::ListManagerHe2(GenericManager* obj){
	this->changeFrom(obj);
}

 void ListManagerHe1::add(std::vector<Node*>& q) {
	std::sort (q.begin(), q.end(), GenericManager::NodeSort);
	for(std::vector<Node*>::iterator it=q.begin(); it!=q.end(); ++it){
		if((*it)->getDistance() < (*it)->getRoot()->getDistance())
      first_q.push_back(*it);
    else
      second_q.push_back(*it);
	}
}

 void ListManagerHe2::add(std::vector<Node*>& q) {
	 std::sort (q.begin(), q.end(), GenericManager::NodeSort);
 	for(std::vector<Node*>::iterator it=q.begin(); it!=q.end(); ++it){
 		if(it==q.begin() && (*it)->getDistance() < (*it)->getRoot()->getDistance())
       first_q.push_back(*it);
     else
       second_q.push_back(*it);
 	}
}

//QueueManager
 void QueueManager::add(std::vector<Node*>& q){
	 for(std::vector<Node*>::iterator it=q.begin(); it!=q.end(); ++it)
 		first_q.push(*it);
}

 void QueueManager::add(Node* n){
  if(n) first_q.push(n);
}


 Node* QueueManager::get(){
  Node* p = nullptr;
	if(!first_q.empty()){
    p = first_q.top();
		first_q.pop();
  }
	return p;
}

QueueManager::QueueManager(){}

QueueManager::QueueManager(QueueManager& obj){
  first_q = obj.first_q;
}

QueueManager::QueueManager(GenericManager* mn){
		if(dynamic_cast<QueueManager*>(mn)){
			first_q = ((QueueManager*) mn)->first_q;
		}
		if(dynamic_cast<ListManager*>(mn)){
			while(mn->isNotEmpty()){
				this->add(mn->get());
			}
			// delete mn;
		}
}
