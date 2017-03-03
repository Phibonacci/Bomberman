#include "ConfigLoader.hpp"

std::string const ConfigLoader::types[3] =
  {
    "int",
    "float",
    "string"
  };

std::map<std::string, std::map<std::string, ConfigLoader::Value *> > ConfigLoader::config_files;

ConfigLoader::ConfigLoader()
{
}

ConfigLoader::~ConfigLoader()
{
  std::map<std::string, std::map<std::string, Value *> >::const_iterator it;
  std::map<std::string, Value *>::const_iterator it2;
  std::pair<std::string, std::map<std::string, Value *> > pair;
  std::pair<std::string, Value *> pair2;

  it = config_files.begin();
  while (it != config_files.end())
    {
      pair = *it;
      it2 = pair.second.begin();
      while (it2 != pair.second.end())
	{
	  pair2 = *it2;
	  delete pair2.second;
	  ++it2;
	}
      ++it;
    }
}

ConfigLoader::Value::Value(const std::string &value, e_type type)
{
  _str = value;
  _type = type;
}

ConfigLoader::Value::~Value()
{
}

ConfigLoader::Value::e_type ConfigLoader::Value::getType() const
{
  return (_type);
}

const std::string &ConfigLoader::Value::getValue() const
{
  return (_str);
}

void ConfigLoader::Value::setType(ConfigLoader::Value::e_type type)
{
  _type = type;
}

void ConfigLoader::Value::setValue(const std::string &str)
{
  _str = str;
}

void ConfigLoader::appendFile(const std::string &name)
{
  config_files.insert(std::pair<std::string, std::map<std::string, Value *> >(name, std::map<std::string, Value *>()));
}

void ConfigLoader::appendValues(const std::string &name, const std::string &var, ConfigLoader::Value::e_type varType, const std::string &value)
{
  std::map<std::string, std::map<std::string, Value *> >::const_iterator it;
  Value *v;

  v = new Value(value, varType);
  it = config_files.find(name);
  if (it == config_files.end())
    appendFile(name);
  config_files[name].insert(std::pair<std::string, Value *>(var, v));
}

void ConfigLoader::parseLine(const std::string &name, const std::string &str)
{
  std::string varName;
  ConfigLoader::Value::e_type varType;
  std::string varValue;

  varName = retrieveVarName(str);
  varType = retrieveVarType(str);
  varValue = retrieveVarValue(str);
  appendValues(name, varName, varType, varValue);
}

void ConfigLoader::parseConfigFile(const std::string &str, const std::string &name)
{
  std::fstream file;
  std::string line;

  file.open(str.c_str());
  if (!file.is_open())
    throw Exception("Impossible to open the file");
  while (!file.eof())
    {
      std::getline(file, line);
      if (line != "")
	parseLine(name, line);
    }
  file.close();
}

std::string ConfigLoader::retrieveVarName(const std::string &str)
{
  std::string::const_iterator it;
  std::string varName;

  it = str.begin();
  if (it != str.begin() && *it != '[')
    throw Exception("Bad variable declaration");
  ++it;
  while (it != str.end() && *it != ']')
    {
      varName.push_back(*it);
      ++it;
    }
  if (it == str.end())
    throw Exception("Bad variable declaration");
  return (varName);
}

ConfigLoader::Value::e_type ConfigLoader::retrieveVarType(const std::string &str)
{
  std::string::const_iterator it;
  std::string varType;

  it = str.begin();
  while (it != str.end() && *it != '<')
    ++it;
  if (it == str.end() || *it != '<')
    throw Exception("Bad variable type declaration");
  ++it;
  while (it != str.end() && *it != '>')
    {
      varType.push_back(*it);
      ++it;
    }
  if (it == str.end())
    throw Exception("Bad variable type declaration");
  return (findVarType(varType));
}

ConfigLoader::Value::e_type ConfigLoader::findVarType(const std::string &str)
{
  std::map<std::string, ConfigLoader::Value::e_type> map;
  std::map<std::string, ConfigLoader::Value::e_type>::const_iterator it;
  std::pair<std::string, ConfigLoader::Value::e_type> pair;

  map.insert(std::pair<std::string, ConfigLoader::Value::e_type>("int", ConfigLoader::Value::INT));
  map.insert(std::pair<std::string, ConfigLoader::Value::e_type>("float", ConfigLoader::Value::FLOAT));
  map.insert(std::pair<std::string, ConfigLoader::Value::e_type>("string", ConfigLoader::Value::STRING));
  it = map.find(str);
  if (it == map.end())
    throw Exception("Bad variable type");
  pair = *it;
  return (pair.second);
}

const std::string &ConfigLoader::findVarType(ConfigLoader::Value::e_type type)
{
  if (type == ConfigLoader::Value::INT)
    return (ConfigLoader::types[0]);
  else if (type == ConfigLoader::Value::FLOAT)
    return (ConfigLoader::types[1]);
  else
    return (ConfigLoader::types[2]);
}

