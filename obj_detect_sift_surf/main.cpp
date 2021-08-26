//
//  Program to illustrate SIFT/SURF keypoint and descriptor extraction, and matching using FLANN
//
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

int main(int argc, const char * argv[]) {
    std::cout << "Starting Object detect for Keypoints!\n";
    
    Mat train = imread("template.jpg"), train_g;
    cvtColor(train, train_g, COLOR_BGR2GRAY);
    
    //detect SIFT keypoints and extract descriptors in the train image
    vector<KeyPoint> train_kp;
    Mat train_desc;
    
    //alternative: SIFT
    Ptr<SURF> featureDetector = SURF::create();
    featureDetector -> detect(train_g, train_kp);
    
    //alternative: SiftDescriptorExtractor
    Ptr<SurfDescriptorExtractor> featureExtractor = SurfDescriptorExtractor::create();
    featureExtractor -> compute(train_g, train_kp, train_desc);
    
    // FLANN based descriptor matcher object
    FlannBasedMatcher matcher;
    vector<Mat> train_desc_collection(1, train_desc);
    matcher.add(train_desc_collection);
    matcher.train();
    
    // VideoCapture object
    VideoCapture cap(0);
    
    while(char(waitKey(1)) != 'q' && cap.isOpened()) {
       double t0 = getTickCount();
       Mat test, test_g;
       cap >> test;
       if(test.empty())
           continue;
        
       cvtColor(test, test_g, COLOR_BGR2GRAY);
        
       //detect keypoints and extract descriptors in the test image
       vector<KeyPoint> test_kp;
       Mat test_desc;
       featureDetector -> detect(test_g, test_kp);
       featureExtractor -> compute(test_g, test_kp, test_desc);
        
        // match train and test descriptors, getting 2 nearest neighbors for all test descriptors
       vector<vector<DMatch>> matches;
       matcher.knnMatch(test_desc, matches, 2);
        
       // filter for good matches according to Lowe's algorithm
       vector<DMatch> good_matches;
       for(int i = 0; i < matches.size(); i++) {
           if(matches[i][0].distance < 0.6 * matches[i][1].distance)
               good_matches.push_back(matches[i][0]);
       }
        
       Mat img_show;
       drawMatches(test, test_kp, train, train_kp, good_matches, img_show);
       imshow("Matches", img_show);

       cout << "Frame rate = " << getTickFrequency() / (getTickCount() - t0) << endl;
   }
    
    return 0;
}
