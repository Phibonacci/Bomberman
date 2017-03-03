#ifndef DIRREADER_HPP_
# define DIRREADER_HPP_

# include <dirent.h>
# include <iostream>
# include <vector>

/**
 ** This class was created to encapsulate the readdir function
 ** @brief Encapsulate the readdir function
 */
class DirReader
{
public:
  DirReader();
  ~DirReader();

private:
  DIR *directory;
  struct dirent *file;
  std::string extension;
  std::string folder;
  std::vector<std::string> list;

public:
  /**
   ** This function returns the actual file pointed by the object
   ** @return std::string file_name
   */
  std::string getFileName() const;

  /**
   ** This functions gets the next file to be read. It return true if success and false on failure
   ** @return bool state
   */
  bool getNextFile();

  /**
   ** This function returns true if the file extension match with set extension
   ** @param str
   ** @return bool state
   */
  bool matchExtension(const std::string &) const;

  /**
   ** This function opens a folder to retrieve it's files. It returns the opening with a boolean
   ** @param str
   ** @return bool state
   */
  bool openFolder(const std::string &);

  /**
   ** This function sets the extension to take only the matching files.
   ** @param str
   */
  void setExtension(const std::string &);

  /**
   ** This function generates the file list on the actual folder
   */
  void genList();

  /**
   ** This function returns a vector of file names for the actual folder. genList() must be called before.
   ** @return std::vector<std::string> files
   */
  std::vector<std::string> getFileList();
};

#endif
