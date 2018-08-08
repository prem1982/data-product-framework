"""Exceptions specific to this project

Classes:
DatastructsFormatError -- Indicates improper object format
DatastructsValueError -- Indicates improper object value
"""

from bnr.utils.generic_verification import GenericVerification

class DatastructsFormatError(Exception):
    """Raised when the user passes in an object that does not conform to a prescribed format"""
    pass

class DatastructsValueError(Exception):
    """Raised when the user passes in object(s) whose values don't make sense"""
    pass

class Verification(GenericVerification):
    """Verification wrapper for this library"""

    def __init__(self):
        GenericVerification.__init__(self)
        self.format_exception = DatastructsFormatError
        self.value_exception = DatastructsValueError

VERIFICATION = Verification()
