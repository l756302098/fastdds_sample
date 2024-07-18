# fastdds_sample
fastdds ros2(humble) sample  

## install
编译安装 Fast CDR ，提供了两种序列化机制   
```
git clone https://github.com/eProsima/Fast-CDR.git -b 1.x
mkdir Fast-CDR/build && cd Fast-CDR/build
cmake ..
cmake -DBUILD_SHARED_LIBS=ON \
	-DCMAKE_INSTALL_PREFIX=/home/li/workspaces/Fast-CDR/install \
	..
make
sudo make install
```
安装编译 Fast-DDS  
```
sudo apt install libasio-dev libtinyxml2-dev
sudo apt install libssl-dev
sudo apt install libp11-dev
git clone https://github.com/eProsima/Fast-DDS.git
mkdir Fast-DDS/build && cd Fast-DDS/build
cmake -DLOG_NO_INFO=OFF -DEPROSIMA_BUILD=ON -DTHIRDPARTY=ON ..
make
sudo make install
```
编译代码生成工具 Fast-DDS Gen (需要先装好Java和Gradle)  
```
git clone --recursive https://github.com/eProsima/Fast-DDS-Gen.git -b 3.3.x
cd Fast-DDS-Gen
source /etc/profile.d/gradle.sh
./gradle assemble

export JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64
export PATH=/home/li/workspaces/Fast-DDS-Gen/scripts:$PATH
fastddsgen -replace -typeros2 AddressBook.idl
or
fastddsgen -example CMake -typeros2 AddressBook.idl
```