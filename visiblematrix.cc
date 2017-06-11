#include "visiblematrix.h"

#define TYPEWINDOW cv::WINDOW_NORMAL
//#define TYPEWINDOW cv::WINDOW_AUTOSIZE

VisibleMatrix::VisibleMatrix(){
}

VisibleMatrix::~VisibleMatrix(){
}

VisibleMatrix::VisibleMatrix(const char* path, Matrix* m){
  this->maze = m;
  this->img_path = path;
  image = cv::imread(path, 1);
  this->imageToMatrix();
}

int VisibleMatrix::loadImage(const char* path){
  this->img_path = path;
  image = cv::imread(path, 1);
}

void VisibleMatrix::showImage(){
  if(!image.data) return;
  cv::namedWindow(WINDOWNAME, TYPEWINDOW);
	cv::imshow(WINDOWNAME, image);
}

int VisibleMatrix::waitKey(int i){
  return cv::waitKey(i);
}

bool VisibleMatrix::takeSShot(std::string filepath){
	cv::imwrite(filepath, image);
	return true;
}

void VisibleMatrix::imageToMatrix(){
  if(!image.data) return;
  Point start(0,0);
  Point end(0,0);
  int cstart = 0, cend = 0;
  maze->create(image.rows, image.cols);
  for(int j=0; j<image.rows; j++){
    for(int i=0; i<image.cols; i++){
      cv::Vec3b intensity = image.at<cv::Vec3b>(cv::Point(i,j));
      unsigned char b = intensity.val[0];
      unsigned char g = intensity.val[1];
      unsigned char r = intensity.val[2];
      if(isBlack(r,g,b)) maze->set(i, j, 1);
      if(isRed(r,g,b)){
        start.setX(start.getX()+i);
        start.setY(start.getY()+j);
        cstart++;
      }
      if(isBlue(r,g,b)){
        end.setX(end.getX()+i);
        end.setY(end.getY()+j);
        cend++;
      }
    }
  }
  start.setX(start.getX()/cstart);
  start.setY(start.getY()/cstart);
  end.setX(end.getX()/cend);
  end.setY(end.getY()/cend);
  maze->set(start, 2);
  maze->set(end, 3);
}

void VisibleMatrix::render(){
  if(!image.data) return;
  unsigned char b,g,r;
  for(int j = 0;j < image.rows;j++){
    for(int i = 0;i < image.cols;i++){
      switch(maze->get(i,j)){
        case 0:
          getWhite(r,g,b);
          break;
        case 2:
          getBlue(r,g,b);
          break;
        case 3:
          getRed(r,g,b);
          break;
        case 4:
          getGreen(r,g,b);
          break;
        case 5:
          getRed(r,g,b);
          break;
        default:
          getBlack(r,g,b);
          break;
      }
      cv::Vec3b intensity;
      intensity.val[0] = b;
      intensity.val[1] = g;
      intensity.val[2] = r;
      image.at<cv::Vec3b>(cv::Point(i,j)) = intensity;
    }
  }
}

void VisibleMatrix::setMatrix(Matrix& m){
  this->maze = &m;
}

void VisibleMatrix::getWhite(unsigned char &r, unsigned char &g, unsigned char &b) {
  r = 255; g = 255; b = 255;
}

void VisibleMatrix::getBlack(unsigned char &r, unsigned char &g, unsigned char &b) {
  r = 0; g = 0; b = 0;
}

void VisibleMatrix::getBlue(unsigned char &r, unsigned char &g, unsigned char &b) {
  r = 0; g = 0; b = 255;
}

void VisibleMatrix::getRed(unsigned char &r, unsigned char &g, unsigned char &b) {
  r = 255; g = 0; b = 0;
}

void VisibleMatrix::getGreen(unsigned char &r, unsigned char &g, unsigned char &b) {
  r = 130; g = 255; b = 130;
}

bool VisibleMatrix::isWhite(unsigned char &r, unsigned char &g, unsigned char &b) {
	return (r>=150 && r<=255 && g>=150 && g<=255 && b>=150 && b<=255);
}

bool VisibleMatrix::isBlack(unsigned char &r, unsigned char &g, unsigned char &b) {
	return (r>=0 && r<=130 && g>=0 && g<=130 && b>=0 && b<=130);
}

bool VisibleMatrix::isBlue(unsigned char &r, unsigned char &g, unsigned char &b) {
	return (r>=0 && r<=130 && g>=0 && g<=130 && b>130 && b<=255);
}

bool VisibleMatrix::isRed(unsigned char &r, unsigned char &g, unsigned char &b) {
	return (r>130 && r<=255 && g>=0 && g<=130 && b>=0 && b<=130);
}
