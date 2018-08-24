# simple_rpn
Verry simple reverse polish notation formula interpreter

This is single header library. It is verry basic and probably not too fast. 

It allows for easy implementation of any formula that requires variables
and constats. It does not support too many operators, but feel free to 
edit. The source is as simple and straightformward as probably possible.

## Example

```c++
#include <iostream>
#include "srpn.hpp"


int main(int argc, char **argv) {
	
	std::string program = "10 x * 2 +"; // Reverse Polish Notation formula
	for (double x: {1,2,20}) {
		std::cout  << program << " = "<< rpn::calculate(program, {{"x",x}}) << std::endl;
	}
	
	return 0;
}
```

## API

There is only one API call:

```c++
	/**
	 * calculates rpn formula given as string and with variables given as map.
	 * 
	 * @arg formula_ the formula. It can look like "3 x * 5 y + -
	 * @arg variables_ the map of variable values that will be placed in the formula. It is in the form of variable_name:value. Variables must consist only of letters and numbers (number cannot be first). For other variable names the function behavior is undefined!
	 * @return calculated formula result
	 * */
	inline double calculate(const std::string &formula_, const std::map<std::string,double> &variables_ = {});
```

Note: the supported operators can be verified in srpn.hpp

