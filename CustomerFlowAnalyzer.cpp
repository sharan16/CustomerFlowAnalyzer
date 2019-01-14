///////////////////////////////////////////////////////////////////////////////////////////////////
// Project Title : VisitorCounter
// Related Files : VisitorCounter.cpp
// Methods Lists : mini, avg, maxi, print, log, now
// Semester/Term : FALL 2017
//
// Author(s)     : Sharan S., Tharseken N., Janujan G.
// Course        : ECE150 - Introduction to Programming
// Course Prof   : PAUL WARD
//
//
// Program Description : With the help of an arduino board, we will be using an ultrasonic sensor
//                       to count the number of people (visitors, customers, etc.) that walk through
//						 a door (or essentially the sensor). This data will be eventually collected
//                       and compiled. Statistics such as minimum, maximum, and average number of 
//						 visitors will calculated and output to a textfile, which can later be accessed.
//						 This program is compiled on a Linux machine and run using an Omega2 Board.
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////***#INCLUDE STATEMENTS***//////////////////////////////////////

// we have made sure we are allowed them...

	// include for usual .cpp files
	#include <iostream>
	#include <stdlib.h>

	// include needed for omega board
	#include <stdio.h>
	#include <string.h>
	#include <string>
	#include <unistd.h>
	#include <fcntl.h>

	// include statement to write to files and include 
	#include <fstream>
	#include <time.h>

	// include statement to read GPIO pins on the omega board
	#include <ugpio/ugpio.h>

	// namespace declaration
	using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////***FUNCTION DEFINITIONS***/////////////////////////////////////

	// function definitions for the statistic helper function
	void stats();
	int mini(const int dataset[], const int size);
	int avg(const int dataset[], const int size);
	int maxi(const int dataset[], const int size);

	// helper function to print the number of people for every day of the week
	void print();

	// functions used to the time stamp
	bool log(string arg);
	string now();

////////////////////////////////***GLOBAL VARIABLE DEFINITIONS***//////////////////////////////////

	// array declaration for each day of the week
	int mon [100];
	int tue [100];
	int wed [100];
	int thu [100];
	int fri [100];
	int sat [100];
	int sun [100];

	// declaration for the index of the arrays
	int monIndex = -1;
	int tueIndex = -1;
	int wedIndex = -1;
	int thuIndex = -1;
	int friIndex = -1;
	int satIndex = -1;
	int sunIndex = -1;

///////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////***FUNCTIONS***//////////////////////////////////////////

