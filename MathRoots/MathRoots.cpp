#include <iostream>
#include <cmath>
using namespace std;

class Programma
{
	class Kwadratische_fx
	{
		private:
			double aFactor, bFactor, cFactor, dFactor; //ax^3+bx^2+cx+d
			double wortelX1, wortelX2;
			
		public:
			Kwadratische_fx(double a, double b, double c, double d) {aFactor=a; bFactor=b; cFactor=c; dFactor=d;}
			void set_wortelX1(double x) {wortelX1=x;}
			void set_wortelX2(double y) {wortelX2=y;}
			
			double vergelijking(double x) {return aFactor*pow(x,3)+bFactor*pow(x,2)+cFactor*x+dFactor;}
			double bepaalsnijpunt()
			{
				double midden_x;
				const double EPS(1.0E-8);
				do
				{
					midden_x = (wortelX1 + wortelX2) / 2.0;
					if (vergelijking(wortelX1) * vergelijking(midden_x) > 0.0)
						wortelX1 = midden_x;
					else
						wortelX2 = midden_x;
				} while (fabs(vergelijking(midden_x)) > EPS);
				
				return midden_x;
			}
	};
	
	public:
		void testRun()
		{
			Kwadratische_fx fx(1.0,0,-1,1.0);
			fx.set_wortelX1(-2.0);
			fx.set_wortelX2(-1.0);
			cout << endl << "\n\nDe wortel van de functie in interval";
			cout << "x1 en x2 wordt: ";
			cout << fx.bepaalsnijpunt() << endl;
		}
};
				

int main(int argc, const char *argv[])
{
	Programma start;
	start.testRun();
	return 0;
}
