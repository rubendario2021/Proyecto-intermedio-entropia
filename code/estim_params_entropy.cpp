#include "estim_params_entropy.hpp"

void estim_paramas_entropy(std::vector<int> &entropy, int &values_saved, int &save_step, double &exponent, double &coefficient){ 

    //SYSTEM OF EQUATIONS for curve fitting.
        // y = a*x^(b)  ---> ln(y) = ln(a) + b * ln(x)
        //Independent term: Time
        //Dependent term: Entropy / rmsd

    //Create and fill the vector with the logarithm of time discretizations
    std::vector<double> time_log(values_saved, 0.0);
    for (int i = 0; i < values_saved; i++) {
        time_log[i] = std::log(save_step*(i+1)); // Each element is a multiple of save_step
    }

    //Creation of the vector for the logarithm values of entropy
    std::vector<double> entropy_log(values_saved, 0.0);
    for (int i = 0; i < values_saved; i++) {
        entropy_log[i] = std::log(entropy[i]); // Each element is a multiple of save_step
    }

    /* EQUATION SYSTEM: 
    |sum_x^2    sum_x|   |  b  |   |sum_(x*y)|
    |                | * |     | = |         |
    |sum_x    sum_x^0|   |ln(a)|   |  sum_y  | */
        
    //Coefficient definition
    double a_12 = std::accumulate(time_log.begin(), time_log.end(), 0); // a_12 = a_21
    double a_22 = static_cast<double>(values_saved);
    double a_11 = 0.0;
    for (int i = 0; i < values_saved; i++) {
        a_11 = a_11 + time_log[i] * time_log[i];
    }
    double b_1 = 0.0;
    for (int i = 0; i < values_saved; i++) {
        b_1 = b_1 + entropy_log[i] * time_log[i];
    }
    double b_2 = std::accumulate(entropy_log.begin(), entropy_log.end(), 0);


    //Solution of the system (Cramer's Method)
    double s_D = a_11*a_22 - a_12*a_12; //System determinant
    double x1_D = b_1*a_22 - b_2*a_12 ; //b determinant solution
    double x2_D = b_2*a_11 - b_1*a_12 ; //ln/a) determinant solution

    exponent = x1_D/s_D;
    coefficient = std::exp(x2_D/s_D);

}