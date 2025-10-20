#include "ServerModule.h"

void ServerModule::serverStartAccept(s3d::uint16 port)
{
	server.startAccept(port);
}

bool ServerModule::serverHasSession()
{
	return server.hasSession();
}

bool ServerModule::serverIsConnected(s3d::uint16 port)
{
	if (server.hasSession() && !connected) {
		connected = true;
		Print << U"クライアント接続！";
	}
	else if (!server.hasSession() && connected) {
		connected = false;
		Print << U"クライアント切断";
		server.disconnect();
		braceDepth = 0;
		bracketDepth = 0;
		server.startAccept(port);
	}

	return connected;
}

JSON ServerModule::serverReadJSON()
{
	//結果を入れる変数
	JSON json;

	//サーバーからデータが読み込める限りループ
	while (server.read(c)) {
		//受信バッファに読み込んだ1文字を追加
		recvBuffer.push_back(c);
		// --- JSONのネスト構造を判定 ---
		if (c == '{') ++braceDepth;
		else if (c == '}') --braceDepth;
		else if (c == '[') ++bracketDepth;
		else if (c == ']') --bracketDepth;

		//JSONが閉じていて、内容がありそうな場合だけパース
		if (   braceDepth == 0
			&& bracketDepth == 0
			&& !recvBuffer.empty()
			&& (recvBuffer.find('{') != std::string::npos
			|| recvBuffer.find('[') != std::string::npos)) {
			//受信したUTF-8文字列を内部のString型に変換
			String s = Unicode::FromUTF8(recvBuffer);
			//文字列の前後の空白を削除
			s = s.trimmed();

			//文字列が空でなければ処理を続行
			if (!s.isEmpty())
			{
				//文字列をJSONオブジェクトとしてパース（解析）
				json = JSON::Parse(s);
				if (json)//JSONのパースに成功した場合
				{
					//受信したJSONをコンソールに出力
					Print << U"受信JSON：" << s;
				}
				else//JSONのパースに失敗した場合
				{
					//エラーメッセージをコンソールに出力
					Print << U"⚠️ JSONパース失敗: [" << s << U"]";
				}
			}
			//次のメッセージを受信するために、受信バッファをクリア
			recvBuffer.clear();
		}
	}

	return json;
}

void ServerModule::serverSendJSON(JSON dat)
{
	//送信時間をつける
	dat[U"server_time"] = DateTime::Now().format(U"{:yyyy-MM-dd HH:mm:ss}");

	//JSONを送信
	std::string jsonStr = dat.formatUTF8();
	String sendText = Unicode::FromUTF8(jsonStr);
	sendText += U"\n";

	std::string u8 = sendText.toUTF8();
	server.send(static_cast<const void*>(u8.data()), static_cast<int32>(u8.size()));

	//デバック表示
	Print << U"返信JSON：" << sendText;
}
