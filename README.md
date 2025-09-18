Face and Age Detection with OpenCV (C++)
Overview
This project is a real-time face and age detection application written in C++ using OpenCV. It uses your laptop camera to detect faces and estimate the age group for each detected face.


How It Works
1.	Loads a face detection model (Haar Cascade).
2.	Loads an age prediction model (Deep Learning, Caffe format).
3.	Captures video from your laptop camera.
4.	Detects faces in each frame.
5.	Estimates the age group for each detected face.
6.	Draws rectangles and age labels on the video.
7.	Displays the result in a window.
8.	Stops when you press the ESC key.


Prerequisites
•	OpenCV installed and linked in your project.
•	The following files in your project directory:
•	haarcascade_frontalface_default.xml (for face detection)
•	age_deploy.prototxt (age model architecture)
•	age_net.caffemodel (age model weights)
•	A working laptop camera.


How to Run
1.	Build the project in Visual Studio (make sure OpenCV is linked correctly).
2.	Copy the required model files (haarcascade_frontalface_default.xml, age_deploy.prototxt, age_net.caffemodel) into the same folder as your executable.
3.	Run the program. A window will open showing your camera feed with rectangles and age labels for detected faces.
4.	Press ESC to close the window and stop the program.


Code Explanation
•	Face Detection: Uses Haar Cascade classifier to find faces in each frame.
•	Age Estimation: Crops each detected face, preprocesses it, and passes it to a deep learning model to predict the age group.
•	Display: Draws rectangles around faces and shows the predicted age group above each face.


Key Functions
•	cv::CascadeClassifier: Loads and applies the face detection model.
•	cv::dnn::readNetFromCaffe: Loads the age prediction neural network.
•	cv::VideoCapture: Captures video from the camera.
•	cv::cvtColor: Converts images to grayscale for face detection.
•	cv::equalizeHist: Improves image contrast.
•	cv::dnn::blobFromImage: Prepares face images for age prediction.
•	cv::minMaxLoc: Finds the most probable age group.
•	cv::rectangle and cv::putText: Draws rectangles and age labels.
•	cv::imshow: Displays the video feed.


Troubleshooting
•	If you get errors about missing DLLs or unresolved symbols, make sure you have linked OpenCV libraries correctly and copied the required DLLs to your output folder.
•	If the camera does not open, check that your laptop camera is working and not used by another application.
•	If you get errors about missing model files, ensure all required files are in the executable directory.