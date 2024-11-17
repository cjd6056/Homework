// Participation Week 09, Conor & Gabrielle Dowdell

#include <iostream>
using namespace std;


template <bool... digits>
int reversed_binary_value() {
    int result = 0;
    int placeValue = 1;
    for (bool digit : {digits...}) 
    {
        if (digit) result += placeValue;
        placeValue <<= 1; 
    }
    return result;
}



template <int n, bool...digits>
struct CheckValues {
  	static void check(int x, int y)
  	{
    	CheckValues<n-1, 0, digits...>::check(x, y);
    	CheckValues<n-1, 1, digits...>::check(x, y);
  	}
};

template <bool...digits>
struct CheckValues<0, digits...> {
  	static void check(int x, int y)
  	{
    	int z = reversed_binary_value<digits...>();
    	std::cout << (z+64*y==x);
  	}
};

int main()
{
    std::cout << "Enter number of cases, then x and y values respectively " << std::endl;
    std::cout << "For example:\n 2\n 65 1\n " << std::endl;


  	int t; std::cin >> t;

  	for (int i=0; i!=t; ++i) {
		int x, y;
    	cin >> x >> y;
    	CheckValues<6>::check(x, y);
    	cout << "\n";
  	}
}
