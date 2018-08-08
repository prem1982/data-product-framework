"""Contains all unit tests for the ConfidenceScorer"""

import unittest

from bnr.metrics._internal.exceptions import MetricsFormatError, MetricsValueError
from bnr.metrics._internal.confidence_scorer import ConfidenceScorer

class ConfidenceScorerTest(unittest.TestCase):
    """Sanity unit test cases for the ConfidenceScorer"""
    def setUp(self):
        self.valid_input = {"uniq_recall":0,
                            "max_recall":0,
                            "uniq_precision":0,
                            "max_precision":0,
                           }
        self.invalid_keys = {"num_recall":0,
                             "max_recall":0,
                             "num_precision":0,
                             "max_precision":0,
                            }
        self.invalid_types = {"uniq_recall":0,
                              "max_recall":0.0,
                              "uniq_precision":0,
                              "max_precision":0.0,
                             }
        self.invalid_vals = {"uniq_recall":-1,
                             "max_recall":0,
                             "uniq_precision":0,
                             "max_precision":0,
                            }

    def test_input_format(self):
        """Validate input format"""
        try:
            ConfidenceScorer().run(**self.valid_input)
        except MetricsFormatError:
            self.fail("ConfidenceScorer raised MetricsFormatError on valid input")

        self.assertRaises(MetricsFormatError, ConfidenceScorer().run, **self.invalid_keys)
        self.assertRaises(MetricsFormatError, ConfidenceScorer().run, **self.invalid_types)
        self.assertRaises(MetricsValueError, ConfidenceScorer().run, **self.invalid_vals)

    def test_worst_score(self):
        """Worst possible score (0.0)"""
        scorer = ConfidenceScorer()
        self.assertAlmostEqual(0.0, scorer.run(**ConfidenceScorerTest._build_metrics(0, 10, 0, 20)))
        self.assertAlmostEqual(0.0, scorer.run(**ConfidenceScorerTest._build_metrics(0, 0, 0, 20)))
        self.assertAlmostEqual(0.0, scorer.run(**ConfidenceScorerTest._build_metrics(0, 10, 0, 0)))

    def test_best_score(self):
        """Best possible score (1.0)"""
        scorer = ConfidenceScorer()
        self.assertAlmostEqual(1.0, scorer.run(**ConfidenceScorerTest._build_metrics(10, 10, 20, 20)))
        self.assertAlmostEqual(1.0, scorer.run(**ConfidenceScorerTest._build_metrics(0, 0, 0, 0)))

    def test_middle_scores(self):
        """Middle score (0.5)"""
        scorer = ConfidenceScorer()
        self.assertAlmostEqual(0.5, scorer.run(**ConfidenceScorerTest._build_metrics(5, 10, 5, 10)))
        self.assertAlmostEqual(0.5, scorer.run(**ConfidenceScorerTest._build_metrics(10, 20, 10, 20)))

    @staticmethod
    def _build_metrics(actual_recall, max_recall, actual_prec, max_prec):
        # Builds a dictionary of metrics assuming num hits == uniq hits
        metrics = {"num_recall":actual_recall,
                   "uniq_recall":actual_recall,
                   "max_recall":max_recall,
                   "num_precision":actual_prec,
                   "uniq_precision":actual_prec,
                   "max_precision":max_prec,
                  }
        return metrics
