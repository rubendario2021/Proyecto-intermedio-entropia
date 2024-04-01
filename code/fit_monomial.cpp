#include "fit_monomial.hpp"

void fit_monomial(std::vector<double> &x, std::vector<double> &y, double &exponent, double &coefficient){ 

    /*
	SYSTEM OF EQUATIONS for curve fitting.
    y = a*x^(b)  ---> ln(y) = ln(a) + b * ln(x)
    Independent term: x
	Dependent term: y
	*/

	int n_elements = static_cast<int>(x.size());

    //Create and fill the vector with the logarithm of x and y respectively
    std::vector<double> x_log(n_elements, 0.0);
	std::vector<double> y_log(n_elements, 0.0);
	for (int i = 0; i < n_elements; i++) {
        x_log[i] += std::log(x[i]);
		y_log[i] += std::log(y[i]);
    }
    
    /*
	EQUATION SYSTEM: 
    |sum_x^2    sum_x|   |  b  |   |sum_(x*y)|
    |                | * |     | = |         |
    |sum_x    sum_x^0|   |ln(a)|   |  sum_y  |
	*/
        
    //Coefficient definition
    double a_12 = std::accumulate(x_log.begin(), x_log.end(), 0.0); // a_12 = a_21
    double a_22 = static_cast<double>(n_elements);
    double b_2 = std::accumulate(y_log.begin(), y_log.end(), 0.0);
	
	double a_11 = 0.0;
	double b_1 = 0.0;
    for (int i = 0; i < n_elements; i++) {
        a_11 += x_log[i] * x_log[i];
		b_1 += y_log[i] * x_log[i];
    }

    //Solution of the system (Cramer's Method)
    double s_D = a_11*a_22 - a_12*a_12; // System determinant
    double x1_D = b_1*a_22 - b_2*a_12 ; // b determinant solution
    double x2_D = b_2*a_11 - b_1*a_12 ; // ln(a) determinant solution

    exponent = x1_D/s_D;
    coefficient = std::exp(x2_D/s_D);
}