#pragma once

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>


namespace PTO {
	class api {

	public:

		bool Setup = false;

		int exp;
		int uid;
		std::string ip;
		std::string post;
		std::string rank;
		std::string rep;
		std::string user;

		std::string appName;
		api(std::string appName) : appName(appName) {}

		void init()
		{
			if (appName.length() < 1)
			{
				std::cout << "\n\n Application Not Setup Correctly. Please give your application a name!" << std::endl;
				Sleep(4500);
				Setup = false;
				exit(0);
			}
			else
			{
				Setup = true;
			}
		}

		bool login(std::string key)
		{
			if (Setup)
			{
				cpr::Session session;

				cpr::Url url = { "https://api.patched.to/v1/user_info" };
				cpr::Header header = { {"Accept", "application/json"},
									 {"User-Agent", appName},
									 {"X-Auth-Key", key}
				};

				session.SetUrl(url);
				session.SetHeader(header);
				cpr::Response response = session.Get();

				auto json = nlohmann::json::parse(response.text);

				if (json[("status")]) // status ? true ? false
				{
					user = json[("user_info")][("user")];
					ip = json[("user_info")][("ip")];
					exp = json[("user_info")][("exp")];
					post = json[("user_info")][("post")];
					rank = json[("user_info")][("rank")];
					rep = json[("user_info")][("rep")];
					uid = json[("user_info")][("uid")];

					if (rank == "2")
					{
						rank = "Member";
					}
					else if (rank == "10")
					{
						rank = "Vip";
					}
					else if (rank == "11")
					{
						rank = "Nova";
					}
					else if (rank == "12")
					{
						rank = "Diamond";
					}
					else
					{
						rank = "Unknown";
					}


				}
				else
				{
					Sleep(2500);
					std::cout << "\n\n Status: Failure: ";
					std::cout << std::string(json[("message")]);
					return false;
				}
			}
			else
			{
				std::cout << "\n\n Please Initialize your application!" << std::endl;
			}
			
		}
	};
}