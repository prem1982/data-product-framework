"""Doer module that contains DetectionDeduplicator

Classes:
DetectionDeduplicator -- Ensures there are no duplicate detections in an image
"""

from bnr.object_detection._internal.exceptions import VERIFICATION
from bnr.datastructs.datastructs import ScoredRect

class DetectionDeduplicator(object):
    """Replaces multiple detections in an image with one representative detection"""

    _OVERLAP_THRESHOLD = 0.9
    _COVER_THRESHOLD = 0.95

    def run(self, input_detections):
        """Algorithm that replaces multiple detections of an object with one representative detection

        Arguments:
        input_detections -- List of ScoredRects to deduplicate

        Returns:
        List of ScoredRects of the deduplicated detections.  Not guaranteed to be a subset of the
        input list.
        """
        VERIFICATION.verify_list_type(input_detections, ScoredRect, "input_detections")

        sorted_dets = sorted(input_detections, key=lambda det: det.rect.area(), reverse=True)
        deduped_dets = []
        for curr_det in sorted_dets:
            if not self._is_duplicate(curr_det, deduped_dets):
                deduped_dets.append(curr_det)

        return deduped_dets

    @classmethod
    def _is_duplicate(cls, candidate_det, target_dets):
        # Helper function that checks if a candidate ScoredBox is a duplicate
        for deduped_det in target_dets:
            overlap_ratio = candidate_det.rect.overlap_ratio(deduped_det.rect)
            cover_ratio = candidate_det.rect.cover_ratio(deduped_det.rect)

            if overlap_ratio >= cls._OVERLAP_THRESHOLD or cover_ratio >= cls._COVER_THRESHOLD:
                return True
        return False
