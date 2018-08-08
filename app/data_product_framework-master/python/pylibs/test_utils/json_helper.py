"""Helper functions to build various test jsons"""

import json as json_handle

def build_size_json(height, width):
    """Builds Size json element"""
    json = dict()
    json["height"] = height
    json["width"] = width
    return json

def build_rect_json(x_coord, y_coord, width, height):
    """Builds Rect json element"""
    json = dict()
    json["x"] = x_coord
    json["y"] = y_coord
    json["width"] = width
    json["height"] = height
    return json

def save_json(output_path, json):
    """Saves json to disk"""
    with open(output_path, "w") as output_path_handle:
        json_handle.dump(json, output_path_handle, indent=4)
