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
	SOCKET serverSocket, clientSocket;
	struct sockaddr_in serverAddr;
	sockaddr_in clientAddr;
	int clientAddrLen = sizeof(clientAddr);

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
	* AcceptConnection
	* @brief クライアントからの接続を受け入れる
	* @return クライアントから受け取ったデータを返す
	* 
	*/
	String AcceptConnection();

	/**
	* @fn
	* GetData
	* @brief クライアントからデータを受け取る
	* @para クライアントのソケット
	* @return クライアントから受け取ったデータを返す
	*
	*/
	String GetData(SOCKET clientSocket);

	/**
	* @fn
	*
	* @brief
	* @return
	*
	*/
	//String SendData();
};

