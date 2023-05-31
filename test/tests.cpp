
#include <iostream>

#include "controller/PetControllerTest.hpp"
#include "controller/UserControllerTest.hpp"
#include "dto/ApiResponseDTOTest.hpp"
#include "dto/CategoryDTOTest.hpp"
#include "dto/OrderDTOTest.hpp"
#include "dto/PetDTOTest.hpp"
#include "dto/TagDTOTest.hpp"
#include "dto/UserDTOTest.hpp"

void runTests()
{
  OATPP_RUN_TEST(UserDTOTest);
  OATPP_RUN_TEST(CategoryDTOTest);
  OATPP_RUN_TEST(OrderDTOTest);
  OATPP_RUN_TEST(PetDTOTest);
  OATPP_RUN_TEST(TagDTOTest);
  OATPP_RUN_TEST(ApiResponseDTOTest);
  OATPP_RUN_TEST(PetControllerTest);
  OATPP_RUN_TEST(UserControllerTest);
}

int main()
{
  oatpp::base::Environment::init();

  runTests();

  /* Print how much objects were created during app running, and what have left-probably leaked */
  /* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag
   * for better performance */
  std::cout << "\nEnvironment:\n";
  std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
  std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";

  OATPP_ASSERT(oatpp::base::Environment::getObjectsCount() == 0);

  oatpp::base::Environment::destroy();

  return 0;
}
