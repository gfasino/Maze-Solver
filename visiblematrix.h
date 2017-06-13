#ifndef VISIBLEMATRIX_H
#define VISIBLEMATRIX_H

#include <opencv2/opencv.hpp>
#include "matrix.h"

#include <string>
#include <thread>

#define WINDOWNAME "Display Maze"

/** \brief provide conversion from image to matrix,
  can load image and save from filesystem, also can display a static image */

class VisibleMatrix{
  protected:
    cv::Mat image;
    Matrix* maze;
    std::string img_path;
    /** \brief constructor used only by inheritance classes */
    VisibleMatrix();

    /** \brief set the variables r,g,b to the designate color */
    static void getWhite(unsigned char &r, unsigned char &g, unsigned char &b);
    /** \brief set the variables r,g,b to the designate color */
    static void getBlack(unsigned char &r, unsigned char &g, unsigned char &b);
    /** \brief set the variables r,g,b to the designate color */
    static void getBlue (unsigned char &r, unsigned char &g, unsigned char &b);
    /** \brief set the variables r,g,b to the designate color */
    static void getGreen(unsigned char &r, unsigned char &g, unsigned char &b);
    /** \brief set the variables r,g,b to the designate color */
    static void getRed  (unsigned char &r, unsigned char &g, unsigned char &b);

    /** \brief color filter*/
    static bool isWhite(unsigned char &r, unsigned char &g, unsigned char &b);
    /** \brief color filter*/
    static bool isBlack(unsigned char &r, unsigned char &g, unsigned char &b);
    /** \brief color filter*/
    static bool isBlue (unsigned char &r, unsigned char &g, unsigned char &b);
    /** \brief color filter*/
    static bool isRed  (unsigned char &r, unsigned char &g, unsigned char &b);

    /** \brief load new image from file */
    int loadImage(const char* path);
    /** \brief convert the image to computable Matrix */
    void imageToMatrix();
    /** \brief change pointer to the Matrix */
    void setMatrix(Matrix& m);
    /** \brief convert the Matrix to Displayable image */
    virtual void render();
    /** \brief display image in CV's window */
    void showImage();
    /** \brief call cv's waitkey (needed by cvgui)*/
    int waitKey(int i);

  public:
    /** \brief constructor */
    VisibleMatrix(const char* path, Matrix* m);
    /** \brief distructor */
    virtual ~VisibleMatrix();
    /** \brief save current image to file */
    bool takeSShot(std::string filepath);
};

#endif
