


//Local Includes
#include "Network.h"
#include "Socket.h"


//Local Includes
#include "Server.h"

Server::Server()
	:m_pcPacketData(0),
	m_pServerSocket(0) {
	ZeroMemory(&m_ClientAddress, sizeof(m_ClientAddress));
}

Server::~Server() {
	delete m_pConnectedClients;
	m_pConnectedClients = 0;

	delete m_pServerSocket;
	m_pServerSocket = 0;

	delete m_pWorkQueue;
	m_pWorkQueue = 0;

	delete[] m_pcPacketData;
	m_pcPacketData = 0;
}

bool Server::Initialise() {
	m_pcPacketData = new char[MAX_MESSAGE_LENGTH];

	//Create a work queue to distribute messages between the main  thread and the receive thread.
	m_pWorkQueue = new CWorkQueue<char*>();

	//Create a socket object
	m_pServerSocket = new Socket();

	//Initialise the socket to the local loop back address and port number
	if (!m_pServerSocket->Initialise(DEFAULT_SERVER_PORT)) {
		return false;
	}

	//Qs 2: Create the map to hold details of all connected clients
	m_pConnectedClients = new std::map < std::string, TClientDetails >();

	//Starting the server clock

	//Set the client's online status to true
	m_bOnline = true;
	return true;
}

bool Server::AddClient(std::string _strClientName) {
	//TO DO : Add the code to add a client to the map here...

	for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it) {
		//Check to see that the client to be added does not already exist in the map, 
		if (it->first == ToString(m_ClientAddress)) {

			//TODO: SEND ERROR MESSAGE
			std::cout << "ERROR: Address already being used.\n";
			return false;
		}
		//also check for the existence of the username
		else if (it->second.m_strName == _strClientName) {

			//TODO: SEND ERROR MESSAGE
			std::cout << "ERROR: An existing user already exists.\n";

			TPacket _packetToSend;
			std::string ErrorMessage = "Error: Invalid Username";
			_packetToSend.Serialize(HANDSHAKE, const_cast<char*>(ErrorMessage.c_str()));
			SendData(_packetToSend.PacketData);
			std::cout << "Sent a return handshake message with username error\n";

			for (const auto& it : *m_pConnectedClients) {
				std::cout << it.first << " ";
			}
			std::cout << std::endl;

			return false;
		}
	}

	std::cout << "Client Being Added to Server\n Current Users: ";
	for (const auto& it : *m_pConnectedClients) {
		std::cout << it.first << " ";
	}
	std::cout << std::endl;

	//Add the client to the map.
	TClientDetails _clientToAdd;
	_clientToAdd.m_strName = _strClientName;
	_clientToAdd.m_ClientAddress = this->m_ClientAddress;

	std::string _strAddress = ToString(m_ClientAddress);
	m_pConnectedClients->insert(std::pair < std::string, TClientDetails >(_strAddress, _clientToAdd));
	LobbyReady = true;
	return true;
}

bool Server::SendData(char* _pcDataToSend) {
	int _iBytesToSend = (int)strlen(_pcDataToSend) + 1;

	int iNumBytes = sendto(
		m_pServerSocket->GetSocketHandle(),				// socket to send through.
		_pcDataToSend,									// data to send
		_iBytesToSend,									// number of bytes to send
		0,												// flags
		reinterpret_cast<sockaddr*>(&m_ClientAddress),	// address to be filled with packet target
		sizeof(m_ClientAddress)							// size of the above address struct.
	);
	//iNumBytes;
	if (_iBytesToSend != iNumBytes) {
		std::cout << "There was an error in sending data from client to server" << std::endl;
		return false;
	}
	return true;
}

