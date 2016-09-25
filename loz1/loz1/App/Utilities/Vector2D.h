#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>

template<class T>
class Vector2D{

public:
	Vector2D<T>(){x=y=0;}
	Vector2D<T>(T a, T b){x=a;y=b;}

	inline Vector2D<T> operator + (Vector2D<T> v){
		return Vector2D<T>(x+v.x, y+v.y);
	}
	inline Vector2D<T> operator - (Vector2D<T> v){
		return Vector2D<T>(x-v.x, y-v.y);
	}
	inline Vector2D<T> operator * (T s){
		return Vector2D<T>(x*s, y*s);
	}
	inline T operator * (Vector2D<T> v){
		return x*v.x+y*v.y;
	}
	inline Vector2D<T> operator / (T s){
		return Vector2D<T>(x/s, y/s);
	}
	inline Vector2D<T> operator = (Vector2D<T> v){
		x = v.x;
		y = v.y;
		return *this;
	}
	inline Vector2D<T> operator += (Vector2D<T> v){
		x += v.x;
		y += v.y;
		return *this;
	}
	inline Vector2D<T> operator -= (Vector2D<T> v){
		x -= v.x;
		y -= v.y;
		return *this;
	}
	inline Vector2D<T> operator *= (T s){
		x *= s;
		y *= s;
		return *this;
	}
	inline Vector2D<T> operator /= (T s){
		x /= s;
		y /= s;
		return *this;
	}
	inline bool operator != (Vector2D<T> v){
		return (x!=v.x || y!=v.y);
	}
	inline bool operator == (Vector2D<T> v){
		return (x==v.x && y==v.y);
	}

	inline T GetLength(){
		return sqrt(x*x+y*y);
	}
	inline Vector2D<T> Normalize(){
		T _temp = sqrt(x*x+y*y);
		x /= _temp;
		y /= _temp;
		return *this;
	}
	inline Vector2D<T> Rotate(float angle){
		float _x, _y;
		_x = x*cos(angle) - y*sin(angle);
		_y = y*cos(angle) + x*sin(angle);
		x=_x;y=_y;
		return *this;
	}
	//使x,y均为正的向量
	inline Vector2D<T> Positive(){
		if(x<0) x=-x;
		if(y<0) y=-y;
		return *this;
	}
	inline Vector2D<T> ReverseX(){
		return Vector2D<T>(-x,y);
	}
	inline Vector2D<T> ReverseY(){
		return Vector2D<T>(x,-y);
	}
	inline Vector2D<T> Reverse(){
		return Vector2D<T>(-x,-y);
	}
	T x,y;
};

template<class T>
inline Vector2D<T> operator - (Vector2D<T> v){
	return Vector2D<T>(-v.x, -v.y);
}
template<class T>
inline Vector2D<T> operator * (T s, Vector2D<T> v){
	return Vector2D<T>(v.x*s, v.y*s);
}

typedef Vector2D<int> Vec2i;
typedef Vector2D<float> Vec2f;
typedef Vector2D<double> Vec2d;

#endif