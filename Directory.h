/*
  Name: Temitope Oladimeji Samuel Adebayo
  Date: 2023-11-03

  I have done all the coding by myself and only copied the code that my professor provided 
  to complete my workshops and assignments.
*/

#ifndef SDDS_DIRECTORY_H
#define SDDS_DIRECTORY_H

#include <iostream>
#include <vector>
#include "Resource.h"

namespace sdds {
  class Directory: public Resource {
      std::vector<Resource*> m_contents{};
    public:
      // a one-argument constructor that receives the name of the directory
      Directory(std::string name);
      // a function that sets the parent path to the parameter
      void update_parent_path(const std::string&);
      // a query function that returns Flags::DIR
      NodeType type() const;
      // a query function that returns the full absolute path of the directory
      std::string path() const;
      // a query function that returns the name of the directory
      std::string name() const;
      // a query function that returns the number of files and directories in the directory
      int count() const;
      // a query function that returns the size of the directory in bytes
      size_t size() const;
      // an operator that adds a resource to the directory and returns a reference to the current directory
      Directory& operator+=(Resource*);
      // a function that returns a pointer to the resource with the name and flags passed as parameters
      Resource* find(const std::string& name, const std::vector<OpFlags>& flags = {});
      // a function that removes the resource with the name and flags passed as parameters
      ~Directory();
      
      // a function that deletes a resource from the directory whose name matches the first argument 
      void remove(const std::string&, const std::vector<OpFlags>& = {});
      // a function that displays the contents of the directory
      void display(std::ostream&, const std::vector<FormatFlags>& = {}) const;

      // remove copy/move constructors and assignment operators
      Directory(const Directory&) = delete;
      Directory(Directory&&) = delete;
      Directory& operator=(const Directory&) = delete;
      Directory& operator=(Directory&&) = delete;
  };
}

#endif