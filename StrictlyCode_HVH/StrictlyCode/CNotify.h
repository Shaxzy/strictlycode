#pragma once

#include <string>
#include <vector>

struct Notification
{
	std::string Message = "";
	int Ticks = 4096;
};

namespace PushNotifications
{
	void Update();
	void Push(std::string Message);
};
