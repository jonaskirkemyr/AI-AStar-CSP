#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <sstream>
#include "../exprtk/exprtk.hpp"


namespace Functions
{
	static string intToStr(int i)
	{
	   stringstream stream;//create a stringstream
	   stream << i;//add number to the stream
	   return stream.str();//return a string with the contents of the stream
	}

	static int strToInt(string i)
	{
		int number;
		istringstream(i)>>number;

		return number;
	}


	struct compNodes
	{
		template<class T>
		bool operator()(const T& left,const T& right) const
		{
			return ((*left)>(*right));
		}
	};

	template <class T>
	bool compareBig(T* left,T* right)
	{
		//cout<<"COMPAGE BIG"<<endl;
		return ((*left)>(*right));
	}

	template <class T>
	bool compareLess(T* left,T* right)
	{
		return ((*left)<(*right));
	}



	template <typename T>
	void square(string a)
	{

		string expr_string=a;                           

		T x=T(0);
		T y=T(0);
		T z=T(0);


		T x_values[5]={0,1,2,3,4};
		T y_values[5]={0,1,2,3,4};
		T z_values[5]={0,1,2,3,4};

		exprtk::symbol_table<T> symbol_table;
		symbol_table.add_variable("x",x);
		symbol_table.add_variable("y",y);
		symbol_table.add_variable("z",z);
		symbol_table.add_constants();

		exprtk::expression<T> expression;
		expression.register_symbol_table(symbol_table);

		exprtk::parser<T> parser;
		parser.compile(expr_string,expression);


		for(int i=0;i<5;++i)
		{
			x=x_values[i];
			for(int j=0;j<5;++j)
			{
				y=y_values[j];
				for(int k=0;k<5;++k)
				{
					z=z_values[k];
					cout<<"----run----"<<endl;
					cout<<"   x: "<<x<<endl;
					cout<<"   y: "<<y<<endl;
					cout<<"   z: "<<z<<endl;
					cout<<" result: "<<expression.value()<<endl;
					cout<<"--end run--"<<endl;
				}
			}
		}


	}




};

#endif