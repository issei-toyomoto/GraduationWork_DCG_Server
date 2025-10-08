#include "TCP_Module.h"

bool TCP_Module::Winsock_Init(int port)
{
	//winsock2の初期化
	WSAStartup(MAKEWORD(2, 0), &wsaData);
	//ソケットの作成
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	//ソケットの設定
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(12345);
	serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;

	//エラーチェック
	if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) != 0) {
		printf_s("bind : %d\n", WSAGetLastError());
		return 1;
	}

	//TCPクライアントからの接続要求を待てる状態にする
	//エラーチェック処理 : listen()!=0でエラー
	if (listen(serverSocket, 5) != 0) {
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

String TCP_Module::AcceptConnection()
{
	//クライアントの接続受け入れ
	clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrLen);
	//エラーチェック
	if (clientSocket == INVALID_SOCKET) {
		return (U"ERROR : accept");
	}
	
	return GetData(clientSocket);
}

String TCP_Module::GetData(SOCKET cs)
{
	char recvBuffer[1024];
	int recvResult;

	//クライアントからのデータ受信をループで処理する
	recvResult = recv(cs, recvBuffer, sizeof(recvBuffer) - 1, 0);
	//受信したデータ
	recvBuffer[recvResult] = '\0';

	//クライアントとの接続を閉じる
	closesocket(cs);

	return s3d::Unicode::FromUTF8(recvBuffer);
}
