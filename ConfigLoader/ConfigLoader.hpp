#ifndef CONFIGLOADER_HPP_
# define CONFIGLOADER_HPP_

# include <iostream>
# include <fstream>
# include <string>
# include <map>
# include <exception>
# include <sstream>

/**
 ** This class is very useful to load and dump configuration files.\n
 ** It acts like a database.
 ** @brief A Configuration Loading and editing class
 */
class ConfigLoader
{
public:

  /**
   ** This class is used to raise ConfigLoader exceptions
   ** @brief An exception class to be risen in the ConfigLoader class
   */
  class Exception : public std::exception
  {
  protected:
    std::string const _error;

  public:
    Exception(std::string const & error) throw() : _error(error) {}
    virtual ~Exception() throw() {}
    virtual char const * what() const throw() { return (this->_error.c_str()); }
  };

  /**
   ** @brief This class is a value container for the ConfigLoader
   */
  class Value
  {
  public:
    /**
     ** This enum reprensents the multiples values that ConfigLoader can handle
     */
    enum e_type
      {
	INT,
	STRING,
	FLOAT
      };

    /**
     ** This constructor takes in parameters a value and his type
     ** @param value
     ** @param type
     */
    Value(const std::string &, Value::e_type);
    ~Value();

  private:
    e_type _type;
    std::string _str;

  public:
    /**
     ** This function returns the Value type
     ** @return Value::e_type type
     */
    e_type getType() const;

    /**
     ** This function sets the Value type
     ** @param type
     */
    void setType(e_type);

    /**
     ** This function return the Value
     ** @return _str
     */
    const std::string &getValue() const;

    /**
     ** This function modify the Value
     ** @param str
     */
    void setValue(const std::string &);
  };

public:
  ConfigLoader();
  ~ConfigLoader();

private:
  static std::map<std::string, std::map<std::string, Value *> > config_files;
  static const std::string types[3];

public:

  /**
   ** This function opens a file and add it in the ConfigLoader.\n
   ** @param str
   ** @param name
   */
  static void parseConfigFile(const std::string &, const std::string &);

  /**
   ** This function parse a line to retrieve it's value and add it in the good key.
   ** @param name
   ** @param str
   */
  static void parseLine(const std::string &, const std::string &);

  /**
   ** This function returns the variable name in the line parsed
   ** @param str
   */
  static std::string retrieveVarName(const std::string &);

  /**
   ** This function returns the variable type in the line parsed
   ** @param str
   */
  static Value::e_type retrieveVarType(const std::string &);

  /**
   ** This function returns the variable type in a string from a Value::e_type
   ** @param type
   */
  static const std::string &findVarType(Value::e_type);

  /**
   ** This function returns the variable type from a string
   ** @param str
   */
  static Value::e_type findVarType(const std::string &);

  /**
   ** This function returns the variable value from a string
   ** @param str
   */
  static std::string retrieveVarValue(const std::string &);

  /**
   ** This function add a value to the correct keys with the correct value
   ** @param name
   ** @param var
   ** @param varType
   ** @param value
   */
  static void appendValues(const std::string &, const std::string &, Value::e_type, const std::string &);

  /**
   ** This function creates a new Key file ready to be filled
   ** @param name
   */
  static void appendFile(const std::string &);

  /**
   ** This function fills the Value variable with the associated variable
   ** @param file
   ** @param var
   ** @param value
   */
  static void getVarValue(const std::string &, const std::string &, int &);

  /**
   ** This function fills the Value variable with the associated variable
   ** @param file
   ** @param var
   ** @param value
   */
  static void getVarValue(const std::string &, const std::string &, float &);

  /**
   ** This function fills the Value variable with the associated variable
   ** @param file
   ** @param var
   ** @param value
   */
  static void getVarValue(const std::string &, const std::string &, std::string &);

  /**
   ** This function replaces the corresponding variable with Value
   ** @param name
   ** @param var
   ** @param value
   */
  static void modifyValue(const std::string &, const std::string &, int);

  /**
   ** This function replaces the corresponding variable with Value
   ** @param name
   ** @param var
   ** @param value
   */
  static void modifyValue(const std::string &, const std::string &, float);

  /**
   ** This function replaces the corresponding variable with Value
   ** @param name
   ** @param var
   ** @param value
   */
  static void modifyValue(const std::string &, const std::string &, const std::string &);

  /**
   ** This function erases the associated variable
   ** @param name
   ** @param var
   */
  static void removeValue(const std::string &, const std::string &);

  /**
   ** This function modifies the corresponding variable type
   ** @param name
   ** @param var
   ** @param type
   */
  static void modifyType(const std::string &, const std::string &, Value::e_type);

  /**
   ** This function dump the Key_File and append it in the file File
   ** @param file
   ** @param name
   */
  static void appendToFile(const std::string &, const std::string &);

  /**
   ** This function dump the Key_File in the file File
   ** @param file
   ** @param name
   */
  static void writeToFile(const std::string &, const std::string &);

  /**
   ** This function displays the contents of all the variables
   */
  static void dump();

  /**
   ** This function returns the existance of the File and Key_file
   ** @param index
   ** @param key
   ** @return bool Exists
   */
  static bool keyExist(const std::string &, const std::string &);

  /**
   ** This function returns the existance of the File
   ** @param str
   ** @return bool Exists
   */
  static bool keyExist(const std::string &);

  /**
   ** This function returns the existance of the File on disk
   ** @param name
   ** @return bool Exists
   */
  static bool fileExists(const std::string &);

  /**
   ** This function empties all the variables
   */
  static void clear();
};

#endif
