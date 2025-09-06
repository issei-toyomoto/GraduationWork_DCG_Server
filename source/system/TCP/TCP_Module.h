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
	struct sockaddr_in server;
	SOCKET sock;
public:
	/**
	 * @fn
	 * Winsock_Init
	 * @brief winsockの初期化
	 * @param (port) ポート番号をここに入れる
	 * @param (addr) アドレスをString型で入れる
	 * @return winsockの初期化が成功したか、成功した場合はTureが返される
	 * @detail winsockの初期化、ソケットの作成、IPアドレスのバイナリ変換をこの関数で行う
	*/
	bool Winsock_Init(int port, String addr);
	/**
	 * @fn
	 * Winsock_End
	 * @brief winsockの終了処理
	 * @detail winsockの終了処理
	*/
	void Winsock_End(void);
	/**
	 * @fn
	 * ConnectServer
	 * @brief サーバに接続
	 * @return サーバに接続成功した場合は0、失敗した場合は-1
	 * @detail winsockを初期化時に設定したポートとIPからサーバに接続する
	*/
	int ConnectServer(void);
	/**
	 * @fn
	 * getData
	 * @brief サーバからデータを取得する
	 * @return サーバからのString型のデータ
	 * @detail サーバからのデータをString型でデータを返す
	*/
	std::string getData(void);
	/**
	 * @fn
	 * sendData
	 * @brief サーバへデータを送信する
	 * @param (sd) サーバへ送信したいデータ（String型）
	 * @detail サーバへchar型でデータを送信する
	*/
	void sendData(std::string sd);
};

