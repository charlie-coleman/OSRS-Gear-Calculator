#include "Database.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

Database::Database()
{
  m_curl = curl_easy_init();

  Equipment none("None", -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  
  std::vector<STANCE_T> stances;

  STANCE_T noneStance = {""};
  stances.push_back(noneStance);
  stances.push_back(noneStance);
  stances.push_back(noneStance);
  stances.push_back(noneStance);
  Weapon noneWeap("None", -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, stances);

  Monster noneMonster("None", -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  m_ammoDB.push_back(none);
  m_bodyDB.push_back(none);
  m_capeDB.push_back(none);
  m_feetDB.push_back(none);
  m_handDB.push_back(none);
  m_headDB.push_back(none);
  m_legsDB.push_back(none);
  m_neckDB.push_back(none);
  m_ringDB.push_back(none);
  m_shieldDB.push_back(none);

  m_weaponDB.push_back(noneWeap);
  m_twoHandedDB.push_back(noneWeap);
  
  m_monsterDB.push_back(noneMonster);
}

Database::~Database()
{
  curl_easy_cleanup(m_curl);
}

size_t Database::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void Database::FetchEquipment()
{
  FetchApiData("https://api.osrsbox.com/equipment?page=", ParseEquipmentApiJsonArray);
}

void Database::FetchMonsters()
{
  FetchApiData("https://api.osrsbox.com/monsters?page=", ParseMonsterApiJsonArray);
}

void Database::FetchApiData(std::string requestString, std::function<void(nlohmann::json)> JsonHandler)
{
  int pageNum = 1;
  int totalResults = 0;

  nlohmann::json parsedJson;

  if (m_curl)
  {
    do
    {
      std::string output = "";
      
      std::string url(requestString + std::to_string(pageNum));

      curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);
      curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &output);

      m_res = curl_easy_perform(m_curl);

      if (m_res != CURLE_OK)
      {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(m_res));
      }
      else
      {
        parsedJson = nlohmann::json::parse(output);

        totalResults = parsedJson["_meta"]["total"];

        int percentComplete = ((pageNum * 25.0) / totalResults) * 100;

        std::cout << "\rPercent complete: " << percentComplete << "%" << std::flush;

        JsonHandler(parsedJson);
      }
    } while ((pageNum++) <= (totalResults / 25));

    std::cout << std::endl;
  }
}

