#pragma once
//�̱���: ��ü(class)�� �ϳ��� ����(new 1��) ���
//�Ѱ��� ��ü�� �����ϴ� ���� ����

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
