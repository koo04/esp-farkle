#include <painlessMesh.h>
#include <map>
#include "name_gen.h"
#include "message_type.h"
#include "screens.h"
#include "buttons.h"

#define MESH_SSID "farkle"
#define MESH_PASSWORD "farkleforthewin"
#define MESH_PORT 1337
#ifndef CREATE_LOBBY
#define CREATE_LOBBY false
#endif

void enableSchedulers();
void sendMessage();
void receivedCallback(uint32_t from, String &msg);
void newConnectionCallback(uint32_t nodeId);
void changedConnectionCallback();
void nodeTimeAdjustedCallback(int32_t offset);
void delayReceivedCallback(uint32_t from, int32_t delay);
void pingHandler(JsonObject playerJson);
void lobbyHandler(JsonObject data);
void upsertLobby(Lobby *lobby);
void broadcastLobby();
void report();
void broadcast(MessageType type, std::string args);

extern std::map<uint32_t, Lobby *> lobbies;
extern Player me;

Scheduler userScheduler;
painlessMesh mesh;

bool calc_delay = false;
SimpleList<uint32_t> nodes;

void sendMessage(); // Prototype
Task taskEnableSchedulers(TASK_SECOND * 5, TASK_FOREVER, &enableSchedulers);
Task taskSendMessage(TASK_SECOND * 5, TASK_FOREVER, &sendMessage);
Task taskReport(TASK_SECOND * 5, TASK_FOREVER, &report);
Task taskSendLobby(TASK_SECOND * 5, TASK_FOREVER, &broadcastLobby);

void setup()
{
  setupButtons();

  Serial.begin(115200);

  randomSeed(time(NULL));

  me = Player();

  mesh.setDebugMsgTypes(ERROR | DEBUG);

  mesh.init(MESH_SSID, MESH_PASSWORD, &userScheduler, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  userScheduler.addTask(taskEnableSchedulers);
  userScheduler.addTask(taskSendMessage);
  userScheduler.addTask(taskReport);
  userScheduler.addTask(taskSendLobby);

  taskEnableSchedulers.enable();

  currentScreen = new MainMenuScreen();

  Serial.println("Setup done");
}

void loop()
{
  mesh.update();
}

void enableSchedulers()
{
  // if (!me.inLobby())
  // {
  //   if (!taskReport.isEnabled())
  //   {
  //     taskReport.enable();
  //   }
  //   return;
  // }

  // if (currentLobby.isValid())
  // {
  //   if (!taskSendLobby.isEnabled())
  //   {
  //     taskSendLobby.enable();
  //   }
  //   taskSendMessage.disable();
  //   taskReport.disable();
  //   return;
  // }

  // taskReport.disable();
}

void report()
{
  if (lobbies.size() == 0)
  {
    Serial.println("No lobbies");
    return;
  }

  String out = "";

  if (lobbies.size() >= 0)
  {

    std::vector<uint32_t> keysToRemove;

    int i = 0;
    for (auto const &kv : lobbies)
    {
      if (kv.second->old())
      {
        keysToRemove.push_back(kv.first);
        continue;
      }

      out += kv.second->info().c_str();
      if (i < lobbies.size() - 1)
      {
        out += "\n";
      }
      i++;
    }

    for (auto const &key : keysToRemove)
    {
      lobbies.erase(key);
    }
  }

  String outStr = "===== Lobbies: ";
  outStr += lobbies.size();
  outStr += " =====";
  outStr += "\n";
  outStr += out;
  outStr += "\n====================\n";

  Serial.println(outStr);
}

void broadcastLobby()
{
  // if (currentLobby.isValid())
  // {
  //   JsonDocument doc;
  //   JsonObject currentLobbyJson = doc.to<JsonObject>();
  //   currentLobby.toJson(currentLobbyJson);

  //   std::string currentLobbyJsonStr;
  //   serializeJson(currentLobbyJson, currentLobbyJsonStr);

  //   broadcast(LOBBY, currentLobbyJsonStr);
  // }
}

void sendMessage()
{
  JsonObject playerJson;
  me.toJson(playerJson);

  std::string playerJsonStr;
  serializeJson(playerJson, playerJsonStr);

  broadcast(PING, playerJsonStr);

  if (calc_delay)
  {
    SimpleList<uint32_t>::iterator node = nodes.begin();
    while (node != nodes.end())
    {
      mesh.startDelayMeas(*node);
      node++;
    }
    calc_delay = false;
  }
}

void receivedCallback(uint32_t from, String &msg)
{
  String delimiter = "|";
  String messageTypeRaw = msg.substring(0, msg.indexOf(delimiter.c_str()));
  int messageTypeInt = atoi(messageTypeRaw.c_str());
  MessageType messageType = static_cast<MessageType>(messageTypeInt);
  String arguments = msg.substring(msg.indexOf(delimiter.c_str()) + 1).c_str();

  JsonDocument argsJson;
  deserializeJson(argsJson, arguments);

  JsonObject args = argsJson.as<JsonObject>();

  switch (messageType)
  {
  case PING:
    pingHandler(args);
    break;
  case LOBBY:
    lobbyHandler(args);
    break;
  case UNKNOWN:
    Serial.printf("Unknown message: %s\n", msg.c_str());
    break;
  }
}

// handlers
void newConnectionCallback(uint32_t nodeId)
{
  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
  Serial.printf("--> startHere: New Connection, %s\n", mesh.subConnectionJson(true).c_str());
}

void pingHandler(JsonObject playerJson)
{
  Player p = Player::fromJson(playerJson);
  // Serial.printf("Received ping from player %s\n", p.name.c_str());
}

void lobbyHandler(JsonObject data)
{
  Lobby *lobby = Lobby::fromJson(data);
  upsertLobby(lobby);
}

void changedConnectionCallback()
{
  Serial.printf("Changed connections\n");

  nodes = mesh.getNodeList();

  Serial.printf("Num nodes: %d\n", nodes.size());
  Serial.printf("Connection list:");

  SimpleList<uint32_t>::iterator node = nodes.begin();
  while (node != nodes.end())
  {
    Serial.printf(" %u", *node);
    node++;
  }
  Serial.println();
  calc_delay = true;
}

void nodeTimeAdjustedCallback(int32_t offset)
{
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}

void delayReceivedCallback(uint32_t from, int32_t delay)
{
  Serial.printf("Delay to node %u is %d us\n", from, delay);
}

// helpers
void broadcast(MessageType type, std::string args)
{
  mesh.sendBroadcast(String(type) + "|" + args.c_str());
}

void upsertLobby(Lobby *lobby)
{
  lobby->setLastUpdated(time(NULL));
  lobbies[lobby->id] = lobby;
}
