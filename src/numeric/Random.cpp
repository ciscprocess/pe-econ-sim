//
// Created by Nathan on 8/1/2015.
//

#include <time.h>
#include "numeric/Random.h"
#include <chrono>
namespace undocked {
    namespace numeric {
        using namespace boost::random;

        Random::Random() : rng(std::chrono::high_resolution_clock::now().time_since_epoch().count()),
        uniform(0, 100), uniformReal(0, 100),
        normalized(0, 1) {

        }

        Random::Random(uint32_t t) : rng(t),
                                     uniform(0, 100), uniformReal(0, 100),
                                     normalized(0, 1) {

        }

        double Random::get() {
            return normalized(rng);
        }

        void Random::setUniform(double lowerBound, double upperBound) {
            uniform.param(uniform_int_distribution<int>::param_type((int)lowerBound, (int)upperBound));
            uniformReal.param(uniform_real_distribution<double>::param_type(lowerBound, upperBound));
        }

        int Random::getUniformInteger() {
            return uniform(rng);
        }

        double Random::getUniformDouble() {
            return uniformReal(rng);
        }
    }
}