#pragma once

#include <iostream>
#include <stddef.h>
#include <assert.h>
#include <math.h>

class Matrix4x4 {
	public:
		Matrix4x4():
			m_mtx {{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }} {}

		Matrix4x4(double mtx[4][4]):
			m_mtx{{ mtx[0][0], mtx[0][1], mtx[0][2], mtx[0][3]}, {mtx[1][0], mtx[1][1], mtx[1][2], mtx[1][3]}, {mtx[2][0], mtx[2][1], mtx[2][2], mtx[2][3]}, {mtx[3][0], mtx[3][1], mtx[3][2], mtx[3][3] }} {}

		Matrix4x4(const double mtx[4][4]):
			m_mtx{{ mtx[0][0], mtx[0][1], mtx[0][2], mtx[0][3]}, {mtx[1][0], mtx[1][1], mtx[1][2], mtx[1][3]}, {mtx[2][0], mtx[2][1], mtx[2][2], mtx[2][3]}, {mtx[3][0], mtx[3][1], mtx[3][2], mtx[3][3] }} {}

		Matrix4x4(double a00, double a01, double a02, double a03, double a10, double a11, double a12, double a13, double a20, double a21, double a22, double a23, double a30, double a31, double a32, double a33):
			m_mtx{{ a00, a01, a02, a03 }, { a10, a11, a12, a13 }, { a20, a21, a22, a23 }, { a30, a31, a32, a33 }} {}

		double operator()(size_t row, size_t col) const {
			assert(row < 4 && col < 4);
			return m_mtx[row][col];
		}

		double& operator()(size_t row, size_t col) {
			assert(row < 4 && col < 4);
			return m_mtx[row][col];
		}

		double operator()(int row, int col) const {
			assert(row >= 0 && row < 4 && col >= 0 && col < 4);
			return m_mtx[row][col];
		}

		double& operator()(int row, int col) {
			assert(row >= 0 && row < 4 && col >= 0 && col < 4);
			return m_mtx[row][col];
		}

		Matrix4x4 operator-() const;
		Matrix4x4& operator+=(const Matrix4x4& m);
		Matrix4x4& operator-=(const Matrix4x4& m);
		Matrix4x4& operator*=(double t);
		Matrix4x4& operator*=(const Matrix4x4& m);
		Matrix4x4& operator/=(double t);
		friend std::ostream& operator<<(std::ostream& os, const Matrix4x4& m);

		Matrix4x4 operator+(const Matrix4x4& m) const;
		Matrix4x4 operator-(const Matrix4x4& m) const;
		Matrix4x4 operator*(double t) const;
		Matrix4x4 operator*(const Matrix4x4& m) const;
		Matrix4x4 operator/(double t) const;

		static Matrix4x4 identity();
		static bool is_identity(const Matrix4x4& m);
		static Matrix4x4 inverse(const Matrix4x4& m);
		static Matrix4x4 transpose(const Matrix4x4& m);
		static Matrix4x4 absolute(const Matrix4x4& m);
		static double determinant(const Matrix4x4& m);

	private:
		static constexpr double s_identityMtx[4][4] = {{ 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 }};

		double m_mtx[4][4];
};

inline Matrix4x4 Matrix4x4::operator-() const {
	Matrix4x4 neg;
	neg(0, 0) = -m_mtx[0][0];
	neg(0, 1) = -m_mtx[0][1];
	neg(0, 2) = -m_mtx[0][2];
	neg(0, 3) = -m_mtx[0][3];
	neg(1, 0) = -m_mtx[1][0];
	neg(1, 1) = -m_mtx[1][1];
	neg(1, 2) = -m_mtx[1][2];
	neg(1, 3) = -m_mtx[1][3];
	neg(2, 0) = -m_mtx[2][0];
	neg(2, 1) = -m_mtx[2][1];
	neg(2, 2) = -m_mtx[2][2];
	neg(2, 3) = -m_mtx[2][3];
	neg(3, 0) = -m_mtx[3][0];
	neg(3, 1) = -m_mtx[3][1];
	neg(3, 2) = -m_mtx[3][2];
	neg(3, 3) = -m_mtx[3][3];
	return neg;
}

