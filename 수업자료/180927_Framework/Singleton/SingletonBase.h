#pragma once
//�̱��� : ��ü(class)�� 1���� ����(new 1��) ����ϴ� �༮ 
//�Ѱ��� ��ü�� ���� 

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
