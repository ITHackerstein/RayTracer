#pragma once

#include <cmath>
#include <iostream>
#include <assert.h>
#include "../Utils/Random.hpp"

class Vec3 {
	public:
		Vec3():
			e{0, 0, 0} {}
		Vec3(double x, double y, double z):
			e{x, y, z} {}

		double x() const { return e[0]; }
		double y() const { return e[1]; }
		double z() const { return e[2]; }

		inline Vec3 operator-() const;
		inline Vec3& operator+=(const Vec3 &v);
		inline Vec3& operator-=(const Vec3 &v);
		inline Vec3& operator*=(double t);
		inline Vec3& operator*=(const Vec3 &v);
		inline Vec3& operator/=(double t);
		inline friend std::ostream& operator<<(std::ostream& os, const Vec3& v);

		inline Vec3 operator+(const Vec3 &v) const;
		inline Vec3 operator-(const Vec3 &v) const;
		inline Vec3 operator*(double t) const;
		inline Vec3 operator*(const Vec3 &v) const;
		inline Vec3 operator/(double t) const;
		inline double operator[](size_t idx) const;

		double mag_sq() const;
		double mag() const;
		bool near_zero() const;

		static Vec3 normalize(const Vec3 &v);
		static double dot(const Vec3 &a, const Vec3 &b);
		static Vec3 cross(const Vec3 &a, const Vec3 &b);
		static Vec3 lerp(const Vec3 &a, const Vec3 &b, double t);
		static Vec3 rotateX(const Vec3 &v, const Vec3 &o, double tx);
		static Vec3 rotateY(const Vec3 &v, const Vec3 &o, double ty);
		static Vec3 rotateZ(const Vec3 &v, const Vec3 &o, double tz);
		static Vec3 rotate(const Vec3 &v, const Vec3 &o, const Vec3 &t);
		static Vec3 random();
		static Vec3 random(double min, double max);
		static Vec3 random_in_unit_sphere();
		static Vec3 random_in_hemisphere(const Vec3& n);
		static Vec3 random_in_unit_disk();
		static Vec3 random_unit_vector();
		static Vec3 reflect(const Vec3& v, const Vec3& n);
		static Vec3 refract(const Vec3& v, const Vec3& n, double refractionRatio);

	public:
		double e[3];
};

inline Vec3 Vec3::operator-() const {
	return Vec3(-e[0], -e[1], -e[2]);
}

inline Vec3& Vec3::operator+=(const Vec3 &v) {
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
}

inline Vec3& Vec3::operator-=(const Vec3 &v) {
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	e[2] -= v.e[2];
	return *this;
}

inline Vec3& Vec3::operator*=(double t) {
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

inline Vec3& Vec3::operator*=(const Vec3 &v) {
	e[0] *= v.e[0];
	e[1] *= v.e[1];
	e[2] *= v.e[2];
	return *this;
}

inline Vec3& Vec3::operator/=(double t) {
	e[0] /= t;
	e[1] /= t;
	e[2] /= t;
	return *this;
}

inline std::ostream& operator<<(std::ostream& os, const Vec3& v) {
	os << "[ " << v.e[0] << ", " << v.e[1] <<  ", " << v.e[2] << " ]";
	return os;
}

inline Vec3 Vec3::operator+(const Vec3 &v) const {
	return Vec3(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]);
}

inline Vec3 Vec3::operator-(const Vec3 &v) const {
	return Vec3(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]);
}

inline Vec3 Vec3::operator*(double t) const {
	return Vec3(e[0] * t, e[1] * t, e[2] * t);
}

inline Vec3 Vec3::operator*(const Vec3 &v) const {
	return Vec3(e[0] * v.e[0], e[1] * v.e[1], e[2] * v.e[2]);
}

inline Vec3 Vec3::operator/(double t) const {
	return Vec3(e[0] / t, e[1] / t, e[2] / t);
}

inline double Vec3::operator[](size_t idx) const {
	return e[idx];
}

inline Vec3 operator*(double t, const Vec3 &v) {
	return v * t;
}