std::string ConfigLoader::retrieveVarValue(const std::string &str)
{
  std::string::const_iterator it;
  std::string varValue;

  it = str.begin();
  while (it != str.end() && *it != '=')
    ++it;
  if (it == str.end())
    throw Exception("Bad variable value");
  ++it;
  while (it != str.end())
    {
      varValue.push_back(*it);
      ++it;
    }
  return (varValue);
}

void ConfigLoader::getVarValue(const std::string &file, const std::string &var, float &value)
{
  Value *v;
  std::map<std::string, std::map<std::string, Value *> >::const_iterator it;
  std::map<std::string, Value *>::const_iterator it2;
  std::pair<std::string, std::map<std::string, Value *> > pair;
  std::pair<std::string, Value *> pair2;

  it = config_files.find(file);
  if (it == config_files.end())
    throw Exception("This config file isn't loaded");
  pair = *it;
  it2 = pair.second.find(var);
  if (it2 == pair.second.end())
    throw Exception("This variable doesn't exist");
  pair2 = *it2;
  v = pair2.second;
  if (v->getType() != ConfigLoader::Value::FLOAT)
    throw Exception("Bad variable type");

  std::istringstream buffer(v->getValue());
  buffer >> value;
}

void ConfigLoader::getVarValue(const std::string &file, const std::string &var, int &value)
{
  Value *v;
  std::map<std::string, std::map<std::string, Value *> >::const_iterator it;
  std::map<std::string, Value *>::const_iterator it2;
  std::pair<std::string, std::map<std::string, Value *> > pair;
  std::pair<std::string, Value *> pair2;

  it = config_files.find(file);
  if (it == config_files.end())
    throw Exception("This config file isn't loaded");
  pair = *it;
  it2 = pair.second.find(var);
  if (it2 == pair.second.end())
    throw Exception("This variable doesn't exist");
  pair2 = *it2;
  v = pair2.second;
  if (v->getType() != ConfigLoader::Value::INT)
    throw Exception("Bad variable type");

  std::istringstream buffer(v->getValue());
  buffer >> value;
}

void ConfigLoader::getVarValue(const std::string &file, const std::string &var, std::string &value)
{
  Value *v;
  std::map<std::string, std::map<std::string, Value *> >::const_iterator it;
  std::map<std::string, Value *>::const_iterator it2;
  std::pair<std::string, std::map<std::string, Value *> > pair;
  std::pair<std::string, Value *> pair2;

  it = config_files.find(file);
  if (it == config_files.end())
    throw Exception("This config file isn't loaded");
  pair = *it;
  it2 = pair.second.find(var);
  if (it2 == pair.second.end())
    throw Exception("This variable doesn't exist");
  pair2 = *it2;
  v = pair2.second;
  if (v->getType() != ConfigLoader::Value::STRING)
    throw Exception("Bad variable type");
  value = v->getValue();
}

void ConfigLoader::appendToFile(const std::string &file, const std::string &name)
{
  std::map<std::string, std::map<std::string, Value *> >::const_iterator it;
  std::map<std::string, Value *>::const_iterator it2;
  std::pair<std::string, std::map<std::string, Value *> > pair;
  std::pair<std::string, Value *> pair2;
  std::ofstream f;
  Value *v;

  it = config_files.find(name);
  if (it == config_files.end())
    throw Exception("This index doesn't exist");
  pair = *it;
  it2 = pair.second.begin();
  f.open(file.c_str(), std::ios_base::app);
  if (!f.is_open())
    throw Exception("Impossible to open the output file");
  while (it2 != pair.second.end())
    {
      pair2 = *it2;
      v = pair2.second;
      f << '[' << pair2.first << ']' << '<' << findVarType(v->getType()) << ">=" << v->getValue() << std::endl;
      ++it2;
    }
}

void ConfigLoader::writeToFile(const std::string &file, const std::string &name)
{
  std::map<std::string, std::map<std::string, Value *> >::const_iterator it;
  std::map<std::string, Value *>::const_iterator it2;
  std::pair<std::string, std::map<std::string, Value *> > pair;
  std::pair<std::string, Value *> pair2;
  std::ofstream f;
  Value *v;

  it = config_files.find(name);
  if (it == config_files.end())
    throw Exception("This index doesn't exist");
  pair = *it;
  it2 = pair.second.begin();
  f.open(file.c_str(), std::ios::in | std::ios::trunc);
  if (!f.is_open())
    throw Exception("Impossible to open the output file");
  while (it2 != pair.second.end())
    {
      pair2 = *it2;
      v = pair2.second;
      f << '[' << pair2.first << ']' << '<' << findVarType(v->getType()) << ">=" << v->getValue() << std::endl;
      ++it2;
    }
}

void ConfigLoader::modifyValue(const std::string &name, const std::string &var, int value)
{
  std::map<std::string, std::map<std::string, Value *> >::const_iterator it;
  std::map<std::string, Value *>::const_iterator it2;
  std::pair<std::string, std::map<std::string, Value *> > pair;
  std::pair<std::string, Value *> pair2;
  std::ostringstream convert;
  Value *v;

  it = config_files.find(name);
  if (it == config_files.end())
    throw Exception("This index doesn't exist");
  pair = *it;
  it2 = pair.second.find(var);
  if (it2 == pair.second.end())
    throw Exception("The variable doesn't exist");
  pair2 = *it2;
  v = pair2.second;
  v->setType(ConfigLoader::Value::INT);
  convert << value;
  v->setValue(convert.str());
}

