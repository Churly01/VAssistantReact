#include <iostream>
#include <fstream>
#include <opencv2/face/facerec.hpp>
#include <string>
#include <vector>
#include <dirent.h>
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>

using namespace std;
using namespace cv;
// Declare directory path
const char *images_dir = "./images";

void facesTrain(){

  // Read all directories (people directories) in images directory
  CascadeClassifier face_cascade("./models/haarcascade_frontalface_alt2.xml");
  // Delcare face recognizer lbph
  Ptr<face::LBPHFaceRecognizer> model = face::LBPHFaceRecognizer::create();

  DIR *dp;
  struct dirent *ep;
  dp = opendir(images_dir);
  if (dp != NULL){
    // Read all images in each directory
    vector<cv::Mat> images;
    vector<int> labels;
    int current_label_id = 0;
    // Map label to integer
    map<string, int> label_map;

    while ((ep = readdir(dp))){
      if (ep->d_type == DT_DIR){
        std::string person_dir = std::string(ep->d_name);
        if (person_dir.compare(".") != 0 && person_dir.compare("..") != 0){

          std::string person_images_dir = std::string(images_dir) + "/" + person_dir;
          DIR *dp_images;
          struct dirent *ep_images;
          dp_images = opendir(person_images_dir.c_str());

          if (dp_images != NULL){
            while ((ep_images = readdir(dp_images))){
              if (ep_images->d_type == DT_REG){
                std::string image_file = std::string(ep_images->d_name);
                std::string image_path = person_images_dir + "/" + image_file;
                cv::Mat image = cv::imread(image_path, IMREAD_GRAYSCALE);
                vector<Rect> faces;
                face_cascade.detectMultiScale(image, faces, 1.2, 5);
                // Find region of interest (face) in image
                for (int i = 0; i < faces.size(); i++){
                  Rect face_i = faces[i];
                  Mat face = image(face_i);
                  // Resize face to 100x100
                  Mat face_resized;
                  // Use antialiasing
                  cv::resize(face, face_resized, Size(550, 550), 1.0, 1.0, INTER_CUBIC);

                  images.push_back(face_resized);

                  // Check if label already exists
                  if (label_map.find(person_dir) == label_map.end()){
                    label_map[person_dir] = current_label_id;
                    labels.push_back(current_label_id);
                    current_label_id++;
                  } else {
                    labels.push_back(label_map[person_dir]);
                  }

                }
              }
            }
          }
        }
      }
    }
    // Print all labels
    ofstream label_map_file;
    label_map_file.open("label_map.txt");
    for (auto const& x : label_map){
      label_map_file << x.second << " " << x.first << endl;
    }
    label_map_file.close();

    // Train model
    model->train(images, labels);
    model->write("model.yml");
  }
}
