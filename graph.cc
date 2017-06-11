#include "graph.h"
#include <unistd.h>

Graph::Graph(int heu_type){
  this->heu_type = heu_type;
  if(heu_type == 1)
    gm = new ListManager();
  else if(heu_type == 2)
    gm = new ListManagerHe1();
  else if(heu_type == 3)
    gm = new ListManagerHe2();
  else
    gm = new QueueManager();
}

Graph::~Graph(){
  if(gm){
    gm->clearAll();
    delete gm;
  }
}

void Graph::changeHeuristic(int type){
  //if if the algorithm is the same do not change
  if(heu_type == type) return;
  //stop the current calculation
  if(thd){
    this->switching = true;
    thd->join();
  }
  GenericManager* old = gm;
  //change
  heu_type = type;
  if(heu_type == 1)
    gm = new ListManager(gm);
  else if(heu_type == 2)
    gm = new ListManagerHe1(gm);
  else if(heu_type == 3)
    gm = new ListManagerHe2(gm);
  else
    gm = new QueueManager(gm);
  //restart calculation
  delete old;
  if(thd){
    delete thd;
    this->switching = false;
    thd = new std::thread(graphThread, this);
  }
}

int Graph::getHeuristic(){
  return heu_type;
}

void Graph::graphThread(Graph* gr){
  while(gr->gm->isNotEmpty() && gr->run && !gr->switching){
    //if slowDown
    if(gr->slowDown)
      usleep(gr->slowDown);
    //get node to calculate
    Node* n = gr->gm->get();
    gr->steps++;
    //if is not solved
    if(n->getCoord()!=gr->end) {
      //generate new nodes
      std::vector<Node*> v = n->genSons(gr->maze);
      //add to the Node's list every sons
      if(v.size() > 0)
        gr->gm->add(v);
      else //if this node have not produced any node delete it
        n->remove();
    } else {
      std::cout<<"Path found\n";
      //create the vector with path's node
      while(n = n->getRoot()){
        gr->result.insert(gr->result.begin(), Point(n->getCoord()));
      }
      //stop execution
      gr->run = false;
    }
  }
}

bool Graph::searchPath(){
  start = maze.findStart();
  end = maze.findEnd();
  //check if are valid coordinates
  if(start == end || start.getX() == -1 ||start.getY() == -1 ||
    end.getX() == -1 ||end.getY() == -1){
      std::cout << "no path provided" << '\n';
      return 0;
  }
  //add the start to the list
  gm->add(new Node(start, nullptr, end));
  run = true;
  //start computation in other thread (so it can be joined from changeHeuristic(val))
  thd = new std::thread(graphThread, this);
  while(run) {} //wait until calculus is not over
  return (result.size());
}

void Graph::showPath(){
  if(result.size() < 1) return;
  for (std::vector<Point>::iterator it=result.begin(); it<result.end(); it++)
    maze.set((*it), 5);
}

std::vector<Point> Graph::getResults(){
  return result;
}

void Graph::printResults(){
  if(result.size() < 1) return;
  for (std::vector<Point>::iterator it=result.begin(); it<result.end(); it++)
    std::cout << (*it).getX() << " " << (*it).getY()<<std::endl;
}

int Graph::getSteps(){
  return steps;
}

int Graph::getLengthPath(){
  return result.size();
}

void Graph::setSlow(int val){
  this->slowDown = val;
}

bool Graph::isSlow(){
  return slowDown;
}

Matrix* Graph::getMatrixPrt(){
  return &maze;
}
