#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "facesTrain.h"
#include <opencv2/face.hpp>
#include <fstream>

using namespace std;
using namespace cv;

// int main(int argc, char** argv ) {

//   // Video capture object
//   VideoCapture cap(0);
//   vector<uchar> buffer;
//   // Only display images
//   if (!cap.isOpened()) {
//     cout << "Error opening video stream or file" << endl;
//     return -1;
//   }

//   while (1) {
//     // Create a frame object
//     Mat frame;
//     // Capture the frame
//     cap >> frame;

//     // Check if the frame is empty
//     if (frame.empty())
//       break;

//     // Encode frame to jpg
//     imencode(".jpg", frame, buffer);

//     // Write size of buffer
//     int size = buffer.size();
//     cout.write((char*)&size, sizeof(int));

//     // Write buffer
//     cout.write((char*)&buffer[0], size);

//     // Wait for parent to say something
//     char b;
//     cin >> b;

//     // Press q on keyboard to exit
//     char c = (char)waitKey(1);
//     if(c=='q')
//       break;
//   }
// }

int main(int argc, char** argv ) {
  vector<uchar> buffer;


  // facesTrain();

  // Video capture object
  VideoCapture cap(0);

  if (argc != 2) {
    cout << "Usage: ./facesDetect path>" << endl;
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
    cap >> frame;
    gray = frame.clone();
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
