#include "Login.h"

String Login::CreateLoginID(JSON playerInfo)
{
	//
	String result;

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

	//クラアントから送られてきた値を取得
	String playerID = playerInfo[U"playerID"].getString();
	int password = playerInfo[U"password"].get<int>();

	//ログインしてきたプレイヤー情報とDBにプレイヤー情報が一致しているか確認
	bool found = false;

	// JSON の配列をコピーして書き換え可能にする
	Array<JSON> players;
	for (const auto& p : playerDB.arrayView()) {  // ここは const でOK
		players << p;  // コピーを作る
	}

	// コピーした配列を変更
	for (auto& player : players) {  // 書き換え可能
		String id = player[U"playerID"].getString();
		int pass = player[U"password"].get<int>();

		if (id == playerID && pass == password) {
			found = true;
			result = GenerateLoginID(10);
			player[U"loginID"] = result;  // 書き換え可能
			break;
		}
	}

	// 変更を JSON に戻す
	playerDB = JSON(players);

	//結果
	if (found) {
		Print << U"ログイン成功！";
		Print << U"loginID : " << result;

	}
	else {
		result = U"IDまたはパスワードが間違っています";
	}

	if (playerDB.save(U"../source/system/JSON/data/DBPlayer.json")) {
		Print << U"DBの更新成功！";
	}
	else {
		Print << U"DBの更新失敗...";
	}
	return result;
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
