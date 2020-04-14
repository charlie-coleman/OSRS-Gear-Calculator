#ifndef LEVELENTRY_H
#define LEVELENTRY_H

#include <gtkmm.h>
#include <vector>

class LevelEntry
{
public:
  LevelEntry(Gtk::Grid *i_grid, int i_row, std::string i_labelStr, std::vector<std::string> i_potionNames, std::vector<std::string> i_prayerNames);
  virtual ~LevelEntry();

  int Level() const;
  int PotionIndex() const;
  int PrayerIndex() const;

  sigc::signal<void, int> signal_level_changed(), signal_prayer_changed(), signal_potion_changed();

protected:
  Gtk::Label m_label;
  Gtk::SpinButton m_levelEntry;
  Gtk::ComboBox m_potionCombo, m_prayerCombo;

  std::vector<std::string> m_potionNames, m_prayerNames;

  class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:
    ModelColumns()
    {
      add(m_colIndex);
      add(m_colName);
    }

    Gtk::TreeModelColumn<int> m_colIndex;
    Gtk::TreeModelColumn<Glib::ustring> m_colName;
  };

  void InitializePotions();
  void InitializePrayers();

  void on_level_changed();
  void on_potion_changed();
  void on_prayer_changed();

  sigc::signal<void, int> m_signal_level_changed, m_signal_prayer_changed, m_signal_potion_changed;

  ModelColumns m_columns;
  Glib::RefPtr<Gtk::TreeStore> m_potionTreeModel, m_prayerTreeModel;

  int m_level;
  int m_potionIndex;
  int m_prayerIndex;
};

#endif