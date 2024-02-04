cd ~

sudo rm /usr/lib/x86_64-linux-gnu/libboost_*

cd ~

wget https://boostorg.jfrog.io/artifactory/main/release/1.82.0/source/boost_1_82_0.tar.bz2
tar --bzip2 -xf boost_1_82_0.tar.bz2
cd boost_1_82_0
sudo ./bootstrap.sh
sudo ./b2

sudo cp -r boost /usr/local/include/boost
sudo cp -r stage/lib/libboost_* /usr/lib/x86_64-linux-gnu/