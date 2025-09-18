#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>

int main() {
    // Load Haar Cascade for face detection
    cv::CascadeClassifier face_cascade;
    if (!face_cascade.load("haarcascade_frontalface_default.xml")) {
        std::cerr << "Error loading face cascade\n";
        return -1;
    }

    // Load age detection model
    cv::dnn::Net ageNet = cv::dnn::readNetFromCaffe("age_deploy.prototxt", "age_net.caffemodel");
    std::vector<std::string> ageList = {
        "0-2", "4-6", "8-12", "15-20", "25-32", "38-43", "48-53", "60-100"
    };

    // Open the default camera (usually laptop camera)
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error opening camera\n";
        return -1;
    }

    cv::Mat frame, gray;
    std::vector<cv::Rect> faces;

    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(gray, gray);

        // Detect faces
        face_cascade.detectMultiScale(gray, faces);

        for (const auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(255, 0, 0), 2);
            // Crop face region
            cv::Mat faceROI = frame(face);
            // Preprocess for age model
            cv::Mat blob = cv::dnn::blobFromImage(faceROI, 1.0, cv::Size(227, 227), cv::Scalar(78.4263377603, 87.7689143744, 114.895847746), false);
            ageNet.setInput(blob);
            cv::Mat agePreds = ageNet.forward();
            cv::Point classIdPoint;
            double confidence;
            cv::minMaxLoc(agePreds, 0, &confidence, 0, &classIdPoint);
            int ageIdx = classIdPoint.x;
            std::string age = ageList[ageIdx];
            // Put age text above face
            cv::putText(frame, age, cv::Point(face.x, face.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0,255,0), 2);
        }

        cv::imshow("Face & Age Detection", frame);
        if (cv::waitKey(10) == 27) break; // Exit on ESC key
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