inline Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& m) {
	m_mtx[0][0] += m(0, 0);
	m_mtx[0][1] += m(0, 1);
	m_mtx[0][2] += m(0, 2);
	m_mtx[0][3] += m(0, 3);
	m_mtx[1][0] += m(1, 0);
	m_mtx[1][1] += m(1, 1);
	m_mtx[1][2] += m(1, 2);
	m_mtx[1][3] += m(1, 3);
	m_mtx[2][0] += m(2, 0);
	m_mtx[2][1] += m(2, 1);
	m_mtx[2][2] += m(2, 2);
	m_mtx[2][3] += m(2, 3);
	m_mtx[3][0] += m(3, 0);
	m_mtx[3][1] += m(3, 1);
	m_mtx[3][2] += m(3, 2);
	m_mtx[3][3] += m(3, 3);
	return *this;
}

inline Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& m) {
	m_mtx[0][0] -= m(0, 0);
	m_mtx[0][1] -= m(0, 1);
	m_mtx[0][2] -= m(0, 2);
	m_mtx[0][3] -= m(0, 3);
	m_mtx[1][0] -= m(1, 0);
	m_mtx[1][1] -= m(1, 1);
	m_mtx[1][2] -= m(1, 2);
	m_mtx[1][3] -= m(1, 3);
	m_mtx[2][0] -= m(2, 0);
	m_mtx[2][1] -= m(2, 1);
	m_mtx[2][2] -= m(2, 2);
	m_mtx[2][3] -= m(2, 3);
	m_mtx[3][0] -= m(3, 0);
	m_mtx[3][1] -= m(3, 1);
	m_mtx[3][2] -= m(3, 2);
	m_mtx[3][3] -= m(3, 3);
	return *this;
}

inline Matrix4x4& Matrix4x4::operator*=(double t) {
	m_mtx[0][0] *= t;
	m_mtx[0][1] *= t;
	m_mtx[0][2] *= t;
	m_mtx[0][3] *= t;
	m_mtx[1][0] *= t;
	m_mtx[1][1] *= t;
	m_mtx[1][2] *= t;
	m_mtx[1][3] *= t;
	m_mtx[2][0] *= t;
	m_mtx[2][1] *= t;
	m_mtx[2][2] *= t;
	m_mtx[2][3] *= t;
	m_mtx[3][0] *= t;
	m_mtx[3][1] *= t;
	m_mtx[3][2] *= t;
	m_mtx[3][3] *= t;
	return *this;
}

