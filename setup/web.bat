cd src/_ext
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk

git pull
emsdk.bat install latest
emsdk.bat activate latest