void Server::ReceiveData(char* _pcBufferToReceiveData) {

	int iSizeOfAdd = sizeof(m_ClientAddress);
	int _iNumOfBytesReceived;
	int _iPacketSize;

	//Make a thread local buffer to receive data into
	char _buffer[MAX_MESSAGE_LENGTH];

	while (m_bOnline) {
		// pull off the packet(s) using recvfrom()
		_iNumOfBytesReceived = recvfrom(			// pulls a packet from a single source...
										m_pServerSocket->GetSocketHandle(),						// client-end socket being used to read from
										_buffer,							// incoming packet to be filled
										MAX_MESSAGE_LENGTH,					   // length of incoming packet to be filled
										0,										// flags
										reinterpret_cast<sockaddr*>(&m_ClientAddress),	// address to be filled with packet source
										&iSizeOfAdd								// size of the above address struct.
		);
		if (_iNumOfBytesReceived < 0) {
			//int _iError = WSAGetLastError();
			//ErrorRoutines::PrintWSAErrorInfo(_iError);
			//return false;
		} else {
			_iPacketSize = static_cast<int>(strlen(_buffer)) + 1;
			strcpy_s(_pcBufferToReceiveData, _iPacketSize, _buffer);
			char _IPAddress[100];
			inet_ntop(AF_INET, &m_ClientAddress.sin_addr, _IPAddress, sizeof(_IPAddress));

			//Push this packet data into the WorkQ
			m_pWorkQueue->push(_pcBufferToReceiveData);
		}
		//std::this_thread::yield();

	} //End of while (true)
}

void Server::GetRemoteIPAddress(char *_pcSendersIP) {
	char _temp[MAX_ADDRESS_LENGTH];
	int _iAddressLength;
	inet_ntop(AF_INET, &(m_ClientAddress.sin_addr), _temp, sizeof(_temp));
	_iAddressLength = static_cast<int>(strlen(_temp)) + 1;
	strcpy_s(_pcSendersIP, _iAddressLength, _temp);
}

unsigned short Server::GetRemotePort() {
	return ntohs(m_ClientAddress.sin_port);
}


