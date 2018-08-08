"""Doer module that contains ConfidenceScorer

Classes:
ConfidenceScorer -- Computes confidence score from metrics
"""

from bnr.metrics._internal.exceptions import VERIFICATION

class ConfidenceScorer(object):
    """Uses metrics from detection results to generate a single score of detection confidence"""

    _RECALL_BIAS = 3.0

    def run(self, **kwargs):
        """Generates confidence score based on a given dict of metrics

        Arguments:
        kwargs -- dict containing at least the following metrics:
                   {"uniq_recall":(int >= 0) Number of unique ground truth objects successfully detected,
                    "max_recall":(int >= 0) Total number of ground truth objects,
                    "uniq_precision":(int >= 0) Number of unique detections that are true positives,
                    "max_precision":(int >= 0) Total number of detections,
                   }

        Returns:
        Confidence score in range [0.0, 1.0] where a larger score is better
        """
        # Validation
        necessary_keys = {"uniq_recall", "max_recall", "uniq_precision", "max_precision"}
        VERIFICATION.verify_dict_keys(kwargs, necessary_keys, "metrics")
        VERIFICATION.verify_list_type(kwargs.values(), int, "metrics")
        for (key, val) in kwargs.items():
            VERIFICATION.verify_value(val >= 0, "{0} must be >= 0".format(key))

        # Compute uniq recall and precision ratios
        recall_ratio = ConfidenceScorer._safe_ratio(kwargs["uniq_recall"], kwargs["max_recall"])
        prec_ratio = ConfidenceScorer._safe_ratio(kwargs["uniq_precision"], kwargs["max_precision"])

        # Weighted geometric mean of the two ratios
        confidence_base = (recall_ratio**self._RECALL_BIAS)*(prec_ratio**1.0)
        confidence_power = 1.0/(self._RECALL_BIAS + 1.0)
        confidence = confidence_base**confidence_power

        return confidence

    @staticmethod
    def _safe_ratio(numerator, denominator):
        # Gracefully handles the case when denominator is zero
        if denominator == 0:
            return 1.0
        return float(numerator)/float(denominator)