void ConfigLoader::modifyValue(const std::string &name, const std::string &var, float value)
{
  std::map<std::string, std::map<std::string, Value *> >::const_iterator it;
  std::map<std::string, Value *>::const_iterator it2;
  std::pair<std::string, std::map<std::string, Value *> > pair;
  std::pair<std::string, Value *> pair2;
  std::ostringstream convert;
  Value *v;

  it = config_files.find(name);
  if (it == config_files.end())
    throw Exception("This index doesn't exist");
  pair = *it;
  it2 = pair.second.find(var);
  if (it2 == pair.second.end())
    throw Exception("The variable doesn't exist");
  pair2 = *it2;
  v = pair2.second;
  v->setType(ConfigLoader::Value::FLOAT);
  convert << value;
  v->setValue(convert.str());
}

void ConfigLoader::modifyValue(const std::string &name, const std::string &var, const std::string &value)
{
  std::map<std::string, std::map<std::string, Value *> >::const_iterator it;
  std::map<std::string, Value *>::const_iterator it2;
  std::pair<std::string, std::map<std::string, Value *> > pair;
  std::pair<std::string, Value *> pair2;
  Value *v;

  it = config_files.find(name);
  if (it == config_files.end())
    throw Exception("This index doesn't exist");
  pair = *it;
  it2 = pair.second.find(var);
  if (it2 == pair.second.end())
    throw Exception("The variable doesn't exist");
  pair2 = *it2;
  v = pair2.second;
  v->setType(ConfigLoader::Value::STRING);
  v->setValue(value);
}

void ConfigLoader::modifyType(const std::string &name, const std::string &var, ConfigLoader::Value::e_type type)
{
  std::map<std::string, std::map<std::string, Value *> >::const_iterator it;
  std::map<std::string, Value *>::const_iterator it2;
  std::pair<std::string, std::map<std::string, Value *> > pair;
  std::pair<std::string, Value *> pair2;
  Value *v;

  it = config_files.find(name);
  if (it == config_files.end())
    throw Exception("This index doesn't exist");
  pair = *it;
  it2 = pair.second.find(var);
  if (it2 == pair.second.end())
    throw Exception("The variable doesn't exist");
  pair2 = *it2;
  v = pair2.second;
  v->setType(type);
}

void ConfigLoader::removeValue(const std::string &name, const std::string &var)
{
  std::map<std::string, std::map<std::string, Value *> >::const_iterator it;
  std::map<std::string, Value *>::const_iterator it2;
  std::pair<std::string, std::map<std::string, Value *> > pair;
  std::pair<std::string, Value *> pair2;
  Value *v;

  it = config_files.find(name);
  if (it == config_files.end())
    throw Exception("This index doesn't exist");
  pair = *it;
  it2 = pair.second.find(var);
  if (it2 == pair.second.end())
    throw Exception("The variable doesn't exist");
  pair2 = *it2;
  v = pair2.second;
  config_files[name].erase(var);
  delete v;
}

void ConfigLoader::dump()
{
  std::map<std::string, std::map<std::string, Value *> >::const_iterator it;
  std::map<std::string, Value *>::const_iterator it2;
  std::pair<std::string, std::map<std::string, Value *> > pair;
  std::pair<std::string, Value *> pair2;

  it = config_files.begin();
  while (it != config_files.end())
    {
      pair = *it;
      it2 = pair.second.begin();
      while (it2 != pair.second.end())
	{
	  pair2 = *it2;
	  ++it2;
	}
      ++it;
    }
}

bool ConfigLoader::keyExist(const std::string &index, const std::string &key)
{
  std::map<std::string, std::map<std::string, Value *> >::const_iterator it;
  std::map<std::string, Value *>::const_iterator it2;
  std::pair<std::string, std::map<std::string, Value *> > pair;

  it = config_files.find(index);
  if (it == config_files.end())
    return (false);
  pair = *it;
  it2 = pair.second.find(key);
  if (it2 == pair.second.end())
      return (false);
  return (true);
}

bool ConfigLoader::fileExists(const std::string &name)
{
  std::fstream file;

  file.open(name.c_str());
  return (file.is_open());
}

bool ConfigLoader::keyExist(const std::string &str)
{
  std::map<std::string, std::map<std::string, Value *> >::const_iterator it;

  it = config_files.find(str);
  if (it == config_files.end())
    return (false);
  return (true);

}

void ConfigLoader::clear()
{
  std::map<std::string, std::map<std::string, Value *> >::const_iterator it;
  std::map<std::string, Value *>::const_iterator it2;
  std::pair<std::string, std::map<std::string, Value *> > pair;
  std::pair<std::string, Value *> pair2;

  it = config_files.begin();
  while (it != config_files.end())
    {
      pair = *it;
      it2 = pair.second.begin();
      while (it2 != pair.second.end())
	{
	  pair2 = *it2;
	  delete pair2.second;
	  ++it2;
	}
      ++it;
    }
}
