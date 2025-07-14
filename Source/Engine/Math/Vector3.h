#pragma once
#include "Math.h"
#include <cassert>

namespace viper {

	template<typename T>
	struct Vector2 {
		T x, y;

		Vector2() = default;
		Vector2(T x, T y) : x{ x }, y{ y } {}

		T operator [] (unsigned int index) const {
			assert(index < 2);
			return (&x)[index];
		}

		T& operator [] (unsigned int index) {
			assert(index < 2);
			return (&x)[index];
		}

		// Arithmetic operators
		Vector2 operator + (const Vector2& v) const {
			return Vector2(x + v.x, y + v.y);
		}

		Vector2 operator - (const Vector2& v) const {
			return Vector2(x - v.x, y - v.y);
		}

		Vector2 operator * (const Vector2& v) const {
			return Vector2(x * v.x, y * v.y);
		}

		Vector2 operator / (const Vector2& v) const {
			return Vector2(x / v.x, y / v.y);
		}

		Vector2 operator + (T s) const {
			return Vector2(x + s, y + s);
		}

		Vector2 operator - (T s) const {
			return Vector2(x - s, y - s);
		}

		Vector2 operator * (T s) const {
			return Vector2(x * s, y * s);
		}

		Vector2 operator / (T s) const {
			return Vector2(x / s, y / s);
		}

		// Compound assignment operators (vector)
		Vector2& operator += (const Vector2& v) {
			x += v.x; y += v.y;
			return *this;
		}

		Vector2& operator -= (const Vector2& v) {
			x -= v.x; y -= v.y;
			return *this;
		}

		Vector2& operator *= (const Vector2& v) {
			x *= v.x; y *= v.y;
			return *this;
		}

		Vector2& operator /= (const Vector2& v) {
			x /= v.x; y /= v.y;
			return *this;
		}

		// Compound assignment operators (scalar)
		Vector2& operator += (T s) {
			x += s; y += s;
			return *this;
		}

		Vector2& operator -= (T s) {
			x -= s; y -= s;
			return *this;
		}

		Vector2& operator *= (T s) {
			x *= s; y *= s;
			return *this;
		}

		Vector2& operator /= (T s) {
			x /= s; y /= s;
			return *this;
		}

		// Length stuff
		T LengthSqr() const {
			return (x * x) + (y * y);
		}

		T Length() const {
			return math::sqrt(LengthSqr());
		}
	};

	using ivec2 = Vector2<int>;
	using vec2 = Vector2<float>;

}
