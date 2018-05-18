#include "CNotify.h"
#include "DrawManager.h"
std::vector<Notification> Notifications;

void PushNotifications::Update()
{
	int iScreenWidth, iScreenHeight;
	NSDK::I::Engine()->GetScreenSize(iScreenWidth, iScreenHeight);
	int i = 0;
	while (i < Notifications.size())
	{
		if (Notifications[i].Ticks >= 0)
		{
			NSDK::uint8_t alpha = Notifications[i].Ticks * .0622558594;
			if (i < 16)
			Drawing::DrawString(NSDK::Color(255, 0, 0, alpha), Drawing::hStrictlyFont, Notifications[i].Message.c_str(), iScreenWidth - 1900, (15 * i) + 55);
			Notifications[i].Ticks--;
			i++;
		}
		else
			Notifications.erase(Notifications.begin() + i);
	}
}

void PushNotifications::Push(std::string Message)
{
	Notification n;
	n.Message = "[strictlycode] " + Message;
	Notifications.push_back(n);
}