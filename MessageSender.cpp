#include "MessageSender.h"

MessageSender::MessageSender(
		vector<ConnInfo*> *info,
		pthread_mutex_t& mutex_connInfos,
		Connector * conn)
: connectionInfo(info), mutex_connInfos(mutex_connInfos), connector(conn)
{

}

void MessageSender::send_msg(ConnInfo &cInfo)
{
	//Marshals and sends the message.
	LSP_Packet packet = cInfo.get_front_msg();
	uint8_t *buf;
	int len = serializer.marshal(packet,buf);
	if(connector->getIsServer())
	{
		connector->send_message(cInfo.getHostName(), cInfo.getPort(), buf, len);
		fprintf(stderr, "MessageSender:: Message sent to %s : %d\n", cInfo.getHostName(), cInfo.getPort());
	}
	else
	{
		connector->send_message(buf,len);
		fprintf(stderr, "MessageSender:: Message sent to server.\n");
	}
	if(packet.getType() == ACK)
	{
		fprintf(stderr, "MessageSender::Popping ACK Message in %d\n",cInfo.getConnectionId());
		cInfo.pop_outMsgs();
		cInfo.setMsgSent(false); /* Next msg hasn't been set*/
	}
	else
	{
		cInfo.setMsgSent(true);
	}
	free(buf);
}

void MessageSender::pollToSend(vector<ConnInfo*>* connectionInfo)
{
	fprintf(stderr, "MessageSender:: Polling from outbox...\n");
	while(1)
	{
		/* Lock before modifying! */
		pthread_mutex_lock (&mutex_connInfos);

		for(vector<ConnInfo*>::iterator it=connectionInfo->begin();
				it!=connectionInfo->end(); ++it)
		{
			if((*it)->isMsgToBeSent())
				send_msg(**it);
		}

		/* Unlock after modifying! */
		pthread_mutex_unlock (&mutex_connInfos);
	}
}

