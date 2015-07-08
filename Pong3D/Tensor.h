#pragma once
#include <stdexcept>
#include <string>



namespace phs
{

	class Tensor
	{
		double comp[3][3];
	public:
		Tensor();
		Tensor(const Tensor&);
		Tensor(double xa, double xb, double xc, double ya, double yb, double yc, double za, double zb, double zc);
	
		inline double get(unsigned int a, unsigned int b)const
		{
			if(a<3&&b<3)
			{
				return comp[a][b];
			}else
			{
				throw std::overflow_error("Array Index Out Of Bounds");
			}
		}
	
		Tensor operator=(const Tensor&);

		Tensor operator*(const double);
		void operator*=(const double);
		
		void transpose();
		void invert();

		Tensor getInversion();
		Tensor getTransposition();

		~Tensor();

		std::string debug(std::string);
	};

}
