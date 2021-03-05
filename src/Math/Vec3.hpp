#pragma once

#include <cmath>

class Vec3 {
	public:
		Vec3():
			x(0), y(0), z(0) {};
		Vec3(double x_, double y_, double z_):
			x(x_), y(y_), z(z_) {};

		inline Vec3 operator-() const;
		inline Vec3& operator+=(const Vec3 &v);
		inline Vec3& operator-=(const Vec3 &v);
		inline Vec3& operator*=(double t);
		inline Vec3& operator*=(const Vec3 &v);
		inline Vec3& operator/=(double t);

		inline Vec3 operator+(const Vec3 &v) const;
		inline Vec3 operator-(const Vec3 &v) const;
		inline Vec3 operator*(double t) const;
		inline Vec3 operator*(const Vec3 &v) const;
		inline Vec3 operator/(double t) const;

		double mag_sq() const;
		double mag() const;

		static Vec3 normalize(const Vec3 &v);
		static double dot(const Vec3 &a, const Vec3 &b);
		static Vec3 cross(const Vec3 &a, const Vec3 &b);
		static Vec3 lerp(const Vec3 &a, const Vec3 &b, double t);
		static Vec3 rotateX(const Vec3 &v, const Vec3 &o, double tx);
		static Vec3 rotateY(const Vec3 &v, const Vec3 &o, double ty);
		static Vec3 rotateZ(const Vec3 &v, const Vec3 &o, double tz);
		static Vec3 rotate(const Vec3 &v, const Vec3 &o, const Vec3 &t);

	public:
		double x;
		double y;
		double z;
};

inline Vec3 Vec3::operator-() const {
	return Vec3(-x, -y, -z);
}

inline Vec3& Vec3::operator+=(const Vec3 &v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

inline Vec3& Vec3::operator-=(const Vec3 &v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

inline Vec3& Vec3::operator*=(double t) {
	x *= t;
	y *= t;
	z *= t;
	return *this;
}

inline Vec3& Vec3::operator*=(const Vec3 &v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

inline Vec3& Vec3::operator/=(double t) {
	x /= t;
	y /= t;
	z /= t;
	return *this;
}

inline Vec3 Vec3::operator+(const Vec3 &v) const {
	return Vec3(x + v.x, y + v.y, z + v.z);
}

inline Vec3 Vec3::operator-(const Vec3 &v) const {
	return Vec3(x - v.x, y - v.y, z - v.z);
}

inline Vec3 Vec3::operator*(double t) const {
	return Vec3(x * t, y * t, z * t);
}

inline Vec3 Vec3::operator*(const Vec3 &v) const {
	return Vec3(x * v.x, y * v.y, z * v.z);
}

inline Vec3 Vec3::operator/(double t) const {
	return Vec3(x / t, y / t, z / t);
}

inline Vec3 operator*(double t, const Vec3 &v) {
	return v * t;
}

inline double Vec3::mag_sq() const {
	return x * x + y * y + z * z;
}

inline double Vec3::mag() const {
	return sqrt(mag_sq());
}

inline Vec3 Vec3::normalize(const Vec3 &v) {
	return v / v.mag();
}

inline double Vec3::dot(const Vec3 &a, const Vec3 &b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Vec3 Vec3::cross(const Vec3 &a, const Vec3 &b) {
	return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

inline Vec3 Vec3::lerp(const Vec3 &a, const Vec3 &b, double t) {
	return (1 - t) * a + t * b;
}

inline Vec3 Vec3::rotateX(const Vec3 &v, const Vec3 &o, double tx) {
	Vec3 rotated;
	Vec3 vo = v - o;
	rotated.x = vo.x;
	rotated.y = vo.y * cos(tx) + vo.z * sin(tx);
	rotated.z = vo.z * cos(tx) - vo.y * sin(tx);
	return rotated + o;
}

inline Vec3 Vec3::rotateY(const Vec3 &v, const Vec3 &o, double ty) {
	Vec3 rotated;
	Vec3 vo = v - o;
	rotated.x = vo.x * cos(ty) - vo.z * sin(ty);
	rotated.y = vo.y;
	rotated.z = vo.z * cos(ty) + vo.x * sin(ty);
	return rotated + o;
}

inline Vec3 Vec3::rotateZ(const Vec3 &v, const Vec3 &o, double tz) {
	Vec3 rotated;
	Vec3 vo = v - o;
	rotated.x = vo.x * cos(tz) - vo.y * sin(tz);
	rotated.y = vo.y * cos(tz) + vo.x * sin(tz);
	rotated.z = vo.z;
	return rotated + o;
}

inline Vec3 Vec3::rotate(const Vec3 &v, const Vec3 &o, const Vec3 &t) {
	return Vec3::rotateZ(Vec3::rotateY(Vec3::rotateX(v, o, t.x), o, t.y), o, t.z);
}