#include <Siv3d.hpp>
#include "system/TCP/TCP_Module.h"

#define PORT 12345

void Main()
{
	Window::SetTitle(U"DCG Server");
	Window::Resize(800, 600);
	// 背景色を塗る
	Scene::SetBackground(ColorF{ 0.2, 0.4, 0.6 });
	// フォントをあらかじめ作成（毎フレーム作らない）
	Font font(20);

	TCP_Module tcp;

	//winsockの初期化
	tcp.Winsock_Init(PORT);
	

	while (System::Update())
	{
		//クライアントからのデータを受信
		String getData = tcp.AcceptConnection();

		// 受け取ったデータをJSON形式に変換
		JSON json = JSON::Parse(getData);
		Print << json.format();

		//受信したデータからどの関数、メソッドで処理するか判定する
		String method = json[U"method"].getString();//methodの値をString型に変換

		if (method == U"Login") {//ログイン処理
			Print << U"Login処理を開始";
		}
		else if (method == U"") {
		}
	}
	//winsockの終了処理
	tcp.Winsock_End();
}