int main (const int argc, const char* const argv[]) {
	
// constant and variable declaration

	// variables to read GPIO 0 (day counter button)
	int rq0;
	int rv0;
	int gpio0 = 0;
	int value0;

	// variables to read GPIO 3 (ultrasonic sensor input)
	int rq;
	int rv;
	int gpio = 3;
	int value;

	log("TRACE: SETTING ALL DAY ARRAYS TO 0")

	// for loop to set each value in the Monday array to 0
	for (int i = 0; i < 100; i++){
		mon [i] = 0;
	}
	// for loop to set each value in the Tuesday array to 0
	for (int i = 0; i < 100; i++){
		tue [i] = 0;
	}
	// for loop to set each value in the Wednesday array to 0
	for (int i = 0; i < 100; i++){
		wed [i] = 0;
	}
	// for loop to set each value in the Thursday array to 0
	for (int i = 0; i < 100; i++){
		thu [i] = 0;
	}
	// for loop to set each value in the Friday array to 0
	for (int i = 0; i < 100; i++){
		fri [i] = 0;
	}
	// for loop to set each value in the Saturday array to 0
	for (int i = 0; i < 100; i++){
		sat [i] = 0;
	}
	// for loop to set each value in the Sudnay array to 0
	for (int i = 0; i < 100; i++){
		sun [i] = 0;
	}

//////////////////////////***EXPORTING AND INITIALIZING VALUE OF BUTTON***/////////////////////////

// check to see if the GPIO is already exported

	if ((rq0 = gpio_is_requested(gpio0)) < 0) {
		log("TRACE : gpio is requested");
		return 0;										// return 0 for error
	}

// export the gpio

	if (!rq0) {
		log ("TRACE : exporting gpio");
		if ((rv0 = gpio_request(gpio0, NULL)) < 0) {
			log("FATAL : gpio_request");
			return 0;									// return 0 for error
		}
	}

// set the initial input direction

	log ("TRACE : setting the input");

	if ((rv0 = gpio_direction_input(gpio0)) < 0) {
		log ("ERROR : gpio_direction_input");
	}

// read the GPIO 20 times

	log ("TRACE : being reading GPIO");
	log ("TRACE : THE GPIO PIN IS " << gpio0);

///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////***EXPORTING AND INITIALIZING VALUE OF ULTRASONIC SENSOR***/////////////////////

// constant and variable declaration

	int pCount = 0;
	int dCount = -1;

// check to see if the GPIO is alreay exported

	if ((rq = gpio_is_requested(gpio)) < 0) {
		log("FATAL : gpio_is_requested");
		return 0;
	}

// export the gpio

	if (!rq) {
		log("TRACE : exporting gpio");
		if ((rv = gpio_request(gpio, NULL)) < 0) {
			log("ERROR : gpio_request");
			return 0;
		}
	}

// set the initial input direction

	log("TRACE : setting the input");

	if ((rv = gpio_direction_input(gpio)) < 0) {
		log("FATAL : gpio_direction_input");
	}

// read the GPIO

	log("TRACE : being reading GPIO" << gpio);

	while (true) {

		// read the gpio
		value = gpio_get_value(gpio);
		value0 = gpio_get_value(gpio0);


		// check to see if the value of the button GPIO is equal to 1
		if (value0 == 1) {
			dCount++;
			log("TRACE : Day has been incremented succesfully");
			
			// switch case structure to increment the index of the day of the week
			switch (dCount%7) {
				case 0: 
						monIndex++;
					break;
				case 1:
						tueIndex++;
					break;
				case 2: 
						wedIndex++;
					break;
				case 3: 
						thuIndex++;
					break;
				case 4: 
						friIndex++;
					break;
				case 5: 
						satIndex++;
					break;
				case 6: 
						sunIndex++;
					break;
			}
			pCount=0;

			// delay the function by 500000 microseconds
			usleep(500000);
		}

		// check to see if the value of the ultrasonic sensor GPIO is 1
		if (value == 1) {
			pCount++;
			log("TRACE : Person has been detected succesfully");

			// switch case to increment the number of people for each respective day
			switch(dCount%7){
				case 0: 
					mon[monIndex] = pCount;
					break;
				case 1: 
					tue[tueIndex] = pCount;
					break;
				case 2: 
					wed[wedIndex] = pCount;
					break;
				case 3: 
					thu[thuIndex] = pCount;
					break;
				case 4: 
					fri[friIndex] = pCount;
					break;
				case 5: 
					sat[satIndex] = pCount;
					break;
				case 6: 
					sun[sunIndex] = pCount;
					break;
			}

			// call the print function to output the number of people for a specific day
			
			log("TRACE: live printing data now")
			print();

			// delay the function by 5000000 microseconds
			usleep (500000);

			// call the stats function to output the final statistics log
			stats();
		}
	}

// unexport the GPIO pin for the day-incrementing button

	if (!rq0) {
		log ("TRACE : unexporting GPIO");
		if (gpio_free(gpio0) < 0){
			log("ERROR : gpio_free");
		}
	}

// unexport the GPIO pin for the ultrasonic sensor

	if (!rq) {
		log ("TRACE : unexporting GPIO");
		if (gpio_free(gpio) < 0){
			log("ERROR : gpio_free");
		}
	}
}


//////////////////////***PRINT FUNCTION TO  ACTIVELY PRINT THE DAILY STATS***//////////////////////

