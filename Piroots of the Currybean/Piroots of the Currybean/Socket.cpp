//Local Includes 
#include "Network.h"

//This Include
#include "Socket.h"


Socket::Socket()
	:m_hSocket(0) {
	ZeroMemory(&m_SocketAddress, sizeof(m_SocketAddress));
}

Socket::~Socket() {
	closesocket(m_hSocket);
}

//Implicit Assumption: We are creating only UDP sockets.....
bool Socket::Initialise(unsigned short _usPortNumber) {
	int _iError;
	//Create a UDP socket 
	m_hSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == m_hSocket) {
		_iError = WSAGetLastError();
		ErrorRoutines::PrintWSAErrorInfo(_iError);
		std::cout << "Unable to create socket\n";
		return false;
	} else {
		std::cout << "Successfully created the socket" << std::endl;
	}

	// now bind the socket to the address and port number supplied.
	m_SocketAddress.sin_family = AF_INET;
	m_SocketAddress.sin_port = htons(_usPortNumber);
	m_SocketAddress.sin_addr.S_un.S_addr = INADDR_ANY;
	//Qs 1 : Change if to while; incrementing the port number every time!
	while (0 != bind(m_hSocket, reinterpret_cast<sockaddr*>(&m_SocketAddress), sizeof(m_SocketAddress))) {
		// Cannot bind to the specified IP and port; 
		//Try with an incremented port number
		_usPortNumber++;

		m_SocketAddress.sin_port = htons(_usPortNumber);

	}
	std::cout << "Successfully bound the socket " << "to " << GetLocalAddress() << ":" << _usPortNumber << std::endl;

	return true;
}

SOCKET Socket::GetSocketHandle() {
	return m_hSocket;
}

std::string Socket::GetLocalAddress() {
	char _pcLocalHostName[256];
	char _pcLocalAddress[256];
	struct sockaddr_in* sockaddr_localIP;

	gethostname(_pcLocalHostName, 256);

	struct addrinfo hints, *result, *p;
	int _iReturnValue;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;


	_iReturnValue = getaddrinfo(_pcLocalHostName, NULL, &hints, &result);

	/* loop over all returned results to get the address */
	for (p = result; p != NULL; p = p->ai_next) {
		sockaddr_localIP = (struct sockaddr_in *) p->ai_addr;
		inet_ntop(AF_INET, &(sockaddr_localIP->sin_addr), _pcLocalAddress, 256);
	}

	return std::string(_pcLocalAddress);
}

int Socket::EnableBroadcast() {
	int _iBroadCastOption = 1;
	int _iResult = setsockopt(m_hSocket, SOL_SOCKET, SO_BROADCAST,
							  reinterpret_cast<char*>(&_iBroadCastOption), sizeof(_iBroadCastOption));
	if (_iResult == SOCKET_ERROR) {
		int _iError = WSAGetLastError();
		ErrorRoutines::PrintWSAErrorInfo(_iError);
		std::cout << "Unable to enable broadcast option on the socket" << std::endl;
		closesocket(m_hSocket);
		return _iError;
	}
	return _iResult;
}


int Socket::DisableBroadcast() {
	int _iBroadCastOption = 0;
	int _iResult = setsockopt(m_hSocket, SOL_SOCKET, SO_BROADCAST,
							  reinterpret_cast<char*>(&_iBroadCastOption), sizeof(_iBroadCastOption));
	if (_iResult == SOCKET_ERROR) {
		int _iError = WSAGetLastError();
		ErrorRoutines::PrintWSAErrorInfo(_iError);
		std::cout << "Unable to disable broadcast option on the socket" << std::endl;
		closesocket(m_hSocket);
		return _iError;
	}
	return _iResult;
}

void Socket::SetRemotePort(unsigned short _usRemotePort) {
	m_usRemotePort = _usRemotePort;
}

void Socket::SetRemoteAddress(unsigned long _ulRemoteAddress) {
	m_ulRemoteIPAddress = _ulRemoteAddress;
}