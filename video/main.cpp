//
//  play a local video
//
//

#include <iostream>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    // Create a VideoCapture object to read from video file
    VideoCapture cap("video.mp4");
    //check if the file was opened properly
    if(!cap.isOpened()) {
        cout << "Capture could not be opened" << endl;
        return -1;
    }
    
    
    namedWindow("Video");

    // Play the video in a loop till it ends
    while(char(waitKey(1)) != 'q' && cap.isOpened()) {
        Mat frame;
        cap >> frame;
        // Check if the video is over
        if(frame.empty())
        {
            cout << "Video over" << endl;
            break;
            
        }
        imshow("Video", frame);
    }
    return 0;
}
