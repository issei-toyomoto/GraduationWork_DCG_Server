#include "Login.h"

String Login::CreateLoginID(JSON playerInfo)
{
	//PlayerDBのJSONを読み込む
	JSON playerDB = JSON::Load(U"../source/system/JSON/data/DBPlayer.json");

	//PlayerDBを読み込めたか判定
	if (playerDB.isEmpty()) {
		return U"PlayerDBを読み込めませんでした";
	}
	else {
		String te = playerDB.format();
		Print << U"PlayerDBの読み込み成功";
	}

	return playerDB.format();
}

String Login::GenerateLoginID(size_t length)
{
	static const String chars = U"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	String result;

	for (size_t i = 0; i < length; ++i)
	{
		result += chars[Random(chars.size() - 1)];
	}

	return result;
}
