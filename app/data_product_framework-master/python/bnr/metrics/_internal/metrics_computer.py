"""Doer module that contains MetricsComputer

Classes:
MetricsComputer -- Computes various useful metrics to assess object detection performance
"""

from collections import defaultdict

from bnr.datastructs.datastructs import ScoredRect
from bnr.metrics._internal.exceptions import VERIFICATION

class MetricsComputer(object):
    """Computes metrics to assess performance of object detection using ground truths"""

    _OVERLAP_RATIO_THRESHOLD = 0.4

    def run(self, detections, ground_truths):
        """Generates all metrics based on an image's detection results and ground truths

        Arguments:
        detections -- List of ScoredRects that represent object detections
        ground_truths -- List of ScoredRects that represent the ground truth objects

        Returns: The following dict:
        {"num_recall":(int) Number of ground truth objects successfully detected,
         "uniq_recall":(int) Number of unique ground truth objects successfully detected,
         "max_recall":(int) Total number of ground truth objects,
         "num_precision":(int) Number of detections that are true positives,
         "uniq_precision":(int) Number of unique detections that are true positives,
         "max_precision":(int) Total number of detections,
        }
        """
        VERIFICATION.verify_list_type(detections, ScoredRect, "detections")
        VERIFICATION.verify_list_type(ground_truths, ScoredRect, "ground_truths")

        (num_recall, uniq_recall) = self._compute_hit_metrics(ground_truths, detections)
        (num_prec, uniq_prec) = self._compute_hit_metrics(detections, ground_truths)

        metrics = {"num_recall":num_recall,
                   "uniq_recall":uniq_recall,
                   "max_recall":len(ground_truths),
                   "num_precision":num_prec,
                   "uniq_precision":uniq_prec,
                   "max_precision":len(detections),
                  }
        return metrics

    def _compute_hit_metrics(self, targets, probes):
        # Compute metrics to evaluate how well the probes hit the targets
        if not targets or not probes:
            return (0, 0)

        hit_map = self._build_hit_map(targets, probes)

        num_hits = sum(hit_map.values())
        uniq_hits = len(hit_map)
        return (num_hits, uniq_hits)

    def _build_hit_map(self, targets, probes):
        # Which probes hit some target?  How many targets does each probe hit?
        hit_map = defaultdict(int)
        for target in targets:
            closest_probe = max(probes, key=lambda x, y=target: x.rect.overlap_ratio(y.rect))
            if closest_probe.rect.overlap_ratio(target.rect) >= self._OVERLAP_RATIO_THRESHOLD:
                hit_map[closest_probe] += 1

        return hit_map
