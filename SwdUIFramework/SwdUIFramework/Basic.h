#ifndef _BASIC_H
#define _BASIC_H
#include <iostream>
namespace swd{
	class Object{
	public:
		Object(){}
		virtual ~Object(){}
		virtual std::wstring ToString() const{
			return L"Object";
		}
	};

	struct Point{
		int x;
		int y;
		Point()
			:x(0), y(0)
		{
		}
		Point(int _x, int _y)
			:x(_x), y(_y)
		{
		}
		bool operator==(Point point)const
		{
			return this->x == point.x && this->y == point.y;
		}
		bool operator!=(Point point)const
		{
			return this->x != point.x || this->y == point.y;
		}
	};
	struct Size{
		int x;
		int y;
		Size()
			:x(0), y(0)
		{
		}
		Size(int _x, int _y)
			:x(_x), y(_y)
		{
		}
		bool operator==(Size size)const
		{
			return this->x == size.x && this->y == size.y;
		}
		bool operator!=(Size size)const
		{
			return this->x != size.x || this->y == size.y;
		}
	};
	typedef void(*ListenerCallBack)(void * sender);
}
#endif