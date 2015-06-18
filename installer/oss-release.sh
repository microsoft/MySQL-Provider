#!/bin/bash

OMI_SOURCE=omi-1.0.8-1.tar.gz

echo
echo "This file creates an open source release kit for MySQL. To use this script,"
echo "you will need $OMI_SOURCE from the Open Group. That file will not be"
echo "part of the release (the cusotmer will download it), but will be used to"
echo "verify that the kit builds properly. This file should be placed in the base"
echo "directory of the open source build directory for MySQL."
echo

# Get and verify target directory

while ( true ); do
    read -e -p "What directory would you like to use for oss-mysql release? "
    eval TARGET_DIR=$REPLY

    if [ ! -d "$TARGET_DIR" ]; then
	echo "Directory \"$TARGET_DIR\" does not exist" 1>&2
	continue
    fi

    if [ ! -f "$TARGET_DIR/$OMI_SOURCE" ]; then
	echo "File $OMI_SOURCE does not exist in directory $TARGET_DIR" 1>&2
	continue
    fi

    break
done

# Get and verify source directory

while ( true ); do
    read -e -p "What is enlistment location for MySQL sources? "
    eval SOURCE_DIR=$REPLY

    if [ ! -d "$SOURCE_DIR" ]; then
	echo "Directory \"$SOURCE_DIR\" does not exist" 1>&2
	continue
    fi

    if [ ! -f "$SOURCE_DIR/build/Makefile" ]; then
	echo "File \"Makefile\" does not exist in directory $SOURCE_DIR/build" 1>&2
	continue
    fi

    if [ ! -f "$SOURCE_DIR/source/code/providers/MySQL_Server_Class_Provider.cpp" ]; then
	echo "File \"MySQL_Server_Class_Provider.cpp\" does not exist in directory $SOURCE_DIR/source/code/providers" 1>&2
	continue
    fi

    if [ ! -f "$SOURCE_DIR/../omi/Unix/configure" ]; then
	echo "File \"configure\" does not exist in directory $SOURCE_DIR/../omi/Unix" 1>&2
	continue
    fi

    if [ ! -f "$SOURCE_DIR/../pal/build/Makefile.pf.Linux" ]; then
	echo "File \"Makefile.pf.Linux\" does not exist in directory $SOURCE_DIR/../pal/build" 1>&2
	continue
    fi

    break
done

# We have what we need; copy the files and clean up what we don't need

echo "---------- Cleaning source MySQL directory ----------"
(cd $SOURCE_DIR/build; ./configure; make clean distclean)

echo "---------- Creating directory structure ----------"
rm -rf $TARGET_DIR/mysql
mkdir $TARGET_DIR/mysql

echo "---------- Copying source code to target directory ----------"
cp -R $SOURCE_DIR/../* $TARGET_DIR/mysql/

echo "---------- Cleaning unnecessary files from target directory ----------"
chmod -R u+w $TARGET_DIR/mysql

rm -r $TARGET_DIR/mysql/pal/build/TeamBuildTypes
rm -r $TARGET_DIR/mysql/pal/build/Tools
rm -r $TARGET_DIR/mysql/pal/installer

rm -r $TARGET_DIR/mysql/mysql/bootstrap
rm -r $TARGET_DIR/mysql/mysql/build/TeamBuildTypes
rm -r $TARGET_DIR/mysql/mysql/build/Tools
rm $TARGET_DIR/mysql/mysql/installer/conf/installinfo.txt
rm -r $TARGET_DIR/mysql/mysql/installer/bundle
rm -r $TARGET_DIR/mysql/mysql/installer/datafiles
rm $TARGET_DIR/mysql/mysql/installer/oss-release.sh
rm -r $TARGET_DIR/mysql/mysql/test/Automation
rm -r $TARGET_DIR/mysql/mysql/test/Dependency
rm -r $TARGET_DIR/mysql/mysql/test/int
rm -r $TARGET_DIR/mysql/mysql/test/code/ClientLibrary
rm -r $TARGET_DIR/mysql/mysql/test/code/ext
mv $TARGET_DIR/mysql/mysql/installer/oss-README $TARGET_DIR/mysql/README

# Blow away development verson of OMI; customer will download this

rm -r $TARGET_DIR/mysql/omi/*

# Set up new configure file to only build open source

sed -i -e "s/^opensource_distro=0$/opensource_distro=1/" $TARGET_DIR/mysql/mysql/build/configure

# Perform a test build to insure success?

while ( true ); do
    read -e -p "Perform a test build (y/n)? "

    if [ "$REPLY" = "y" ]; then
	# Extract OMI and get it set up
	cd $TARGET_DIR/mysql/omi
	tar xf $TARGET_DIR/$OMI_SOURCE
	mv omi-1.0.8 Unix

	# Now try the build
	cd $TARGET_DIR/mysql/mysql/build
	./configure; make all test

	if [ $? -ne 0 ]; then
	    echo "MySQL provider build failed - aborting" 1>&2
	    exit 1
	fi

	# Clean up from the build
	make clean distclean
	chmod -R u+w $TARGET_DIR/mysql/omi
	rm -r $TARGET_DIR/mysql/omi/*
    else
	if [ "$REPLY" != "n" ]; then
	    continue
	fi
    fi

    break
done

# Build tarball?

while ( true ); do
    read -e -p "Build the distribution .tar file (y/n)? "

    if [ "$REPLY" = "y" ]; then
	cd $TARGET_DIR; tar czf mysql-cimprov.tar.gz mysql
    else
	if [ "$REPLY" != "n" ]; then
	    continue
	fi
    fi

    break
done

exit 0
