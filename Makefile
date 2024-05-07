build:
	ninja -C build

run: build

clear:
	rm -rf build/*
	rm -rf build/.*