inline double Vec3::mag_sq() const {
	return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

inline double Vec3::mag() const {
	return sqrt(mag_sq());
}

inline bool Vec3::near_zero() const {
	return fabs(e[0]) < 1e-8 && fabs(e[1]) < 1e-8 && fabs(e[2]) < 1e-9;
}

inline Vec3 Vec3::normalize(const Vec3 &v) {
	return v / v.mag();
}

inline double Vec3::dot(const Vec3 &a, const Vec3 &b) {
	return a.e[0] * b.e[0] + a.e[1] * b.e[1] + a.e[2] * b.e[2];
}

inline Vec3 Vec3::cross(const Vec3 &a, const Vec3 &b) {
	return Vec3(a.e[1] * b.e[2] - a.e[2] * b.e[1], a.e[2] * b.e[0] - a.e[0] * b.e[2], a.e[0] * b.e[1] - a.e[1] * b.e[0]);
}

inline Vec3 Vec3::lerp(const Vec3 &a, const Vec3 &b, double t) {
	return (1 - t) * a + t * b;
}

inline Vec3 Vec3::rotateX(const Vec3 &v, const Vec3 &o, double tx) {
	Vec3 rotated;
	Vec3 vo = v - o;
	rotated.e[0] = vo.e[0];
	rotated.e[1] = vo.e[1] * cos(tx) + vo.e[2] * sin(tx);
	rotated.e[2] = vo.e[2] * cos(tx) - vo.e[1] * sin(tx);
	return rotated + o;
}

inline Vec3 Vec3::rotateY(const Vec3 &v, const Vec3 &o, double ty) {
	Vec3 rotated;
	Vec3 vo = v - o;
	rotated.e[0] = vo.e[0] * cos(ty) - vo.e[2] * sin(ty);
	rotated.e[1] = vo.e[1];
	rotated.e[2] = vo.e[2] * cos(ty) + vo.e[0] * sin(ty);
	return rotated + o;
}

inline Vec3 Vec3::rotateZ(const Vec3 &v, const Vec3 &o, double tz) {
	Vec3 rotated;
	Vec3 vo = v - o;
	rotated.e[0] = vo.e[0] * cos(tz) - vo.e[1] * sin(tz);
	rotated.e[1] = vo.e[1] * cos(tz) + vo.e[0] * sin(tz);
	rotated.e[2] = vo.e[2];
	return rotated + o;
}

inline Vec3 Vec3::rotate(const Vec3 &v, const Vec3 &o, const Vec3 &t) {
	return Vec3::rotateZ(Vec3::rotateY(Vec3::rotateX(v, o, t.e[0]), o, t.e[1]), o, t.e[2]);
}

inline Vec3 Vec3::random() {
	return Vec3(random_double(), random_double(), random_double());
}

inline Vec3 Vec3::random(double min, double max) {
	return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

inline Vec3 Vec3::random_in_unit_sphere() {
	while (true) {
		Vec3 p = Vec3::random(-1, 1);
		if (p.mag_sq() >= 1)
			continue;

		return p;
	}
}

inline Vec3 Vec3::random_in_hemisphere(const Vec3& n) {
	Vec3 inUnitSphere = Vec3::random_in_unit_sphere();
	return Vec3::dot(inUnitSphere, n) > 0.0 ? inUnitSphere : -inUnitSphere;
}

inline Vec3 Vec3::random_in_unit_disk() {
	while (true) {
		Vec3 p = Vec3(random_double(-1, 1), random_double(-1, 1), 0);
		if (p.mag_sq() >= 1)
			continue;

		return p;
	}
}

inline Vec3 Vec3::random_unit_vector() {
	return Vec3::normalize(Vec3::random_in_unit_sphere());
}

inline Vec3 Vec3::reflect(const Vec3& v, const Vec3& n) {
	return v - 2 * Vec3::dot(v, n) * n;
}

inline Vec3 Vec3::refract(const Vec3& v, const Vec3& n, double refractionRatio) {
	auto cosT = fmin(Vec3::dot(-v, n), 1.0);
	Vec3 rOutY = refractionRatio * (v + cosT * n);
	Vec3 rOutX = -sqrt(fabs(1.0 - rOutY.mag_sq())) * n;
	return rOutX + rOutY;
}
