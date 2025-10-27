#include <Siv3d.hpp>
#include "system/TCP/ServerModule.h"//通信
#include "Login/Login.h"

void Main()
{
	Window::SetTitle(U"DCG Server");
	Window::Resize(800, 600);
	// 背景色を塗る
	Scene::SetBackground(ColorF{ 0.2, 0.4, 0.6 });
	// フォントをあらかじめ作成（毎フレーム作らない）
	Font font(20);

	//データを受け取る変数
	JSON json;
	//通信用のインスタンス作成
	ServerModule tcp;
	//
	Login login;


	//サーバを開放
	tcp.serverStartAccept();

	while (System::Update())
	{
		//データ受信処理
		if (tcp.serverHasSession() && tcp.serverIsConnected()) {
			json = tcp.serverReadJSON();//クライアントからデータを受け取る
		}

		//jsonデータからどの処理を実行するか判定
		if (tcp.serverHasSession() && tcp.serverIsConnected() && json.hasElement(U"method")) {
			Print << U"メソッド判定開始...";
			String method = json[U"method"].get<String>();

			if (method == U"Login") {//ログイン処理
				Print << U"Login処理を開始";
				login.CreateLoginID(json);
			}
			else if (method == U"") {
			}
			else {
				Print << U"メソッドがありません";
			}
		}

		//クラアントのログアウト処理
		
	}
}