void Server::ProcessData(char* _pcDataReceived) {
	TPacket _packetRecvd, _packetToSend;
	_packetRecvd = _packetRecvd.Deserialize(_pcDataReceived);
	std::string Message;
	switch (_packetRecvd.MessageType) {
		case HANDSHAKE: {
			//Keep Alive Message

			//Qs 3: To DO : Add the code to do a handshake here
			std::cout << "Server received a handshake message.\n";
			if (_pcDataReceived == "Keep Alive") {
				std::cout << "Keep Alive Packet\n";
				return;
			}

			//Checking for the User in the current Client List
			for (const auto& it : *m_pConnectedClients) {
				//_pcDataReceived should be the username
				if (it.second.m_strName == _packetRecvd.MessageContent) {	//If the user was found on the client list
					std::cout << "ERROR: User entered an invalid username. Requested new username.\n";

					//Sending an error packet to the client to prompt another username
					Message = "Invalid Username";
					_packetToSend.Serialize(HANDSHAKE, const_cast<char*>(Message.c_str()));
					SendData(_packetToSend.PacketData);
					return;
				}
			}

			//Add the user to the client list and send the Welcome Message
			AddClient(_packetRecvd.MessageContent);
			#pragma region Welcome Message
			//Sending a message to all users that a new client has joined
			std::cout << "User " << _pcDataReceived << " joined successfully.\n";
			//Sending a special message to the client that just joined, containing
			//the user list
			std::string UserName(_pcDataReceived);
			UserName.erase(0, 2);
			Message = UserName + " joined the server!";
			_packetToSend.Serialize(DATA, const_cast<char*>(Message.c_str()));
			SendData(_packetToSend.PacketData);
			Message = "Current User List:";
			_packetToSend.Serialize(DATA, const_cast<char*>(Message.c_str()));
			SendData(_packetToSend.PacketData);
			Message = "------------------";
			_packetToSend.Serialize(DATA, const_cast<char*>(Message.c_str()));
			SendData(_packetToSend.PacketData);

			//Iterating through the user list and sending it to the new client
			for (const auto& it : *m_pConnectedClients) {
				Message = it.second.m_strName;
				_packetToSend.Serialize(DATA, const_cast<char*>(Message.c_str()));
				SendData(_packetToSend.PacketData);
			}

			Message = "------------------";
			_packetToSend.Serialize(DATA, const_cast<char*>(Message.c_str()));
			SendData(_packetToSend.PacketData);

			//Sending existing users a notification that a new user has joined
			for (const auto& it : *m_pConnectedClients) {
				if (it.first == UserName) continue;	//Ignoring if the iterates to the current Client
				m_ClientAddress = it.second.m_ClientAddress;
				Message = "[SERVER]> " + UserName + " has joined the room";
				_packetToSend.Serialize(DATA, const_cast<char*>(Message.c_str()));
				SendData(_packetToSend.PacketData);
			}
			#pragma endregion
			break;
		}
		case DATA: {
			std::cout << "Server Received a Data Message";
			std::string ClientName;
			std::string Message = _packetRecvd.MessageContent;

			//Finding if the user exists in the list, and saving it to string ClientName
			auto it = m_pConnectedClients->find(ToString(m_ClientAddress));
			if (it == m_pConnectedClients->end()) {
				std::cout << "Error: User was not found in the User List. Message Ignored\n";
				return;
			}

			//if the first character of the user's message is an ! (a command)
			else if (Message.substr(1, 6) == "!quit") {
				//Quit Command Received from user
				std::cout << "Quit Command Received\n";

				//Sending the disconnection message to the client
				TPacket GoodByePacket;
				Message = "[SERVER]> You have been disconnected from the server.";
				GoodByePacket.Serialize(DATA, const_cast<char*>(Message.c_str()));
				SendData(GoodByePacket.PacketData);

				Message = "[SERVER]> Have a nice day ;)";
				GoodByePacket.Serialize(DATA, const_cast<char*>(Message.c_str()));
				SendData(GoodByePacket.PacketData);

				//Removing the user from the client map
				auto it = m_pConnectedClients->find(ToString(m_ClientAddress));
				if (it != m_pConnectedClients->end()) m_pConnectedClients->erase(it);
				return;
			}

			it->second.m_fTimeSinceLastMessage = 0.0f;
			ClientName = it->second.m_strName;
			ClientName.erase(0, 1);
			//Generating the message
			Message = "[" + ClientName + "]> " + _packetRecvd.MessageContent;

			//For loop iterating through the entire client list to send the same message to each client connected
			for (auto& it1 : *m_pConnectedClients) {
				//Setting current client address
				m_ClientAddress = it1.second.m_ClientAddress;
				//Serializing and sending the message to the current client
				_packetToSend.Serialize(DATA, const_cast<char*>(Message.c_str()));
				SendData(_packetToSend.PacketData);
			}
			break;
		}

		case BROADCAST: {
			std::cout << "Received a broadcast packet" << std::endl;
			//Just send out a packet to the back to the client again which will have the server's IP and port in it's sender fields
			_packetToSend.Serialize(BROADCAST, "I'm here!");
			SendData(_packetToSend.PacketData);
			break;
		}
		
		case PLAYERPOS: {
			std::string str(_pcDataReceived);
			std::stringstream ss(str);
			std::cout << ss.str() << std::endl;
			float x, y;
			ss >> x >> y;
			Player1Pos = glm::vec3(x, y, -0.2f);
		}

		default:break;
	}
}

CWorkQueue<char*>* Server::GetWorkQueue() {
	return m_pWorkQueue;
}

void Server::KeepAliveCheck() {
	TPacket KeepAlive;
	KeepAlive.Serialize(KEEPALIVE, "KeepAlive");

	//Sending the keep alive message to all clients
	for (auto& it : *m_pConnectedClients) {
		m_ClientAddress = it.second.m_ClientAddress;
		SendData(KeepAlive.PacketData);
	}
}