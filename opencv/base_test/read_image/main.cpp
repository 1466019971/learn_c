#include "opencv.h"
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	const char* imagename = "lena.jpg";

	//�q���Ū�J�Ϲ�
	Mat img = imread(imagename);

	//�p�GŪ�J�Ϲ�����
	if(img.empty())
	{
		fprintf(stderr, "Can not load image %s\n", imagename);
		return -1;
	}

	//��ܹϹ�
	imshow("image", img);

	//����Ƶ��ݫ���A����L���N��N��^
	waitKey();

	return 0;
}
