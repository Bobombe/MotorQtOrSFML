projectName=${PWD##*/}
config="widgets"
defines="IN_QT=1"


if [ "$1" = "clean" ]
then
	make clean
	rm $projectName.pro $projectName Makefile
else


	echo "Creating $projectName.pro ..."
	#/usr/share/isis/qt/5.5.1/bin/qmake -project -r
	qmake-qt5 -project -r

	echo "Adding conf to $projectName.pro ..."

	echo "QT += $config"$'\n'"DEFINES += \"$defines\"" > temp_file
	cat $projectName.pro >> temp_file
	mv temp_file $projectName.pro

	echo "Creating Makefile ..."
	qmake-qt5 $projectName.pro

	echo "Compile ..."
	make
fi
