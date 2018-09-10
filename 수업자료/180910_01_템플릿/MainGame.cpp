#include "MainGame.h"
#include <iostream>
template<typename T>

MainGame<T>::MainGame(T data)
	: data(data)
{
	//this->data = data;
}
template<typename T>
MainGame<T>::~MainGame()
{
}
template<typename T>
void MainGame<T>::Print()
{
	std::cout << data << std::endl;
}
