#pragma once
//싱글톤: 객체(class)를 하나만 만들어서(new 1번) 사용
//한개의 객체를 관리하는 것이 목적

template<typename T>
class SingletonBase
{
protected:
	SingletonBase();
	~SingletonBase();

	static T* instance;

public:
	static T* Get();
	static void Delete();
};

template<typename T>
T*  SingletonBase<T>::instance = NULL;

template<typename T>
SingletonBase<T>::SingletonBase()
{
}

template<typename T>
SingletonBase<T>::~SingletonBase()
{
}

template<typename T>
T * SingletonBase<T>::Get()
{
	if (instance == NULL)
	{
		instance = new T;
	}
	return  instance;
}

template<typename T>
void SingletonBase<T>::Delete()
{
	if (instance != NULL)
	{
		//SAFE_DELETE(instance);
		delete instance;
		instance = NULL;
	}
}
