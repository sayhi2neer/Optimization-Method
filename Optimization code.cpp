#include <bits/stdc++.h>
#include <cmath>
using namespace std;

double objective_function(double x);

pair<double, double> Bounding_Phase(double a, double b, bool minimize);
void Interval_Halving(double a, double b);
int c, funcNum;
fstream out;


int main() {
    double a, b;       
    pair<double, double> result;
    cout << "Enter\n a = lower limit of x\n b = upper limit of x\n Enter 1 to minimize :\n";
    cin >> a >> b >> c;

    /*Calling Bounding Phase Method*/
    result = (c == 1) ? Bounding_Phase(a, b, true) : Bounding_Phase(a, b, false);

    /*Calling Interval Halving Method*/
    a = result.first; b = result.second;
    Interval_Halving(a, b);

    return 0;
}

/*Objective Function*/
double objective_function(double x) {
    // return -1*(pow((2*x-5),4)-pow((x*x-1),3));               //(-10,0)
    // return -1*(8+pow(x,3)-2*x-2*exp(x));                     //(-2,1)
    // return -1*(4*x*sin(x));                                  //(0.5,3.14)
    // return 2*pow((x-3),2)+exp(0.5*x*x);                      //(-2,3)
    // return x*x-10*exp(0.1*x);                                //(-6,6)
    // return 20*sin(x)-15*x*x;                                 //(-4,4)
    
        return x*x+54/x;                                         //(0,5)
    
}

void Interval_Halving (double a, double b) {
    out.open("Iterations.out", ios::app);
    out << ("\n**********************************\n");
	out << ("Interval Halving Method\n");
    out << "#It\t\tx1\t\t\tx_m\t\t\tx2\t\t\tf(x1)\t\t\tf(x_m)\t\t\tf(x2)\n";

    /* Step 1: */
    double epsilon = 0.0001;
    double l = b-a;
    double x_m;
    int feval = 0; /*function evaluation*/
    int k = 0;

    double f_xm;
	
    double x1, x2, f1, f2;

	/* Step 2*/
    Step_2:
    x_m = (a+b)/2; /*New point*/
    f_xm = objective_function(x_m); /*Calculate objective_function*/
    feval++;

    x1 = a+(l/4); x2 = b-(l/4); /*New points*/
    f1 = objective_function(x1); /*Calculate objective_function*/
    f2 = objective_function(x2);
    feval = feval + 2;

    /*Copying values to file*/
    out << setprecision(5) << k << "\t\t" << setprecision(5) << x1 << "\t\t" << setprecision(5) << x_m << "\t\t" << setprecision(5) << x2 << "\t\t" 
        << setprecision(5) << f1 << "\t\t\t" << setprecision(5) << f_xm << "\t\t\t" << setprecision(5) << f2 << "\n";

    /* Step 3*/
    if (f1 > f_xm) {
        a = x1;
    }
    if (f2 > f_xm) {
        b = x2;
    }
    l = b-a;

    /*Step 4*/
    if (l > epsilon) {
        k++;
        goto Step_2;  
    }
    else {
        cout << ("\n**********************************\n");
        cout << " From Interval_Halving Method Minimum lies between (" << a << ", " << b << ")" << endl;
        cout << "Total number of function evaluations: " << feval << endl;

        /*Copying final results to file*/
        out << ("\n**********************************\n");
        out << "From Interval_Halving Method Minimum lies between (" << a << ", " << b << ")" << endl;
        out << "Total number of function evaluations: " << feval << endl;
    }
    out.close();
}

pair<double, double> Bounding_Phase (double a, double b, bool minimize) {
    out.open("Iterations.out", ios::out);
    out << ("\n**********************************\n");
	out << ("Bounding Phase Method\n");
    out << "#It\t\tx_(k-1)\t\tx_(k)\t\tx_(k+1)\t\tf(x_(k-1))\t\tf(x_(k))\t\tf(x_(k+1))\n";

    /* Step 1: */
    uniform_real_distribution<double> unif(a, b);
    default_random_engine re;
    
    double initial_guess = unif(re);  /* Getting a random double value between a and b*/
    double delta;
    int k = 0;
	
	cout << ("\n**********************************\n");
	cout << ("Bounding Phase Method\n");
	cout << ("Enter 'delta':\t");
    cin >> delta;


    /* Step 2: */
    double x1, x2, x3, f1, f2, f3;
    int feval;
    delta = fabs(delta);

    x2 = initial_guess; x1 = x2 - delta; x3 = x2 + delta; /*New points*/
	feval = 0; /*function evaluation*/
	f1 = objective_function(x1); /*Calculate objective_function*/
	f2 = objective_function(x2);
	f3 = objective_function(x3);

	feval = feval + 3;

    if (minimize) {
        if (f1 >= f2 && f2 >= f3) {
            delta = delta;
        }
        else {
            delta = -delta;
        }
    }
    else {
        if (f1 >= f2 && f2 >= f3) {
            delta = -delta;
        }
        else {
            delta = delta;
        }
    }

    double x_k = x2, x_k1, x_k0 = x2; 
    double f_k = f2, f_k1, f_k0 = f2;


    /* Step 3: */
    Step_3:
	x_k1 = x_k + (pow(2, k) * delta);
    f_k1 = objective_function(x_k1);
    feval++;
    
    /*Copying values to file*/
    out << setprecision(5) << k << "\t\t" << setprecision(5) << x_k0 << "\t\t" << setprecision(5) << x_k << "\t\t" << setprecision(5) << x_k1 << "\t\t" 
        << setprecision(5) << f_k0 << "\t\t\t" << setprecision(5) << f_k << "\t\t\t" << setprecision(5) << f_k1 << "\n";


    /* Step 4: */

    /*Termination Condition for minimization problem*/
    if(minimize) {
        if(f_k1 < f_k) {              /*If not terminated update the value of 'x' and f(x). Go to Step 3*/
            k = k + 1;
            x_k0 = x_k; x_k = x_k1;   
            f_k0 = f_k; f_k = f_k1;   
            goto Step_3;
        }
        else {
            cout << ("\n**********************************\n");
            cout << "From Bounding_Phase Method Minimum lies between (" << x_k0 << ", " << x_k1 << ")" << endl;
            cout << "Total number of function evaluations: " << feval << endl;

            /*Copying final results to file*/
            out << ("\n**********************************\n");
            out << " From Bounding_Phase Method Minimum lies between (" << x_k0 << ", " << x_k1 << ")" << endl;
            out << "Total number of function evaluations: " << feval << endl;
        }
    }

    /*Termination Condition for minimization problem*/
    else {
        if(f_k1 > f_k) {              /*If not terminated update the value of 'x' and f(x). Go to Step 3*/
            k = k + 1;
            x_k0 = x_k; x_k = x_k1;   
            f_k0 = f_k; f_k = f_k1;   
            goto Step_3;
        }
        else {
            cout << ("\n**********************************\n");
            cout << "Maximum lies between (" << x_k0 << ", " << x_k1 << ")" << endl;
            cout << "Total number of function evaluations: " << feval << endl;

            /*Copying final results to file*/
            out << ("\n**********************************\n");
            out << "Maximum lies between (" << x_k0 << ", " << x_k1 << ")" << endl;
            out << "Total number of function evaluations: " << feval << endl;
        }
    }  
    out.close();
    return make_pair(x_k0, x_k1);
}