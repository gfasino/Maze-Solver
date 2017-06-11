#include "cvgui.h"
#include "graph.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/core/types_c.h"
#include <thread>
#include <ctime>

#define STDELEY 5

void CVGui::constructor(const char* path, int heu_type, bool delay){
  this->maze = graph.getMatrixPrt();
  if(delay)
    this->graph.setSlow(STDELEY);
  this->img_path = path;
  image = cv::imread(path, 1);
  this->imageToMatrix();
  cv::namedWindow(WINDOWNAME, cv::WINDOW_AUTOSIZE);
}

CVGui::CVGui(std::string path, int heu_type, bool delay) : graph(heu_type) {
  constructor(path.c_str(), heu_type, delay);
}

CVGui::CVGui(char* path, int heu_type, bool delay) : graph(heu_type){
  constructor(path, heu_type, delay);
}

CVGui::~CVGui(){
}

void CVGui::actionWithKey(char key){
  if(key == '0'){
    this->graph.changeHeuristic(0);
  }
  if(key == '1'){
    this->graph.changeHeuristic(1);
  }
  if(key == '2'){
    this->graph.changeHeuristic(2);
  }
  if(key == '3'){
    this->graph.changeHeuristic(3);
  }
  if(key == 's'){
    if(graph.isSlow())
      graph.setSlow(0);
    else
      graph.setSlow(STDELEY);
  }
  if(key == 'f'){
    /** get the path to the folder of the image and save the screen */
    std::size_t found = img_path.find_last_of("/");
    std::string path = img_path.substr(0,found);
    this->takeSShot(path+"/sshot"+std::to_string(time(0))+".jpg");
  }
}

void CVGui::start(){
  run = true;
  //start parallel computing
  std::thread t1(thd, this);

  char key = 0;
	while(this->run || key != ' '){
		this->render();
		this->showImage();
		key = this->waitKey(STDELEY);
		this->actionWithKey(key);
	}
  //sync gui and comp
  t1.join();
}

void CVGui::render(){
  VisibleMatrix::render();
  //Display information at top
  std::string display = "Computed: "+std::to_string(graph.getSteps());
  display += " | Alg: "+std::to_string(graph.getHeuristic())+" (0-3)";
  if(graph.isSlow())
    display += " | Speed:Slow (s)";
  else
    display += " | Speed:Fast (s)";
  display += " | Path: "+std::to_string(graph.getLengthPath());
  display += " | Sshot (f)";
  //NODE COMPUTED | HEU TYPE (Keys) | PATH LENGTH | SLOW DOWN (o/f) Key | SShot
  cv::putText(image, display, cvPoint(10, 30),
    cv::FONT_HERSHEY_SIMPLEX, 0.5, cvScalar(100,100,250), 2);
}

Graph& CVGui::getGraph(){
  return graph;
}

void CVGui::thd(CVGui* g){
	g->getGraph().searchPath();
	g->getGraph().showPath();
	g->run = 0;
}
