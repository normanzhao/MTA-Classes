#include "Console.h"
#include "trainStopData.h"
#include "MTAData.h"
#include <iostream>;
using namespace std;
Console::Console() 
{
	MTAData mtad;
	bool end = false;
	while (end == false)
	{
		cout << "_____Menu_____\n1. Trip planner\n2. Distance calculator\n3. Route listing\n4. Stop lookup\n5. Stop proximity\n6. Exit\n";
		int choice;
		cin >> choice;
		switch (choice)
		{
			default:
			{
				cout << "\nInvalid choice, please choose again";
				cout << "\n\n";
				break;
			}
			case 1:
			{
				mtad.planRoute();
				cout << "\n\n";
				break;
			}
			case 2:
			{
				trainStopData stop1 = mtad.search();
				trainStopData stop2 = mtad.search();
				mtad.stopDistance(stop1, stop2);
				break;
			}
			case 3:
			{
				mtad.mapRoute();
				break;
			}
			case 4:
			{
				mtad.stopLookup();
				break;
			}
			case 5:
			{
				mtad.stopProx();
				break;
			}
			case 6:
			{
				end = true;
				break;
			}

		}
	}




};



