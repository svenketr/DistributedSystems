#ifndef CONNECTIONINFO_H
#define CONNECTIONINFO_H

#include "lsppacket.h"
#include "lsp.h"
#include "header.h"
#include "connection.h"

class ConnInfo : public Uncopyable
{
private:


public:
	char* hostName;
	int port;
	int connectionID;
	//might have to be made volatile
	int epochsSinceMsgRcd;
	int epochsSinceMsgSent;
	int countMsgsRcd;
	int countMsgsSent;
	bool isAlive;
	bool msgSent;
	queue<LSP_Packet> outMsgs;
	ConnInfo(int connId, int p, char* host) : connectionID(connId), port(p), hostName(host)
	{
		//default values when constructed.
		msgSent = false; //Only now connection request has come in. So msgSent will be false.
		isAlive = true;  //Assumed alive since connection request has just come in.
		//change these based on client and server
		countMsgsRcd = 1; //only connection request is got at this point.
		countMsgsSent = 0;
		epochsSinceMsgRcd = 0;
		epochsSinceMsgSent = 0;
	}

	void addPacket(int seqNo, size_t len, uint8_t *bytes);

	bool isMsgToBeSent()
	{
		if(isAlive && !msgSent && outMsgs.size()!=0)
			return true;
		return false;
	}

	int getOutMsgsCount() const {
		return outMsgs.size();
	}

};

#endif

