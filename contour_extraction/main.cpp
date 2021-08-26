//
//  contour_extraction
//
//

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat img;
vector<vector<Point> > contours;
vector<Vec4i> heirarchy;


void on_trackbar(int pos, void *) {
    if(contours.empty()) return;
    Mat img_show = img.clone();
    
    // Draw contours of the level indicated by slider
    drawContours(img_show, contours, -1, Scalar(0, 0, 255), 3, 8, heirarchy, pos);
    imshow("Contours", img_show);
}

int main() {
    std::cout << "Starting up contour extraction!\n";
    Mat i = imread("circles.jpg");

    GaussianBlur(i, img, Size(3, 3), 0, 0);
    
    Mat img_gray;
    cvtColor(img, img_gray, COLOR_RGB2GRAY);
    Mat edges;
    Canny(img_gray, edges, 50, 100);
    // Extract contours and hirarchy
    
    findContours(edges, contours, heirarchy, RETR_TREE, CHAIN_APPROX_NONE);
    
    namedWindow("Contours");
    createTrackbar("levels", "Contours", NULL, 15, on_trackbar);
    // Initialize by drawing the top level contours (as 'levels' is initialized to 0)
    on_trackbar(0, 0);
    
    while(char(waitKey(1)) != 'q') {}
    
    return 0;

}
