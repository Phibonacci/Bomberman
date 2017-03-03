#include "DirReader.hpp"

DirReader::DirReader()
{
  directory = NULL;
  file = NULL;
}

DirReader::~DirReader()
{
  if (directory)
    closedir(directory);
}

bool DirReader::openFolder(const std::string &str)
{
  file = NULL;
  folder = str;
  if ((directory = opendir(str.c_str())))
    genList();
  directory = opendir(str.c_str());
  return (!!(directory));
}

bool DirReader::getNextFile()
{
  if (directory)
    {
      file = readdir(directory);
      if (getFileName() != "" && matchExtension(getFileName()))
	return (true);
      else if (file)
	return (getNextFile());
    }
  return (false);
}

void DirReader::setExtension(const std::string &str)
{
  extension = str;
  openFolder(folder);
}

std::string DirReader::getFileName() const
{
  return (file ? file->d_name : "");
}

bool DirReader::matchExtension(const std::string &str) const
{
  std::string::const_iterator it;
  std::string::const_iterator it2;

  if (extension == "")
    return (true);
  it = extension.begin();
  it2 = str.begin();
  while (it2 != str.end() && *it2 != '.')
    ++it2;
  if (it2 == str.end())
    return (false);
  ++it2;
  if (it2 == str.end())
    return (false);
  while (it != extension.end() && it2 != str.end())
    {
      if (*it != *it2)
	return (false);
      ++it;
      ++it2;
    }
  return (it == extension.end() && it2 == str.end());
}

void DirReader::genList()
{
  list.clear();
  while (getNextFile())
    list.push_back(getFileName());
}

std::vector<std::string> DirReader::getFileList()
{
  return (list);
}
