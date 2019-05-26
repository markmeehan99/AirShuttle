#include "user.h"

User::User() {
	this->userID = 0;
	this->time.hour = 0;
	this->time.minutes = 0;
}

User::User(int id, int hour, int minutes, int hotelId) {
	this->userID = id;
	this->time.hour = hour;
	this->time.minutes = minutes;
	this->hotelId = hotelId;
}

bool User::operator<(User u) {
	if (this->time.hour < u.time.hour) return true;
	else if (this->time.hour > u.time.hour) return false;
	else if (this->time.minutes < u.time.minutes) return true;

	return true;
}

int User::getHotelId() {
	return this->hotelId;
}
