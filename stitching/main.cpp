//
// Code to create a panorama from a collection of images
//
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/stitching.hpp>
#include <opencv2/stitching/warpers.hpp>

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    cout << "Starting stitching!\n";
    vector<Mat> images;
    vector<String> names;
    
    glob("stitching/*.jpg", names, false);
    size_t count = names.size();
    for (size_t i=0; i<count; i++)
        images.push_back(imread(names[i]));
    
    if (images.size() <= 0) {
        cout << "No images!\n";
        return 1;
    }
    
    cout << "Read " << images.size() << " images" << endl << "Now making panorama..." << endl;
    
    Mat panorama;
    //args: panorama(default)|scans
    Ptr<Stitcher> stitcher = Stitcher::create();
    stitcher -> stitch(images, panorama);
    namedWindow("Panorama", WINDOW_NORMAL);
    imshow("Panorama", panorama);
    while(char(waitKey(1)) != 'q') {}
    
    return 0;
}
