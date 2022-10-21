import glob
import shutil
import sys
import os

# compile cpython if not was compiled
files = glob.glob("../cpython/PCbuild/amd64/*.dll")

if not files:
    os.system('"../cpython/PCbuild/get_externals.bat"')
    os.system('"../cpython/PCbuild/build.bat"')

# copy dlls
files = glob.glob("../cpython/PCbuild/amd64/*.dll")

for f in files:
    shutil.copy(f, sys.argv[1] + "/" + os.path.basename(f))

print(sys.argv)