#include <iostream>
#include <vector>
#include <complex>
#include <map>
#include <ctime>
#include <fstream>
#include "Polynomial.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;

vector <complex <double>> get_roots(int power)
{
    const double pi = 3.14159265358979323846;
    int counter;
    vector <complex <double>> roots(power);
    for (counter = 0; counter < power; counter += 1)
    {
        roots[counter] = exp(1i * ((counter) * 2 * pi / power));
    }
    return roots;
}

int newton(complex <double> c, double epsilon, int max_iter)
{
    complex <double> xn = c;
    /*complex<double> power = 1i;*/
    //double a = -0.5;
    for (int counter = 0; counter < max_iter; counter++)
    {
        complex <double> pxn = pow(xn, 3) - 1.0;
        if (abs(pxn) < epsilon) {
            return counter;
        }
        complex <double> dpxn = 3.0 * pow(xn, 2);

        complex <double> zero = 0;
        if (dpxn == zero) {
            return 0;
        }
        else {
            xn = xn - (pxn / dpxn);
        }
    }  
    return 255;
}


void drawing_for_root()
{
    const map <string, vector <int>> quality
    {
        {"480p", {480, 854}},
        {"720p", {720, 1280}},
        {"1080p", {1080, 1920}},
        {"4K", {2160, 3840}},
        {"8K", {4320, 7680}},
        {"16K", {8640, 15360}}
    };

    string resolution;
    std::cout << "Enter the required resolution" << endl;
    std::cin >> resolution;
    //int power;
    //std::cout << "Enter the power of a polynomial" << endl;
    //cin >> power;
    std::cout << "Enter the width" << endl;
    double border_y;
    std::cin >> border_y;
    double border_x = border_y * 16 / 9;
    int qual1 = quality[resolution][0]; //height
    int qual2 = quality[resolution][1]; //width

    //Polynomial  p{ power - 1, get_roots(power) , get_roots(power), true };
    //Polynomial dp = p.derivative();
    double epsilon = 1e-10;
    int max_iter = 255;
    vector <complex <double>> complex_plane;
    double dx = border_x / qual2;
    double dy = border_y / qual1;
    double x, y;
    int maximum = 0;
    int minimum = 100;
    cv::Mat gradient = cv::imread("(./gradient.png)");
    std::cout << "Doing some math...." << endl;
    string path = R"(./fractals/)";
    string name = path + resolution + "_newton_3" + ".png";
    cv::UMat img(qual1, qual2, CV_8UC3);
    int previous_percent = -1;
    int percent = 0;
    cv::parallel_for_(cv::Range(0, qual1), [&](const cv::Range& range)
    {
            for (int y_point = range.start; y_point < range.end; y_point++)
            {
                for (int x_point = 0; x_point <= qual2; x_point++) 
                {
                    x = - border_x / 2 + x_point * dx;
                    y = - border_y / 2 + y_point * dy;
                    unsigned char dot = newton(x + y * 1i, epsilon, max_iter);
                    cv::Point pt(x_point, y_point);
                    cv::Scalar color = gradient.at<cv::Vec3b>(0, dot);
                    //img.at<cv::Vec3b>(pt) = color;
                    cv::circle(img, pt, 0.25, color, 1);
                    
                } 
            }

    });
    cv::imwrite(name, img);

}


int main()
{
    drawing_for_root();
    double end_time = clock();
    std::cout << "done\n";
    return 0;
}


