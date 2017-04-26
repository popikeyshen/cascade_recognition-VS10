// face.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <cv.h>
#include <highgui.h>

// Create memory for calculations
static CvMemStorage* storage = 0;
// Create a new Haar classifier
static CvHaarClassifierCascade* cascade = 0;
// Function prototype for detecting and drawing an object from an image
void detect_and_draw( IplImage* image );
// Create a string that contains the cascade name

using namespace std;
using namespace cv;

int counter=0;
char filename[512] = {0};
String window_name = "FaceDetection";


String cascade_name = "haarcascade_frontalface_alt2.xml";
String foto_cascade_name = "cascade.xml";


CascadeClassifier face_cascade;
CascadeClassifier foto_cascade;



// Main function, defines the entry point for the program.
int main( int argc, char** argv )
{
	VideoCapture capture;
    Mat frame;

	void detectAndDisplay( Mat frame );

if( !face_cascade.load( cascade_name ) ) { 
                printf("[!] Error loading face cascade\n");
                return -1;
        }
if( !foto_cascade.load( foto_cascade_name ) ) { 
                printf("[!] Error loading face cascade\n");
                return -1;
        }

    // начинаем захват видео
    capture.open( -1 );
    if ( ! capture.isOpened() ) {
                printf("[!] Error opening video capture\n");
                return -1;
        }
        
        // установка разрешения для видео
        capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
        capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

        // цикл получения кадров с камеры
    while ( capture.read(frame) ) {
        if( frame.empty() ) {
            printf("[!] No captured frame -- Break!\n");
            break;
        }

        // обработка кадра
        detectAndDisplay( frame );

        // обработка клавиатуры
        int c = waitKey(10);
        if( (char)c == 27 ) { 
                        break;
                }
    }
    return 0;
}

void detectAndDisplay( Mat frame )
{
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
	


    // детектор лиц
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0, Size(80, 80) );


        printf("[i] frame %d x %d detect faces: %d\n", frame.cols, frame.rows, faces.size());
        
    for( size_t i = 0; i < faces.size(); i++ ) {        
        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;


          
            // отрисовка рамки вокруг лица
            Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
            ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 0 ), 2, 8, 0 );
    }

    foto_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0, Size(80, 80) );

    for( size_t i = 0; i < faces.size(); i++ ) {        
        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;


            printf("\n Open!!!");
            // отрисовка рамки фото
            Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
            ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 0, 255, 0 ), 2, 8, 0 );
    }


    // показываем результат
    imshow( window_name, frame );

}


