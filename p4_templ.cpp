/*
 * 
 * */

#include "image_pr4.h" 
#include <thread>
#include <chrono>
#include <math.h>


using namespace std;
int red = 0;
int xC;
int yC;
int freq = 0.1;

int xT;
int yT;


int yCMax;
int xCMax;

int count;


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
				yC = row;
				xC = col;
				count++;
				
            }
        }
    }
}


struct Orbit {
	// logged position and time
	std::vector<int> x;
	std::vector<int> y;
	std::vector<int> t;
	int xc,yc,r;  // center and radius
	int x_sunrise,y_sunrise;
	double omega = 0.1;
} orbit;

void reset(int time) {
    if (xC == 0 || yC == 0) {
        cout << "Sun is hidden" << endl;
    } else {
        cout << xC << " " << yC << endl;
        orbit.t.push_back(time);
        orbit.x.push_back(xC);
        orbit.y.push_back(yC);
    }
}

void calculateOrbit(){
    double a11 = orbit.y.size();
    double a12 = 0;
    double a13 = 0;
    for (int i: orbit.t) {
        a13 += cos(freq * i);
    }

    double b1 = 0;
    for (int i: orbit.x) {
        b1 += i;
    }
    double b2 = 0;
    for (int i: orbit.y) {
        b2 += i;
    }
    double b3 = 0;
    for (int i: orbit.x) {
        b3 += i;
    }
    double temp = 0;
    for (int i: orbit.t) {
        temp += cos(freq * i);
    }
    b3 = b3 * temp;
    double temp2 = 0;
    temp = 0;
    for (int i: orbit.y) {
        temp += i;
    }
    for (int i: orbit.t) {
        temp2 += sin(freq * i);
    }
    b3 = b3 + (temp * temp2);

    double a21 = 0;
    double a22 = orbit.y.size();
    double a23 = 0;
    for (int i: orbit.t) {
        a23 += sin(freq * i);
    }
    double a31 = 0;
    for (int i: orbit.t) {
        a31 += cos(freq * i);
    }
    double a32 = 0;
    for (int i: orbit.t) {
        a32 += sin(freq * i);
    }
    double a33 = orbit.t.size();

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
			reset(time);
			calculateOrbit();
			move_aim(time);
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
   }

    return 0;
}

