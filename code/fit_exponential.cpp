#include "fit_exponential.hpp"

void fit_exponential(std::vector<double> &x, std::vector<double> &y, double &exponent_coefficient, double &coefficient){ 

    /*
	SYSTEM OF EQUATIONS for curve fitting.
    y = a*exp(b*x)  ---> log(y) = b*x + log(a)
    Independent term: x
	Dependent term: y
	*/

	int n_elements = static_cast<int>(x.size());

    //Create and fill the vector with the logarithm of x and y respectively
	std::vector<double> y_log(n_elements, 0.0);
	for (int i = 0; i < n_elements; i++) {
		y_log[i] = std::log(y[i]);
    }
    
    /*
	EQUATION SYSTEM: 
    |sum_x^2    sum_x|   |   b  |   |sum_(x*y)|
    |                | * |      | = |         |
    |sum_x    sum_x^0|   |log(a)|   |  sum_y  |
	*/
        
    //Coefficient definition
    double a_12 = std::accumulate(x.begin(), x.end(), 0.0); // a_12 = a_21
    double a_22 = static_cast<double>(n_elements);
    double b_2 = std::accumulate(y_log.begin(), y_log.end(), 0.0);
	
	double a_11 = 0.0;
	double b_1 = 0.0;
    for (int i = 0; i < n_elements; i++) {
        a_11 += x[i] * x[i];
		b_1 += y_log[i] * x[i];
    }

    //Solution of the system (Cramer's Method)
    double s_D = a_11*a_22 - a_12*a_12; // System determinant
    double x1_D = b_1*a_22 - b_2*a_12 ; // b determinant solution
    double x2_D = b_2*a_11 - b_1*a_12 ; // log(a) determinant solution

    exponent_coefficient = x1_D/s_D;
    coefficient = std::exp(x2_D/s_D);
}