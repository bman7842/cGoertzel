echo "Building Goertzel.exe ...."
if [ ! -d dist ]; then
	mkdir dist
fi
gcc src/Goertzel.c -o dist/Goertzel
echo "Build complete!"