#include <iostream>
#include <fstream>
#include <string>

// Menu function to get user choice
int getUserChoice()
{
  std::cout << "Enter a number and press Enter" << std::endl;
  std::cout << "1 - plain items" << std::endl;
  std::cout << "2 - helpful items" << std::endl;
  std::cout << "3 - harmful items" << std::endl;
  std::cout << "4 - quit game" << std::endl;
  int choice;
  std::cin >> choice;
  if ((choice > 0) && (choice < 5))
  {
    return choice;
  }
  return -1;
}

// Function ti display the desired items
void displayItem(int x)
{
  std::ifstream object_file("objects.bin", std::ios::in | std::ios::binary);
  if (!object_file.is_open())
  {
    std::cout << "Error opening file" << std::endl;
  }
  std::string name;
  int power;

  switch (x)
  {
    case 1:
      std::cout << "----------------------------------------" << std::endl;
      while (object_file >> name >> power)
      {
        if (power == 0)
        {
          std::cout << name << ' ' << power << std::endl;
        }
      }
      break;
    case 2:
      std::cout << "----------------------------------------" << std::endl;
      while (object_file >> name >> power)
      {
        if (power > 0)
        {
          std::cout << name << ' ' << power << std::endl;
        }
      }
      break;
    case 3:
      std::cout << "----------------------------------------" << std::endl;
      while (object_file >> name >> power)
      {
        if (power < 0)
        {
          std::cout << name << ' ' << power << std::endl;
        }
      }
      break;
    case -1:
      std::cout << "----------------------------------------" << std::endl;
      std::cout << "You need to enter 1, 2, 3 or 4!" << std::endl;
      break;
  }   
  object_file.close();
}

int main()
{
  int user_choice;
  user_choice = getUserChoice();

  while (user_choice != 4)
  {
    displayItem(user_choice);
    std::cout << "----------------------------------------" << std::endl;
    user_choice = getUserChoice();
  }
  std::cout << "Thanks for playing!" << std::endl;

  return 0;
}
