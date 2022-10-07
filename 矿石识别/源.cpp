#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cstdio>

using namespace std;
using namespace cv;

class OreIdentifier {
public:
	OreIdentifier(Mat img);

	void OreIdentify();
private:
	Mat _img_ori, _img;
	void _ImgPreprocess();
private:
	vector<vector<Point>> _contours;
	vector<Rect> _boundRect;
	vector<int> _six_index, _square_index;
	vector<int> _key_index, _other_index;
	void _GraphicsDetect();
private:
	void _RDirectionDetect();
};

int main() {
	//图像
	//string path = "C:/Users/TianRui/Desktop/stone1.jpg";
	//Mat img = imread(path);
	//视频
	VideoCapture cap(0);
	Mat img;

	while (true) {
		cap.read(img);
		if (img.empty()) {
			printf("load error");
			throw("error occurred");
		}
		OreIdentifier OreIdentify(img);
		OreIdentify.OreIdentify();

		waitKey(1);
	}
	return 0;
}

OreIdentifier::OreIdentifier(Mat img) {
	_img_ori = img;
	_img = img;
}

void OreIdentifier::OreIdentify() {
	_ImgPreprocess();
	_GraphicsDetect();
}

void OreIdentifier::_ImgPreprocess() {
	//电子变焦
	//Rect roi(_img.size().width * 0.1, _img.size().height * 0.1, _img.size().width * 0.8, _img.size().height * 0.8);
	//_img = _img(roi);

	//resize(_img, _img, Size(), 2, 2, INTER_LINEAR);
	//flip(_img, _img, 1);
	cvtColor(_img, _img, COLOR_BGR2GRAY);
	GaussianBlur(_img, _img, Size(7, 7), 5, 0);
	imshow("_img_gray", _img);
	threshold(_img, _img, 120, 255, THRESH_BINARY);
	imshow("_img_threshold", _img);

	//Mat _erode_kernel = getStructuringElement(MORPH_RECT, Size(9, 9));
	//Mat _dilate_kernel = getStructuringElement(MORPH_RECT, Size(9, 9));
	//erode(_img, _img, _erode_kernel);
	//dilate(_img, _img, _dilate_kernel);
	Mat _open_kernel = getStructuringElement(MORPH_RECT, Size(9, 9));
	morphologyEx(_img, _img, MORPH_OPEN, _open_kernel, Point(-1, -1), 1);

	Canny(_img, _img, 25, 75);
	imshow("_img_canny", _img);
}

void OreIdentifier::_GraphicsDetect() {
	vector<Vec4i> _hierarchy;
	findContours(_img, _contours, _hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>> _conPoly(_contours.size());
	_boundRect.resize(_contours.size());
	for (int i = 0; i < _contours.size(); i++) {
		int _area = contourArea(_contours[i]);
		if (_area > 1000 && _area < 20000) {
			string _objectType;
			float _peri = arcLength(_contours[i], true);
			approxPolyDP(_contours[i], _conPoly[i], 0.02 * _peri, true);
			_boundRect[i] = boundingRect(_conPoly[i]);

			int _objCor = (int)_conPoly[i].size();
			if (_objCor == 6) {
				_objectType = "Six";
				_six_index.push_back(i);
				_key_index.push_back(i);
			}
			else if (_objCor == 4) {
				_objectType = "Rect";
				_square_index.push_back(i);
				_key_index.push_back(i);
			}
			/*else if (objCor == 4) {
				float aspRatio = (float)_boundRect[i].width / (float)_boundRect[i].height;
				cout << aspRatio << endl;
				if (aspRatio > 0.95 && aspRatio < 1.05) { _objectType = "Square"; }
				else { _objectType = "Rect"; }
			}*/
			else if (_objCor > 4) {
				_objectType = "R";
				_other_index.push_back(i);
			}
			drawContours(_img_ori, _conPoly, i, Scalar(255, 0, 255), 2);
			putText(_img_ori, _objectType, { _boundRect[i].x, _boundRect[i].y }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 2);
		}
	}
	imshow("img_detect", _img_ori);

	if (_six_index.size() == 2) {
		if (_square_index.size() == 2) {
			cout << "顶面" << endl;
		}
		else if (_other_index.size() > 0 || _square_index.size() > 2) {
			cout << "底面" << endl;
		}
	}
	else if (_six_index.size() == 3) {
		cout << "侧面";
		_RDirectionDetect();
		cout << endl;
	}
	cout << " 四边形" << _square_index.size() << " 六边形" << _six_index.size() << " 其他形状" << _other_index.size() << endl;
}

void OreIdentifier::_RDirectionDetect() {
	cout << " R向";
	int R_direction = 0;
	Point key_centre = Point(0, 0);
	for (vector<int>::iterator it = _key_index.begin(); it != _key_index.end(); it++) {
		key_centre.x += _boundRect[*it].x / _key_index.size();
		key_centre.y += _boundRect[*it].y / _key_index.size();
	}
	if (!_square_index.empty()) {
		if (_boundRect[_square_index[0]].x > key_centre.x) {
			if (_boundRect[_square_index[0]].y > key_centre.y) cout << "上";
			else if (_boundRect[_square_index[0]].y < key_centre.y) cout << "左";
		}
		else if (_boundRect[_square_index[0]].x < key_centre.x) {
			if (_boundRect[_square_index[0]].y > key_centre.y) cout << "右";
			else if (_boundRect[_square_index[0]].y < key_centre.y) cout << "下";
		}
	}
	else { cout << "未知"; }
}
