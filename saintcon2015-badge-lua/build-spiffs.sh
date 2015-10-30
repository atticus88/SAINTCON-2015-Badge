#!/bin/bash -u

#Script forked from https://gist.github.com/kireevco/dfe1e80fb509d57b0f49

######
PROJECT_NAME='saintcon_nodemcu_spiffs'
FWVERSION='1.0.1-fw'
LUAVERSON='1.0.1-lua'
BUILD_DATE=$(TZ='America/Denver' date +%Y%m%d)



#x00000='eagle.app.flash.bin'
#x10000='eagle.irom0text.bin'
x00000='0x00000.bin'
x10000='0x10000.bin'
PROJECT_DIR="$(pwd)"
BUILD_DIR="$PROJECT_DIR/builddir"
SPIFFS_DIR="$BUILD_DIR/files"
NODEMCU_DIR="$BUILD_DIR/nodemcu-firmware"
"${SEMAPHORE:=false}"
######


# Getting required packages
#sudo apt-get install -y python-serial srecord bc


################################################
# Building FW


mkdir $BUILD_DIR -p
cd $BUILD_DIR
#Clone latest NodeMCU with SaintCon modifications.
git clone --depth=1 --branch=$FWVERSION -- git@bitbucket.org:jkarras/nodemcu-firmware.git $NODEMCU_DIR || exit 1

cd $NODEMCU_DIR
NODEBUILD_NUMBER=`git log --pretty=format:'%h' -n 1 .`

cd $PROJECT_DIR
BUILD_NUMBER=${REVISION:=`git log --pretty=format:'%h' -n 1`}
#Cut down SHA1 to 7 characters. 
BUILD_NUMBER=${BUILD_NUMBER:0:7}

# Setting env variables to build fw
cd $NODEMCU_DIR
export PATH=$PATH:$NODEMCU_DIR/esp-open-sdk/sdk:$NODEMCU_DIR/esp-open-sdk/xtensa-lx106-elf/bin
export BAUD_RATE=115200

tar -zxvf tools/esp-open-sdk.tar.gz
make clean
make EXTRA_CCFLAGS="-DLUA_NUMBER_INTEGRAL -DBIT_RATE_DEF=BIT_RATE_${BAUD_RATE} -DBUILD_DATE='\"'$BUILD_DATE'\"'" all || exit 1

rm -r $NODEMCU_DIR/esp-open-sdk

################################################
# Joining two bin files (expecting 0x00000.bin and 0x10000.bin)
################################################
cd $NODEMCU_DIR/bin

merged_file_name="${PROJECT_NAME}_merge.bin"
output_file_name="${PROJECT_NAME}_v${FWVERSION}.${BUILD_NUMBER}.${BUILD_DATE}.${BAUD_RATE}.bin"

echo "Joining two firmware bin files"
srec_cat  -output ${merged_file_name} -binary $x00000 -binary -fill 0xff 0x00000 0x10000 $x10000 -binary -offset 0x10000 > srec_cat.log || exit 1
cp "$NODEMCU_DIR/bin/${merged_file_name}" "$PROJECT_DIR/firmware-images/saintcon_nodemcu_v${FWVERSION}.${NODEBUILD_NUMBER}.${BUILD_DATE}.${BAUD_RATE}.bin" || exit 1

main_firmware_offset=0x$(echo "obase=16; $(($(stat --format="%s" $NODEMCU_DIR/bin/${merged_file_name})))" | bc)
spiff_start_offset=0x$(echo "obase=16; $((($(stat --format="%s" $NODEMCU_DIR/bin/${merged_file_name}) + 16384) & (0xFFFFC000))) " | bc)
echo "Main firmware offset: $main_firmware_offset"
echo "Spiff start offset: $spiff_start_offset"
#-redundant-bytes=ignore

################################################
# Writing files to spiffs zone
################################################

