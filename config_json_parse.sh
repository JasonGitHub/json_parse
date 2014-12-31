set -e
# Set following variables to your liking
LIB_VERSION=2.7
INSTALL_DIR=/home/zhowu/json_parse/jansson_lib
# Do not change anything below this line 
LIB_NAME=jansson-$LIB_VERSION
FILE_NAME=$LIB_NAME.tar.gz
DOWNLOAD_LINK=http://www.digip.org/jansson/releases/$FILE_NAME

wget $DOWNLOAD_LINK
tar -xvf ./$FILE_NAME
rm $FILE_NAME
cd ./$LIB_NAME/
./configure --prefix=$INSTALL_DIR
make
make install
make check
cd ..
rm -rf $LIB_NAME
gcc json_parse.c -I $INSTALL_DIR/include -L $INSTALL_DIR/lib -ljansson -o json_parse
