#pragma once
#include <iostream>
#include <ctime>
#include <string>

struct PersonID {
	std::string series;
	int number;
};

class Person {
private: 

	PersonID id;
	std::string firstName;
	std::string middleName;
	std::string lastName;
	time_t birthdate;


public:

	Person() {
		id.number = 0;
		id.series = "";
		firstName = "";
		middleName = "";
		lastName = "";
		birthdate = 0;
	}

	Person(std::string first, std::string last) {
		id.number = 0;
		id.series = "";
		firstName = first;
		middleName = "";
		lastName = last;
		birthdate = 0;
	}
	
	void setDate(int day, int month, int year) {
		struct tm timeinfo;
		timeinfo.tm_year = year - 1900;
		timeinfo.tm_mon = month - 1;
		timeinfo.tm_mday = day;
		birthdate = mktime(&timeinfo);
	}

	void setMiddleName(std::string name) {
		middleName = name;
	}

	friend std::ostream& operator<<  (std::ostream& out, Person& pers)
	{
		struct tm *ptm;
		ptm = gmtime(&pers.birthdate);
		out << pers.lastName;
		out << " ";
		out << pers.firstName;
		out << " ";
		out << pers.middleName;
		out << " ";
		out << ptm->tm_mday;
		out << ".";
		out << (ptm->tm_mon + 1);
		out << ".";
		out << (ptm->tm_year + 1900);
		return out;
	}
};