void print(){

	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	
	// print the layout and count if the current day is Monday
	for(int i=0;i<=monIndex;i++){
		cout<<"MONDAY: " << mon[i]<<",";
	}
	cout <<"" <<endl;

	// print the layout and count if the current day is Tuesday
	for(int i=0;i<= tueIndex;i++){
		cout<<"TUESDAY: " << tue[i]<<",";
	}
	cout <<"" <<endl;

	// print the layout and count if the current day is Wednesday
	for(int i=0;i<=wedIndex;i++){
		cout<<"WEDNESDAY: " << wed[i]<<",";
	}
	cout <<"" <<endl;

	// print the layout and count if the current day is Thursday
	for(int i=0;i<=thuIndex;i++){
		cout<<"THURSDAY: " << thu[i]<<",";
	}
	cout <<"" <<endl;

	// print the layout and count if the current day is Friday
	for(int i=0;i<=friIndex;i++){
		cout<<"FRIDAY: " << fri[i]<<",";
	}
	cout <<"" <<endl;

	// print the layout and count if the current day is Saturday
	for(int i=0;i<=satIndex;i++){
		cout<<"SATURDAY: " << sat[i]<<",";
	}
	cout <<"" <<endl;

	// print the layout and count if the current day is Sunday
	for(int i=0;i<=sunIndex;i++){
		cout<<"SUNDAY: " << sun[i]<<",";
	}
	cout <<"" <<endl;

	log("TRACE: live display has been printed")
}

///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////***HELPER FUNCTIONS FOR CALCULATING STATS***////////////////////////////

// function to calculate the average of the array for each day
int avg (int day[], int size) {
	
// constants and variable declaration
	int sum = 0;

// for-loop structure to determine the sum of all the elements in the array
	for (int i = 0; i < size; i++) {
		sum += day[i];
	}

// return the sum of the array elements divided by the size of the array
	return sum/size;
}


// function to determine the minimum number of people on a specific day of the week
int mini (int day[], int size) {

// constants and variable declaration
	int min = day[0];

// for-loop structure to determine the minimum value of an array
	for (int i = 0; i < size; i++) {
		if (day[i] < min)
			min = day[i];
	}

// return the minimum value of the array
	return min;
}


// function to determine the maximum number of people on a specific day of the week
int maxi (int day[], int size) {

// constants and variable declaration
	int max = day[0];

// for-loop structure to determine the maximum value of an array
	for (int i = 0; i < size; i++) {
		if (day[i] > max)
			max = day[i];
	}

// return the  maximum value of the array
	return max;
}

