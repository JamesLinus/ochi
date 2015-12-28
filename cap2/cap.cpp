
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		std::cerr << "Error: cannot create VideoCapture\n";
		exit(1);
	}

	//namedWindow("Image", 1);
	namedWindow("Grayscale", 1);
	namedWindow("Edges", 1);
	namedWindow("Lines", 1);

	for (;;)
	{
		Mat frame;

		cap >> frame;
		//imshow("Image", frame);

		Mat gray;
		cvtColor(frame, gray, CV_BGR2GRAY);
		imshow("Grayscale", gray);

		Mat edges;
		Canny(gray, edges, 50, 100, 3);
		imshow("Edges", edges);

		vector<Vec2f> lines;
		HoughLines(edges, lines, 1, CV_PI/180, 150, 0, 0);

		Mat comb;
		frame.copyTo(comb);
		for (int i = 0; i < lines.size(); i++)
		{
			float rho = lines[i][0];
			float theta = lines[i][1];
			double a = cos(theta);
			double b = sin(theta);
			Point x1, x2;
			x1.x = cvRound(rho*a + 1000*(-b));
			x1.y = cvRound(rho*b + 1000*a);
			x2.x = cvRound(rho*a - 1000*(-b));
			x2.y = cvRound(rho*b - 1000*a);

			line(comb, x1, x2, Scalar(10, 240, 10), 1, CV_AA);
		}
		imshow("Lines", comb);

		if (waitKey(30) >= 0)
			break;
	}

	return 0;
}
