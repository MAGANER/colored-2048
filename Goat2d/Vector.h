#ifndef VECTOR_H
#define VECTOR_H
namespace Goat2d
{
namespace core
{
	template<typename T>
	struct Vector2
	{
		T x, y;
		Vector2()
		{
			x = T();
			y = T();
		}
		Vector2(T x, T y):x(x),y(y){}
		Vector2(const Vector2& vec)
		{
			this->x = vec.x;
			this->y = vec.y;
		}

		Vector2& operator=(const Vector2& vec) = default;
		Vector2 operator+(const Vector2& vec)
		{
			return Vector2(x + vec.x, y + vec.y);
		}
		Vector2 operator-(const Vector2& vec)
		{
			return Vector2(x - vec.x, y - vec.y);
		}
		Vector2 operator*(T number)
		{
			return Vector2(x * number, y * number);
		}
		~Vector2(){}
	};

	template<class T>
	bool operator==(const Vector2<T>& a, const Vector2<T>& b)
	{
		return a.x == b.x and a.y == b.y;
	}

	typedef Vector2<int> Vector2i;
	typedef Vector2<float> Vector2f;
};
};
#endif