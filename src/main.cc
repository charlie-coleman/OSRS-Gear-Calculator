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

  int headIdx = db.FindHeadById(-1);
  int bodyIdx = db.FindBodyById(4720);
  int legsIdx = db.FindLegsById(4722);
  int twoHIdx = db.FindTwoHandedById(4718);

  int ammoIdx = db.FindAmmunitionById(22947);
  int neckIdx = db.FindNeckById(19553);
  int ringIdx = db.FindRingById(11773);
  int bootsIdx = db.FindFeetById(13239);
  int glovesIdx = db.FindHandById(7462);
  int capeIdx = db.FindCapeById(6570);

  std::cout << "Getting enemy by id..." << std::endl;

  int enemyIdx = db.FindMonsterById(5779);

  if (headIdx != -1 && bodyIdx != -1 && legsIdx != -1 && twoHIdx != -1 && ammoIdx != -1 && neckIdx != -1 &&
      ringIdx != -1 && bootsIdx != -1 && glovesIdx != -1 && capeIdx != -1 && enemyIdx != -1)
  {
    Equipment head = db.Head()[headIdx];
    Equipment body = db.Body()[bodyIdx];
    Equipment legs = db.Legs()[legsIdx];
    Weapon twoH    = db.TwoHanded()[twoHIdx];

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
    std::cout << "Weapon: " << twoH.Name() << std::endl;
    std::cout << "Ammo: " << ammo.Name() << std::endl;
    std::cout << "Necklace: " << neck.Name() << std::endl;
    std::cout << "Ring: " << ring.Name() << std::endl;
    std::cout << "Boots: " << boots.Name() << std::endl;
    std::cout << "Gloves: " << gloves.Name() << std::endl;
    std::cout << "Cape: " << cape.Name() << std::endl;
    std::cout << "Enemy: " << enemy.Name() << std::endl;

    std::cout << "Creating setup..." << std::endl;

    Setup s(player, enemy, ammo, body, cape, boots, gloves, head, legs, neck, ring, twoH);
    s.SetStance(1);
    s.SetCurrentHitpoints(1);
    s.SetOnTask(false);

    std::cout << "Max hit: " << s.GetMaxHit() << std::endl;
  }
  else
  {
    std::cout << "Error finding a piece of equipment or monster." << std::endl;
  }
}