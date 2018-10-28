#include "non-templated.h"
#include "templated.h"
#include "customassert.h"
#include <iostream>

using namespace std;

class X{}x;

int main() {

	assertTestSoft(Templated::f(), "Empty");
	assertTestSoft(NonTemplated::f(), "Empty");

	assertTestSoft(Templated::f(228), "228");
	assertTestSoft(NonTemplated::f(228), "228");

	assertTestSoft(Templated::f(-700), "-700");
	assertTestSoft(NonTemplated::f(-700), "-700");

	assertTestSoft(Templated::f(3.14), "3.14");
	assertTestSoft(NonTemplated::f(3.14), "3.14");

	assertTestSoft(Templated::f("That WaS uNexPectEd"), "That WaS uNexPectEd");
	assertTestSoft(NonTemplated::f("That WaS uNexPectEd"), "That WaS uNexPectEd");
	
	pair<double, double> p(3.14, 3.22);
	assertTestSoft(Templated::f(p), "pair<double, double> p(3.14, 3.22)");
	assertTestSoft(NonTemplated::f(p), "pair<double, double> p(3.14, 3.22)");

	vector <double> v{2.14, 3, 3.14, 3.22, 6.4};
	assertTestSoft(Templated::f(v), "vector <double> v{2.14, 3, 3.14, 3.22, 6.4}");
	assertTestSoft(NonTemplated::f(v), "vector <double> v{2.14, 3, 3.14, 3.22, 6.4}");

	assertTestSoft(Templated::f(x), "X");
	assertTestSoft(NonTemplated::f(x), "X");

	system("pause");
	return 0;
}