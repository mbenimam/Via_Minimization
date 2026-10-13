/*
 * Assertion test for the crossing algorithms.
 *
 * It checks that the naive method and both sweep methods (sorted list and
 * AVL tree) find the same crossings, and that the counts match the values
 * recorded from earlier runs. Run it from the repository root with `make check`.
 */
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "netlist.h"
#include "detect_intersection.h"
#include "echeancier.h"

static int checks = 0;
static int failures = 0;

#define CHECK(cond, msg)                                                  \
  do {                                                                    \
    checks++;                                                             \
    if (!(cond)) {                                                        \
      failures++;                                                         \
      fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, msg);       \
    }                                                                     \
  } while (0)

/* Each method works on its own fresh copy of the netlist, because the
   algorithms fill the intersection lists of the segments they visit. */
static void check_instance(const char *file, int expected) {
  Netlist *a = read_net_from_file((char *)file);
  Netlist *b = read_net_from_file((char *)file);
  Netlist *c = read_net_from_file((char *)file);
  CHECK(a != NULL && b != NULL && c != NULL, "the netlist file must load");
  if (!a || !b || !c) return;

  int naive = intersect_naif(a);
  int list = intersect_baleyage(b);
  int avl = intersect_baleyage_avl(c);

  CHECK(naive == expected, file);
  CHECK(list == naive, "sorted-list sweep must agree with the naive method");
  CHECK(avl == naive, "AVL sweep must agree with the naive method");
}

int main(void) {
  check_instance("tests/test.net", 2);
  check_instance("tests/alea0100_050_10_097.net", 984);
  check_instance("tests/c1.net", 3385);
  check_instance("tests/alea0300_300_10_044.net", 19839);

  printf("%d checks, %d failed\n", checks, failures);
  return failures ? EXIT_FAILURE : EXIT_SUCCESS;
}
