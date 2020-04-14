#ifndef THING_H
#define THING_H

#include <string>

class Thing
{
public:
  Thing() {};
  ~Thing() {};

  void SetName(std::string i_name) { m_name = i_name; };
  std::string Name() const  { return m_name;   };

  void SetId(int i_id)  { m_id = i_id; };
  int Id() const { return m_id; };

protected:
  std::string m_name;
  int m_id;
};

#endif