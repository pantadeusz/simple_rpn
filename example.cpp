/*
 * This file is unlicensed - use it as you wish. This is an example of RPN formula evaluator
 * 
 * 
 *    g++ example.cpp -Wall
 * 
 * */

#include <iostream>
#include "srpn.hpp"


int main(int argc, char **argv) {
	
	std::string program = "100 0.5 ^ x +"; // Reverse Polish Notation formula for pow(100,0.5) + x
	for (double x: {1,2,20}) {
		std::cout  << program << " = "<< rpn::calculate(program, {{"x",x}}) << std::endl;
	}
	
	return 0;
}
