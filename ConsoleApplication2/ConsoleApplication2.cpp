#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;


void solveLinearSystem(double A[][2], double b[], double x[], int n) {
    for (int i = 0; i < n; i++) {
        int maxRow = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(A[j][i]) > abs(A[maxRow][i]))
                maxRow = j;
        }
        swap(A[i], A[maxRow]);
        swap(b[i], b[maxRow]);

        for (int j = i + 1; j < n; j++) {
            double ratio = A[j][i] / A[i][i];
            for (int k = i; k < n; k++) {
                A[j][k] -= ratio * A[i][k];
            }
            b[j] -= ratio * b[i];
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / A[i][i];
    }
}

int main() {
    setlocale(LC_ALL, "rus");
 
    double s[] = { 1, 2.5, 5, 7.5, 10, 12.5, 15, 17.5, 20 };
    double V[] = { 1.11, 1.57, 2.26, 2.84, 3.25, 3.75, 4.05, 4.45, 4.75 };
    int n = sizeof(s) / sizeof(s[0]);

    
    double sum_s = 0, sum_s2 = 0, sum_V = 0, sum_sV = 0;
    for (int i = 0; i < n; i++) {
        sum_s += s[i];
        sum_s2 += s[i] * s[i];
        sum_V += V[i];
        sum_sV += s[i] * V[i];
    }

    double a = (n * sum_sV - sum_s * sum_V) / (n * sum_s2 - sum_s * sum_s);
    double b = (sum_V - a * sum_s) / n;


    double sum_dV2 = 0, sum_V2 = 0;
    for (int i = 0; i < n; i++) {
        double dV = V[i] - (a * s[i] + b);
        sum_dV2 += dV * dV;
        sum_V2 += V[i] * V[i];
    }

    double correlation = sqrt(1 - sum_dV2 / sum_V2);

    
    double A[2][2] = { {0, 0}, {0, 0} };
    double b_fit[2] = { 0, 0 };
    double x_fit[2] = { 0, 0 };

    for (int i = 0; i < n; i++) {
        A[0][0] += s[i] * s[i];
        A[0][1] += s[i] * exp(s[i]);
        A[1][0] += s[i] * exp(s[i]);
        A[1][1] += exp(2 * s[i]);
        b_fit[0] += V[i] * s[i];
        b_fit[1] += V[i] * exp(s[i]);
    }

    solveLinearSystem(A, b_fit, x_fit, 2);

    double b_fit0 = x_fit[0];
    double C = x_fit[1];

  
    double sum_dV2_fit = 0;
    for (int i = 0; i < n; i++) {
        double dV_fit = V[i] - (b_fit0 * pow(s[i], b_fit0) * exp(C * s[i]));
        sum_dV2_fit += dV_fit * dV_fit;
    }

  
    ofstream dataFile("data.txt");
    for (int i = 0; i < n; i++) {
        dataFile << s[i] << " " << V[i] << endl;
    }
    dataFile.close();

  
    cout << "Regression line equation: V(s) = " << a << "*s + " << b << endl;
    cout << "Correlation coefficient: " << correlation << endl;
    cout << "Total mean square error (regression line): " << sum_dV2 << endl;
    cout << "Mean error (regression line): " << sqrt(sum_dV2 / n) << endl;
    cout << "Fitted dependence equation: V(s) = " << b_fit0 << " * s^" << b_fit0 << " * exp(" << C << " * s)" << endl;
    cout << "Total mean square error (fitted dependence): " << sum_dV2_fit << endl;
    cout << "Mean error (fitted dependence): " << sqrt(sum_dV2_fit / n) << endl;

    ofstream scriptFile("script.plt");
    scriptFile << "set title 'Experimental Data'\n";
    scriptFile << "set xlabel 's'\n";
    scriptFile << "set ylabel 'V'\n";
    scriptFile << "plot 'data.txt' with linespoints title 'Experimental Data', \\" << endl;
    scriptFile << "     " << a << "*x + " << b << " title 'Regression Line', \\" << endl;
    scriptFile << "     x**" << b_fit0 << "*exp(" << C << "*x) title 'Fitted Curve'\n";
    scriptFile << "pause -1 'Press any key to exit'\n";
    scriptFile.close();

 
    system("gnuplot script.plt");

    return 0;
}
