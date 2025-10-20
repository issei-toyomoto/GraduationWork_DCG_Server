#pragma once
//siv3dのTCPを使用
#include <Siv3d.hpp>

#define DEFULT_PORT 8877

class ServerModule
{
private:
	//siv3dのserverインスタンスを作成
	TCPServer server;
	//サーバの接続状況を管理するFlg
	bool connected;
	//送られた文字を一時保存
	std::string recvBuffer;
	//カウント変数
	int braceDepth;//{}←のカウント、対であるなら０
	int bracketDepth;//[]←のカウント、対であるなら０
	//送られた文字を受け取る
	char c;

public:
	//サーバの接続待ち受けを開始
	// @para : port 開放するポート番号をここで指定する
	void serverStartAccept(s3d::uint16 port = DEFULT_PORT);

	//サーバのSessionが有効か
	// @return : true(有効) false(無効)
	bool serverHasSession();

	//サーバが接続されているか状態管理
	// @para : port ポート番号をここに入れる
	// @ return : connected変数の状態が返ってくる true(接続) false(切断)
	bool serverIsConnected(s3d::uint16 port = DEFULT_PORT);

	//クラアントからJSONデータを受け取る
	// @return : 受け取ったJSONデータを返す
	JSON serverReadJSON();

	//クラアントへJSONデータを送る（文字列を送る）
	// @para : dat 送るJSONデータを入れる
	void serverSendJSON(JSON dat);
};

