#pragma once

struct time_ {
	int hour;
	int minutes;
};

class User {
private:
	int userID;
	time_ time;
	int hotelId;

public:
	User();
	User(int id, int hour, int minutes, int hotelId);
	bool operator<(User u);
	int getHotelId();
};
