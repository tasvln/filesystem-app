/*
  Name: Temitope Oladimeji Samuel Adebayo
  Date: 2023-11-03

  I have done all the coding by myself and only copied the code that my professor provided 
  to complete my workshops and assignments.
*/

#include "File.h"

namespace sdds {
  File::File(std::string name, std::string contents) {
    m_name = name;
    m_contents = contents;
  };

  void File::update_parent_path(const std::string& newPath) {
    m_parent_path = newPath;
  };

  NodeType File::type() const {
    return NodeType::FILE;
  };

  std::string File::path() const {
    return m_parent_path + m_name;
  };

  std::string File::name() const {
    return m_name;
  };

  int File::count() const {
    return -1;
  };

  size_t File::size() const {
    return m_contents.size();
  };
};