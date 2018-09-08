/*
MIT License
Copyright (c) 2018 fuzun
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef VECTOR_H
#define VECTOR_H

template<class T>
struct Vector2
{
    T x;
    T y;

    inline Vector2(void)
    {
        reset();
    }

    inline Vector2(T x_, T y_)
    {
        x = x_;
        y = y_;
    }

    inline Vector2(const Vector2 &vector2)
    {
        x = vector2.x;
        y = vector2.y;
    }

    inline Vector2 makeVector2(T x_, T y_)
    {
        Vector2 vector2;
        vector2.x = x_;
        vector2.y = y_;
        return vector2;
    }

    inline Vector2 *makeVector2Temporary(T x_, T y_)
    {
        static Vector2 *vector2 = new Vector2(x_, y_);
        return vector2;
    }

    inline Vector2 operator + (const Vector2 &vector2)
    {
        Vector2 vector2_;
        vector2_.x = x + vector2.x;
        vector2_.y = y + vector2.y;
        return vector2_;
    }

    inline Vector2 operator - (const Vector2 &vector2)
    {
        Vector2 vector2_;
        vector2_.x = x - vector2.x;
        vector2_.y = y - vector2.y;
        return vector2_;
    }

    inline int operator * (const Vector2 &vector2)
    {
        int result;
        result = (x * vector2.x) + (y * vector2.y);
        return result;
    }

    inline Vector2& operator = (const Vector2 &vector2)
    {
        if(this != &vector2)
        {
            x = vector2.x;
            y = vector2.y;
        }
        return *this;
    }

    inline bool operator == (const Vector2 &vector2)
    {
        if(x == vector2.x && y == vector2.y)
            return true;
        else
            return false;
    }

    inline bool operator != (const Vector2 &vector2)
    {
        return !(*this == vector2);
    }

    inline int dotProduct(const Vector2 &vector2)
    {
        return (*this * vector2);
    }

    inline static int dotProduct(const Vector2 &vector2_1, const Vector2 &vector2_2)
    {
        return (vector2_1 * vector2_2);
    }

    inline void reset(void)
    {
        x = (T)0;
        y = (T)0;
    }

    inline static void reset(Vector2 &vector2)
    {
        vector2.x = (T)0;
        vector2.y = (T)0;
    }
};

#endif // VECTOR_H
