#include "TCP_Module.h"

bool TCP_Module::Winsock_Init(int port, String addr)
{
	//Winsock2の初期化
	int initState = WSAStartup(MAKEWORD(2, 0), &wsaData);
	if (initState != 0) {//winsock2の初期化に失敗
		printf_s("winsock init....fail\n");
		printf_s("winsock state....%d\n", initState);
		return false;
	}
	//ソケットの作成
	sock = socket(AF_INET, SOCK_STREAM, 0);
	//接続先指定用構造体の準備
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	//Siv3D String(UTF-32) -> std::wstring(UTF-16)　※変換
	std::wstring waddr = Unicode::ToWstring(addr);
	//IPアドレスをテキスト形式からバイナリ形式に変換
	InetPton(server.sin_family, waddr.c_str(), &server.sin_addr.S_un.S_addr);

	printf_s("winsock init....succeed\n");
	return true;
}

void TCP_Module::Winsock_End(void)
{
	// Winsockの終了処理
	WSACleanup();
	printf("winsock cleanup done.\n");
}

int TCP_Module::ConnectServer(void)
{
	int connectState;
	connectState = connect(sock, (struct sockaddr*)&server, sizeof(server));
	if (connectState != 0) {
		printf_s("connect fail\n");
		return -1;
	}
	else {
		printf_s("connect success\n");
		return 0;
	}

	return -1;
}

std::string TCP_Module::getData()
{
	char buf[32];
	//サーバからデータを受信
	memset(buf, 0, sizeof(buf));
	int n = recv(sock, buf, sizeof(buf), 0);
	printf_s("Received from server %d %s\n", n, buf);

	return buf;
}

void TCP_Module::sendData(std::string sd)
{
	//string型 -> char型
	char buf[32];
	strcpy_s(buf, sizeof(buf), sd.c_str());

	//サーバに送信
	int n = send(sock, buf, 3, 0);
	if (n < 1) {//送信エラーが発生した場合はソケットを閉じる
		printf_s("send : %d\n", WSAGetLastError());
		closesocket(sock);
	}
}
