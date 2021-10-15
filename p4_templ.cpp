/*
 * 
 * */

#include "image_pr4.h" 
#include <thread>
#include <chrono>
#include <math.h>


using namespace std;
int red = 0;
int x;
int y;
int freq = 0.1;

int xc;
int yc;
int r;
int e;

double a11,a12,a13,a21,a22,a23,a31,a32,a33,b1,b2,b3;

int count = -1;
int crossx;
int crossy;

struct Orbit {
	// logged position and time
	std::vector<int> x;
	std::vector<int> y;
	std::vector<int> t;
	int xc,yc,r;  // center and radius
	int x_sunrise,y_sunrise;
	double omega = 0.1;
} orbit;


void locateSun() {
	int red;
	int green;
	int blue;
    for (int row = 0; row < image.height; ++row) {
        for (int col = 0; col < image.width; ++col) {
        	red= get_pixel(image, row, col, 0);
			green = get_pixel(image,row,col,1);
			blue = get_pixel(image,row,col,2);
            if(red / ((blue+green /2) + 1) > 2 ) {     
				y = row;
                count++;
                orbit.y.push_back(y);
                orbit.x.push_back(x);
                orbit.t.push_back(count);
				x = col;				
            }
        }
    }
}







double D[3][3] = {
    {a11,a12,a13},
    {a21,a22,a23},
    {a31,a32,a33}
};
double Dx[3][3] = {
    {b1,a12,a13},
    {b2,a22,a23},
    {b3,a32,a33}
};
double Dy[3][3] = {
    {a11,b1,a13},
    {a21,b2,a23},
    {a31,b3,a33}
};


void calculateOrbit(){
    a11 = orbit.x.size();
    a12 =0;
    for(int i =0; i < orbit.t.size(); i++){
        a13 +=cos(freq*orbit.t.at(i));
    }
    a21 = 0;
    a22 = orbit.x.size();
    for(int i =0; i<orbit.t.size(); i++){
        a23 += sin(freq*orbit.t.at(i));

    }
    for(int i =0; i<orbit.t.size();i++){
        a31+= cos(freq*orbit.t.at(i));
    }
    for(int i =0; i<orbit.t.size();i++){
        a32 += sin(freq*orbit.t.at(i));
    }
    double a33 = orbit.t.size();
    for(int i =0; i<orbit.x.size(); i++){
        b1 += orbit.x.at(i);
    }
    for(int i =0; i < orbit.t.size(); i++){
        b2 += orbit.y.at(i);
    }
    for (int i =0; i<orbit.x.size(); i++){
        b3 += orbit.x.at(i) * cos(orbit.omega*orbit.t.at(i) + (orbit.y.at(i) * sin(freq*orbit.t.at(i))));
    }

}
}




}

int main()
{        
	std::cout<<"start..."<<std::endl;
	init(1);
	double orbit;
	
    for ( int time = 0 ; time < 950; time++){
       draw_all(time); 
      std::cout<<"Time: " << time << endl;
      
      // your code here
            locateSun();
            cout << a33 << endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
   }

    return 0;
}

