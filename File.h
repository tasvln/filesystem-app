/*
  Name: Temitope Oladimeji Samuel Adebayo
  Date: 2023-11-03

  I have done all the coding by myself and only copied the code that my professor provided 
  to complete my workshops and assignments.
*/

#ifndef SDDS_FILE_H
#define SDDS_FILE_H

#include <iostream>
#include "Resource.h"

namespace sdds {
  class File: public Resource {
      std::string m_contents{};
    public:
      // a two-argument constructor that receives the name of the file and its contents
      File(std::string name, std::string contents = "");
      // a function that sets the parent path to the parameter
      void update_parent_path(const std::string&);
      // a query function that returns Flags::FILE
      NodeType type() const;
      // a query function that returns the full absolute path of the file
      std::string path() const;
      // a query function that returns the name of the file
      std::string name() const;
      // a query function that returns -1
      int count() const;
      // a query function that returns the size of the file in bytes
      size_t size() const;
  };
}

#endif