#include "TCP_Module.h"

bool TCP_Module::Winsock_Init(int port)
{
	//winsock2の初期化
	WSAStartup(MAKEWORD(2, 0), &wsaData);
	//ソケットの作成
	sock0 = socket(AF_INET, SOCK_STREAM, 0);
	//ソケットの設定
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	//エラーチェック
	if (bind(sock0, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
		printf_s("bind : %d\n", WSAGetLastError());
		return 1;
	}

	//TCPクライアントからの接続要求を待てる状態にする
	//エラーチェック処理 : listen()!=0でエラー
	if (listen(sock0, 5) != 0) {
		printf_s("listen : %d\n", WSAGetLastError());
		return 1;
	}
}

void TCP_Module::Winsock_End(void)
{
	// Winsockの終了処理
	WSACleanup();
	printf("winsock cleanup done.\n");
}