inline Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& m) {
	Matrix4x4 r;
	r(0, 0) = m_mtx[0][0] * m(0, 0) + m_mtx[0][1] * m(1, 0) + m_mtx[0][2] * m(2, 0) + m_mtx[0][3] * m(3, 0);
	r(0, 1) = m_mtx[0][0] * m(0, 1) + m_mtx[0][1] * m(1, 1) + m_mtx[0][2] * m(2, 1) + m_mtx[0][3] * m(3, 1);
	r(0, 2) = m_mtx[0][0] * m(0, 2) + m_mtx[0][1] * m(1, 2) + m_mtx[0][2] * m(2, 2) + m_mtx[0][3] * m(3, 2);
	r(0, 3) = m_mtx[0][0] * m(0, 3) + m_mtx[0][1] * m(1, 3) + m_mtx[0][2] * m(2, 3) + m_mtx[0][3] * m(3, 3);

	r(1, 0) = m_mtx[1][0] * m(0, 0) + m_mtx[1][1] * m(1, 0) + m_mtx[1][2] * m(2, 0) + m_mtx[1][3] * m(3, 0);
	r(1, 1) = m_mtx[1][0] * m(0, 1) + m_mtx[1][1] * m(1, 1) + m_mtx[1][2] * m(2, 1) + m_mtx[1][3] * m(3, 1);
	r(1, 2) = m_mtx[1][0] * m(0, 2) + m_mtx[1][1] * m(1, 2) + m_mtx[1][2] * m(2, 2) + m_mtx[1][3] * m(3, 2);
	r(1, 3) = m_mtx[1][0] * m(0, 3) + m_mtx[1][1] * m(1, 3) + m_mtx[1][2] * m(2, 3) + m_mtx[1][3] * m(3, 3);

	r(2, 0) = m_mtx[2][0] * m(0, 0) + m_mtx[2][1] * m(1, 0) + m_mtx[2][2] * m(2, 0) + m_mtx[2][3] * m(3, 0);
	r(2, 1) = m_mtx[2][0] * m(0, 1) + m_mtx[2][1] * m(1, 1) + m_mtx[2][2] * m(2, 1) + m_mtx[2][3] * m(3, 1);
	r(2, 2) = m_mtx[2][0] * m(0, 2) + m_mtx[2][1] * m(1, 2) + m_mtx[2][2] * m(2, 2) + m_mtx[2][3] * m(3, 2);
	r(2, 3) = m_mtx[2][0] * m(0, 3) + m_mtx[2][1] * m(1, 3) + m_mtx[2][2] * m(2, 3) + m_mtx[2][3] * m(3, 3);

	r(3, 0) = m_mtx[3][0] * m(0, 0) + m_mtx[3][1] * m(1, 0) + m_mtx[3][2] * m(2, 0) + m_mtx[3][3] * m(3, 0);
	r(3, 1) = m_mtx[3][0] * m(0, 1) + m_mtx[3][1] * m(1, 1) + m_mtx[3][2] * m(2, 1) + m_mtx[3][3] * m(3, 1);
	r(3, 2) = m_mtx[3][0] * m(0, 2) + m_mtx[3][1] * m(1, 2) + m_mtx[3][2] * m(2, 2) + m_mtx[3][3] * m(3, 2);
	r(3, 3) = m_mtx[3][0] * m(0, 3) + m_mtx[3][1] * m(1, 3) + m_mtx[3][2] * m(2, 3) + m_mtx[3][3] * m(3, 3);

	*this = r;

	return *this;
}

inline Matrix4x4& Matrix4x4::operator/=(double t) {
	*this *= (1 / t);
	return *this;
}

inline std::ostream& operator<<(std::ostream& os, const Matrix4x4& m) {
	os << "[\n";
	os << "  [ " << m(0, 0) << ", " << m(0, 1) <<  ", " << m(0, 2) << ", " << m(0, 3) << " ]\n";
	os << "  [ " << m(1, 0) << ", " << m(1, 1) <<  ", " << m(1, 2) << ", " << m(1, 3) << " ]\n";
	os << "  [ " << m(2, 0) << ", " << m(2, 1) <<  ", " << m(2, 2) << ", " << m(2, 3) << " ]\n";
	os << "  [ " << m(3, 0) << ", " << m(3, 1) <<  ", " << m(3, 2) << ", " << m(3, 3) << " ]\n";
	os << "]\n";
	return os;
}

inline Matrix4x4 Matrix4x4::operator+(const Matrix4x4& m) const {
	Matrix4x4 r(m_mtx);
	r(0, 0) += m(0, 0);
	r(0, 1) += m(0, 1);
	r(0, 2) += m(0, 2);
	r(0, 3) += m(0, 3);
	r(1, 0) += m(1, 0);
	r(1, 1) += m(1, 1);
	r(1, 2) += m(1, 2);
	r(1, 3) += m(1, 3);
	r(2, 0) += m(2, 0);
	r(2, 1) += m(2, 1);
	r(2, 2) += m(2, 2);
	r(2, 3) += m(2, 3);
	r(3, 0) += m(3, 0);
	r(3, 1) += m(3, 1);
	r(3, 2) += m(3, 2);
	r(3, 3) += m(3, 3);
	return r;
}

