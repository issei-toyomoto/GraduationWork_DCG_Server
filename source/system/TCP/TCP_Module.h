#pragma once
//サーバ・クライアント間で通信する際に使用するクラス

//通信
#include <WinSock2.h>
#include <ws2tcpip.h>
//_Tマクロ使用
#include <tchar.h>

class TCP_Module
{
private:
	WSADATA wsaData;
	SOCKET sock0;
	struct sockaddr_in addr;
	struct sockaddr_in client;
	SOCKET sock;

public:
	/**
	 * @fn
	 * Winsock_Init
	 * @brief winsockの初期化
	 * @param (port) ソケットにするポート番号をここに入れる
	 * @return winsockの初期化が成功したか、成功した場合はTureが返される
	 * @detail winsockの初期化、ソケットの作成、IPアドレスのバイナリ変換をこの関数で行う
	*/
	bool Winsock_Init(int port);
	/**
	 * @fn
	 * Winsock_End
	 * @brief winsockの終了処理
	 * @detail winsockの終了処理
	*/
	void Winsock_End(void);

	/**
	* @fn
	* ClientHandler
	* @brief クライアントからデータを取得する
	* @return 受け取った値を返す
	* @Clientの
	*/
	String ClientHandler(SOCKET clientSocket);
};

