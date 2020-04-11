#include "Equipment.h"
#include "Player.h"
#include "Database.h"
#include "Setup.h"

#include <iostream>
#include <curl/curl.h>

int main(int argc, char **argv)
{
  Database db;

  // std::cout << "Fetching equipment..." << std::endl;
  // db.FetchEquipment();
  // std::cout << "Fetching monsters..." << std::endl;
  // db.FetchMonsters();

  // db.DumpJsonToFiles();

  std::cout << "Reading item data from JSON files..." << std::endl;

  db.ReadFilesToJson();
  db.ConvertJsonToDatabases();

  std::cout << db.Head()[0].Name() << std::endl;

  std::cout << "Creating player..." << std::endl;

  Player player(99, 99, 99, 99, 99, 99, 99, 
                POTIONS_E::SUPER_POTION, POTIONS_E::SUPER_POTION, POTIONS_E::SUPER_POTION, POTIONS_E::REGULAR_POTION, MAGIC_POTIONS_E::NONE,
                ATTACK_PRAYER_E::PIETY, STRENGTH_PRAYER_E::PIETY, DEFENCE_PRAYER_E::PIETY, RANGED_PRAYER_E::RIGOUR, MAGIC_PRAYER_E::AUGURY);

  std::cout << "Getting equipment by ids..." << std::endl;

  int headIdx = db.FindHeadById(23073);
  int bodyIdx = db.FindBodyById(-1);
  int legsIdx = db.FindLegsById(-1);
  int twoHIdx = db.FindTwoHandedById(-1);
  int oneHIdx = db.FindOneHandedById(19675);
  int shieldIdx = db.FindShieldById(-1);

  int ammoIdx = db.FindAmmunitionById(-1);
  int neckIdx = db.FindNeckById(12018);
  int ringIdx = db.FindRingById(-1);
  int bootsIdx = db.FindFeetById(-1);
  int glovesIdx = db.FindHandById(-1);
  int capeIdx = db.FindCapeById(-1);

  std::cout << "Getting enemy by id..." << std::endl;

  int enemyIdx = db.FindMonsterById(6611);

  if (headIdx != -1 && bodyIdx != -1 && legsIdx != -1 && twoHIdx != -1 && ammoIdx != -1 && neckIdx != -1 &&
      ringIdx != -1 && bootsIdx != -1 && glovesIdx != -1 && capeIdx != -1 && enemyIdx != -1)
  {
    Equipment head   = db.Head()[headIdx];
    Equipment body   = db.Body()[bodyIdx];
    Equipment legs   = db.Legs()[legsIdx];
    Weapon twoH      = db.TwoHanded()[twoHIdx];
    Weapon oneH      = db.OneHanded()[oneHIdx];
    Equipment shield = db.Shield()[shieldIdx];

    Equipment ammo   = db.Ammunition()[ammoIdx];
    Equipment neck   = db.Neck()[neckIdx];
    Equipment ring   = db.Ring()[ringIdx];
    Equipment boots  = db.Feet()[bootsIdx];
    Equipment gloves = db.Hand()[glovesIdx];
    Equipment cape   = db.Cape()[capeIdx];

    Monster enemy = db.Monsters()[enemyIdx];

    std::cout << "Helmet: " << head.Name() << std::endl;
    std::cout << "Body: " << body.Name() << std::endl;
    std::cout << "Legs: " << legs.Name() << std::endl;
    std::cout << "Weapon: " << oneH.Name() << std::endl;
    std::cout << "Stance: " << oneH.WeaponStats().Stances[1].AttackStyle << " (" << oneH.WeaponStats().Stances[1].AttackType << ")" << std::endl;
    std::cout << "Ammo: " << ammo.Name() << std::endl;
    std::cout << "Necklace: " << neck.Name() << std::endl;
    std::cout << "Ring: " << ring.Name() << std::endl;
    std::cout << "Boots: " << boots.Name() << std::endl;
    std::cout << "Gloves: " << gloves.Name() << std::endl;
    std::cout << "Cape: " << cape.Name() << std::endl;
    std::cout << "Enemy: " << enemy.Name() << std::endl;
    for (int i = 0; i < enemy.Attributes().size(); i++)
    {
      std::cout << "\tAttr: " << enemy.Attributes()[i] << std::endl;
    }

    std::cout << "Creating setup..." << std::endl;

    Setup s(player, enemy, ammo, body, cape, boots, gloves, head, legs, neck, ring, shield, oneH);
    s.SetStance(1);
    s.SetCurrentHitpoints(99);
    s.SetOnTask(true);

    std::cout << "Max hit: " << s.GetMaxHit() << std::endl;
  }
  else
  {
    std::cout << "Error finding a piece of equipment or monster." << std::endl;
  }
}