#include "MainGame.h"
#include <iostream>

template<typename T>
MainGame<T>::MainGame(T data)
	: data(data)
{
	//this->data = data;
}

template<typename T>//템플릿을 사용하면 소멸자를 사용하지 않더라도 다 템플릿으로 지정을 해줘야한다
MainGame<T>::~MainGame()
{
}

template<typename T>
void MainGame<T>::Print()
{
	std::cout << data << std::endl;
}