inline Matrix4x4 Matrix4x4::operator-(const Matrix4x4& m) const {
	Matrix4x4 r(m_mtx);
	r(0, 0) -= m(0, 0);
	r(0, 1) -= m(0, 1);
	r(0, 2) -= m(0, 2);
	r(0, 3) -= m(0, 3);
	r(1, 0) -= m(1, 0);
	r(1, 1) -= m(1, 1);
	r(1, 2) -= m(1, 2);
	r(1, 3) -= m(1, 3);
	r(2, 0) -= m(2, 0);
	r(2, 1) -= m(2, 1);
	r(2, 2) -= m(2, 2);
	r(2, 3) -= m(2, 3);
	r(3, 0) -= m(3, 0);
	r(3, 1) -= m(3, 1);
	r(3, 2) -= m(3, 2);
	r(3, 3) -= m(3, 3);
	return r;
}

inline Matrix4x4 Matrix4x4::operator*(double t) const {
	Matrix4x4 r(m_mtx);
	r(0, 0) *= t;
	r(0, 1) *= t;
	r(0, 2) *= t;
	r(0, 3) *= t;
	r(1, 0) *= t;
	r(1, 1) *= t;
	r(1, 2) *= t;
	r(1, 3) *= t;
	r(2, 0) *= t;
	r(2, 1) *= t;
	r(2, 2) *= t;
	r(2, 3) *= t;
	r(3, 0) *= t;
	r(3, 1) *= t;
	r(3, 2) *= t;
	r(3, 3) *= t;
	return r;
}

inline Matrix4x4 Matrix4x4::operator*(const Matrix4x4& m) const {
	Matrix4x4 r;
	r(0, 0) = m_mtx[0][0] * m(0, 0) + m_mtx[0][1] * m(1, 0) + m_mtx[0][2] * m(2, 0) + m_mtx[0][3] * m(3, 0);
	r(0, 1) = m_mtx[0][0] * m(0, 1) + m_mtx[0][1] * m(1, 1) + m_mtx[0][2] * m(2, 1) + m_mtx[0][3] * m(3, 1);
	r(0, 2) = m_mtx[0][0] * m(0, 2) + m_mtx[0][1] * m(1, 2) + m_mtx[0][2] * m(2, 2) + m_mtx[0][3] * m(3, 2);
	r(0, 3) = m_mtx[0][0] * m(0, 3) + m_mtx[0][1] * m(1, 3) + m_mtx[0][2] * m(2, 3) + m_mtx[0][3] * m(3, 3);

	r(1, 0) = m_mtx[1][0] * m(0, 0) + m_mtx[1][1] * m(1, 0) + m_mtx[1][2] * m(2, 0) + m_mtx[1][3] * m(3, 0);
	r(1, 1) = m_mtx[1][0] * m(0, 1) + m_mtx[1][1] * m(1, 1) + m_mtx[1][2] * m(2, 1) + m_mtx[1][3] * m(3, 1);
	r(1, 2) = m_mtx[1][0] * m(0, 2) + m_mtx[1][1] * m(1, 2) + m_mtx[1][2] * m(2, 2) + m_mtx[1][3] * m(3, 2);
	r(1, 3) = m_mtx[1][0] * m(0, 3) + m_mtx[1][1] * m(1, 3) + m_mtx[1][2] * m(2, 3) + m_mtx[1][3] * m(3, 3);

	r(2, 0) = m_mtx[2][0] * m(0, 0) + m_mtx[2][1] * m(1, 0) + m_mtx[2][2] * m(2, 0) + m_mtx[2][3] * m(3, 0);
	r(2, 1) = m_mtx[2][0] * m(0, 1) + m_mtx[2][1] * m(1, 1) + m_mtx[2][2] * m(2, 1) + m_mtx[2][3] * m(3, 1);
	r(2, 2) = m_mtx[2][0] * m(0, 2) + m_mtx[2][1] * m(1, 2) + m_mtx[2][2] * m(2, 2) + m_mtx[2][3] * m(3, 2);
	r(2, 3) = m_mtx[2][0] * m(0, 3) + m_mtx[2][1] * m(1, 3) + m_mtx[2][2] * m(2, 3) + m_mtx[2][3] * m(3, 3);

	r(3, 0) = m_mtx[3][0] * m(0, 0) + m_mtx[3][1] * m(1, 0) + m_mtx[3][2] * m(2, 0) + m_mtx[3][3] * m(3, 0);
	r(3, 1) = m_mtx[3][0] * m(0, 1) + m_mtx[3][1] * m(1, 1) + m_mtx[3][2] * m(2, 1) + m_mtx[3][3] * m(3, 1);
	r(3, 2) = m_mtx[3][0] * m(0, 2) + m_mtx[3][1] * m(1, 2) + m_mtx[3][2] * m(2, 2) + m_mtx[3][3] * m(3, 2);
	r(3, 3) = m_mtx[3][0] * m(0, 3) + m_mtx[3][1] * m(1, 3) + m_mtx[3][2] * m(2, 3) + m_mtx[3][3] * m(3, 3);

	return r;
}

