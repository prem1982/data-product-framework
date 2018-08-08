"""Contains GenericVerification, a class to aid in error checking"""

import numpy as np

class GenericVerification(object):
    """Contains various methods to check the format and value of various objects"""

    def __init__(self):
        """Default format and value exceptions"""
        self.format_exception = None
        self.value_exception = None

    def verify_value(self, condition, message):
        """Check a certain value by validating a condition"""
        GenericVerification._verify(condition, self.value_exception, message)

    def verify_type(self, input_type, expected_type, message):
        """Check an object's type"""
        type_is_correct = isinstance(input_type, expected_type)
        GenericVerification._verify(type_is_correct, self.format_exception, message)

    def verify_list_type(self, input_list, expected_type, name):
        """Check a list's type composition"""
        self.verify_type(input_list, list, "{0} must be a list".format(name))

        expected_name = expected_type.__name__
        for value in input_list:
            self.verify_type(value, expected_type,
                             "All elements of {0} should be {1}".format(name, expected_name))

    def verify_dict_keys(self, input_dict, necessary_keys, name):
        """Check that a dict contains the necessary keys"""
        self.verify_type(input_dict, dict, "{0} must be a dict".format(name))

        keys = input_dict.keys()
        for necessary_key in necessary_keys:
            GenericVerification._verify(necessary_key in keys, self.format_exception,
                                        "Expected key: {0}".format(necessary_key))

    def verify_image(self, image, expected_resolution=None):
        """Checks format of input image"""
        self.verify_type(image, np.ndarray, "Image must be numpy.ndarray")
        GenericVerification._verify(image.dtype == np.uint8, self.format_exception,
                                    "Image must consist of numpy.uint8 values")
        GenericVerification._verify(len(image.shape) == 3, self.format_exception,
                                    "Image must have 3 dimensions")
        GenericVerification._verify(image.shape[2] == 3, self.format_exception,
                                    "Image must have 3 channels")
        if expected_resolution is not None:
            GenericVerification._verify(image.shape[:2] == expected_resolution, self.format_exception,
                                        "Image is not of expected shape")

    def verify_dims(self, input_dims, expected_num_dims, name):
        """Verifies format of input dims"""
        self.verify_type(input_dims, tuple, "{0} must be a tuple".format(name))
        GenericVerification._verify(len(input_dims) == expected_num_dims, self.format_exception,
                                    "{0} must have {1} elements".format(name, expected_num_dims))
        for dim in input_dims:
            self.verify_type(dim, int, "{0}'s elements all must be int".format(name))
            self.verify_value(dim > 0, "{0}'s elements all must be > 0".format(name))

    @staticmethod
    def _verify(condition, exception, message):
        # Verifies a condition
        if not condition:
            raise exception(message)