void Database::_jsonArrayToEquipmentDB(nlohmann::json i_json)
{
  for (int i = 0; i < i_json.size(); i++)
  {
    nlohmann::json item = i_json[i];
    nlohmann::json itemEssense;

    if (item.is_null())
    {
      continue;
    }

    std::string name   = itemEssense["wiki_name"]                    = item["wiki_name"];
    bool equipable     = itemEssense["equipable_by_player"]          = item["equipable_by_player"];
    bool duplicate     = itemEssense["duplicate"]                    = item["duplicate"];

    std::string idStr = itemEssense["id"] = item["id"];
    int id = std::stoi(idStr);

    if (!equipable || duplicate)
    {
      continue;
    }

    int stabAttack     = itemEssense["equipment"]["attack_stab"]     = item["equipment"]["attack_stab"];
    int slashAttack    = itemEssense["equipment"]["attack_slash"]    = item["equipment"]["attack_slash"];
    int crushAttack    = itemEssense["equipment"]["attack_crush"]    = item["equipment"]["attack_crush"];
    int rangedAttack   = itemEssense["equipment"]["attack_ranged"]   = item["equipment"]["attack_ranged"];
    int magicAttack    = itemEssense["equipment"]["attack_magic"]    = item["equipment"]["attack_magic"];

    int stabDefence    = itemEssense["equipment"]["defence_stab"]    = item["equipment"]["defence_stab"];
    int slashDefence   = itemEssense["equipment"]["defence_slash"]   = item["equipment"]["defence_slash"];
    int crushDefence   = itemEssense["equipment"]["defence_crush"]   = item["equipment"]["defence_crush"];
    int rangedDefence  = itemEssense["equipment"]["defence_ranged"]  = item["equipment"]["defence_ranged"];
    int magicDefence   = itemEssense["equipment"]["defence_magic"]   = item["equipment"]["defence_magic"];

    int strength       = itemEssense["equipment"]["melee_strength"]  = item["equipment"]["melee_strength"];
    int rangedStrength = itemEssense["equipment"]["ranged_strength"] = item["equipment"]["ranged_strength"];
    int magicDamage    = itemEssense["equipment"]["magic_damage"]    = item["equipment"]["magic_damage"];
    int prayer         = itemEssense["equipment"]["prayer"]          = item["equipment"]["prayer"];

    Equipment eq;
    Weapon weap;

    if (!item["weapon"].is_null())
    {
      int attackSpeed = itemEssense["weapon"]["attack_speed"] = item["weapon"]["attack_speed"];

      std::vector<STANCE_T> stances;

      itemEssense["weapon"]["stances"] = item["weapon"]["stances"];
      for (int i = 0; i < item["weapon"]["stances"].size(); ++i)
      {
        if (!item["weapon"]["stances"][i].is_null())
        {
          std::string attackStyle = GetJsonString(item["weapon"]["stances"][i]["attack_style"]);
          std::string attackType  = GetJsonString(item["weapon"]["stances"][i]["attack_type"]);
          std::string boosts      = GetJsonString(item["weapon"]["stances"][i]["boosts"]);
          std::string combatStyle = GetJsonString(item["weapon"]["stances"][i]["combat_style"]);
          std::string experience  = GetJsonString(item["weapon"]["stances"][i]["experience"]);

          STANCE_T t = {
            attackStyle,
            attackType,
            boosts,
            combatStyle,
            experience
          };

          stances.push_back(t);
        }
      }

      Weapon t(name, id, stabAttack, slashAttack, crushAttack, rangedAttack, magicAttack,
                         stabDefence, slashDefence, crushDefence, rangedDefence, magicDefence,
                         strength, rangedStrength, magicDamage, prayer, attackSpeed, stances);

      weap = t;
    }
    else
    {
      Equipment t(name, id, stabAttack, slashAttack, crushAttack, rangedAttack, magicAttack,
                            stabDefence, slashDefence, crushDefence, rangedDefence, magicDefence,
                            strength, rangedStrength, magicDamage, prayer);

      eq = t;
    }

    std::string strSlot = itemEssense["equipment"]["slot"] = item["equipment"]["slot"];

    if (strSlot == "ammo")
    {
      m_ammoJSON.push_back(itemEssense);
      m_ammoDB.push_back(eq);
    }
    else if (strSlot == "body")
    {
      m_bodyJSON.push_back(itemEssense);
      m_bodyDB.push_back(eq);
    }
    else if (strSlot == "cape")
    {
      m_capeJSON.push_back(itemEssense);
      m_capeDB.push_back(eq);
    }
    else if (strSlot == "feet")
    {
      m_feetJSON.push_back(itemEssense);
      m_feetDB.push_back(eq);
    }
    else if (strSlot == "hands")
    {
      m_handJSON.push_back(itemEssense);
      m_handDB.push_back(eq);
    }
    else if (strSlot == "head")
    {
      m_headJSON.push_back(itemEssense);
      m_headDB.push_back(eq);
    }
    else if (strSlot == "legs")
    {
      m_legsJSON.push_back(itemEssense);
      m_legsDB.push_back(eq);
    }
    else if (strSlot == "neck")
    {
      m_neckJSON.push_back(itemEssense);
      m_neckDB.push_back(eq);
    }
    else if (strSlot == "ring")
    {
      m_ringJSON.push_back(itemEssense);
      m_ringDB.push_back(eq);
    }
    else if (strSlot == "shield")
    {
      m_shieldJSON.push_back(itemEssense);
      m_shieldDB.push_back(eq);
    }
    else if (strSlot == "2h")
    {
      m_twoHandedJSON.push_back(itemEssense);
      m_twoHandedDB.push_back(weap);
    }
    else if (strSlot == "weapon")
    {
      m_weaponJSON.push_back(itemEssense);
      m_weaponDB.push_back(weap);
    }
    else
    {
      std::cout << "Couldn't find item type: " << strSlot << std::endl;
    }
  }
}

