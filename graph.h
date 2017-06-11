#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>

#include "point.h"
#include "node.h"
#include "matrix.h"
#include "dataman.h"

#include <thread>

class Graph{
  private:
    GenericManager* gm;
    Matrix maze;
    Point start;
    Point end;
    int heu_type;
    bool run;
    bool switching;
    std::vector<Point> result;
    int slowDown = 0;
    int steps = 0;
    /** \brief pointer to pathsearch's thread */
    std::thread* thd;
    /** \brief thread's function for pathsearch */
    static void graphThread(Graph* gr);

  public:
    /** \brief constructor: allocate DataManager, Matrix maze */
    Graph(int heu_type);
    /** \brief delete all computed nodes left*/
    ~Graph();
    /** \brief halt current calculus and switch DataManager */
    void changeHeuristic(int heu_type);
    /** \brief get current algorithm */
    int getHeuristic();
    /** \brief start calculus */
    bool searchPath();
    /** \brief show path on matrix */
    void showPath();
    /** \brief return results' vector */
    std::vector<Point> getResults();
    /** \brief cout result's path coordinates*/
    void printResults();
    /** \brief get how many node are calculated */
    int getSteps();
    /** \brief get the length of the path found*/
    int getLengthPath();
    /** \brief set delay */
    void setSlow(int val);
    /** \brief get if delayed */
    bool isSlow();
    /** \brief get the pointer to the Matrix */
    Matrix* getMatrixPrt();
};

#endif
