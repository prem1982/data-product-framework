"""Represents a rectangle with an associated score"""

from bnr.datastructs._internal.exceptions import VERIFICATION
from bnr.datastructs._internal.rect import Rect

class ScoredRect(object):
    """Represents a Rect with an associated score

    Invariants:
    -Same as Rect
    """
    def __init__(self, rect, score):
        """Builds a new ScoredRect directly from the passed in arguments

        Arguments:
        rect -- Rect that represents the ROI for this ScoredRect
        score -- confidence score associated with this ScoredRect
        """
        VERIFICATION.verify_type(rect, Rect, "rect must be Rect")
        VERIFICATION.verify_type(score, float, "score must be float")

        self.rect = rect
        self.score = score

    @classmethod
    def from_dict(cls, input_dict):
        """Factory function that builds a ScoredRect from a dict"""
        expected_keys = set(["rect", "score"])
        VERIFICATION.verify_type(input_dict, dict, "input must be dict")
        VERIFICATION.verify_value(set(input_dict.keys()) == expected_keys,
                                  "expected keys: {0}".format(expected_keys))

        return cls(Rect.from_dict(input_dict["rect"]), input_dict["score"])

    def to_tuple(self):
        """Returns a tuple that represents the ScoredRect

        Returns:
        A tuple in the following form:
        (rect, score)
        """
        return (self.rect.to_tuple(), self.score)

    def to_dict(self):
        """Returns a dict that represents the ScoredRect

        Returns:
        A dict in the following form:
        {"rect": rect
         "score": score}
        """
        return {"rect":self.rect.to_dict(), "score":self.score}

    def shifted(self, offset):
        """Shifts and returns a new ScoredRect

        Arguments:
        offset -- Same as offset arg in Rect.shifted
        """
        new_rect = self.rect.shifted(offset)
        return ScoredRect(new_rect, self.score)

    def __eq__(self, other):
        """Two ScoredRects are equal when their Rects are equal and scores are almost equal"""
        rects_same = self.rect == other.rect
        scores_same = abs(self.score - other.score) <= 1e-06
        return rects_same and scores_same

    def __ne__(self, other):
        """Inverse of equality"""
        return not self.__eq__(other)

    def __repr__(self):
        """Returns a displayable string to represent this ScoredRect"""
        return "(rect={0}, score={1})".format(self.rect, self.score)

    def __hash__(self):
        """Hash based off of the data members"""
        return hash((self.rect, round(self.score, 2)))