# Building spiffy tool
mkdir $SPIFFS_DIR -p
cp $PROJECT_DIR/src/*.lua $SPIFFS_DIR

echo "Cloning spiffsimg tool"
git clone --depth=1 -- https://github.com/DiUS/spiffsimg.git $BUILD_DIR/spiffsimg || exit 1

#echo "Patching spiffy to support Windows"
#wget https://gist.githubusercontent.com/kireevco/0183f3ca9df19ce7f9d7/raw/abc2b65f3e0cf6036f074fa723411e6825baa17d/spiffs.h.patch -O $BUILD_DIR/spiffs.h.patch --no-check-certificate
#wget https://gist.githubusercontent.com/kireevco/0183f3ca9df19ce7f9d7/raw/f3f056c97690ca3df0c1aeef1f6f4f30c8f9de8c/spiffs_hydrogen.c.patch -O $BUILD_DIR/spiffs_hydrogen.c.patch --no-check-certificate
#wget https://gist.githubusercontent.com/kireevco/0183f3ca9df19ce7f9d7/raw/794d161fbececfd6b5ce9966f94708fc3ce0dc1c/spiffs_nucleus.h.patch -O $BUILD_DIR/spiffs_nucleus.h.patch --no-check-certificate
#wget https://gist.githubusercontent.com/kireevco/0183f3ca9df19ce7f9d7/raw/20ed340149922ce18902ccdf37be900d86466eaf/main.c.patch -O $BUILD_DIR/main.c.patch --no-check-certificate
#patch $BUILD_DIR/spiffy/src/spiffs.h < $BUILD_DIR/spiffs.h.patch
#patch $BUILD_DIR/spiffy/src/spiffs_hydrogen.c < $BUILD_DIR/spiffs_hydrogen.c.patch
#patch $BUILD_DIR/spiffy/src/spiffs_nucleus.h < $BUILD_DIR/spiffs_nucleus.h.patch
#patch $BUILD_DIR/spiffy/src/main.c < $BUILD_DIR/main.c.patch

#echo "Patching spiffy to support our larger flash module"
#patch $BUILD_DIR/spiffy/src/main.c < $PROJECT_DIR/spiffy_size.patch

cd $BUILD_DIR/spiffsimg

echo "Building spiffsimg"
make

cd $BUILD_DIR
for f in files/*.lua; do
    echo "Processing $f ..."
    echo "import $f $(basename $f)" >> $BUILD_DIR/import_script.txt;
done

echo "Building spiff bin file"
$BUILD_DIR/spiffsimg/spiffsimg -f $NODEMCU_DIR/bin/${spiff_start_offset}.bin -c 524288 || exit 1
$BUILD_DIR/spiffsimg/spiffsimg -f $NODEMCU_DIR/bin/${spiff_start_offset}.bin -r $BUILD_DIR/import_script.txt || exit 1

#Move spiffs image into nodemcu directory for later processing.
#mv $BUILD_DIR/spiff_rom.bin $NODEMCU_DIR/bin/${spiff_start_offset}.bin

echo "Building final bin file"
srec_cat -output $NODEMCU_DIR/bin/${output_file_name} -binary $NODEMCU_DIR/bin/${merged_file_name} \
  -binary -fill 0xff $main_firmware_offset $spiff_start_offset $NODEMCU_DIR/bin/${spiff_start_offset}.bin \
  -binary -offset $spiff_start_offset >> srec_cat.log

cd $PROJECT_DIR/src/
echo -n '{' > $PROJECT_DIR/src/update.json
for f in *.json; do
      echo "Processing $f ..."
      echo -n '"'$(basename $f)'":"'download'"' >> $PROJECT_DIR/src/update.json
done
for f in *.lua; do
      echo "Processing $f ..."
      echo -n '"'$(basename $f)'":"'download'"' >> $PROJECT_DIR/src/update.json
done
echo -n '}' >> $PROJECT_DIR/src/update.json
mv $PROJECT_DIR/src/update.json $PROJECT_DIR/src/update2.json
sed 's/""/","/g' update2.json > $PROJECT_DIR/src/update.json
rm $PROJECT_DIR/src/update2.json

#Copy firmware out of build dir for final storage.
mv "$NODEMCU_DIR/bin/${output_file_name}" "$PROJECT_DIR/firmware-images/"

if [[ $SEMAPHORE = "true" ]] ; then
    echo "done"
else
    echo "Cleaning build files. 15 second delay... "
    sleep 15

    echo "Cleaning up build directory"
    rm -rf $BUILD_DIR
fi
