#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "facesTrain.h"
#include <opencv2/face.hpp>
#include <fstream>
#include <lccv.hpp>

using namespace std;
using namespace cv;

// int main()
// {
//   std::cout<<"Sample program for LCCV video capture"<<std::endl;
//   std::cout<<"Press ESC to stop."<<std::endl;
//   cv::Mat image;
//   lccv::PiCamera cam;
//   cam.options->video_width=1024;
//   cam.options->video_height=768;
//   cam.options->framerate=29;
//   cam.options->verbose=true;
//   cv::namedWindow("Video",cv::WINDOW_NORMAL);
//   cam.startVideo();
//   int ch=0;
//   while(ch!=27){
//     if(!cam.getVideoFrame(image,1000)){
//       std::cout<<"Timeout error"<<std::endl;
//     }
//     else{
//       cv::imshow("Video",image);
//       ch=cv::waitKey(10);
//     }
//   }
//   cam.stopVideo();
//   cv::destroyWindow("Video");
// }

int main(int argc, char** argv ) {
  vector<uchar> buffer;
  llcv::PiCamera cam;
  cam.startVideo();
  facesTrain();

  // Video capture object
  VideoCapture cap(0);

  if (!cap.isOpened()) {
    cout << "Error opening video stream or file" << endl;
    return -1;
  }

  if (argc != 2) {
    cout << "Usage: <face_recog_path>" << endl;
    return -1;
  }

  string path = argv[1];
  // Declare a facecascade object
  // Read from argv[1] the path to the xml file
  // Example: ./models/haarcascade_frontalface_alt2.xml

  CascadeClassifier face_cascade(path + "/models/haarcascade_frontalface_alt2.xml");

  Ptr<face::LBPHFaceRecognizer> model = face::LBPHFaceRecognizer::create();
  model->read(path + "/model.yml");

  // Read from "label_map.txt" the map<int, string> label_map
  // This format example:
  // 0 carlos_nieto
  // 1 elena_llorente

  map<int, string> label_map;
    ifstream file(path + "/label_map.txt");
  string line;
  while (getline(file, line)) {
    stringstream ss(line);
    int label;
    string name;
    ss >> label >> name;
    label_map[label] = name;
  }

  // Show map values
  // for (auto it = label_map.begin(); it != label_map.end(); it++) {
  //   cout << it->first << " " << it->second << endl;
  // }

  // Check if the camera is open
  // if (!cap.isOpened()) {
  //   cout << "Error opening video stream or file" << endl;
  //   return -1;
  // }

  while (1) {
    // Create a frame object
    Mat frame;
    Mat gray;
    // Capture the frame
    if (!cam.getVideoFrame(frame, 1000)) {
      cout << "Timeout error" << endl;
    };

    gray = frame.clone();

    // Capture frames until not empty frame
    while (frame.empty()) {
      cap >> frame;
      cout << "Empty frame" << endl;
    }

    cvtColor(frame, gray, COLOR_BGR2GRAY);

    // Detect faces
    vector<Rect> faces;
    //Detect with higher confidence
    face_cascade.detectMultiScale(gray, faces, 1.1, 5, 0, Size(30, 30));

    for (size_t i = 0; i < faces.size(); i++) {
      //cout << faces[i] << endl;
      // Only draw rectangle with certain confidence

      rectangle(frame, faces[i], Scalar(255, 0, 0), 2);
      Mat faceROI = gray(faces[i]);
      Mat faceROI_resized;
      resize(faceROI, faceROI_resized, Size(100, 100));
      int label;
      double confidence;
      model->predict(faceROI_resized, label, confidence);
      // Add text on top of the rectangle with label and confidence
      string text_label = label_map[label];
      if (confidence > 110) {
        text_label = "Unknown";
        confidence = 0;
      }
      putText(frame, text_label, Point(faces[i].x, faces[i].y - 10), FONT_HERSHEY_SIMPLEX, 0.9, Scalar(0, 0, 255), 2);
      putText(frame, to_string(confidence), Point(faces[i].x, faces[i].y + faces[i].height + 20), FONT_HERSHEY_SIMPLEX, 0.9, Scalar(0, 0, 255), 2);
    }

    // Display the frame
    // Encode frame to jpg
    imencode(".jpg", frame, buffer);

    // Write size of buffer
    int size = buffer.size();
    cout.write((char*)&size, sizeof(int));

    // Write buffer
    cout.write((char*)&buffer[0], size);

    // Show frame

    // Wait for parent to say something
    char b;
    cin >> b;

    // Press q on keyboard to exit
    char c = (char)waitKey(1);
    if(c=='q')
      break;
  }

  return 0;
}
