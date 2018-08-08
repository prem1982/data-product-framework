"""Simple unit test bootstrapper"""

import sys
import unittest

sys.path.append("./python/")

# pylint: disable=wrong-import-position
from bnr.metrics.test.metrics_computer import MetricsComputerSanityTest, MetricsComputerAutomatedTest
from bnr.metrics.test.confidence_scorer import ConfidenceScorerTest

def build_test_suite(test_cases):
    """Packages individual test cases into a single suite"""
    test_suite = unittest.TestSuite()
    for test_case in test_cases:
        test_suite.addTest(unittest.TestLoader().loadTestsFromTestCase(test_case))

    return test_suite

def main():
    """Runs all tests defined in this package"""
    test_cases = [MetricsComputerSanityTest,
                  MetricsComputerAutomatedTest,
                  ConfidenceScorerTest,
                 ]
    test_suite = build_test_suite(test_cases)
    test_results = unittest.TextTestRunner(verbosity=2).run(test_suite)

    if test_results.failures or test_results.errors:
        sys.exit(-1)

if __name__ == "__main__":
    main()
