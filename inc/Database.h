#ifndef DATA_FETCHER_H
#define DATA_FETCHER_H

#include <vector>
#include <functional>
#include <curl/curl.h>
#include "json.hpp"

#include "Equipment.h"
#include "Weapon.h"
#include "Monster.h"

struct CurlString
{
  char* ptr;
  size_t len;
};

class Database
{
public:
  Database();
  ~Database();

  void FetchEquipment();
  void FetchMonsters();

  void DumpJsonToFiles();
  void ReadFilesToJson();
  void ConvertJsonToDatabases();

  const std::vector<Equipment>& Ammunition() const;
  const std::vector<Equipment>& Body() const;
  const std::vector<Equipment>& Cape() const;
  const std::vector<Equipment>& Feet() const;
  const std::vector<Equipment>& Hand() const;
  const std::vector<Equipment>& Head() const;
  const std::vector<Equipment>& Legs() const;
  const std::vector<Equipment>& Neck() const;
  const std::vector<Equipment>& Ring() const;
  const std::vector<Equipment>& Shield() const;
  const std::vector<Weapon>& Weapons() const;
  const std::vector<Monster>& Monsters() const;

  int FindAmmunition(int i_id);
  int FindAmmunition(std::string i_name);
  int FindBody(int i_id);
  int FindBody(std::string i_name);
  int FindCape(int i_id);
  int FindCape(std::string i_name);
  int FindFeet(int i_id);
  int FindFeet(std::string i_name);
  int FindHand(int i_id);
  int FindHand(std::string i_name);
  int FindHead(int i_id);
  int FindHead(std::string i_name);
  int FindLegs(int i_id);
  int FindLegs(std::string i_name);
  int FindNeck(int i_id);
  int FindNeck(std::string i_name);
  int FindRing(int i_id);
  int FindRing(std::string i_name);
  int FindShield(int i_id);
  int FindShield(std::string i_name);
  int FindWeapon(int i_id);
  int FindWeapon(std::string i_name);
  int FindMonster(int i_id);
  int FindMonster(std::string i_name);

private:
  CURL *m_curl;
  CURLcode m_res;

  static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *user);

  void FetchApiData(std::string requestString, std::function<void(nlohmann::json)> JsonHandler);

  void _parseEquipmentApiJsonArray(nlohmann::json i_json) { JsonArrayToEquipmentDB(i_json["_items"]); };
  std::function<void(nlohmann::json)> ParseEquipmentApiJsonArray = std::bind(&Database::_parseEquipmentApiJsonArray, this, std::placeholders::_1);

  void _parseMonsterApiJsonArray(nlohmann::json i_json) { JsonArrayToMonsterDB(i_json["_items"]); };
  std::function<void(nlohmann::json)> ParseMonsterApiJsonArray = std::bind(&Database::_parseMonsterApiJsonArray, this, std::placeholders::_1);

  void _jsonArrayToEquipmentDB(nlohmann::json i_json);
  std::function<void(nlohmann::json)> JsonArrayToEquipmentDB = std::bind(&Database::_jsonArrayToEquipmentDB, this, std::placeholders::_1);

  void _jsonArrayToMonsterDB(nlohmann::json i_json);
  std::function<void(nlohmann::json)> JsonArrayToMonsterDB = std::bind(&Database::_jsonArrayToMonsterDB, this, std::placeholders::_1);

  std::string GetJsonString(nlohmann::json i_json);
  
  void DumpJsonToFile(std::string i_filePath, nlohmann::json i_json);
  void ReadFileToJson(std::string i_filePath, nlohmann::json& o_json);
  
  template <typename T>
  int FindById(std::vector<T> i_db, int i_id);
  
  template <typename T>
  int FindByName(std::vector<T> i_db, std::string i_name);

  nlohmann::json m_ammoJSON,
                 m_bodyJSON,
                 m_capeJSON, 
                 m_feetJSON, 
                 m_handJSON, 
                 m_headJSON,
                 m_legsJSON,
                 m_neckJSON,
                 m_ringJSON,
                 m_shieldJSON,
                 m_weaponJSON,
                 m_monsterJSON;

  std::vector<Equipment> m_ammoDB,
                         m_bodyDB,
                         m_capeDB,
                         m_feetDB,
                         m_handDB,
                         m_headDB,
                         m_legsDB,
                         m_neckDB,
                         m_ringDB,
                         m_shieldDB;

  std::vector<Weapon> m_weaponDB;

  std::vector<Monster> m_monsterDB;

  const std::string m_ammoJSONFile = "./db/ammo.json";
  const std::string m_bodyJSONFile = "./db/body.json";
  const std::string m_capeJSONFile = "./db/cape.json";
  const std::string m_feetJSONFile = "./db/feet.json";
  const std::string m_handJSONFile = "./db/hand.json";
  const std::string m_headJSONFile = "./db/head.json";
  const std::string m_legsJSONFile = "./db/legs.json";
  const std::string m_neckJSONFile = "./db/neck.json";
  const std::string m_ringJSONFile = "./db/ring.json";
  const std::string m_shieldJSONFile = "./db/shield.json";
  const std::string m_weaponJSONFile = "./db/weapon.json";
  const std::string m_monsterJSONFile = "./db/monster.json";
};

#endif