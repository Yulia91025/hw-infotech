#include "Array.h"
#include "Array.cpp"
template class Array<int>; // явно создаем экземпляр шаблона класса Array<int>
template class Array<double>; // явно создаем экземпляр шаблона класса Array<double>
template class Array<char>; // явно создаем экземпляр шаблона класса Array<char>
template class Array<Array<int>>; // явно создаем экземпляр шаблона класса Array<Array<int>>