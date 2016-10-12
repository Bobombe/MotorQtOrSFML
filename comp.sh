projectName=${PWD##*/}
config="widgets"
defines="IN_QT=1"


if [ "$1" = "clean" ]
then
	make clean
	rm $projectName.pro $projectName Makefile
else


	echo "Creating $projectName.pro ..."
	/usr/share/isis/qt/bin/qmake -project -r ./src/

	echo "Adding conf to $projectName.pro ..."

	echo "QT += $config"$'\n'"DEFINES += \"$defines\"" > temp_file
	cat $projectName.pro >> temp_file
	mv temp_file $projectName.pro

	echo "Creating Makefile ..."
	/usr/share/isis/qt/bin/qmake $projectName.pro

	echo "Compile ..."
	make
fi
