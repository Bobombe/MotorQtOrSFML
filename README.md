# MotorQtOrSFML
The goal of this motor is to have a similar behavior using whether Qt or SFML

# To create new project
Copy TU folder and change name to projectName
Go to this new projectName folder
delete the .user file
Rename TU-SFML.pro to projectName.pro
Open projectName.pro in Qt creator
Configure the project with your favorite kit
In Project tab => Build => debug => Add Build Step "make install"
In Project tab => Build => release => Add Build Step "make install"
In Project tab => Build => release => Add Build Step "make clean"