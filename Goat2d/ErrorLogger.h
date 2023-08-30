#ifndef ERROR_LOGGER_H
#define ERROR_LOGGER_H
#include"SDL.h"
#include<string>
#include<iostream>
#include<fstream>
namespace Goat2d
{
namespace core 
{
	//these proceduras are used to print/write special SDL Errors
	static inline void print_error(const std::string& additional_info)
	{
		std::cout << additional_info << SDL_GetError()<<std::endl;
	}
	static void write_error(const std::string& additional_info)
	{
		std::time_t t = std::time(0);
		auto time = std::string(std::ctime(&t));
		std::ofstream f("error_log.txt",std::ios::app);
		f <<time<<" : "<< additional_info << SDL_GetError() << std::endl;
	}
	//TODO:: write same proceduras for Goat2d errors
};
};
#endif //ERROR_LOGGER_H
