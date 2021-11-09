//
//  ActivationFunction.hpp
//  eigen-sandbox
//
//  Created by Joshua Lynn on 10/24/21.
//

#ifndef ActivationFunction_h
#define ActivationFunction_h

#include "NeuralNetwork.hpp"

namespace ActivationFunction {

    Scalar activationFunction(Scalar x)
    {
        return tanhf(x);
    }

    Scalar activationFunctionDerivative(Scalar x)
    {
        return 1 - (tanhf(x) * tanhf(x));
    }
    // you can use your own code here!}
}

#endif /* ActivationFunction_h */
