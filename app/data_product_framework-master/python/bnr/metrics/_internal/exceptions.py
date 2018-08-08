"""Exceptions specific to this project

Classes:
MetricsFormatError -- Indicates improper object format
MetricsValueError -- Indicates improper object value
Verification -- Library wrapper around GenericVerification
"""

from bnr.utils.generic_verification import GenericVerification

class MetricsFormatError(Exception):
    """Raised when the user passes in an object that does not conform to a prescribed format"""
    pass

class MetricsValueError(Exception):
    """Raised when the user passes in object(s) whose values don't make sense"""
    pass

class Verification(GenericVerification):
    """Verification wrapper for this library"""

    def __init__(self):
        GenericVerification.__init__(self)
        self.format_exception = MetricsFormatError
        self.value_exception = MetricsValueError

VERIFICATION = Verification()
