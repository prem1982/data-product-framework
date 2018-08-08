"""For different types of data objects"""

import sys
import os

sys.path.append("./python/")

# pylint: disable=wrong-import-position
from pylibs.test_utils.json_helper import build_size_json, build_rect_json, save_json

def _build_valid_simple_json(output_file):
    # Builds and writes valid json
    json = dict()
    json["int_value"] = 1
    json["float_value"] = 0.2
    json["double_value"] = 0.03
    json["string_value"] = "my_string"
    json["size_value"] = build_size_json(4, 5)
    json["rect_value"] = build_rect_json(6, 7, 8, 9)
    json["rect2f_value"] = build_rect_json(2.5, 3.5, 5.5, 6.5)
    save_json(output_file, json)

def _build_invalid_size_json(output_file, height, width):
    # Builds and writes invalid json
    json = build_size_json(height, width)
    save_json(output_file, json)

def main():
    """Builds and writes simple json config files"""
    base_folder = sys.argv[1]
    _build_valid_simple_json(os.path.join(base_folder, "valid_simple.json"))
    _build_invalid_size_json(os.path.join(base_folder, "invalid_size_1.json"), 4.5, 5)
    _build_invalid_size_json(os.path.join(base_folder, "invalid_size_2.json"), 5, 4.5)

if __name__ == "__main__":
    main()
