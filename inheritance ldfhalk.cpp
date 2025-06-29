#include<iostream>

using namespace std;

class vehicle{
	protected:
		string model;
		string color;
		public:
		vehicle(string model, string color)
		{
			this -> model = model;
			this -> color = color;
		}
};

class car: public vehicle{
	protected:
		int number;
		`
		public:
			car(string model, string color, int number):vehicle(model, color)
			{
				this-> number = number; 
			}
			void show()
			{
				cout<<model<<endl;
				cout<<color<<endl;
				cout<<number<<endl;
			}
};

int main()
{
	car cr("bmw", "blue", 7777);
	
	cr.show();
	return 0;
	
}
