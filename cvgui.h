#ifndef CVGUI_H
#define CVGUI_H


#include "visiblematrix.h"
#include <string>
#include "graph.h"

class CVGui: public VisibleMatrix{
  private:
      /** \brief object to compute the maze */
      Graph graph;
      /** \brief Function for calculating the path in a separate thread */
      static void thd(CVGui* g);
      /** \brief Method called in GUIThread to elaborate keybord's inputs */
      virtual void actionWithKey(char key);
      /** \brief method called by constructors to set up the object*/
      void constructor(const char* path, int heu_type, bool delay);
      bool run;

  public:
    /**
      \brief constructor.
      \param path path to file.
      \param heu_type algorithm to use in path's elaboration.
      \param delay slow down execution.
    */
    CVGui(std::string path, int heu_type, bool delay);
    /**
      \brief constructor.
      \param path path to file.
      \param heu_type algorithm to use in path's elaboration.
      \param delay slow down execution.
    */
    CVGui(char* path, int heu_type, bool delay);
    /** \brief deallocate graph object */
    virtual ~CVGui();
    /** \brief lauch the window and start computing */
    void start();
    /** \brief return pointer to Graph object (allocated by constructor )*/
    Graph& getGraph();
    /** \brief call the VisibleMatrix method and display exec's informations over the image*/
    virtual void render();
};

#endif