// function to determine the statistics of the data
void stats () {

// returns back to the function if the indexes of any of the days are -1 (if one week has not passed)
	if (monIndex <0 || tueIndex <0 || wedIndex <0 ||   thuIndex <0 || friIndex <0 || satIndex <0 || sunIndex <0){
		log("WARNING : Cannot calculate stats because atleast one week of data is needed");
		return;
	}

// constant and variable declaration
	
	// declaration for average, min, and max arrays

	// the array consists of each day of the week
	int average[7];
	int min[7];
	int max[7];

	// declaration of the busiest and least busiest days
	int leastBusiestDayAvg = 0;
	int busiestDayAvg = 0;

	// declaration of the average daily amount
	int averageDaily = 0;	


//average of leastbusiest and busiest days

	string busiestDay = "";
	string leastBusiestDay = "";


	//store average of each day in average array
	average [0] = avg (mon, monIndex + 1);
	average [1] = avg (tue, tueIndex + 1);
	average [2] = avg (wed, wedIndex + 1);
	average [3] = avg (thu, thuIndex + 1);
	average [4] = avg (fri, friIndex + 1);
	average [5] = avg (sat, satIndex + 1);
	average [6] = avg (sun, sunIndex + 1);

	//store minimum of each day in average array
	min [0] = mini (mon, monIndex + 1);
	min [1] = mini (tue, tueIndex + 1);
	min [2] = mini (wed, wedIndex + 1);
	min [3] = mini (thu, thuIndex + 1);
	min [4] = mini (fri, friIndex + 1);
	min [5] = mini (sat, satIndex + 1);
	min [6] = mini (sun, sunIndex + 1);

	//store maximum of each day in average array
	max [0] = maxi (mon, monIndex + 1);
	max [1] = maxi (tue, tueIndex + 1);
	max [2] = maxi (wed, wedIndex + 1);
	max [3] = maxi (thu, thuIndex + 1);
	max [4] = maxi (fri, friIndex + 1);
	max [5] = maxi (sat, satIndex + 1);
	max [6] = maxi (sun, sunIndex + 1);


	//find the daily average, least busiest and busiest day averages
	averageDaily = avg (average, 7);
	leastBusiestDayAvg = mini (average, 7);
	busiestDayAvg = maxi (average, 7);

	//set values for the average count of each day
	int monAvg = avg (mon, monIndex + 1);
	int tueAvg = avg (tue, tueIndex + 1);
	int wedAvg = avg (wed, wedIndex + 1);
	int thuAvg = avg (thu, thuIndex + 1);
	int friAvg = avg (fri, friIndex + 1);
	int satAvg = avg (sat, satIndex + 1);
	int sunAvg = avg (sun, sunIndex + 1);

	//get the day for the busiest and least busiest
	if(busiestDayAvg == average[0]) {
		busiestDay = "Monday";		
	} else if (busiestDayAvg == average[1]) {
		busiestDay = "Tuesday";
	} else if (busiestDayAvg == average[2]) {
		busiestDay = "Wednesday";
	} else if (busiestDayAvg == average[3]) {
		busiestDay = "Thursday";
	} else if (busiestDayAvg == average [4]) {
		busiestDay = "Friday";
	} else if (busiestDayAvg == average [5]) {
		busiestDay = "Saturday";
	} else if (busiestDayAvg == average [6]) {
		busiestDay = "Sunday";
	}

	// if-else statement to find the least busiest day
	if(leastBusiestDayAvg == average[0]) {
		leastBusiestDay = "Monday";		
	} else if (leastBusiestDayAvg == average[1]) {
		leastBusiestDay = "Tuesday";
	} else if (leastBusiestDayAvg == average[2]) {
		leastBusiestDay = "Wednesday";
	} else if (leastBusiestDayAvg == average[3]) {
		leastBusiestDay = "Thursday";
	} else if (leastBusiestDayAvg == average [4]) {
		leastBusiestDay = "Friday";
	} else if (leastBusiestDayAvg == average [5]) {
		leastBusiestDay = "Saturday";
	} else if (leastBusiestDayAvg == average [6]) {
		leastBusiestDay = "Sunday";
	}

//// outputting the statistics to a text file using ofstream
	ofstream outfile;

	outfile.open ("datalog.txt");

	outfile << "\t\t CUSTOMER STATISTICS\n" << endl;

	outfile << "Busiest Day : " << busiestDay << endl;

	outfile << "\nLeast Busiest Day : " << leastBusiestDay << endl;

	outfile << "\nAverage Daily Activity : " << averageDaily << endl;

	outfile << "\n++++++++++++++++++++++++ Daily Stats ++++++++++++++++++++\n" << endl;

	outfile << "------------------------MONDAY------------------------\n" << endl;

	outfile << "\tAverage : " << monAvg << "   Lowest : " << min[0] << "   Highest : " << max[0] << endl;

	outfile << "\n------------------------TUESDAY------------------------" << endl;

	outfile << "\tAverage : " << tueAvg << "   Lowest : " << min[1] << "   Highest : " << max[1] << endl;

	outfile << "\n------------------------WEDNESDAY------------------------" << endl;

	outfile << "\tAverage : " << wedAvg << "   Lowest : " << min[2] << "   Highest : " << max[2] << endl;

	outfile << "\n------------------------THURSDAY------------------------" << endl;

	outfile << "\tAverage : " << thuAvg << "   Lowest : " << min[3] << "   Highest : " << max[3] << endl;

	outfile << "\n------------------------FRIDAY------------------------" << endl;

	outfile << "\tAverage : " << friAvg << "   Lowest : " << min[4] << "   Highest : " << max[4] << endl;

	outfile << "\n------------------------SATURDAY------------------------" << endl;

	outfile << "\tAverage : " << satAvg << "   Lowest : " << min[5] << "   Highest : " << max[5] << endl;

	outfile << "\n------------------------SUNDAY------------------------" << endl;

	outfile << "\tAverage : " << sunAvg << "   Lowest : " << min[6] << "   Highest : " << max[6] << endl;

	outfile << "\nThank you for using our software! For technical support call 34223564." << endl;

	outfile << "\nViggy says : Thank you for your time!" << endl;

  	outfile << output << endl;
  	outfile.close();
  	log ("TRACE: DataLog.txt created successfully")
  }

  bool log(string arg){
  	ofstream log;

  	log.open("log.txt", ios_base::app);
  	log << "[" << now() << "]: " << arg<< "\n";
  	log.close();
  	return true;

  }
string now()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d|%X", &tstruct);

    return buf;
}