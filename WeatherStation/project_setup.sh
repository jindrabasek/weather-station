#!/bin/sh

path_to_eclipse=
libraries_folder=

help() {
  echo "Usage:"
  echo " ./project_setup.sh -l <absolute path to Arduino IDE libraries folder> -e <absolutepath Eclipse installation with Arduino plugin version 3>"
  echo
  echo "Example:"
  echo " ./project_setup.sh -l /home/johndoe/Arduino/libraries -e /home/johndoe/eclipse/eclipseArduino"
  echo
  echo " ./project_setup.sh -h --- this help"

  exit 1
}

while getopts 'l:e:h' opt
do
  case "$opt" in
    l)
      libraries_folder=$OPTARG
      ;;
    e)
      path_to_eclipse=$OPTARG
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

if [ -z "$path_to_eclipse" ] || [ -z "$libraries_folder" ] ; then
  help
fi

sed "s#%ABSOLUTE_PATH_TO_ARDUINO_IDE_LIBRARIES_FOLDER%#$libraries_folder#g; s#%ABSOLUTE_PATH_TO_ECLIPSE_INSTALLATION_WITH_ARDUINO_PLUGIN%#$path_to_eclipse#g" .project.template > .project
sed "s#%ABSOLUTE_PATH_TO_ECLIPSE_INSTALLATION_WITH_ARDUINO_PLUGIN%#$path_to_eclipse#g" .settings/org.eclipse.cdt.core.prefs.template > .settings/org.eclipse.cdt.core.prefs
