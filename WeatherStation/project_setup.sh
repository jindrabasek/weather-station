#!/bin/sh

path_to_eclipse=
libraries_folder=
arduino_core_version=

help() {
  echo "Usage:"
  echo " ./project_setup.sh -l <absolute path to Arduino IDE libraries folder> -e <absolutepath Eclipse installation with Arduino plugin version 3> -v <Arduino core version>"
  echo
  echo "Example:"
  echo " ./project_setup.sh -l /home/johndoe/Arduino/libraries -e /home/johndoe/eclipse/eclipseArduino -v 1.6.17"
  echo
  echo " ./project_setup.sh -h --- this help"

  exit 1
}

while getopts 'l:e:v:h' opt
do
  case "$opt" in
    l)
      libraries_folder=$OPTARG
      ;;
    e)
      path_to_eclipse=$OPTARG
      ;;
    v)
      arduino_core_version=$OPTARG
      ;;
    h)
      help
      ;;
    \?)
      echo "Invalid option '-$OPTARG'"
      help
      ;;
    :)
      echo "Option '-$OPTARG' requires an argument"
      help
      ;;
  esac
done

if [ -z "$path_to_eclipse" ] || [ -z "$libraries_folder" ] || [ -z "$arduino_core_version" ] ; then
  help
fi

sed "s#%ABSOLUTE_PATH_TO_ARDUINO_IDE_LIBRARIES_FOLDER%#$libraries_folder#g; s#%ABSOLUTE_PATH_TO_ECLIPSE_INSTALLATION_WITH_ARDUINO_PLUGIN%#$path_to_eclipse#g" .project.template > .project
cp .settings/org.eclipse.cdt.core.prefs.template .settings/org.eclipse.cdt.core.prefs

# patch arduino core
patch_file="$(pwd)/../ArduinoCorePatches/file.patch"
cd "$path_to_eclipse/arduinoPlugin/packages/arduino/hardware/avr/$arduino_core_version/cores/arduino"
patch -s -p0 < "$patch_file"