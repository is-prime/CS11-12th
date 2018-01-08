#include<iostream>
#include<string>
#include<stdio.h>

using namespace std;

string decipherMonth(int);
int getNumDays(int, int);
int getDayOfWeek(int, int, int);

struct Month {
	int monthNum = 1, numDays;
	string monthName = "";
};

class Calendar {
public:
	Month month;
	int year;

	void display() {
		cout << decipherMonth(month.monthNum) << "\t\t\t" << year << endl;
		cout << "M\tT\tW\tTh\tF\tS\tSu" << endl;
		int day = 1, endOffset = 6; //endOffset is to account for 28, 29, 30 or 31 days at the end of calendar 

		month.numDays = getNumDays(month.monthNum, year); //get number of days in the month
		int firstDayOfWeek = getDayOfWeek(year, month.monthNum, 1); 
		if (firstDayOfWeek == 0) firstDayOfWeek += 7; // change sunday from 0 to 7
		int startOffset = firstDayOfWeek - 1; //to account for missing days at the beginning of calendar 

		while (day <= month.numDays) {
			if (firstDayOfWeek != 1) { //if first day of week isn't monday, skip the positions till the first day
				while (firstDayOfWeek != 1) {
					cout << "\t";
					--firstDayOfWeek;
				}
			}
			for (int j = day; j <= (day + endOffset - startOffset); ++j) {
				if (j <= month.numDays) cout << j << "\t";
			}
			cout << "\n";

			if ((day + 7) < 28) { //if-else to check for end of last week
				day += 7 - startOffset;
			} else {
				endOffset = month.numDays - 28;
				day += 7;
			}
			startOffset = 0;
		}
			
	}

};
string decipherMonth(int m) { //get name of month from its number
	string months[] = { "Jan","Feb","Mar","Apr","May","Jun",
						"Jul","Aug","Sep","Oct","Nov","Dec" };
	return months[m - 1];
}
int getNumDays(int m, int y) { //get number of days in month from its number
	if (m == 2) {
		if (y % 400 == 0 || (y % 100 != 0 && y % 4 == 0)) return 29;
		else return 28;
	} else if (m == 4 || m == 6 || m == 9 || m == 11) {
		return 30;
	} else {
		return 31;
	}
}
int getDayOfWeek(int y, int m, int d)	{ // using Zeller's congruence method to get the day of week from year, month, and date 
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 }; 
	y -= m < 3;
	return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
} 
int main() {
	Calendar calendar;

	cout << "Enter Month:\t ";
	cin >> calendar.month.monthNum;
	cout << "Enter Year:\t ";
	cin >> calendar.year;

	calendar.display();
	
	return 0;
}



