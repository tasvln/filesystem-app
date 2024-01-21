/*
  Name: Temitope Oladimeji Samuel Adebayo
  Date: 2023-11-03

  I have done all the coding by myself and only copied the code that my professor provided 
  to complete my workshops and assignments.
*/

#include "Directory.h"
#include <iomanip>

using namespace std;

namespace sdds {
  Directory::Directory(std::string name) {
    m_name = name;
  };

  void Directory::update_parent_path(const std::string& newPath) {
    m_parent_path = newPath;

    for (auto i = 0u; i < m_contents.size(); i++) {
      m_contents[i]->update_parent_path(newPath + m_name);
    }
  };

  NodeType Directory::type() const {
    return NodeType::DIR;
  };

  std::string Directory::path() const {
    return m_parent_path + m_name;
  };

  std::string Directory::name() const {
    return m_name;
  };

  int Directory::count() const {
    return (int)m_contents.size();
  };

  size_t Directory::size() const {
    size_t size = 0u;

    for (auto i = 0u; i < m_contents.size(); i++) {
      size += m_contents[i]->size();
    }

    return size;
  };

  Directory& Directory::operator+=(Resource* src) {
    for (auto i = 0u; i < m_contents.size(); i++) {
      if (m_contents[i]->name() == src->name()) {
        throw std::runtime_error("Resource with the same name already exists in this directory");
      }
    }

    m_contents.push_back(src);
    m_contents.back()->update_parent_path(m_parent_path + m_name);
    
    return *this;
  };

  Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags) {
    Resource* resource = nullptr;

    bool recursive = false;

    // check if its recursive
    for(auto flag : flags) {
      if (flag == OpFlags::RECURSIVE) {
        recursive = true;
      }
    }

    // find the resource
    for (auto i = 0u; i < m_contents.size(); i++) {
      if (m_contents[i]->name() == name) {
        resource = m_contents[i];
      } else if (recursive && m_contents[i]->type() == NodeType::DIR) {
        resource = dynamic_cast<Directory*>(m_contents[i])->find(name, flags);
      }
    }

    return resource;
  };

  Directory::~Directory() {
    for (auto i = 0u; i < m_contents.size(); i++) {
      delete m_contents[i];
    }
  };

  void Directory::remove(const std::string& name, const std::vector<OpFlags>& flags) {
    bool recursive = false;

    Resource* resource = nullptr;
    resource = find(name, flags);

    // check if its recursive
    for(auto flag : flags) {
      if (flag == OpFlags::RECURSIVE) {
        recursive = true;
      }
    }

    if (resource) {
      for (auto i = 0u; i < m_contents.size(); i++) {
        if (m_contents[i]->name() == name) {
          if (m_contents[i]->type() == NodeType::DIR) {
            if (recursive) {
              delete m_contents[i];
              m_contents.erase(m_contents.begin() + i);
            } else {
              throw std::invalid_argument(name + " is a directory. Pass the recursive flag to delete directories.");
            }
          } else {
            delete m_contents[i];
            m_contents.erase(m_contents.begin() + i);
          }
        }
      }
    } else {
      throw std::string(name + " does not exist in " + m_name);
    }
  };

  void Directory::display(std::ostream& os, const std::vector<FormatFlags>& flags) const {
    bool isLong = false;

    // check if its long
    for(auto flag : flags) {
      if (flag == FormatFlags::LONG) {
        isLong = true;
      }
    }

    os << "Total size: " << size() << " bytes" << endl;

    for (auto i = 0u; i < m_contents.size(); i++) {
      if (m_contents[i]->type() == NodeType::DIR) {
        os << "D | " << left << setw(15) << m_contents[i]->name() << " |";
      } else if (m_contents[i]->type() == NodeType::FILE) {
        os << "F | " << left << setw(15) << m_contents[i]->name() << " |";
      }

      if (isLong) {
        if (m_contents[i]->type() == NodeType::DIR) {
          os << " " << right << setw(2) << m_contents[i]->count() << " | ";
        } else if (m_contents[i]->type() == NodeType::FILE) {
          os << " " << right << setw(2) << " " << " | ";
        }
        os << right << setw(4) << m_contents[i]->size() << " bytes | ";
      }

      os << endl;
    }
  };
}