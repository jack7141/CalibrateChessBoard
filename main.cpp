
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
    VideoCapture cam(1);
    int board_w=27;
    int board_h=19;
    int board_n = board_w*board_h;
    Size board_sz(board_w,board_h );

    const int maxwidth = 640;
    const int maxheight = 480;

    Point2f imgPts[4],dst[4];

    Mat frame, readImage;
    cam >> frame;
    imwrite("Test.jpg",frame);

    vector<Point2f> corners,corners2;
    readImage = imread("Test.jpg");
    bool found = findChessboardCorners(readImage,board_sz,corners);

    if (!found) {
        cout << "Couldnt found chessboard cornors" << "chessboard size :"<< corners.size() <<endl;
    } else {
        cout <<  "found chessboard!!!!!"<<" ChessBoard Size is : " << corners.size() <<endl;

        imgPts[0]=corners[0];
        imgPts[1]=corners[board_w-1];
        imgPts[2]=corners[(board_h-1)*board_w];
        imgPts[3]=corners[(board_h-1)*board_w+board_w-1];

        circle(readImage,imgPts[0],30,Scalar(255,0,0),3);
        circle(readImage,imgPts[1],30,Scalar(0,255,0),3);
        circle(readImage,imgPts[2],30,Scalar(0,0,255),3);
        circle(readImage,imgPts[3],30,Scalar(255,255,0),3);
    }

    while (1) {
        Mat frame;
        Mat output;
        cam >> frame;

        dst[0]=Point2f(0,0);
        dst[1]=Point2f(maxwidth-1,0);
        dst[2]=Point2f(0, maxheight-1);
        dst[3]=Point2f(maxwidth-1,maxheight-1);


        Mat transform = getPerspectiveTransform(imgPts, dst);
        warpPerspective(frame,output,transform,Size(maxwidth,maxheight));
        imshow("affine",output);
        imshow("frame",frame);
        if ( waitKey(1) == 27)break;
    }
}
