#pragma warning(disable : 4996)

#include <iostream>
#include <fstream>
#include <filesystem>
#include "API.hpp"

using namespace PTO;
void login();

std::string appName = "kekw";

api PTOApp(appName);

int main()
{
	SetConsoleTitleA("Patched.to native Auth example");

	std::cout << "\n\n Connecting...";
	PTOApp.init(); // required
	Sleep(2000);
	system("cls");
	login(); // required
	system("cls");
	
	// Logged in successfully
	// Good luck from here with your application!

	std::cout << "\n Welcome back: " << PTOApp.user << std::endl;
	std::cout << "\n Ip: " << PTOApp.ip << std::endl;
	std::cout << " Exp: " << PTOApp.exp << std::endl;
	std::cout << " Posts: " << PTOApp.post << std::endl;
	std::cout << " Rank: " << PTOApp.rank << std::endl;
	std::cout << " Rep: " << PTOApp.rep << std::endl;
	std::cout << " Uid: " << PTOApp.uid << std::endl;

	Sleep(-1); // Keep application open forever (just for debugging purposes)
}

void login() // yes this can be done better but ok who tf cares.
{
	if (std::filesystem::exists("config." + appName))
	{
		std::string key;
		std::ifstream InFile("config." + appName, std::ios::in);
		std::getline(InFile, key);

		InFile.close();

		std::cout << "\n\n Activating your old auth key: ";
		std::cout << key;
		Sleep(1500);

		if (PTOApp.login(key))
		{
		}
		else
		{
			std::string del = "config." + appName;
			if (remove(del.c_str()) == 0)
			{
				system("cls");
				goto A;
			}
		}
	}
	else
	{
	A:
		std::cout << "\n\n Please enter your auth key: ";
		bool authed = false;
		while (authed == false)
		{
			std::string authKey;
			std::cin >> authKey;
			if (PTOApp.login(authKey))
			{
				std::ofstream OutFile("config." + appName, std::ios::out);
				OutFile << authKey;
				OutFile.close();
				authed = true;
			}
			else
			{
				Sleep(2500);
				system("cls");
				goto A;
			}
		}
	}
}