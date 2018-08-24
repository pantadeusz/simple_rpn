/*

MIT License

Copyright (c) 2018 Tadeusz Puźniakowski

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

 */
 
#ifndef __PUZNIAKOWSKI_SIMPLE_RPN_INTERPRETER_HPP___
#define __PUZNIAKOWSKI_SIMPLE_RPN_INTERPRETER_HPP___

#include <map>
#include <functional>
#include <vector>
#include <regex>
#include <list>
#include <iterator>
#include <regex>
#include <string>
#include <map>
#include <cmath>

namespace rpn {
	/**
	 * calculates rpn formula given as string and with variables given as map.
	 * 
	 * @arg formula_ the formula. It can look like "3 x * 5 y + -
	 * @arg variables_ the map of variable values that will be placed in the formula. It is in the form of variable_name:value. Variables must consist only of letters and numbers (number cannot be first). For other variable names the function behavior is undefined!
	 * @return calculated formula result
	 * */
	inline double calculate(const std::string &formula_, const std::map<std::string,double> &variables_ = {}) {
	std::string formula = formula_;
	
	for (auto &kv : variables_) {
		std::string rxs = std::string("( |^)(") + kv.first + ")( |$)";
		std::string rplaces = std::string("$1 ") + std::to_string(kv.second) + "$3";		
		std::regex var_re(rxs);
		formula = std::regex_replace(formula, var_re, rplaces);
	}
	
	static std::regex re("[ ]+");
    std::sregex_token_iterator first{formula.begin(), formula.end(), re, -1}, last;
    std::vector<std::string> formula_tokens {first, last};
	
	auto pop = [](std::list < double > &stack){
		auto ret = stack.back();
		stack.pop_back();
		return ret;
	};
	
	static std::map < std::string, std::function < void(std::list < double >&) > > 
		commands = {
			{"sin",[pop](std::list < double > &stack){
				stack.push_back(std::sin(pop(stack)));
			}},
			{"cos",[pop](std::list < double > &stack){
				stack.push_back(std::cos(pop(stack)));
			}},
			{"^",[pop](std::list < double > &stack){
				auto a = pop(stack), b = pop(stack);
				stack.push_back(std::pow(b,a));
			}},
			{"+",[pop](std::list < double > &stack){
				stack.push_back(pop(stack)+pop(stack));
			}},
			{"*",[pop](std::list < double > &stack){
				stack.push_back(pop(stack)*pop(stack));
			}},
			{"/",[pop](std::list < double > &stack){
				auto a = pop(stack), b = pop(stack);
				stack.push_back(b/a);
			}},
			{"-",[pop](std::list < double > &stack){
				auto a = pop(stack), b = pop(stack);
				stack.push_back(b-a);
			}}
		};
	
	std::list < double > stack; // stos
	for (auto &token : formula_tokens) {
		if (commands.count(token)) {
			commands.at(token)(stack);
		} else {
			stack.push_back(std::stod(token));
		}
	}
	
		// todo: if (stack.size() != 1) throw std:: ....
		return stack.back();
	}
	
	
}


#endif



