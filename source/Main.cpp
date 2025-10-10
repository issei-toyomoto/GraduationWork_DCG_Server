#include <Siv3d.hpp>
#include "Login/Login.h"

#define PORT 12345

void Main()
{
	Window::SetTitle(U"DCG Server");
	Window::Resize(800, 600);
	// 背景色を塗る
	Scene::SetBackground(ColorF{ 0.2, 0.4, 0.6 });
	// フォントをあらかじめ作成（毎フレーム作らない）
	Font font(20);

	//利用するポートを開放
	const uint16 port = 50000;
	//クライアントとの接続状態を管理するフラグ
	bool connected = false;
	//TCPサーバーオブジェクトを作成し、指定ポートで接続受付を開始する
	TCPServer server;
	server.startAccept(port);
	//ウィンドウタイトルに初期状態（接続待機中）を表示
	Window::SetTitle(U"TCPServer: Waiting for connection...");
	

	while (System::Update())
	{
		//クライアントからの接続セッションが存在する場合
		if (server.hasSession()) {
			//初回の接続確立時に接続状態フラグを更新し、ウィンドウタイトルを変更する
			if (not connected) {
				connected = true;
				Window::SetTitle(U"TCPServer: Connection established!");
			}
			//クライアントへ送信
			//server.send();

			//クライアントから送信されたデータを受信する
			//（複数データが同時に送られてくる可能性に備えて、すべてのデータを読み込む）
			//while (server.read());
		}

		//接続済みだが、セッションが切断された場合の処理
		if (connected && (not server.hasSession())) {
			//セッション切断処理を実行する
			server.disconnect();
			connected = false;
			//ウィンドウタイトルを接続待機中に変更し、再度接続受付を開始する
			Window::SetTitle(U"TCPServer: Waiting for connection...");
			server.startAccept(port);
		}
	}
}
