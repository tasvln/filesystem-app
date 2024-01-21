/*
  Name: Temitope Oladimeji Samuel Adebayo
  Date: 2023-11-03

  I have done all the coding by myself and only copied the code that my professor provided 
  to complete my workshops and assignments.
*/

#include <fstream>
#include <string>
#include "Filesystem.h"
#include "Directory.h"
#include "File.h"

using namespace std;

namespace sdds {
  Filesystem::Filesystem(const std::string name, const std::string path) {
    // create a new directory
    m_root = new Directory(path);
    // update the current directory
    m_current = m_root;

    std::ifstream file(name);

    if (file.is_open()) {
      std::string line;

      while (getline(file, line)) {
        // find the first occurence of the character
        bool delimPos = line.find('|') != std::string::npos;
        string filePath;
        string fileContents;
        string directoryPath;

        // if the character is found
        if (delimPos) {
          // get the file path
          filePath = line.substr(0, line.find('|'));
          // remove leading and trailing spaces
          trim(filePath);

          // get the file contents
          fileContents = line.substr(line.find('|') + 1);
          // remove leading and trailing spaces
          trim(fileContents);

          addResource(filePath, fileContents);
        } else {
          // get the directory path
          directoryPath = line.substr(0, line.find('\n'));
          // remove leading and trailing spaces
          trim(directoryPath);

          addResource(directoryPath);
        }
      }

      file.close();
    } else {
      delete m_root;
      m_root = nullptr;
      throw std::runtime_error("Cannot open file " + name);
    }
  }

  void Filesystem::addResource(std::string& path, const std::string& contents) {
    Directory* currentDirectory = m_root;
    size_t start = 0;
    size_t delimPos = path.find('/');

    // loop through the path
    while (delimPos != std::string::npos) {
      // get the directory name
      string dirName = path.substr(start, delimPos - start + 1);

      // check if the directory exists
      if (!currentDirectory->find(dirName)) {
        // Create a new directory
        Directory* newDir = new Directory(dirName);

        *currentDirectory += newDir;
        currentDirectory = newDir;
      } else {
        // Update the current directory
        currentDirectory = dynamic_cast<Directory*>(currentDirectory->find(dirName));
      }

      // update the start and delimPos
      start = delimPos + 1;
      delimPos = path.find('/', start);
    }

    // check if there's a file to add
    if (!contents.empty() && !currentDirectory->find(path)) {
      // get the file name
      string fileName = path.substr(start, path.length() - start);

      // create a new file with the file name and contents
      File* newFile = new File(fileName, contents);

      // add the file to the current directory
      *currentDirectory += newFile;
    }
  }

  void Filesystem::trim(std::string& str) {
    // remove leading spaces
    while (str[0] == ' ') {
      str.erase(0, 1);
    }

    // remove trailing spaces
    while (str[str.length() - 1] == ' ') {
      str.erase(str.length() - 1, 1);
    }
  }

  Filesystem::Filesystem(Filesystem&& src) {
    *this = std::move(src);
  }

  Filesystem& Filesystem::operator=(Filesystem&& src) {
    // check for self assignment
    if (this != &src) {
      // delete the current root and current directory
      delete m_root;

      // shallow copy
      m_root = src.m_root;
      m_current = src.m_current;

      // set the source to safe empty state
      src.m_root = nullptr;
      src.m_current = nullptr;
    }
    return *this;
  }

  Filesystem& Filesystem::operator+=(Resource* src) {
    *m_current += src;
    return *this;
  }

  Directory* Filesystem::change_directory(const std::string& name) {
    Directory* dir = {};

    // check if the name is empty
    if (name.empty()) {
      m_current = m_root;
    } else {
      // check if the directory exists
      dir = dynamic_cast<Directory*>(m_current->find(name));

      if (dir) {
        m_current = dir;
      } else {
        throw std::invalid_argument("Cannot change directory! " + name + " not found!");
      }
    }

    return m_current;
  }

  Directory* Filesystem::get_current_directory() const {
    return m_current;
  }

  Filesystem::~Filesystem() {
    delete m_root;
  }
}