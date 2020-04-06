#include "DataFetcher.h"

#include <iostream>
#include <string>

DataFetcher::DataFetcher()
{
  m_curl = curl_easy_init();
}

DataFetcher::~DataFetcher()
{
}

size_t DataFetcher::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::vector<Equipment> DataFetcher::FetchEquipment()
{
  std::vector<Equipment> o_list;

  std::string requestString = "https://api.osrsbox.com/equipment?page=";
  int pageNum = 1;
  nlohmann::json parsedJson;
  int totalResults = 0;

  if (m_curl)
  {
    do
    {
      std::string output = "";
      std::cout << "Page: " << pageNum << std::endl;
      std::string url(requestString + std::to_string(pageNum));
      curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());

      curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);
      curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &output);

      m_res = curl_easy_perform(m_curl);

      if (m_res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(m_res));

      parsedJson = nlohmann::json::parse(output);

      totalResults = parsedJson["_meta"]["total"];

      std::vector<Equipment> l = JSON_ToEquipmentList(parsedJson);
      o_list.insert(o_list.end(), l.begin(), l.end());
    } while ((pageNum++) <= (totalResults / 25));

    curl_easy_cleanup(m_curl);
  }

  return o_list;
}

void DataFetcher::FetchMonsters()
{
  std::string output = "";

  m_curl = curl_easy_init();
  if (m_curl)
  {
    curl_easy_setopt(m_curl, CURLOPT_URL, "https://api.osrsbox.com/monsters");

    curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, output);

    m_res = curl_easy_perform(m_curl);

    if (m_res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(m_res));

    curl_easy_cleanup(m_curl);
  }

  std::cout << output << std::endl;
}

std::vector<Equipment> DataFetcher::JSON_ToEquipmentList(nlohmann::json i_json)
{
  std::vector<Equipment> o_list;

  for (int i = 0; i < i_json["_items"].size(); i++)
  {
    nlohmann::json item = i_json["_items"][i];
    
    std::string name = item["name"];
    bool equipable = item["equipable_by_player"];

    int stabAttack = item["equipment"]["attack_stab"];
    int slashAttack = item["equipment"]["attack_slash"];
    int crushAttack = item["equipment"]["attack_crush"];
    int rangedAttack = item["equipment"]["attack_ranged"];
    int magicAttack = item["equipment"]["attack_magic"];

    int stabDefense = item["equipment"]["defence_stab"];
    int slashDefense = item["equipment"]["defence_slash"];
    int crushDefense = item["equipment"]["defence_crush"];
    int rangedDefense = item["equipment"]["defence_ranged"];
    int magicDefense = item["equipment"]["defence_magic"];

    int strength = item["equipment"]["melee_strength"];
    int rangedStrength = item["equipment"]["ranged_strength"];
    int magicDamage = item["equipment"]["magic_damage"];
    int prayer = item["equipment"]["prayer"];

    SLOT_E::Type slot;

    std::string strSlot = item["equipment"]["slot"];

    if (strSlot == "ammo") slot = SLOT_E::Type::AMMUNITION;
    else if (strSlot == "body") slot = SLOT_E::Type::BODY;
    else if (strSlot == "cape") slot = SLOT_E::Type::CAPE;
    else if (strSlot == "feet") slot = SLOT_E::Type::FEET;
    else if (strSlot == "hands") slot = SLOT_E::Type::HAND;
    else if (strSlot == "head") slot = SLOT_E::Type::HEAD;
    else if (strSlot == "legs") slot = SLOT_E::Type::LEGS;
    else if (strSlot == "neck") slot = SLOT_E::Type::NECK;
    else if (strSlot == "ring") slot = SLOT_E::Type::RING;
    else if (strSlot == "shield") slot = SLOT_E::Type::SHIELD;
    else if (strSlot == "2h") slot = SLOT_E::Type::TWOHANDED;
    else if (strSlot == "weapon") slot = SLOT_E::Type::WEAPON;
    else
    {
      std::cout << strSlot << " type not found." << std::endl;
    }

    Equipment piece(name, slot, stabAttack,  slashAttack,    crushAttack,  rangedAttack,  magicAttack,
                                stabDefense, slashDefense,   crushDefense, rangedDefense, magicDefense,
                                strength,    rangedStrength, magicDamage,  prayer);
    
    if (equipable)
      o_list.push_back(piece);
  }

  return o_list;
}