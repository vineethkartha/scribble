#include <string>

/**
 * @brief This class is an Interface for the data structures.
 */
class DataStructureInterface {
  
public:
  /**
   *@brief Constructor
   */
  DataStructureInterface() {}
  virtual ~DataStructureInterface(){}

  /**
   *@brief Factory Method
   */
  static DataStructureInterface * CreateDS(int choice);
  /**
   * @name Insert
   * @brief This functions inserts the given character
   * @param symbol
   */
  virtual void Insert(char symbol) = 0;

  /**
   * @name Delete
   * @brief This function deletes the character at the current position.
   */
  virtual void Delete() = 0;

  /**
   * @name Backspace
   * @brief This function deletes the character previous to the current position.
   */
  virtual void Backspace() = 0;
  
  /**
   * @name MoveCursor
   * @brief This function moves cursor to the mentioned positions
   * @param int pos
   */
  virtual void MoveCursor(int pos) = 0;
  
  /**
   * @name ResizeBuffer
   * @brief When the buffer runs ou of space this function increases the buffer size.
   */
  virtual void ResizeBuffer() = 0;
  
  /**
   * @name getContentOfBuffer
   * @brief This function returns the contents of the buffer.
   * @return std::string
   */
  virtual std::string getContentOfBuffer() const = 0;
};
