#include <zephyr/ztest.h>

ZTEST_SUITE(dummy_suite, NULL, NULL, NULL, NULL, NULL);

ZTEST(dummy_suite, test_pass)
{
    zassert_true(true, "This should always pass");
}
