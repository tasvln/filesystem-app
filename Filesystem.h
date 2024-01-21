/*
  Name: Temitope Oladimeji Samuel Adebayo
  Date: 2023-11-03

  I have done all the coding by myself and only copied the code that my professor provided 
  to complete my workshops and assignments.
*/

#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H

#include <iostream>
#include "Directory.h"

namespace sdds {
  class Filesystem {
      Directory* m_root = {};
      Directory* m_current = {};
    public:
      // a two-argument constructor that receives the name of the file and the name of root directory
      Filesystem(const std::string name, const std::string path = "");

      // delete copy constructor and assignment operator
      Filesystem(const Filesystem&) = delete;
      Filesystem& operator=(const Filesystem&) = delete;

      // delete move constructor and assignment operator
      Filesystem(Filesystem&&);
      Filesystem& operator=(Filesystem&&);

      // an operator that adds a resource to the current directory
      Filesystem& operator+=(Resource*);

      // a function that changes the current directory to the directory
      Directory* change_directory(const std::string& name = "");

      // a query function that returns the current directory
      Directory* get_current_directory() const;

      // a function to remove spaces from the beginning and end of a string
      void trim(std::string&);

      // a function to add a file to the current directory
      void addResource(std::string& path, const std::string& contents = {});

      // destructor
      ~Filesystem();
  };
};

#endif


