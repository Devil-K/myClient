//系统消息
#ifndef H_MESSAGE_H
#define H_MESSAGE_H

#include <afxtempl.h>

class Message{
public:
	Message(LPCSTR sz_msg){
		GetSystemTime(&time);
		
		memset(sz_message, 0, sizeof(sz_message));
		int msg_len = strlen(sz_msg);
		msg_len = msg_len < MAX_PATH ? msg_len : MAX_PATH - 1;
		
		strncpy(sz_message, sz_msg, msg_len);
	}

public:
	SYSTEMTIME	time;
	char		sz_message[MAX_PATH];
};

typedef CTypedPtrList<CPtrList, Message*> MessageList;

#endif//H_MESSAGE_H