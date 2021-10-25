#include <fstream>
#include <iostream>
#include "functions.h"
#include <cmath>
#include <valarray>


using namespace std;


int main() {

    string file_name;
    cin >> file_name;
    double h;

    ifstream input(file_name);
    char *str = new char[1024];
    int l = -1;
    while (!input.eof()) {
        input.getline(str, 1024, '\n');
        l++;
    }
    input.close();

    ifstream file(file_name);
    Barrier Barriers[l];
    Vector2D V{};

    for (int i = 0; i < l; i++) {
        if (i == 0) {
            file >> h;

        } else if (i == 1) {
            file >> V.x >> V.y;
        } else {
            file >> Barriers[i-2].x >> Barriers[i-2].h;
        }
    }
    file.close();

    const double g = 9.81;
    Point Point{};
    Point.x = 0;
    Point.y = h;
    int cur_bar = -1;

    /*
    for (int q = 0; q<l-2; q++) {
        cout << "Barriers[" << q << "].x = " << Barriers[q].x << endl;
        cout << "Barriers[" << q << "].h = " << Barriers[q].h << endl;
    }

    cout << V.x << " " << V.y << endl;
    cout << h << endl;
    */




    double fall_time;
    bool flag = false;
    double x_fall;

    while (true) {
        if (flag) break;
        /*
        cout << "---------------" << endl;
        cout << "Point.x = " << Point.x << endl;
        cout << "Point.y = " << Point.y << endl;
        cout << "V.x = " << V.x << endl;
        cout << "V.y = " << V.y << endl;
         */

        double fall_time_1 = (V.y + sqrt(V.y*V.y+2*g*Point.y))/g;
        double fall_time_2 = (V.y - sqrt(V.y*V.y+2*g*Point.y))/g;
        //cout << fall_time_1 << " " << fall_time_2 << endl;

        if (fall_time_1 > fall_time_2) {
            fall_time = fall_time_1;
        } else fall_time = fall_time_2;

        //cout << "fall_time = " << fall_time << endl;
        int direction = V.x/abs(V.x);
        int m = cur_bar + direction;

        while (true) {
            double x = Barriers[m].x;
            double bar = Barriers[m].h;
            double t = (x - Point.x) / V.x;
            //cout << "m = " << m << endl;
            //cout << "t = " << t << endl;

            if (m < 0) {
                cout << 0 << endl;
                return 0;
            }
            if (m > l-3) {
                cout << l-2 << endl;
                return 0;
            }

            if (fall_time < t) {
                x_fall = Point.x + V.x*fall_time;
                //cout << "Шар упал в точке x = " << x_fall << endl;
                flag = true;
                break;
            }
            double y = Point.y + V.y * t - (g * t * t) / 2;
            //cout << "y = " << y << endl;
            //cout << "h = " << bar << endl;

            if (y >= bar) {
                //cout << "Перелет" << endl;
                m += direction;
                continue;
            } else {
                V.x = -V.x;
                V.y = V.y - g*t;
                Point.x = x;
                Point.y = y;
                //cout << "Попали в препятствие с m = " << m <<  endl;
                cur_bar = m;
                break;

            }
        }
    }

    if (x_fall < Barriers[0].x) cout << 0;


    for (int n = 0; n < l-2; n++) {
        if (x_fall > Barriers[n].x and x_fall < Barriers[n+1].x){
            cout << n+1;
        }
    }


}