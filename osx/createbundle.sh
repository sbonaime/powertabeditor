#!/bin/bash
set -e # Exit immediately if an error occurs.
set -x # Echo commands.

APP_DIR="powertabeditor.app"
BUILD_DIR=$1

# Set up the directory structure.
rm -rf ${APP_DIR}
mkdir -p ${APP_DIR}/Contents/MacOS/data
mkdir -p ${APP_DIR}/Contents/Resources

# Copy executable and dependencies.
cp ${BUILD_DIR}/bin/powertabeditor ${APP_DIR}/Contents/MacOS
cp ${BUILD_DIR}/bin/data/tunings.json ${APP_DIR}/Contents/MacOS/data
cp Info.plist ${APP_DIR}/Contents
cp powertabeditor.icns ${APP_DIR}/Contents/Resources

# Debugging.
otool -L ${APP_DIR}/Contents/MacOS/powertabeditor
# Deal with dependencies.
macdeployqt --verbose=3 ${APP_DIR}
# Debugging.
otool -L ${APP_DIR}/Contents/MacOS/powertabeditor

# Assemble!
zip -r9uq ${APP_DIR}.zip ${APP_DIR}
