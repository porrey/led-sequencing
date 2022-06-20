/*
 * The MIT License (MIT)
 * 
 * Copyright © 2022 Daniel Porrey
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 * and associated documentation files (the “Software”), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial 
 * portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "Math.h"

double Math::Max(double a, double b)
{
  double returnValue = a;

  if (a > b)
  {
    returnValue = a;
  }
  else
  {
    returnValue = b;
  }

  return returnValue;
}

double Math::Min(double a, double b)
{
  double returnValue = a;

  if (a < b)
  {
    returnValue = a;
  }
  else
  {
    returnValue = b;
  }

  return returnValue;
}

double Math::Modulo(double a, double b)
{
  return a - (b * ((int)(a / b)));
}

double Math::Abs(double a)
{
  double returnValue = a;

  if (a < 0)
  {
    returnValue = a * -1;
  }

  return returnValue;
}
