#!/usr/bin/env python3
#
# Do not edit this file, it was auto generated
#

import os
import platform
import shutil
import sys
from setuptools import setup

if "install" in sys.argv[1:]:
  is_windows = platform.system() == "Windows"

  if os.path.isdir("build"):
    try:
      shutil.rmtree("build")
    except PermissionError:
      if is_windows:
        print(
            "Could not remove previous installation build folder, rerun same"
            " command as an admin"
        )
      else:
        print(
            "Could not remove previous installation build folder, rerun same"
            " command with sudo"
        )
      exit()

  if is_windows:
    print("""\
Do not run this script with the following command:

    python setup.py install

instead use the following command:

    python -m pip install .
""")
  else:
    print("""\
Do not run this script with the following command:

    sudo python3 setup.py install

instead use the following command:

    python3 -m pip install .
""")
  exit()

plugin_path = os.path.join("skydelsdx", "plugins")
packages = ["skydelsdx"]

if os.path.exists(plugin_path):
  orgs = os.listdir(plugin_path)

  for org in orgs:
    org_path = os.path.join(plugin_path, org)
    plugins = os.listdir(org_path)

    for plugin in plugins:
      packages.append("skydelsdx.plugins." + org + "." + plugin)

setup(
    name="Skydel SDX",
    version="47+google1",
    packages=packages,
    license="Commercial License",
    long_description="Skydel package for remote commands.",
)
