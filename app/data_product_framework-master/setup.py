"""Script to build a deliverable wheel file for this library"""
import os
import shutil

from setuptools import setup, find_packages
from git import Repo
from semantic_version import Version as SemanticVersion

SETUP_REQUIREMENTS_PATH = "./requirements/setup.txt"
INSTALL_REQUIREMENTS_PATH = "./requirements/deploy.txt"

def _get_file_lines(path):
    # Gets a list of lines from a file
    with open(path) as handle:
        lines = handle.read().splitlines()
    return lines

def _generate_version(tags):
    # Generates wheel version from list of git tags
    if tags is None or not tags:
        version = "0.0.1"
    else:
        version = max([SemanticVersion(tag.name) for tag in tags])
    return str(version)

def _run_setup():
    # Builds a wheel for data_product_framework
    repo = Repo(os.getcwd())

    # The inflexibility of BN's publishWheel and setuptool's setup functions
    # force us to manually change directories, build locally, and move 'dist' out
    os.chdir("python")
    setup(name="data_product_framework",
          version=_generate_version(repo.tags),
          packages=find_packages(exclude=["clients*", "*.test*"]),
          setup_requires=_get_file_lines(SETUP_REQUIREMENTS_PATH),
          install_requires=_get_file_lines(INSTALL_REQUIREMENTS_PATH),
          description="Bossa Nova: Data Product Framework",
          author="Karanhaar Singh",
          author_email="karanhaar.singh@bossanova.com",
          url="https://github.com/karanhaarsingh",
         )
    shutil.rmtree("data_product_framework.egg-info")
    shutil.rmtree("build")
    shutil.move("dist", "..")
    os.chdir("..")

if __name__ == "__main__":
    _run_setup()
