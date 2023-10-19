#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
namespace Utils {

	/// <summary>
	/// Represents a date and time structure.
	/// </summary>
	struct DateTime
	{
		unsigned int year = 0;

		unsigned short month = 0;

		unsigned short day = 0;

		unsigned short hour = 0;

		unsigned short minute = 0;

		unsigned short second = 0;

		std::ostream& operator<<(std::ostream& os)
		{
			os << this->day << '/' 
				<< this->month << '/' 
				<< this->year << ' ' 
				<< this->hour << ':' 
				<< this->minute << ':' 
				<< this->second;

			return os;
		}

		std::string ToStringTime() const
		{
			return std::to_string(this->hour) + ':' +
					std::to_string(this->minute) + ':' +
					std::to_string(this->second);
		}

		std::string ToStringDate() const
		{
			return std::to_string(this->day) + '/' +
					std::to_string(this->month) + '/' +
					std::to_string(this->year);
		}

		std::string ToStringDateTime() const
		{
			return std::to_string(this->day) + '/' + 
					std::to_string(this->month) + '/' + 
					std::to_string(this->year) + ' ' + 
					std::to_string(this->hour) + ':' + 
					std::to_string(this->minute) + ':' + 
					std::to_string(this->second);
		}

		std::string ToFileNameDateTime() const
		{
			return std::to_string(this->day) + '-' +
				std::to_string(this->month) + '-' +
				std::to_string(this->year) + ' ' +
				std::to_string(this->hour) + '-' +
				std::to_string(this->minute) + '-' +
				std::to_string(this->second);
		}
	};
}}}