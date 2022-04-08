#include <stdlib.h>

#include "../libraries/munit/munit.h"

// -----------------------------------------------------------------------------
// Define a set of tests
// -----------------------------------------------------------------------------
static MunitResult
test_compare(const MunitParameter params[], void* data) {
    munit_assert(0 != 1);
    munit_assert(0 != 1);
    munit_assert(0 != 1);
}


// -----------------------------------------------------------------------------
// Run the Munit tests
// -----------------------------------------------------------------------------

static MunitTest test_suite_tests[] = {
  { (char*) "/SIVM/fetch8", test_compare, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/SIVM/fetch8", test_compare, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/SIVM/fetch8", test_compare, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
  (char*) "",
  test_suite_tests,
  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  /* Finally, we'll actually run our test suite!  That second argument
   * is the user_data parameter which will be passed either to the
   * test or (if provided) the fixture setup function. */
  return munit_suite_main(&test_suite, (void*) "µnit", argc, argv);
}