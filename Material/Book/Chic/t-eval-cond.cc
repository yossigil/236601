/*
 * cond evaluation: normal evaluation + lazy evaluation
 * (default in Lisp: eager evaluation, which can be prevented by quote ')
 *
 * Example of test case:
 *
 * a-list before:
 * --------------
 * our a-list:  t -> nil
 *              |     |
 *              t     nil
 *
 * Evaluate cond:
 * --------------
 * (cond
 *     ((null (set 'a 'x))  'a)
 *     ((atom (set 'b 'y))  'b)
 *     ((null (set 'c 'z))  'c)
 * )
 *
 *
 * a-list After: (expected)
 * -------------
 * our a-list:  b -> a -> t -> nil
 *              |    |    |     |
 *              y    x    t    nil
 *
 * (without "c")
 *
 */

#import  <string.h>
#import  <gtest/gtest.h>
#import  "eval.h"
#import  "test.h"
#import  "a-list.h"

namespace Engine { namespace Inner { S evaluate_cond(S); }}

using Engine::lookup, Engine::alist;
using Engine::Inner::evaluate_cond;

static S x("x");

// ----------------------------
// Test:
TEST(CondEvaluationOrder, CondEvaluationOrder) {
    // unique variables names:
    int total_variables = 6;
    std::string unique_names[total_variables];
    for (int i=0; i < total_variables; i++) {
        unique_names[i] = "v_" + std::to_string(i);
    }

    // Test:
    int var_idx = 0;

    // Define S names:
    S v_0(unique_names[var_idx++].c_str());
    S v_1(unique_names[var_idx++].c_str());
    S v_2(unique_names[var_idx++].c_str());
    S v_3(unique_names[var_idx++].c_str());
    S v_4(unique_names[var_idx++].c_str());
    S v_5(unique_names[var_idx++].c_str());

    // Define our cond:
    S s = list(
            list(
                    list(NULL, list(SET, v_0.q(), x.q())),
                    x.q()
            ),
            list(
                    list(NULL, list(SET, v_1.q(), x.q())),
                    x.q()
            ),
            list(
                    list(ATOM, list(SET, v_2.q(), x.q())),
                    x.q()
            ),
            list(
                    list(NULL, list(SET, v_3.q(), x.q())),
                    x.q()
            ),
            list(
                    list(ATOM, list(SET, v_4.q(), x.q())),
                    x.q()
            ),
            list(
                    list(NULL, list(SET, v_5.q(), x.q())),
                    x.q()
            )
    );

    // Evaluate cond on the list:
    evaluate_cond(s);

    // Check if v0, v1, v2 are defined:
    EXPECT_EQ(lookup(v_0), x);
    EXPECT_EQ(lookup(v_1), x);
    EXPECT_EQ(lookup(v_2), x);

    // Check if v3, v4, v5 are NOT defined:
    EXPECT_EXCEPTION(lookup(v_3, alist), v_3, UNDEFINED_ATOM);
    EXPECT_EXCEPTION(lookup(v_4, alist), v_4, UNDEFINED_ATOM);
    EXPECT_EXCEPTION(lookup(v_5, alist), v_5, UNDEFINED_ATOM);
}
