"""Exceptions specific to this project

Classes:
ObjectDetectionFormatError -- Indicates improper object format
ObjectDetectionValueError -- Indicates improper object value
"""

from bnr.utils.generic_verification import GenericVerification

class ObjectDetectionFormatError(Exception):
    """Raised when the user passes in an object that does not conform to a prescribed format

    Example:
    Invoking Rect.intersection(other) when other is an int
    Invoking ImageChuner.get_chunked_images(image) when image is 2 channels
    """
    pass

class ObjectDetectionValueError(Exception):
    """Raised when the user passes in object(s) whose values don't make sense

    Example:
    Invoking Rect(row_start=1, row_end=0, col_start=0, col_end=1)
    """
    pass

class Verification(GenericVerification):
    """Verification wrapper for this library"""

    def __init__(self):
        GenericVerification.__init__(self)
        self.format_exception = ObjectDetectionFormatError
        self.value_exception = ObjectDetectionValueError

VERIFICATION = Verification()
