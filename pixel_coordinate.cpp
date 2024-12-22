#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

#include<iostream>
#include<fstream>

using namespace std;

cv::Point2f point;
float quadrangle[4][2];
bool addRemovePt = false;
// ����ѭ����ǵ㣬ѭ���д���3ֱ�Ӷ�4ȡ��
int circ_flag = 0;

static void onMouse(int event, int x, int y, int /*flags*/, void* /*param*/)
{
    if (event == cv::EVENT_LBUTTONDOWN)
    {
        point = cv::Point2f((float)x, (float)y);
        cout << "Pixel location: " << x << ", " << y << endl;

        quadrangle[circ_flag][0] = x;
        quadrangle[circ_flag][1] = y;
        // ѭ����ʼǰȡһ����
        circ_flag %= 4;
        circ_flag++;
        addRemovePt = true;
    }
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
int main(int argc, char* argv[])
{
    std::ofstream fout;
    // ��ʼ��ȡ����ͷ
    cv::Mat figure = cv::imread(argv[1]);
    if (figure.empty()) return -1;

    cv::Mat marked_figure(figure);
    cv::TermCriteria termcrit(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, 20, 0.03);

    cv::namedWindow("marked_figure");
    cv::setMouseCallback("marked_figure", onMouse);

    for (;;)
    {
        cv::imshow("marked_figure", marked_figure);
        if (addRemovePt)
        {
            figure.copyTo(marked_figure);
            cv::circle(marked_figure, point, 3, cv::Scalar(0, 255, 0), -1, 8);
            addRemovePt = false;
        }

        char c = (char)cv::waitKey(10);
        if (c == 27) break;
    }

    cv::destroyWindow("marked_figure");

    //�켣�ļ��洢λ��
    fout.open("D:/C++/Pixel_Coordinate/cache.tsv");
    fout << "point.x" << "\t" << "point.y" << "\n";
    for (int i = 0; i < 4; i++) 
    {
        fout << quadrangle[i][0] << "\t" << quadrangle[i][1] << "\n";
    }
    fout.close();

    return 0;
}