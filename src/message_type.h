#include <string>
#include <map>
using namespace std;

enum MessageType
{
    PING,
    LOBBY,
    UNKNOWN
};

std::map<MessageType, string> messageTypeToStringMap = {
    {PING, "PING"},
    {LOBBY, "LOBBY"},
    {UNKNOWN, "UNKNOWN"}
};

string messageTypeToString(MessageType messageType) {
    return messageTypeToStringMap[messageType];
}
