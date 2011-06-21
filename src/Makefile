#Create by Tom(Tom@awaysoft.com)
#2011-06-21 22:22:22
#Copyright 2011(c) awaysoft.com

JsCompressor : cJSON.o FilePreviewColumnDefinition.o FilePreviewStore.o FileUtils.o JsCompressorFrame.o JsCompressor.o
	g++ -o JsCompressor cJSON.o FilePreviewColumnDefinition.o FilePreviewStore.o FileUtils.o JsCompressorFrame.o  JsCompressor.o `pkg-config --libs --cflags gtkmm-2.4`
cJSON.o : cJSON/cJSON.c cJSON/cJSON.h
	g++ -c cJSON/cJSON.c -lm
FilePreviewColumnDefinition.o : FilePreviewColumnDefinition.cpp FilePreviewColumnDefinition.h
	g++ -c FilePreviewColumnDefinition.cpp `pkg-config --libs --cflags gtkmm-2.4`
FilePreviewStore.o : FilePreviewStore.cpp FilePreviewStore.h
	g++ -c FilePreviewStore.cpp `pkg-config --libs --cflags gtkmm-2.4`
FileUtils.o : FileUtils.cpp FileUtils.h
	g++ -c FileUtils.cpp `pkg-config --libs --cflags gtkmm-2.4`
JsCompressorFrame.o : JsCompressorFrame.cpp JsCompressorFrame.h
	g++ -c JsCompressorFrame.cpp `pkg-config --libs --cflags gtkmm-2.4`
JsCompressor.o : JsCompressor.cpp
	g++ -c JsCompressor.cpp `pkg-config --libs --cflags gtkmm-2.4`
clean:
	rm JsCompressor cJSON.o FilePreviewColumnDefinition.o FilePreviewStore.o FileUtils.o JsCompressorFrame.o JsCompressor.o 
