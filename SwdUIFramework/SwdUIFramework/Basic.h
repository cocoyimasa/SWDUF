#ifndef _BASIC_H
#define _BASIC_H
#include <iostream>
#define TO_STRING(TYPE,VAL) L"Handle<"#TYPE">"#VAL
namespace swd{
	class Object{
	public:
		Object(){}
		virtual ~Object(){}
		virtual std::wstring ToString() const{
			return L"Object";
		}
	};
	template<typename T>
    	class Handle : public Object{
    	public:
        	Handle(){}
        	Handle(T val){
            		this->val = val;
        	}
        	T Val(){
            		return this->val;
        	}
        	std::wstring ToString() const{
            		return TO_STRING(T,val);
        	}
    	protected:
        	T val;
    	};
	//Maybe,Just,Nothing
    	template<typename T>
    	class Maybe{
    	public:
        	Maybe(T val)
        	:val(val){}
    	public:
        	T val;
    	};
    	template<typename T>
    	class Nothing: public Maybe<T>{
    	public:
        	Nothing(T val)
        	:Maybe<T>(val){}
    	public:
		T val;
    	};
    	template<typename T>
    	class Just: public Maybe<T>{
    	public:
        	Just(T val)
        	:Maybe<T>(val){}
    	public:
        	T val;
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
