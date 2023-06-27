# Linear Interpolation

Estimates a linear Interpolation from a given datasets (domain and range values)

## Design
[![Linear Interpolation recursive](https://www.johndcook.com/interp)](https://github.com/salvadorz/embedded_c_utils/tree/develop/src/lib/interpolation "I'm a Linear interpolation! duh...")
> Linear Interpolation

-------------
This library takes two arrays with information of the dataset (domain and range) and will receive a value within the domain range and calculare the range value either by performing a serch on the LUT or by performing a linear ineterpolation from the two closest points.

$$x{_{n-1}} < val < x{_n}$$

The interpolation is performed only within the domain values, if the value is outside of the domain range a saturated output will be provided.

> It's assumed both arrays has the same length.