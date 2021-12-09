#ifndef WEIGHTS_H_INCLUDED
#define WEIGHTS_H_INCLUDED

#include "Dataset.h"

class Weights{
    private:
        int MAX_WEIGHTS;

    public:
        float* values;
        int number_weights;

        Weights();
        void init(int number_predictor, int random_init);
        ~Weights();
        void update(Dataset data, float *y_pred, float learning_rate);
};


#endif // WEIGHTS_H_INCLUDED
