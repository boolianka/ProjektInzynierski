// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

//#include "..\..\..\algebra\dyn_mat.hpp"
#include "..\..\..\algebra\dyn_vec.hpp"

int main(int argc, char* argv[])
{
	dyn_vec<float> u;
	u + u;
	u - u;
	u*u;
	u / 2;
	u * 2;
	2 * u;
	u.dist(u);
	u.dist_sq(u);
	u.length();
	u.length_sq();
	u.dot(u);
	u.normalize();
	u = u;

	return 0;
}

