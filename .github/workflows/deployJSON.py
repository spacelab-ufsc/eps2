#
# deployJSON.py
#
# Copyright (C) 2021, SpaceLab.
#
# This file is part of EPS 2.0.
#
# EPS 2.0 is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# EPS 2.0 is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with EPS 2.0. If not, see <http://www.gnu.org/licenses/>.
#
#


import sys
import os
import json

if len(sys.argv) <= 2:
    print("\nWrong arguments")
    print("Use: python3 test-deployer --source <target directory>\n")

    sys.exit(1)
else:
    if sys.argv[1] == '--source':
        # Directory path and list
        path = sys.argv[2]
        if path.startswith('/'):
            path = '.' + path
        elif not path.startswith('./'):
            path = './' + path
        file_dir = os.listdir(path)

    files = {
        "include": []
    }

    # Naming convention:
    #   - test files should end with '_test.c';
    #   - and executables should be named '<target>_unit_test
    #   - makefile commands should be 'make <target>' for each test file
    #
    # This script should work for all folders that follow these guidelines
    # otherwise this script will have to be edited to function properly

    for file in file_dir:
        if file.endswith('_test.c'):
            file_name = file.replace('.c', '')
            test_file = file_name.replace('_test', '_unit_test')
            file_path = path + test_file

            file_info = {
                "name": file_name,
                "test_name": test_file,
                "path": file_path
            }

            files['include'].append(file_info)

    # Convert the dictionary to JSON format
    json_target = json.dumps(files)

    with open(".github/workflows/test-list.json", "w") as json_file:
        json_file.write(json_target)
    json_file.close()

    print("JSON created successfully for folder " + sys.argv[2])
