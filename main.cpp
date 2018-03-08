#include<iostream>
#include <string>
#include <unistd.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp> 
#include <opencv2/opencv.hpp>

using namespace std;

cv::Mat cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
cv::Mat distCoeffs = cv::Mat::zeros(4, 1, CV_64F);
cv::Matx33d K2;
cv::Mat new_intrinsic_mat;

void loadImageFromFile(const std::string file_name)
{
    cv::Mat img = cv::imread(file_name);
}

cv::Mat undistortCameraImage(cv::Mat & img)
{
    cv::Mat undisImg;
    cv::undistort(img, undisImg, cameraMatrix, distCoeffs, new_intrinsic_mat);
    return undisImg;
}

void loadSettings()
{
    // Load Settings and Check
    string strSettingsFile = "config.yaml";
    
    cv::FileStorage fsSettings(strSettingsFile.c_str(), cv::FileStorage::READ);
    if(!fsSettings.isOpened())
    {
        std::cout<<"Open file faild!!"<<std::endl;
    }
    // load parameters
    float fx = fsSettings["Camera.fx"];
    float fy = fsSettings["Camera.fy"];
    float cx = fsSettings["Camera.cx"];
    float cy = fsSettings["Camera.cy"];

    cameraMatrix.at<double>(0, 0) = fx;
    cameraMatrix.at<double>(0, 2) = cx;
    cameraMatrix.at<double>(1, 1) = fy;
    cameraMatrix.at<double>(1, 2) = cy;

    float k1 = fsSettings["Camera.k1"];
    float k2 = fsSettings["Camera.k2"];
    float p1 = fsSettings["Camera.p1"];
    float p2 = fsSettings["Camera.p2"];

    distCoeffs.at<double>(0, 0) = k1;
    distCoeffs.at<double>(1, 0) = k2;
    distCoeffs.at<double>(2, 0) = p1;
    distCoeffs.at<double>(3, 0) = p2;

    int width = fsSettings["Image.width"];
    int height = fsSettings["Image.height"];

    cameraMatrix.copyTo(new_intrinsic_mat);
    new_intrinsic_mat.at<double>(0, 0) *= 1;
    new_intrinsic_mat.at<double>(1, 1) *= 1;
    new_intrinsic_mat.at<double>(0, 2) = 0.5 * width;
    new_intrinsic_mat.at<double>(1, 2) = 0.5 * height;
}

int main(int argc, char **argv)
{
    loadSettings();
    cv::Mat image = cv::imread(argv[1]);
    // cv::imshow("ori",image);
    cv::Mat undisImag = undistortCameraImage(image);
    // cv::imshow("after",undisImag);
    cv::imwrite(argv[2],undisImag);
    // cv::waitKey(0);
    return 0;
}