inline Matrix4x4 Matrix4x4::operator/(double t) const {
	return *this * (1 / t);
}

inline Matrix4x4 Matrix4x4::identity() {
	return Matrix4x4(s_identityMtx);
}

inline bool Matrix4x4::is_identity(const Matrix4x4& m) {
	return m(0, 0) == s_identityMtx[0][0] &&
		     m(0, 1) == s_identityMtx[0][1] &&
		     m(0, 2) == s_identityMtx[0][2] &&
		     m(0, 3) == s_identityMtx[0][3] &&
		     m(1, 0) == s_identityMtx[1][0] &&
		     m(1, 1) == s_identityMtx[1][1] &&
		     m(1, 2) == s_identityMtx[1][2] &&
		     m(1, 3) == s_identityMtx[1][3] &&
		     m(2, 0) == s_identityMtx[2][0] &&
		     m(2, 1) == s_identityMtx[2][1] &&
		     m(2, 2) == s_identityMtx[2][2] &&
		     m(2, 3) == s_identityMtx[2][3] &&
		     m(3, 0) == s_identityMtx[3][0] &&
		     m(3, 1) == s_identityMtx[3][1] &&
		     m(3, 2) == s_identityMtx[3][2] &&
		     m(3, 3) == s_identityMtx[3][3];
}

