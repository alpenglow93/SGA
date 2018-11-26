#pragma once
//싱글톤 : 객체(class)를 1개만 만들어서(new 1번) 사용하는 녀석 
//한개의 객체를 관리 

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
T* SingletonBase<T>::instance = NULL;

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
	return instance;
}
template<typename T>
void SingletonBase<T>::Delete()
{
	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}