void Database::_jsonArrayToMonsterDB(nlohmann::json i_json)
{
  for (int i = 0; i < i_json.size(); ++i)
  {
    nlohmann::json item = i_json[i];
    nlohmann::json itemEssense;

    std::string idStr  = itemEssense["id"]              = item["id"];
    int id = std::stoi(idStr);

    std::vector<std::string> attributes;

    std::string name   = itemEssense["wiki_name"]       = item["wiki_name"];

    int combatAttack   = itemEssense["attack_level"]    = item["attack_level"];

    int combatStrength = itemEssense["strength_level"]  = item["strength_level"];
    int combatDefence  = itemEssense["defence_level"]   = item["defence_level"];
    int combatMagic    = itemEssense["magic_level"]     = item["magic_level"];
    int combatRanged   = itemEssense["ranged_level"]    = item["ranged_level"];
    int hitpoints      = itemEssense["hitpoints"]       = item["hitpoints"];
    int accuracy       = itemEssense["attack_accuracy"] = item["attack_accuracy"];
    int size           = itemEssense["size"]            = item["size"];
    
    int attackStab     = itemEssense["attack_stab"]     = item["attack_stab"];
    int attackSlash    = itemEssense["attack_slash"]    = item["attack_slash"];
    int attackCrush    = itemEssense["attack_crush"]    = item["attack_crush"];
    int attackMagic    = itemEssense["attack_magic"]    = item["attack_magic"];
    int attackRanged   = itemEssense["attack_ranged"]   = item["attack_ranged"];

    int defenceStab    = itemEssense["defence_stab"]    = item["defence_stab"];
    int defenceSlash   = itemEssense["defence_slash"]   = item["defence_slash"];
    int defenceCrush   = itemEssense["defence_crush"]   = item["defence_crush"];
    int defenceMagic   = itemEssense["defence_magic"]   = item["defence_magic"];
    int defenceRanged  = itemEssense["defence_ranged"]  = item["defence_ranged"];

    int meleeStrength  = itemEssense["melee_strength"]  = item["melee_strength"];
    int rangedStrength = itemEssense["ranged_strength"] = item["ranged_strength"];
    int magicDamage    = itemEssense["magic_damage"]    = item["magic_damage"];

    itemEssense["attributes"] = item["attributes"];

    for (int j = 0; j < item["attributes"].size(); ++j)
    {
      attributes.push_back(GetJsonString(item["attributes"][j]));
    }

    Monster m(name, id, combatAttack, combatStrength, combatDefence, combatRanged, combatMagic, hitpoints, accuracy, size,
                        attackStab, attackSlash, attackCrush, attackMagic, attackRanged,
                        defenceStab, defenceSlash, defenceCrush, defenceMagic, defenceRanged,
                        meleeStrength, rangedStrength, magicDamage,
                        attributes);

    m_monsterJSON.push_back(itemEssense);
    m_monsterDB.push_back(m);
  }
}

void Database::DumpJsonToFiles()
{
  DumpJsonToFile(m_ammoJSONFile, m_ammoJSON);
  DumpJsonToFile(m_bodyJSONFile, m_bodyJSON);
  DumpJsonToFile(m_capeJSONFile, m_capeJSON);
  DumpJsonToFile(m_feetJSONFile, m_feetJSON);
  DumpJsonToFile(m_handJSONFile, m_handJSON);
  DumpJsonToFile(m_headJSONFile, m_headJSON);
  DumpJsonToFile(m_legsJSONFile, m_legsJSON);
  DumpJsonToFile(m_neckJSONFile, m_neckJSON);
  DumpJsonToFile(m_ringJSONFile, m_ringJSON);
  DumpJsonToFile(m_shieldJSONFile, m_shieldJSON);
  DumpJsonToFile(m_twoHandedJSONFile, m_twoHandedJSON);
  DumpJsonToFile(m_weaponJSONFile, m_weaponJSON);
  DumpJsonToFile(m_monsterJSONFile, m_monsterJSON);
}

void Database::ReadFilesToJson()
{
  ReadFileToJson(m_ammoJSONFile, m_ammoJSON);
  ReadFileToJson(m_bodyJSONFile, m_bodyJSON);
  ReadFileToJson(m_capeJSONFile, m_capeJSON);
  ReadFileToJson(m_feetJSONFile, m_feetJSON);
  ReadFileToJson(m_handJSONFile, m_handJSON);
  ReadFileToJson(m_headJSONFile, m_headJSON);
  ReadFileToJson(m_legsJSONFile, m_legsJSON);
  ReadFileToJson(m_neckJSONFile, m_neckJSON);
  ReadFileToJson(m_ringJSONFile, m_ringJSON);
  ReadFileToJson(m_shieldJSONFile, m_shieldJSON);
  ReadFileToJson(m_twoHandedJSONFile, m_twoHandedJSON);
  ReadFileToJson(m_weaponJSONFile, m_weaponJSON);
  ReadFileToJson(m_monsterJSONFile, m_monsterJSON);
}

