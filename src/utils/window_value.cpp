/**
  * @file window_value.cpp
  */

#include <cmath>
#include "SFML/System.hpp"

#include "window_value.h"


ut::WindowValue::WindowValue()
{
    _min = 0.0;
    _max = 1.0;
}


ut::WindowValue::WindowValue(double min, double max)
{
    _min = min;
    _max = max;
}


double ut::WindowValue::get()
{
    return _value;
}


void ut::WindowValue::set(double value)
{
    _value = value;

    if (_value > _max)
        _value = _max;

    if (_value < _min)
        _value = _min;
}


ut::WindowValue ut::WindowValue::operator *=(double value){
    _value *= value;

    if (_value > _max)
        _value = _max;

    if (_value < _min)
        _value = _min;

    return *this;
}


ut::WindowValue ut::WindowValue::operator +=(double value){
    _value += value;

    if (_value > _max)
        _value = _max;

    if (_value < _min)
        _value = _min;

    return *this;
}


ut::WindowValue ut::WindowValue::operator -=(double value){
    _value -= value;

    if (_value > _max)
        _value = _max;

    if (_value < _min)
        _value = _min;

    return *this;
}


ut::WindowValue ut::WindowValue::operator /=(double value){
    _value /= value;

    if (_value > _max)
        _value = _max;

    if (_value < _min)
        _value = _min;

    return *this;
}