inline Matrix4x4 Matrix4x4::inverse(const Matrix4x4& m) {
	double i[4][4] =
		{
			{
				 m(1, 1) * m(2, 2) * m(3, 3) + m(1, 2) * m(2, 3) * m(3, 1) + m(1, 3) * m(2, 1) * m(3, 2) - m(1, 3) * m(2, 2) * m(3, 1) - m(1, 2) * m(2, 1) * m(3, 3) - m(1, 1) * m(2, 3) * m(3, 2),
				-m(0, 1) * m(2, 2) * m(3, 3) - m(0, 2) * m(2, 3) * m(3, 1) - m(0, 3) * m(2, 1) * m(3, 2) + m(0, 3) * m(2, 2) * m(3, 1) + m(0, 2) * m(2, 1) * m(3, 3) + m(0, 1) * m(2, 3) * m(3, 2),
				 m(0, 1) * m(1, 2) * m(3, 3) + m(0, 2) * m(1, 3) * m(3, 1) + m(0, 3) * m(1, 1) * m(3, 2) - m(0, 3) * m(1, 2) * m(3, 1) - m(0, 2) * m(1, 1) * m(3, 3) - m(0, 1) * m(1, 3) * m(3, 2),
				-m(0, 1) * m(1, 2) * m(2, 3) - m(0, 2) * m(1, 3) * m(2, 1) - m(0, 3) * m(1, 1) * m(2, 2) + m(0, 3) * m(1, 2) * m(2, 1) + m(0, 2) * m(1, 1) * m(2, 3) + m(0, 1) * m(1, 3) * m(2, 2)
			},
			{
				-m(1, 0) * m(2, 2) * m(3, 3) - m(1, 2) * m(2, 3) * m(3, 0) - m(1, 3) * m(2, 0) * m(3, 2) + m(1, 3) * m(2, 2) * m(3, 0) + m(1, 2) * m(2, 0) * m(3, 3) + m(1, 0) * m(2, 3) * m(3, 2),
				 m(0, 0) * m(2, 2) * m(3, 3) + m(0, 2) * m(2, 3) * m(3, 0) + m(0, 3) * m(2, 0) * m(3, 2) - m(0, 3) * m(2, 2) * m(3, 0) - m(0, 2) * m(2, 0) * m(3, 3) - m(0, 0) * m(2, 3) * m(3, 2),
				-m(0, 0) * m(1, 2) * m(3, 3) - m(0, 2) * m(1, 3) * m(3, 0) - m(0, 3) * m(1, 0) * m(3, 2) + m(0, 3) * m(1, 2) * m(3, 0) + m(0, 2) * m(1, 0) * m(3, 3) + m(0, 0) * m(1, 3) * m(3, 2),
				 m(0, 0) * m(1, 2) * m(2, 3) + m(0, 2) * m(1, 3) * m(2, 0) + m(0, 3) * m(1, 0) * m(2, 2) - m(0, 3) * m(1, 2) * m(2, 0) - m(0, 2) * m(1, 0) * m(2, 3) - m(0, 0) * m(1, 3) * m(2, 2)
			},
			{
				 m(1, 0) * m(2, 1) * m(3, 3) + m(1, 1) * m(2, 3) * m(3, 0) + m(1, 3) * m(2, 0) * m(3, 1) - m(1, 3) * m(2, 1) * m(3, 0) - m(1, 1) * m(2, 0) * m(3, 3) - m(1, 0) * m(2, 3) * m(3, 1),
				-m(0, 0) * m(2, 1) * m(3, 3) - m(0, 1) * m(2, 3) * m(3, 0) - m(0, 3) * m(2, 0) * m(3, 1) + m(0, 3) * m(2, 1) * m(3, 0) + m(0, 1) * m(2, 0) * m(3, 3) + m(0, 0) * m(2, 3) * m(3, 1),
				 m(0, 0) * m(1, 1) * m(3, 3) + m(0, 1) * m(1, 3) * m(3, 0) + m(0, 3) * m(1, 0) * m(3, 1) - m(0, 3) * m(1, 1) * m(3, 0) - m(0, 1) * m(1, 0) * m(3, 3) - m(0, 0) * m(1, 3) * m(3, 1),
				-m(0, 0) * m(1, 1) * m(2, 3) - m(0, 1) * m(1, 3) * m(2, 0) - m(0, 3) * m(1, 0) * m(2, 1) + m(0, 3) * m(1, 1) * m(2, 0) + m(0, 1) * m(1, 0) * m(2, 3) + m(0, 0) * m(1, 3) * m(2, 1)
			},
			{
				-m(1, 0) * m(2, 1) * m(3, 2) - m(1, 1) * m(2, 2) * m(3, 0) - m(1, 2) * m(2, 0) * m(3, 1) + m(1, 2) * m(2, 1) * m(3, 0) + m(1, 1) * m(2, 0) * m(3, 2) + m(1, 0) * m(2, 2) * m(3, 1),
				 m(0, 0) * m(2, 1) * m(3, 2) + m(0, 1) * m(2, 2) * m(3, 0) + m(0, 2) * m(2, 0) * m(3, 1) - m(0, 2) * m(2, 1) * m(3, 0) - m(0, 1) * m(2, 0) * m(3, 2) - m(0, 0) * m(2, 2) * m(3, 1),
				-m(0, 0) * m(1, 1) * m(3, 2) - m(0, 1) * m(1, 2) * m(3, 0) - m(0, 2) * m(1, 0) * m(3, 1) + m(0, 2) * m(1, 1) * m(3, 0) + m(0, 1) * m(1, 0) * m(3, 2) + m(0, 0) * m(1, 2) * m(3, 1),
				 m(0, 0) * m(1, 1) * m(2, 2) + m(0, 1) * m(1, 2) * m(2, 0) + m(0, 2) * m(1, 0) * m(2, 1) - m(0, 2) * m(1, 1) * m(2, 0) - m(0, 1) * m(1, 0) * m(2, 2) - m(0, 0) * m(1, 2) * m(2, 1)
			}
		};

	return Matrix4x4(i) / Matrix4x4::determinant(m);
}

