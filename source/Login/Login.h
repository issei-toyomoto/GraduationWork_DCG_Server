#pragma once
#include <Siv3d.hpp>

#define LOGINID_CHRA_COUNT 10

class Login
{
private:
	String GenerateLoginID(size_t length);

public:
	String CreateLoginID(JSON playerInfo);

};

