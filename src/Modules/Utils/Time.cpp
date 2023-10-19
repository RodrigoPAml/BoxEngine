#include <BoxEngine.hpp>
#include "Time.hpp"

namespace BoxEngine {
namespace Modules {
namespace Utils {
namespace Time {

	double GetTimestamp()
	{
		return glfwGetTime();
	}

	DateTime GetDateTime()
	{
		time_t now = time(0);

		tm* ltm = localtime(&now);

		DateTime date = { 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour,  ltm->tm_min, ltm->tm_sec };

		return date;
	}
}}}}
