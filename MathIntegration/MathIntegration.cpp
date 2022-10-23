#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

class Programm
{
	class IntegralSimpson
	{
		private:
			double interval, beginx, endx, valuex, sum;
			
		public:
			void set_valuex(const double x) {valuex = x;}
			void set_sum(const double s) {sum = s;}
			double get_sum() const {return sum;}
			
			double fx(const double x) {return exp(2*x);} // this is the function you want to integrate
			double e_2x() {return 0.5*(exp(2.0)-1.0);} // optional = calculates the value using the cmath library
			
			IntegralSimpson (const int n, const double a, const double b)
			{ interval = n; beginx = a; endx = b;}
			
			void CalculateIntegral()
			{
				double h {(endx - beginx)/interval};
				double summation = fx(beginx) + fx(endx);
				for (int i{1}; i<interval; i++)
				{
					set_valuex(beginx + i*h); // x = a + i.h
					if ((i%2) == 0)
						summation += 2.0*fx(valuex);
					else
						summation += 4.0*fx(valuex);
				}
				
				summation += fx(beginx) + fx(endx);
				summation *= (h/3.0);
				set_sum(summation);
			}
	};
	
	public:
		void Start()
		{
			int n;
			double startlimit {0.0}, stoplimit {1.0};
			
			do
			{
				cout << "\nEnter the number of intervals: ";
				cin >> n;
			} while ((n%2) != 0); // interval must be an even number
			
			IntegralSimpson calculate = IntegralSimpson(n, startlimit, stoplimit);
			cout << setprecision(7);
			cout << endl;
			cout << "Simpson integral for function is: ";
			calculate.CalculateIntegral();
			cout << calculate.get_sum() << endl;
			cout << "Exact value is: ";
			cout << calculate.e_2x();
		}
};

int main(int argc, const char *argv[])
{
	Programm start;
	start.Start();
	return 0;
}