void Database::ConvertJsonToDatabases()
{
  JsonArrayToEquipmentDB(m_ammoJSON);
  JsonArrayToEquipmentDB(m_bodyJSON);
  JsonArrayToEquipmentDB(m_capeJSON);
  JsonArrayToEquipmentDB(m_feetJSON);
  JsonArrayToEquipmentDB(m_handJSON);
  JsonArrayToEquipmentDB(m_headJSON);
  JsonArrayToEquipmentDB(m_legsJSON);
  JsonArrayToEquipmentDB(m_neckJSON);
  JsonArrayToEquipmentDB(m_ringJSON);
  JsonArrayToEquipmentDB(m_shieldJSON);
  JsonArrayToEquipmentDB(m_twoHandedJSON);
  JsonArrayToEquipmentDB(m_weaponJSON);
  JsonArrayToMonsterDB(m_monsterJSON);
}

int Database::FindAmmunitionById(int i_id)
{
  return FindById(m_ammoDB, i_id);
}
int Database::FindBodyById(int i_id)
{
  return FindById(m_bodyDB, i_id);
}
int Database::FindCapeById(int i_id)
{
  return FindById(m_capeDB, i_id);
}
int Database::FindFeetById(int i_id)
{
  return FindById(m_feetDB, i_id);
}
int Database::FindHandById(int i_id)
{
  return FindById(m_handDB, i_id);
}
int Database::FindHeadById(int i_id)
{
  return FindById(m_headDB, i_id);
}
int Database::FindLegsById(int i_id)
{
  return FindById(m_legsDB, i_id);
}
int Database::FindNeckById(int i_id)
{
  return FindById(m_neckDB, i_id);
}
int Database::FindRingById(int i_id)
{
  return FindById(m_ringDB, i_id);
}
int Database::FindShieldById(int i_id)
{
  return FindById(m_shieldDB, i_id);
}
int Database::FindOneHandedById(int i_id)
{
  return FindById(m_weaponDB, i_id);
}
int Database::FindTwoHandedById(int i_id)
{
  return FindById(m_twoHandedDB, i_id);
}
int Database::FindMonsterById(int i_id)
{
  return FindById(m_monsterDB, i_id);
}

void Database::DumpJsonToFile(std::string i_fileName, nlohmann::json i_json)
{
  std::ofstream file(i_fileName);
  file << std::setw(2) << i_json;
  file.close();
}

void Database::ReadFileToJson(std::string i_filename, nlohmann::json& o_json)
{
  std::ifstream file(i_filename);
  file >> o_json;
  file.close();
}

std::string Database::GetJsonString(nlohmann::json i_json)
{
  if (i_json.is_null())
  {
    return "";
  }
  else
  {
    return i_json;
  }
}

int Database::FindById(std::vector<Equipment> i_db, int i_id)
{
  for (int i = 0; i < i_db.size(); ++i)
  {
    if (i_db[i].Id() == i_id)
    {
      return i;
    }
  }
  return -1;
}

int Database::FindById(std::vector<Weapon> i_db, int i_id)
{
  for (int i = 0; i < i_db.size(); ++i)
  {
    if (i_db[i].Id() == i_id)
    {
      return i;
    }
  }
  return -1;
}

int Database::FindById(std::vector<Monster> i_db, int i_id)
{
  for (int i = 0; i < i_db.size(); ++i)
  {
    if (i_db[i].Id() == i_id)
    {
      return i;
    }
  }
  return -1;
}

const std::vector<Equipment>& Database::Ammunition() const
{
  return m_ammoDB;
}

const std::vector<Equipment>& Database::Body() const
{
  return m_bodyDB;
}

const std::vector<Equipment>& Database::Cape() const
{
  return m_capeDB;
}

const std::vector<Equipment>& Database::Feet() const
{
  return m_feetDB;
}

const std::vector<Equipment>& Database::Hand() const
{
  return m_handDB;
}

const std::vector<Equipment>& Database::Head() const
{
  return m_headDB;
}

const std::vector<Equipment>& Database::Legs() const
{
  return m_legsDB;
}

const std::vector<Equipment>& Database::Neck() const
{
  return m_neckDB;
}

const std::vector<Equipment>& Database::Ring() const
{
  return m_ringDB;
}

const std::vector<Equipment>& Database::Shield() const
{
  return m_shieldDB;
}

const std::vector<Weapon>& Database::TwoHanded() const
{
  return m_twoHandedDB;
}

const std::vector<Weapon>& Database::OneHanded() const
{
  return m_weaponDB;
}

const std::vector<Monster>& Database::Monsters() const
{
  return m_monsterDB;
}