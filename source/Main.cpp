#include "system/TCP/TCP_Module.h"

#define PORT 12345

void Main()
{
	Window::SetTitle(U"DCG Server");
	Window::Resize(800, 600);
	TCP_Module tcp;

	//winsockの初期化
	tcp.Winsock_Init(PORT);
	// フォントをあらかじめ作成（毎フレーム作らない）
	Font font(20);
	// 背景色を塗る
	Scene::SetBackground(ColorF{ 0.2, 0.4, 0.6 });

	while (System::Update())
	{
		//クライアントからのデータを受信
		String getData = tcp.AcceptConnection();
		font(getData).draw(Vec2{ 0,0 }, ColorF{ 0.2 });

		//受け取ったデータをJSON形式に変換する
		JSON json = getData;

		//受信したデータからデータを送信
		
	}

	//winsockの終了処理
	tcp.Winsock_End();
}
