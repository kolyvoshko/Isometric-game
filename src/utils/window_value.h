/**
  * @file window_value.h
  */

#ifndef WINDOWVALUE_H
#define WINDOWVALUE_H

#include "SFML/System.hpp"

namespace ut
{
    class WindowValue
    {
    private:
        double _min, _max;
        double _value;

    public:
        WindowValue();
        WindowValue(double min, double max);

        double get();
        void set(double value);

        WindowValue operator +=(double value);
        WindowValue operator -=(double value);
        WindowValue operator *=(double value);
        WindowValue operator /=(double value);
    };
}


#endif // WINDOWVALUE_H
