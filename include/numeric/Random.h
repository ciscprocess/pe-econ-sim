//
// Created by Nathan on 8/1/2015.
//

#ifndef PE_ECON_SIM_RANDOM_H
#define PE_ECON_SIM_RANDOM_H

#include "boost/random.hpp"

namespace undocked {
    namespace numeric {
        class Random {
        public:
            Random();
            Random(uint32_t);
            double get();
            int getUniformInteger();
            double getUniformDouble();
            void setUniform(double lowerBound, double upperBound);

            std::function<double ()> createUniformDouble(double lowerBound, double upperBound) {
                boost::random::uniform_real_distribution<double> gen(lowerBound, upperBound);
                return [=]() { return gen(rng); };
            }

            std::function<int ()> createUniformInteger(int lowerBound, int upperBound) {
                boost::random::uniform_int_distribution<int> gen(lowerBound, upperBound);
                return [=]() { return gen(rng); };
            }

        private:
            boost::random::mt19937 rng;
            boost::random::uniform_int_distribution<int> uniform;
            boost::random::uniform_real_distribution<double> normalized;
            boost::random::uniform_real_distribution<double> uniformReal;
        };
    }
}

#endif //PE_ECON_SIM_RANDOM_H