inline Matrix4x4 Matrix4x4::transpose(const Matrix4x4& m) {
	double t[4][4] =
		{
			{ m(0, 0), m(1, 0), m(2, 0), m(3, 0) },
			{ m(0, 1), m(1, 1), m(2, 1), m(3, 1) },
			{ m(0, 2), m(1, 2), m(2, 2), m(3, 2) },
			{ m(0, 3), m(1, 3), m(2, 3), m(3, 3) }
		};

	return Matrix4x4(t);
}

inline Matrix4x4 Matrix4x4::absolute(const Matrix4x4 &m) {
	// The last coefficients are used to translate objects so their sign should be left intact and the coefficients in the fourth row are just placeholders.
	return Matrix4x4(
		fabs(m(0, 0)), fabs(m(0, 1)), fabs(m(0, 2)), m(0, 3),
		fabs(m(1, 0)), fabs(m(1, 1)), fabs(m(1, 2)), m(1, 3),
		fabs(m(2, 0)), fabs(m(2, 1)), fabs(m(2, 2)), m(2, 3),
		m(3, 0), m(3, 1), m(3, 2), m(3, 3)
	);
}

inline double Matrix4x4::determinant(const Matrix4x4& m) {
	double det = 0;
	det += m(0, 0) * (m(1, 1) * m(2, 2) * m(3, 3) + m(1, 2) * m(2, 3) * m(3, 1) + m(1, 3) * m(2, 1) * m(3, 2) - m(1, 3) * m(2, 2) * m(3, 1) - m(1, 2) * m(2, 1) * m(3, 3) - m(1, 1) * m(2, 3) * m(3, 2));
	det -= m(0, 1) * (m(1, 0) * m(2, 2) * m(3, 3) + m(1, 2) * m(2, 3) * m(3, 0) + m(1, 3) * m(2, 0) * m(3, 2) - m(1, 3) * m(2, 2) * m(3, 0) - m(1, 2) * m(2, 0) * m(3, 3) - m(1, 0) * m(2, 3) * m(3, 2));
	det += m(0, 2) * (m(1, 0) * m(2, 1) * m(3, 3) + m(1, 1) * m(2, 3) * m(3, 0) + m(1, 3) * m(2, 0) * m(3, 1) - m(1, 3) * m(2, 1) * m(3, 0) - m(1, 1) * m(2, 0) * m(3, 3) - m(1, 0) * m(2, 3) * m(3, 1));
	det -= m(0, 3) * (m(1, 0) * m(2, 1) * m(3, 2) + m(1, 1) * m(2, 2) * m(3, 0) + m(1, 2) * m(2, 0) * m(3, 1) - m(1, 2) * m(2, 1) * m(3, 0) - m(1, 1) * m(2, 0) * m(3, 2) - m(1, 0) * m(2, 2) * m(3, 1));
	return det;
}
