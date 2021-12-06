#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3
{
public:
    float e[3];
public:
    vec3() : e{0.0f, 0.0f, 0.0f} {}
    vec3(float x, float y, float z) : e{x, y, z} {}
    // Getters
    float x() const { return e[0]; }
    float y() const { return e[1]; }
    float z() const { return e[2]; }
    // Operator overloads
    vec3 operator-() const { return vec3(-x(), -y(), -z()); }
    float operator[](int i) const { return e[i]; }
    float& operator[](int i) {return e[i]; }
    vec3 operator+=(const vec3& v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }
    vec3 operator*=(const float t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }
    vec3 operator/=(const float t)
    {
        return *this *= (1 / t);
    }
    double length_squared() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }
    double length() const
    {
        return sqrt(length_squared());
    }
};

typedef vec3 Point3;
typedef vec3 Color;

inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v)
{
    return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline vec3 operator-(const vec3& u, const vec3& v)
{
    return u + (-v);
}

inline vec3 operator*(const vec3& u, const vec3& v)
{
    return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline vec3 operator*(const vec3& v, float t)
{
    return vec3(v.x() * t, v.y() * t, v.z() * t);
}

inline vec3 operator*(float t, const vec3& v)
{
    return v * t;
}

inline vec3 operator/(const vec3& v, float t)
{
    return v * (1 / t);
}

inline float dot(const vec3& u, const vec3& v)
{
    return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

inline vec3 cross(const vec3& u, const vec3& v)
{
    return vec3(u.y() * v.z() - u.z() * v.y(),
                u.z() * v.x() - u.x() * v.z(),
                u.x() * v.y() - u.y() * v.x());
}

inline vec3 unit_vector(const vec3& v)
{
    return v / v.length();
}
#endif