#ifndef DATA_FETCHER_H
#define DATA_FETCHER_H

#include <vector>
#include <curl/curl.h>
#include "json.hpp"

#include "Equipment.h"

struct CurlString
{
  char* ptr;
  size_t len;
};

class DataFetcher
{
public:
  DataFetcher();
  ~DataFetcher();

  std::vector<Equipment> FetchEquipment();
  void FetchMonsters();

private:
  CURL *m_curl;
  CURLcode m_res;

  static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

  std::vector<Equipment> JSON_ToEquipmentList(nlohmann::json i_json);
};

#endif