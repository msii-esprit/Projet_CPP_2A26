   #ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include "Dataset.h"

#include "Weights.h"

Dataset read_csv(const char* filename);

float mean(float *y, int length);
float sum_of_square(float *y, int length);
float sum_residual(Dataset data, float *y_pred, int current_predictor);
float residual_sum_of_square(float *y_pred, float *y_true, int length);
int calculate_r2(float *y_pred, float *y_true, int length);
float mean_squared_error(float *y_pred, float *y_true, int length);

float intercept_sum(float *y_pred, float *y_true, int length);
float slope_sum(float *x, float *y_pred, float *y_true, int length);

#endif // UTILS_H_INCLUDED
