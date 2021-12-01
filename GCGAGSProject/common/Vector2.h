#pragma once

template<class T>
class Vector2Temple
{
public:
	Vector2Temple();
	~Vector2Temple();
	Vector2Temple(T x, T y);

	T x, y;

	//ë„ì¸ââéZéq
	Vector2Temple& operator = (const Vector2Temple& vec);

	//ìYÇ¶éöââéZéq
	T& operator[](int no);

	//íPçÄââéZéq
	Vector2Temple& operator +=(const Vector2Temple& vec);
	Vector2Temple& operator -=(const Vector2Temple& vec);
	Vector2Temple& operator *=(T k);
	Vector2Temple& operator /=(T k);
	Vector2Temple operator +()const;
	Vector2Temple operator -()const;
	Vector2Temple& operator +=(const T k);
	Vector2Temple& operator -=(const T k);

	//template <class T>
	//Vector2Temple& operator = (Vector2Temple <T> const& v)
	//{
	//	x = v.x;
	//	y = v.y;
	//	return *this;
	//}

	//î‰ärââéZéq
	bool operator == (const  Vector2Temple& Vec)const;

	bool operator != (const Vector2Temple& Vec)const;

	bool operator <= (const  Vector2Temple& Vec)const;

	bool operator <(const  Vector2Temple& Vec)const;

	bool operator >= (const  Vector2Temple& Vec)const;

	bool operator >(const  Vector2Temple& Vec)const;
};

using Vector2 = Vector2Temple<int>;
using Vector2dbl = Vector2Temple<double>;
using Vector2flt = Vector2Temple<float>;

//Vector2 + T
template<class T>
Vector2Temple<T> operator +(const Vector2Temple<T>& u, T v);
//Vector2 - T
template<class T>
Vector2Temple<T> operator -(const Vector2Temple<T>& u, T v);
//Vector2 * T
template<class T>
Vector2Temple<T> operator *(const Vector2Temple<T>& u, T v);
//T * Vector2
template<class T>
Vector2Temple<T> operator *(T v, const Vector2Temple<T>& u);
//Vector2 / T
template<class T>
Vector2Temple<T> operator /(const Vector2Temple<T>& u, T v);
//Vector2 % T
template<class T>
Vector2Temple<T> operator %(const Vector2Temple<T>& u, T v);
//Vector2 + Vector2
template<class T>
Vector2Temple<T> operator +(const Vector2Temple<T>& u, const Vector2Temple<T>& u2);
//Vector2 - Vector2
template<class T>
Vector2Temple<T> operator -(const Vector2Temple<T>& u, const Vector2Temple<T>& u2);

#include "./details/Vector2.h"
