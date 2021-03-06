#pragma once
#ifndef EPOCH_H
#define EPOCH_H

#include "header.h"

class Epoch : public Uncopyable
{
protected:
	LSP* lsp;

public:
	Epoch(LSP* lsp);

	virtual void run();

	bool epoch_passed(const clock_t start, const clock_t end);
	int check_epoch(ConnInfo* connInfo);
	void send_packet_again(ConnInfo* connInfo);
	virtual int take_action(ConnInfo* connInfo) = 0;

	virtual ~Epoch();
};

class EpochServer : public Epoch
{
private:
	vector<ConnInfo*>* connInfos;

public:
	EpochServer(LSP* lsp);

	LSP_Server* get_lsp();

	virtual void run();
	virtual int take_action(ConnInfo* connInfo);

	virtual ~EpochServer();
};

class EpochClient: public Epoch
{
private:
	ConnInfo* connInfo;

public:
	EpochClient(LSP* lsp);

	LSP_Client* get_lsp();

	virtual void run();
	virtual int take_action(ConnInfo* connInfo);

	virtual ~EpochClient();
};

#endif
